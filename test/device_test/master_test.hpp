#ifndef MASTER_TEST_HPP
#define MASTER_TEST_HPP

#include "devices/master.hpp"
#include "devices/slave.hpp"

#include <utility>

namespace master_bus_test
{
constexpr void
bus_byte_size ()
{
  slave<1> s1{};
  master<1> m1{};
  s1.read_data ();
  auto s1_bus = s1.get_data_bus ();
  m1.read_data_bus (s1_bus);
  static_assert (m1.get_bus_size () == 1, "master<1> device failed");

  slave<8> s8{};
  master<8> m8{};
  s8.read_data ();
  auto s8_bus = s8.get_data_bus ();
  m8.read_data_bus (s8_bus);
  static_assert (m8.get_bus_size () == 8, "master<8> device failed");

  slave<16> s16{};
  master<16> m16{};
  s16.read_data ();
  auto s16_bus = s16.get_data_bus ();
  m16.read_data_bus (s16_bus);
  static_assert (m16.get_bus_size () == 16, "master<16> device failed");

  slave<32> s32{};
  master<32> m32{};
  s32.read_data ();
  auto s32_bus = s32.get_data_bus ();
  m32.read_data_bus (s32_bus);
  static_assert (m32.get_bus_size () == 32, "master<32> device failed");
}
}

#endif // !MASTER_TEST_HPP
