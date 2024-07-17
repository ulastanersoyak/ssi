#ifndef MASTER_HPP
#define MASTER_HPP

#include "devices/crc.hpp"
#include "interfaces/data_package.hpp"
#include <cstdint>
#if (__cplusplus == 202302L)
#include <print>
#else
#include <iostream>
#endif

#include "bus.hpp"

#include <algorithm>

template <std::uint8_t master_bus_width>
class master : public bus_width_helper<master_bus_width>
{
  constexpr void
  voltage_to_logic (auto &voltage_bus)
  {
    std::ranges::for_each (
        voltage_bus, [] (auto &voltage) { voltage = (voltage == 5) ? 1 : 0; });
  }

  constexpr void
  remove_noise (auto &voltage_bus)
  {
    std::ranges ::for_each (
        voltage_bus, [] (auto &voltage) { voltage = (voltage >= 3) ? 5 : 0; });
  }

public:
  [[nodiscard]] constexpr void
  read_data_bus (auto &data_bus_) noexcept
  {
    for (std::uint8_t idx = 0; const auto line : data_bus_)
      {
        this->data_bus[idx++] = line;
      }
  }

  [[nodiscard]] constexpr auto
  get_data_bus () const noexcept
  {
    return this->data_bus;
  }

  [[nodiscard]] constexpr bool
  receive_data_package (data_package<master_bus_width> &package)
  {
    this->remove_noise (package.voltage_bus);
    this->voltage_to_logic (package.voltage_bus);
    const auto hash = crc_hash<master_bus_width> (package.voltage_bus);
    this->data_bus = package.voltage_bus;
    this->process_data ();
    if (hash != package.hash)
      {
        std::cerr << "\ncrc check failed. data corrupted on on the way to the "
                     "master\n";
        return false;
      }
    return true;
  }

  constexpr void
  process_data () const noexcept
  {
#if (__cplusplus == 202302L)
    std::print ("\nmaster device:\t");
#else
    std::cout << "\nmaster device:\t";
#endif
    for (std::uint8_t idx = 0; idx < master_bus_width; ++idx)
      {
#if (__cplusplus == 202302L)
        std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
        std::cout << "bit" << static_cast<int> (idx)
                  << " := " << static_cast<int> (this->data_bus[idx]) << ' ';
#endif
      }
  }

  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
    return master_bus_width;
  }
};

#endif // !MASTER_HPP
