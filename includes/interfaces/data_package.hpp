#ifndef DATA_PACKAGE_HPP
#define DATA_PACKAGE_HPP

<<<<<<< HEAD
#include <cstdint>
template <typename bus_width_integer> struct data_package
{
  bus_width_integer data{ 0 };
=======
#include <array>
#include <cstdint>

template <std::size_t size> struct data_package
{
  std::array<std::uint8_t, size> voltage_bus{ 0 };
>>>>>>> master
  std::uint16_t hash{ 0 };
};

#endif // !DATA_PACKAGE_HPP
