#ifndef MASTER_HPP
#define MASTER_HPP

#include <cstdint>
#if (__cplusplus == 202302L)
#include <print>
#else
#include <iostream>
#endif

#include "bus.hpp"

template <std::uint8_t master_bus_width>
class master : public bus_width_helper<master_bus_width>
{

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
  process_data () const noexcept
  {
    for (std::uint8_t idx = 0; idx < master_bus_width; ++idx)
      {
        bool bit = (this->data & (1U << idx));
#if (__cplusplus == 202302L)
        std::println ("bit{} := {}", idx, bit ? 1 : 0);
#else
        std::iostream << "bit" << idx << " := " << bit ? 1 : 0 << '\n';
#endif
      }
  }
#if (TEST == 1)
  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
    return sizeof (this->data);
  }
#endif // ! TEST
};

#endif // !MASTER_HPP
