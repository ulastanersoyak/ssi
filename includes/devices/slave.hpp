#ifndef SLAVE_HPP
#define SLAVE_HPP

#include <array>
#include <cstdint>
#include <random>
#include <type_traits>

#include "bus.hpp"

template <std::uint8_t slave_bus_width> class slave
{
  static_assert (slave_bus_width == 1 || slave_bus_width == 8
                     || slave_bus_width == 16 || slave_bus_width == 32,
                 "slave_bus_width must be 1, 8, 16, or 32");

  using bus_wide_integer = std::conditional_t<
      slave_bus_width == BUS_WIDTH_1, std::uint8_t,
      std::conditional_t<slave_bus_width == BUS_WIDTH_8, std::uint8_t,
                         std::conditional_t<slave_bus_width == BUS_WIDTH_16,
                                            std::uint16_t, std::uint32_t> > >;
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
            (this->data << 1)
            | static_cast<bus_wide_integer> ((distrib (gen))));
      }
  }

  constexpr std::array<std::uint8_t, slave_bus_width>
  get_data_bits () const noexcept
  {
    std::array<std::uint8_t, slave_bus_width> bits{};

    const std::uint8_t mask = 0x01;

    for (std::uint8_t i = 0; i < slave_bus_width; ++i)
      {
        bits[i] = (data & (mask << i)) ? 1 : 0;
      }

    return bits;
  }

  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
    return sizeof (this->data);
  }

  [[nodiscard]] constexpr auto
  get_data () const noexcept
  {
    return this->data;
  }
};

#endif // !SLAVE_HPP
