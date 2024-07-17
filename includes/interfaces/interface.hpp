#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "devices/bus.hpp"
#include "devices/crc.hpp"
#include "devices/master.hpp"
#include "devices/slave.hpp"
#include "interfaces/data_package.hpp"
<<<<<<< HEAD
#include <array>
#include <cstdint>
=======

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>
>>>>>>> master

template <std::uint8_t interface_bus_width>
class interface : public bus_width_helper<interface_bus_width>
{
<<<<<<< HEAD
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
=======
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
>>>>>>> master
  }

public:
  constexpr void
  get_package_from_slave () noexcept
  {
    this->slave_.read_data ();
<<<<<<< HEAD
    this->slave_.visualize_data ();
    auto pkg = this->slave_.send_data_package ();
    bool is_resolved{ false };
    for (std::int8_t noise_variant = -10; noise_variant < 11; ++noise_variant)
      {
        auto data_with_noise
            = static_cast<bus_wide_integer> (pkg.data + noise_variant);
        auto bits = this->data_to_bits (data_with_noise);
        auto hash = crc_hash<bits.size ()> (bits);
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
=======
    this->slave_.print_captured_data ();
    auto pkg = this->slave_.send_data_package ();
    this->remove_noise (pkg.voltage_bus);
    this->voltage_to_logic (pkg.voltage_bus);
    const auto hash = crc_hash (pkg.voltage_bus);
    if (hash == pkg.hash)
      {
        this->package = pkg;
#if (__cplusplus == 202302L)
        std::print ("\nmaster device:\n");
#else
        std::cout << "\ninterface:\n";
#endif
        for (std::uint8_t idx = 0; idx < interface_bus_width; ++idx)
          {
#if (__cplusplus == 202302L)
            std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
            std::cout << "bit" << static_cast<int> (idx)
                      << " := " << pkg.voltage_bus[idx] << ' ';
#endif
          }
      }
>>>>>>> master
  }

  constexpr void
  send_package_to_master () noexcept
  {
<<<<<<< HEAD
    const auto bits = this->data_to_bits (this->package.data);
    const auto hash = crc_hash<bits.size ()> (bits);
    this->master_.receive_data_package (data_package<bus_wide_integer>{
        .data = this->package.data, .hash = hash });
=======
    const auto hash = crc_hash (this->package.voltage_bus);
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
    data_package pkg = {.voltage_bus = this->package.voltage_bus, .hash = hash };
    this->master_.receive_data_package (pkg);
>>>>>>> master
  }
};

using ssi = interface<1>;
using biss8 = interface<8>;
using biss16 = interface<16>;
using biss32 = interface<32>;

#endif // !INTERFACE_HPP
