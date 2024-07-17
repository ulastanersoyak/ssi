#ifndef SLAVE_HPP
#define SLAVE_HPP

#include <array>
#include <cstdint>
#include <print>
#include <random>

#include "bus.hpp"
#include "devices/crc.hpp"
#include "interfaces/data_package.hpp"

template <std::uint8_t slave_bus_width>
class slave : public bus_width_helper<slave_bus_width>
{
  using typename bus_width_helper<slave_bus_width>::bus_wide_integer;
  bus_wide_integer data{ 0 };

public:
  constexpr void
  read_data () noexcept
  {
    std::random_device rd;
    std::mt19937 gen (rd ());
    std::uniform_int_distribution<> distrib (0, 1);
    for (std::uint8_t idx = 0; idx < slave_bus_width; ++idx)
      {
        this->data = static_cast<bus_wide_integer> (
            (this->data << 1) | static_cast<std::uint8_t> (distrib (gen)));
      }
    std::uniform_int_distribution<> noise (5, 10);
  }

  constexpr void
  visualize_data ()
  {
#if (__cplusplus == 202302L)
    std::print ("\nslave device:\n");
#else
    std::cout << "\nslave device:\n";
#endif
    for (std::uint8_t idx = 0; idx < slave_bus_width; ++idx)
      {
        bool bit = (this->data & (1U << idx));
#if (__cplusplus == 202302L)
        std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
        std::iostream << "bit" << idx << " := " << bit ? 1 : 0 << ' ';
#endif
      }
  }

  [[nodiscard]] constexpr auto
  get_data () const noexcept
  {
    return this->data;
  }

  [[nodiscard]] constexpr std::array<std::uint8_t, slave_bus_width>
  get_data_bits () const noexcept
  {
    std::array<std::uint8_t, slave_bus_width> bits{};
    const std::uint8_t mask = 0x01;
    for (std::uint8_t i = 0; i < slave_bus_width; ++i)
      {
        bits[i] = static_cast<std::uint8_t> ((data & (mask << i)) ? 1 : 0);
      }

    return bits;
  }

  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
    return sizeof (this->data);
  }

  [[nodiscard]] constexpr data_package<bus_wide_integer>
  send_data_package () noexcept
  {
    const auto data_bits = this->get_data_bits ();
    const auto hash = crc_hash<data_bits.size ()> (data_bits);
    std::random_device rd;
    std::mt19937 gen (rd ());
    std::uniform_int_distribution<> noise (5, 10);
    this->data += static_cast<bus_wide_integer> (noise (gen));
    return data_package{ .data = this->data, .hash = hash };
  }
};

#endif // !SLAVE_HPP
