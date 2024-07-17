#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "devices/bus.hpp"
#include "devices/crc.hpp"
#include "devices/master.hpp"
#include "devices/slave.hpp"
#include "interfaces/data_package.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>

template <std::uint8_t interface_bus_width>
class interface : public bus_width_helper<interface_bus_width>
{
  master<interface_bus_width> master_{};
  slave<interface_bus_width> slave_{};
  data_package<interface_bus_width> package{};

  constexpr void
  voltage_to_logic (auto &voltage_bus)
  {
    std::ranges::for_each (
        voltage_bus, [] (auto &voltage) { voltage = voltage == 5 ? 1 : 0; });
  }

  constexpr void
  remove_noise (auto &voltage_bus)
  {
    std::ranges::for_each (
        voltage_bus, [] (auto &voltage) { voltage = voltage >= 3 ? 5 : 0; });
  }

public:
  [[nodiscard]] constexpr bool
  get_package_from_slave () noexcept
  {
    this->slave_.read_data ();
    this->slave_.print_captured_data ();
    auto pkg = this->slave_.send_data_package ();
    this->remove_noise (pkg.voltage_bus);
    this->voltage_to_logic (pkg.voltage_bus);
    const auto hash = crc_hash (pkg.voltage_bus);
    this->package = pkg;
#if (__cplusplus == 202302L)
    std::print ("\ninterace:\t");
#else
    std::cout << "\ninterface:\t";
#endif
    for (std::uint8_t idx = 0; idx < interface_bus_width; ++idx)
      {
#if (__cplusplus == 202302L)
        std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
        std::cout << "bit" << static_cast<int> (idx)
                  << " := " << static_cast<int> (pkg.voltage_bus[idx]) << ' ';
#endif
      }
    if (hash != pkg.hash)
      {
        std::cerr << "\ncrc check failed! not forwarding it to the master\n";
        return false;
      }
    return true;
  }

  [[nodiscard]] constexpr bool
  send_package_to_master () noexcept
  {
    const auto hash = crc_hash<interface_bus_width> (this->package.voltage_bus);
    std::random_device rd;
    std::mt19937 gen (rd ());
    std::uniform_int_distribution<> noise (0, 2);
    std::uniform_int_distribution<> sign (0, 1);
    std::uniform_int_distribution<> noise_chance (0, 1);
    auto chance = noise_chance (gen);
    std::ranges::for_each (this->package.voltage_bus, [&] (auto &line) {
      if (chance == 1)
        {
          if (line == 1)
            {
              auto noise_ = noise (gen);
              auto sign_ = sign (gen);
              line = 5;
              line = sign_ == 0 ? line + noise_ : line - noise_;
            }
          else
            {
              line += noise (gen);
            }
        }
    });
    data_package pkg
        = { .voltage_bus = this->package.voltage_bus, .hash = static_cast<std::uint32_t> (hash) };
    return this->master_.receive_data_package (pkg);
  }
};

using ssi = interface<1>;
using biss8 = interface<8>;
using biss16 = interface<16>;
using biss32 = interface<32>;

#endif // !INTERFACE_HPP
