#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "devices/bus.hpp"
#include "devices/master.hpp"
#include "devices/slave.hpp"

template <std::uint8_t interface_bus_width> class interface
{
  static_assert (interface_bus_width == 1 || interface_bus_width == 8
                     || interface_bus_width == 16 || interface_bus_width == 32,
                 "interface_bus_width must be 1, 8, 16, or 32");

  using bus_wide_integer = std::conditional_t<
      interface_bus_width == BUS_WIDTH_1, std::uint8_t,
      std::conditional_t<
          interface_bus_width == BUS_WIDTH_8, std::uint8_t,
          std::conditional_t<interface_bus_width == BUS_WIDTH_16,
                             std::uint16_t, std::uint32_t> > >;

  master<interface_bus_width> master_{};
  slave<interface_bus_width> slave_{};

public:
};

using ssi = interface<1>;
using biss8 = interface<8>;
using biss16 = interface<16>;
using biss32 = interface<32>;

#endif // !INTERFACE_HPP
