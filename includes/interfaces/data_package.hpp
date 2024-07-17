#ifndef DATA_PACKAGE_HPP
#define DATA_PACKAGE_HPP

#include <cstdint>
template <std::size_t size> struct data_package
{
  std::array<std::uint8_t, size> voltage_bus{ 0 };
  std::uint16_t hash{ 0 };
};

#endif // !DATA_PACKAGE_HPP
