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

<<<<<<< HEAD
template <std::uint8_t master_bus_width>
class master : public bus_width_helper<master_bus_width>
{

  using typename bus_width_helper<master_bus_width>::bus_wide_integer;
  bus_wide_integer data{ 0 };

  [[nodiscard]] constexpr std::array<std::uint8_t, master_bus_width>
  data_to_bits (bus_wide_integer data_) const noexcept
  {
    std::array<std::uint8_t, master_bus_width> bits{};
    const std::uint8_t mask = 0x01;
    for (std::uint8_t i = 0; i < master_bus_width; ++i)
      {
        bits[i] = static_cast<std::uint8_t> ((data_ & (mask << i)) ? 1 : 0);
      }

    return bits;
  }

public:
  constexpr void
  read_data (auto data_) noexcept
  {
    this->data = data_;
  }

  [[nodiscard]] constexpr auto
  get_data () const noexcept
  {
    return this->data;
  }

  constexpr void
  receive_data_package (const data_package<bus_wide_integer> &package)
  {
    const auto bits = data_to_bits (package.data);
    const auto hash = crc_hash<bits.size ()> (bits);
    if (package.hash == hash)
      {
        this->data = package.data;
=======
#include <algorithm>

template <std::uint8_t master_bus_width>
class master : public bus_width_helper<master_bus_width>
{
  constexpr void
  voltage_to_logic (auto &voltage_bus)
  {
    std::for_each (voltage_bus.begin (), voltage_bus.end (),
                   [] (auto &voltage) { voltage = (voltage == 5) ? 1 : 0; });
  }

  constexpr void
  remove_noise (auto &voltage_bus)
  {
    std::for_each (voltage_bus.begin (), voltage_bus.end (),
                   [] (auto &voltage) { voltage = (voltage >= 3) ? 5 : 0; });
  }

public:
  [[nodiscard]] constexpr void
  read_data_bus (auto &data_bus_) noexcept
  {
    for (std::uint8_t idx=0;const auto line : data_bus_)
      {
        this->data_bus[idx++] = line;
      }
  }

  [[nodiscard]] constexpr auto
  get_data_bus () const noexcept
  {
    return this->data_bus;
  }

  constexpr void
  receive_data_package (data_package<master_bus_width> &package)
  {
    this->remove_noise (package.voltage_bus);
    this->voltage_to_logic (package.voltage_bus);
    const auto hash = crc_hash<master_bus_width> (package.voltage_bus);
    if (package.hash == hash)
      {
        this->data_bus = package.voltage_bus;
>>>>>>> master
        this->process_data ();
      }
  }

  constexpr void
  process_data () const noexcept
  {
#if (__cplusplus == 202302L)
    std::print ("\nmaster device:\n");
#else
    std::cout << "\nmaster device:\n";
#endif
    for (std::uint8_t idx = 0; idx < master_bus_width; ++idx)
      {
<<<<<<< HEAD
        bool bit = (this->data & (1U << idx));
#if (__cplusplus == 202302L)
        std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
        std::iostream << "bit" << idx << " := " << bit ? 1 : 0 << ' ';
=======
#if (__cplusplus == 202302L)
        std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
        std::cout << "bit" << static_cast<int> (idx)
                  << " := " << this->data_bus[idx] << ' ';
>>>>>>> master
#endif
      }
  }

  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
<<<<<<< HEAD
    return sizeof (this->data);
=======
    return master_bus_width;
>>>>>>> master
  }
};

#endif // !MASTER_HPP
