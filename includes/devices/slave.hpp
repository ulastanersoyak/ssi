#ifndef SLAVE_HPP
#define SLAVE_HPP

<<<<<<< HEAD
=======
#include <algorithm>
>>>>>>> master
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
<<<<<<< HEAD
  using typename bus_width_helper<slave_bus_width>::bus_wide_integer;
  bus_wide_integer data{ 0 };

=======
>>>>>>> master
public:
  constexpr void
  read_data () noexcept
  {
    std::random_device rd;
    std::mt19937 gen (rd ());
    std::uniform_int_distribution<> distrib (0, 1);
<<<<<<< HEAD
    for (std::uint8_t idx = 0; idx < slave_bus_width; ++idx)
      {
        this->data = static_cast<bus_wide_integer> (
            (this->data << 1) | static_cast<std::uint8_t> (distrib (gen)));
      }
    std::uniform_int_distribution<> noise (5, 10);
  }

  constexpr void
  visualize_data ()
=======
    for (auto &line : this->data_bus)
      {
        line = static_cast<std::uint8_t> (distrib (gen));
      }
  }

  constexpr void
  print_captured_data ()
>>>>>>> master
  {
#if (__cplusplus == 202302L)
    std::print ("\nslave device:\n");
#else
    std::cout << "\nslave device:\n";
#endif
    for (std::uint8_t idx = 0; idx < slave_bus_width; ++idx)
      {
<<<<<<< HEAD
        bool bit = (this->data & (1U << idx));
#if (__cplusplus == 202302L)
        std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
        std::iostream << "bit" << idx << " := " << bit ? 1 : 0 << ' ';
=======
        bool bit = (this->data_bus[idx]);
#if (__cplusplus == 202302L)
        std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
        std::cout << "bit " << static_cast<int> (idx)
                  << " := " << (bit ? 1 : 0) << ' ';
>>>>>>> master
#endif
      }
  }

  [[nodiscard]] constexpr auto
<<<<<<< HEAD
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
=======
  get_data_bus () const noexcept
  {
    return this->data_bus;
>>>>>>> master
  }

  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
<<<<<<< HEAD
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
=======
    return slave_bus_width;
  }

  [[nodiscard]] constexpr data_package<slave_bus_width>
  send_data_package () noexcept
  {
    const auto hash = crc_hash (this->data_bus);
    std::random_device rd;
    std::mt19937 gen (rd ());
    std::uniform_int_distribution<> noise (0, 2);
    std::uniform_int_distribution<> sign (0, 1);
    std::uniform_int_distribution<> noise_chance (0, 1);
    auto chance = noise_chance (gen);
    std::for_each (this->data_bus.begin (), this->data_bus.end (),
                   [&] (auto &line) {
                     if (chance == 1)
                       {
                         auto noise_ = noise (gen);
                         if (line == 1)
                           {
                             auto sign_ = sign (gen);
                             line = 5;
                             line = sign_ == 0 ? line + noise_ : line - noise_;
                           }
                         else
                           {
                             line += noise_;
                           }
                       }
                   });
    return data_package{ .voltage_bus = this->data_bus, .hash = hash };
>>>>>>> master
  }
};

#endif // !SLAVE_HPP
