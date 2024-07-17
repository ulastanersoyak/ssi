#ifndef CRC_HPP
#define CRC_HPP

#include <array>
#include <cstdint>

template <std::uint8_t data_width>
[[nodiscard]] constexpr auto
crc_hash (const std::array<std::uint8_t, data_width> &bit_array) noexcept;

template <>
[[nodiscard]] constexpr auto
crc_hash<1> (const std::array<std::uint8_t, 1> &bit_array) noexcept
{
  return static_cast<std::uint8_t> (bit_array[0] & 0x1U);
}

// https://stackoverflow.com/questions/51752284/how-to-calculate-crc8-in-c
template <>
[[nodiscard]] constexpr auto
crc_hash<8> (const std::array<std::uint8_t, 8> &bit_array) noexcept
{
  std::uint8_t crc = 0xff;
  for (const auto bit : bit_array)
    {
      crc ^= bit;
      for (int j = 0; j < 8; j++)
        {
          if ((crc & 0x80U) != 0)
            {
              crc = static_cast<std::uint8_t> (
                  static_cast<std::uint8_t> ((crc << 1U)) ^ 0x31U);
            }
          else
            {
              crc <<= 1U;
            }
        }
    }
  return crc;
}

// https://stackoverflow.com/questions/10564491/function-to-calculate-a-crc16-checksum
template <>
[[nodiscard]] constexpr auto
crc_hash<16> (const std::array<std::uint8_t, 16> &bit_array) noexcept
{
  std::uint16_t out = 0;
  std::size_t bits_read = 0;
  int bit_flag = 0;
  auto size = static_cast<std::uint8_t> (bit_array.size ());
  std::uint16_t CRC16{ 0x8005 };
  std::uint32_t idx = 0;
  while (size > 0)
    {
      bit_flag = out >> 15U;

      out <<= 1U;
      out = ((bit_array.at (idx) >> bits_read) & 1U) | out;

      bits_read++;
      if (bits_read > 7)
        {
          bits_read = 0;
          idx++;
          size--;
        }
      if (bit_flag != 0)
        {
          out ^= CRC16;
        }
    }
  std::uint32_t i = 0;
  for (; i < 16; ++i)
    {
      bit_flag = out >> 15U;
      out <<= 1U;
      if (bit_flag != 0)
        {
          out ^= CRC16;
        }
    }
  uint16_t crc = 0;
  i = 0x8000;
  std::uint32_t j = 0x0001;
  for (; i != 0; i >>= 1U, j <<= 1U)
    {
      if ((i & out) != 0)
        {
          crc = static_cast<std::uint16_t> (crc | j);
        }
    }

  return crc;
}

// http://web.archive.org/web/20080303102530/http://c.snippets.org/snip_lister.php?fname=crc_32.c
template <>
[[nodiscard]] constexpr auto
crc_hash<32> (
    [[maybe_unused]] const std::array<std::uint8_t, 32> &bit_array) noexcept
{
  return 0;
}

#endif // !CRC_HPP
