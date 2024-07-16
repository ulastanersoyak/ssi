#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "devices/bus.hpp"
#include "devices/master.hpp"
#include "devices/slave.hpp"

template <std::uint8_t interface_bus_width>
class interface : public bus_width_helper<interface_bus_width>
{
  master<interface_bus_width> master_{};
  slave<interface_bus_width> slave_{};

public:
  [[nodiscard]] constexpr bool
  crc () const noexcept
  {
  }
};

using ssi = interface<1>;
using biss8 = interface<8>;
using biss16 = interface<16>;
using biss32 = interface<32>;

#endif // !INTERFACE_HPP
