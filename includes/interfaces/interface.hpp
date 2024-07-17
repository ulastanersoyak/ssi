#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "devices/bus.hpp"
#include "devices/crc.hpp"
#include "devices/master.hpp"
#include "devices/slave.hpp"
#include "interfaces/data_package.hpp"
#include <array>
#include <cstdint>

template <std::uint8_t interface_bus_width>
class interface : public bus_width_helper<interface_bus_width>
{
  using typename bus_width_helper<interface_bus_width>::bus_wide_integer;
  master<interface_bus_width> master_{};
  slave<interface_bus_width> slave_{};
  data_package<bus_wide_integer> package{};

  [[nodiscard]] constexpr std::array<std::uint8_t, interface_bus_width>
  data_to_bits (bus_wide_integer data) const noexcept
  {
    std::array<std::uint8_t, interface_bus_width> bits{};
    const std::uint8_t mask = 0x01;
    for (std::uint8_t i = 0; i < interface_bus_width; ++i)
      {
        bits[i] = static_cast<std::uint8_t> ((data & (mask << i)) ? 1 : 0);
      }

    return bits;
  }

public:
  constexpr void
  get_package_from_slave () noexcept
  {
    this->slave_.read_data ();
    this->slave_.visualize_data ();
    auto pkg = this->slave_.send_data_package ();
    bool is_resolved{ false };
    for (std::int8_t noise_variant = -10; noise_variant < 11; ++noise_variant)
      {
        auto data_with_noise
            = static_cast<bus_wide_integer> (pkg.data + noise_variant);
        auto bits = this->data_to_bits (data_with_noise);
        auto hash = crc16_hash<bits.size ()> (bits);
        if (hash == pkg.hash)
          {
            this->package = pkg;
            is_resolved = true;
            break;
          }
      }
    if (!is_resolved)
      {
        this->package = data_package<bus_wide_integer>{ .data = 0, .hash = 0 };
      }
  }

  constexpr void
  send_package_to_master () noexcept
  {
    const auto bits = this->data_to_bits (this->package.data);
    const auto hash = crc16_hash<bits.size ()> (bits);
    this->master_.receive_data_package (data_package<bus_wide_integer>{
        .data = this->package.data, .hash = hash });
  }
};

using ssi = interface<1>;
using biss8 = interface<8>;
using biss16 = interface<16>;
using biss32 = interface<32>;

#endif // !INTERFACE_HPP
