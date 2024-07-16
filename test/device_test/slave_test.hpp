#ifndef SLAVE_TEST_HPP
#define SLAVE_TEST_HPP

#include "devices/slave.hpp"

namespace slave_bus_tests
{
constexpr void
bus_byte_size ()
{
  slave<1> ss{};
  static_assert (ss.get_bus_size () == 1, "slave<1> device failed");

  slave<8> s8{};
  static_assert (s8.get_bus_size () == 1, "slave<8> device failed");

  slave<16> s16{};
  static_assert (s16.get_bus_size () == 2, "slave<16> device failed");

  slave<32> s32{};
  static_assert (s32.get_bus_size () == 4, "slave<32> device failed");
}

constexpr void
bus_bit_size ()
{
  constexpr slave<1> s1{};
  static_assert (s1.get_data_bits ().size () == 1, "slave<1> device failed");

  constexpr slave<8> s8{};
  static_assert (s8.get_data_bits ().size () == 8, "slave<8> device failed");

  constexpr slave<16> s16{};
  static_assert (s16.get_data_bits ().size () == 16,
                 "slave<16> device failed");

  constexpr slave<32> s32{};
  static_assert (s32.get_data_bits ().size () == 32,
                 "slave<32> device failed");
}
}
#endif // !SLAVE_TEST_HPP
