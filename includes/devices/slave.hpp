#ifndef SLAVE_HPP
#define SLAVE_HPP

#include <algorithm>
#include <array>
#include <cstdint>
#include <print>
#include <random>

#include "bus.hpp"
#include "devices/crc.hpp"
#include "interfaces/data_package.hpp"

template <std::uint8_t slave_bus_width>
class slave : public bus_width_helper<slave_bus_width>
{
public:
  constexpr void
  read_data () noexcept
  {
    std::random_device rd;
    std::mt19937 gen (rd ());
    std::uniform_int_distribution<> distrib (0, 1);
    for (auto &line : this->data_bus)
      {
        line = static_cast<std::uint8_t> (distrib (gen));
      }
  }

  constexpr void
  print_captured_data ()
  {
#if (__cplusplus == 202302L)
    std::print ("\nslave device:\t");
#else
    std::cout << "\nslave device:\t";
#endif
    for (std::uint8_t idx = 0; idx < slave_bus_width; ++idx)
      {
        bool bit = (this->data_bus[idx]);
#if (__cplusplus == 202302L)
        std::print ("bit{} := {} ", idx, bit ? 1 : 0);
#else
        std::cout << "bit" << static_cast<int> (idx) << " := " << (bit ? 1 : 0)
                  << ' ';
#endif
      }
  }

  [[nodiscard]] constexpr auto
  get_data_bus () const noexcept
  {
    return this->data_bus;
  }

  [[nodiscard]] constexpr auto
  get_bus_size () const noexcept
  {
    return slave_bus_width;
  }

  [[nodiscard]] constexpr data_package<slave_bus_width>
  send_data_package () noexcept
  {
    const auto hash = crc_hash<slave_bus_width> (this->data_bus);
    std::random_device rd;
    std::mt19937 gen (rd ());
    std::uniform_int_distribution<> noise (0, 2);
    std::uniform_int_distribution<> sign (0, 1);
    std::uniform_int_distribution<> noise_chance (0, 1);
    auto chance = noise_chance (gen);
    std::ranges::for_each (this->data_bus, [&] (auto &line) {
      line = line == 0 ? 0 : 5;
      if (chance == 1)
        {
          auto noise_ = noise (gen);
          if (line == 1)
            {
              auto sign_ = sign (gen);
              line = sign_ == 0 ? line + noise_ : line - noise_;
            }
          else
            {
              line += noise_;
            }
        }
    });
    return data_package{ .voltage_bus = this->data_bus,
                         .hash = static_cast<std::uint32_t> (hash) };
  }
};

#endif // !SLAVE_HPP
