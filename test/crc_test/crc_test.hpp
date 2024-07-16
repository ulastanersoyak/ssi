#ifndef CRC_TEST_HPP
#define CRC_TEST_HPP

#include "devices/crc.hpp"
#include <algorithm>
#include <print>

namespace crc_test
{
constexpr void
hash_test () noexcept
{
  {
    constexpr std::array<uint8_t, 1> data1_1{ 1 };
    constexpr std::array<uint8_t, 1> data1_0{ 0 };
    constexpr auto hash1_1 = crc16_hash<data1_1.size ()> (data1_1);
    constexpr auto hash1_0 = crc16_hash<data1_0.size ()> (data1_0);

    static_assert (hash1_1 == 32767 && hash1_0 == 57342,
                   "crc16 for 1 bit bus failed");
  }
  {
    constexpr std::array<uint8_t, 8> data8_1 = [] () {
      std::array<uint8_t, 8> ret_val{ 0 };
      std::ranges::fill (ret_val, 1);
      return ret_val;
    }();

    constexpr std::array<uint8_t, 8> data8_0 = [] () {
      std::array<uint8_t, 8> ret_val{ 0 };
      std::ranges::fill (ret_val, 0);
      return ret_val;
    }();

    constexpr std::array<uint8_t, 8> data8_rand{ 1, 0, 1, 1, 1, 0, 0, 1 };
    constexpr auto hash8_1 = crc16_hash<data8_1.size ()> (data8_1);
    constexpr auto hash8_0 = crc16_hash<data8_0.size ()> (data8_0);
    constexpr auto hash8_rand = crc16_hash<data8_rand.size ()> (data8_rand);

    static_assert (hash8_1 == 31293 && hash8_0 == 2880 && hash8_rand == 60029,
                   "crc16 for 8 bit bus failed");
  }

  {
    constexpr std::array<uint8_t, 16> data16_0 = [] () {
      std::array<uint8_t, 16> ret_val{ 0 };
      std::ranges::fill (ret_val, 0);
      return ret_val;
    }();

    constexpr std::array<uint8_t, 16> data16_1 = [] () {
      std::array<uint8_t, 16> ret_val{ 0 };
      std::ranges::fill (ret_val, 1);
      return ret_val;
    }();
    constexpr std::array<uint8_t, 16> data16_rand{ 1, 0, 1, 1, 1, 0, 0, 1,
                                                   0, 0, 1, 1, 0, 0, 0 };
    constexpr auto hash16_1 = crc16_hash<data16_1.size ()> (data16_1);
    constexpr auto hash16_0 = crc16_hash<data16_0.size ()> (data16_0);
    constexpr auto hash16_rand = crc16_hash<data16_rand.size ()> (data16_rand);
    static_assert (hash16_1 == 17846 && hash16_0 == 37889
                       && hash16_rand == 10331,
                   "crc16 for 16 bit bus failed");
  }
  {
    constexpr std::array<uint8_t, 32> data32_0 = [] () {
      std::array<uint8_t, 32> ret_val{ 0 };
      std::ranges::fill (ret_val, 0);
      return ret_val;
    }();

    constexpr std::array<uint8_t, 32> data32_1 = [] () {
      std::array<uint8_t, 32> ret_val{ 0 };
      std::ranges::fill (ret_val, 1);
      return ret_val;
    }();
    constexpr std::array<uint8_t, 32> data32_rand{ 1, 0, 1, 1, 1, 0, 0, 1,
                                                   0, 0, 1, 1, 0, 0, 0, 0,
                                                   0, 1, 1, 1, 0, 1, 1, 0,
                                                   1, 0, 1, 0, 1, 0, 0, 0 };
    constexpr auto hash32_1 = crc16_hash<data32_1.size ()> (data32_1);
    constexpr auto hash32_0 = crc16_hash<data32_0.size ()> (data32_0);
    constexpr auto hash32_rand = crc16_hash<data32_rand.size ()> (data32_rand);
    std::println ("{} {} {}", hash32_1, hash32_0, hash32_rand);
    static_assert (hash32_1 == 8939 && hash32_0 == 64510
                       && hash32_rand == 33796,
                   "crc16 for 16 bit bus failed");
  }
}
}

#endif // !CRC_TEST_HPP
