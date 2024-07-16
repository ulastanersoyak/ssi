#ifndef MASTER_HPP
#define MASTER_HPP

#include <cstdint>
#include <type_traits>
#if (__cplusplus == 202302L)
#include <print>
#else
#include <iostream>
#endif

#include "bus.hpp"

template <std::uint8_t master_bus_width> class master
{
  static_assert (master_bus_width == 1 || master_bus_width == 8
                     || master_bus_width == 16 || master_bus_width == 32,
                 "master_bus_width must be 1, 8, 16, or 32");

  using bus_wide_integer = std::conditional_t<
      master_bus_width == BUS_WIDTH_1, std::uint8_t,
      std::conditional_t<master_bus_width == BUS_WIDTH_8, std::uint8_t,
                         std::conditional_t<master_bus_width == BUS_WIDTH_16,
                                            std::uint16_t, std::uint32_t> > >;
  bus_wide_integer data{ 0 };

public:
  constexpr void
  read_data (auto data_) noexcept
  {
    this->data = data_;
  }

  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
    return sizeof (this->data);
  }

  [[nodiscard]] constexpr auto
  get_data () const noexcept
  {
    return this->data;
  }

  constexpr void
  process_data () const noexcept
  {
    for (std::uint8_t idx = 0; idx < master_bus_width; ++idx)
      {
        bool bit = (data & (1U << idx));
#if (__cplusplus == 202302L)
        std::println ("bit{} := {}", idx, bit ? 1 : 0);
#else
        std::iostream << "bit" << idx << " := " << bit ? 1 : 0 << '\n';
#endif
      }
  }
};

#endif // !MASTER_HPP
