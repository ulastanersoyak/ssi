#include "devices/master.hpp"
#include "devices/slave.hpp"

#if (__cplusplus == 202302L)
#include <print>
#else
#include <iostream>
#endif

constexpr void
bus_byte_size ()
{
  slave<1> s1{};
  master<1> m1{};
  s1.read_data ();
  m1.read_data (s1.get_data ());
  static_assert (m1.get_bus_size () == 1, "master<1> device failed");

  slave<8> s8{};
  master<8> m8{};
  s8.read_data ();
  m8.read_data (s8.get_data ());
  static_assert (m8.get_bus_size () == 1, "master<8> device failed");

  slave<16> s16{};
  master<16> m16{};
  s16.read_data ();
  m16.read_data (s16.get_data ());
  static_assert (m16.get_bus_size () == 2, "master<16> device failed");

  slave<32> s32{};
  master<32> m32{};
  s32.read_data ();
  m32.read_data (s32.get_data ());
  static_assert (m32.get_bus_size () == 4, "master<32> device failed");
}
