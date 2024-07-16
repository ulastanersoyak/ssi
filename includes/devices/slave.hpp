#ifndef SLAVE_HPP
#define SLAVE_HPP

#include <array>
#include <cstdint>
#include <random>

#include "bus.hpp"

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
  }

  [[nodiscard]] constexpr auto
  get_data () const noexcept
  {
    return this->data;
  }

  constexpr std::array<std::uint8_t, slave_bus_width>
  get_data_bits () const noexcept
  {
    std::array<std::uint8_t, slave_bus_width> bits{};

    const std::uint8_t mask = 0x01;

    for (std::uint8_t i = 0; i < slave_bus_width; ++i)
      {
        bits[i] = (this->data & (mask << i)) ? 1 : 0;
      }

    return bits;
  }

  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
    return sizeof (this->data);
  }
};

#endif // !SLAVE_HPP
