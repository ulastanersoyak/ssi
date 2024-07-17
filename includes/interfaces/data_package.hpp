#ifndef DATA_PACKAGE_HPP
#define DATA_PACKAGE_HPP

#include <cstdint>
template <typename bus_width_integer> struct data_package
{
  bus_width_integer data{ 0 };
  std::uint16_t hash{ 0 };
};

#endif // !DATA_PACKAGE_HPP
