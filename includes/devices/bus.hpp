#ifndef BUS_HPP
#define BUS_HPP

#include <cstdint>
#include <type_traits>
#include <array>

constexpr std::uint8_t BUS_WIDTH_1{ 1 };
constexpr std::uint8_t BUS_WIDTH_8{ 8 };
constexpr std::uint8_t BUS_WIDTH_16{ 16 };
constexpr std::uint8_t BUS_WIDTH_32{ 32 };

template <std::uint8_t bus_width> class bus_width_helper
{
  static_assert (bus_width == BUS_WIDTH_1 || bus_width == BUS_WIDTH_8
                     || bus_width == BUS_WIDTH_16 || bus_width == BUS_WIDTH_32,
                 "bus_width must be 1, 8, 16, or 32");

protected:
  std::array<std::uint8_t, bus_width> data_bus{};
};

#endif // !BUS_HPP
