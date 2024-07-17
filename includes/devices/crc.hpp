#ifndef CRC_HPP
#define CRC_HPP

#include <array>
#include <cstdint>

// template <std::uint8_t data_width>
// [[nodiscard]] constexpr std::uint16_t
// crc16_hash (const std::array<std::uint8_t, data_width> &bit_array) noexcept
// {
//   std::uint16_t crc = 0xFFFF;
//   constexpr std::uint16_t polynomial = 0xA001;
//
//   for (std::uint8_t byte : bit_array)
//     {
//       crc ^= byte;
//
//       for (std::size_t j = 0; j < bit_array.size (); ++j)
//         {
//           if (crc & 0x0001U)
//             {
//               crc = static_cast<std::uint16_t> ((crc >> 1U)) ^ polynomial;
//             }
//           else
//             {
//               crc >>= 1U;
//             }
//         }
//     }
//   return crc;
// }

template <std::uint8_t data_width>
[[nodiscard]] constexpr std::uint16_t
crc16_hash (const std::array<std::uint8_t, data_width> &bit_array) noexcept
{
  constexpr std::uint16_t CRC16 = 0x8005;
  std::uint16_t out = 0;
  int bits_read = 0;
  int bit_flag = 0;

  for (const auto &data : bit_array)
    {
      bit_flag = out >> 15;

      out <<= 1;
      out |= (data >> bits_read) & 1;

      bits_read++;
      if (bits_read > 7)
        {
          bits_read = 0;
        }

      if (bit_flag)
        {
          out ^= CRC16;
        }
    }

  for (int i = 0; i < 16; ++i)
    {
      bit_flag = out >> 15;
      out <<= 1;
      if (bit_flag)
        {
          out ^= CRC16;
        }
    }

  std::uint16_t crc = 0;
  for (std::uint16_t i = 0x8000, j = 0x0001; i != 0; i >>= 1, j <<= 1)
    {
      if (i & out)
        {
          crc |= j;
        }
    }

  return crc;
}

#endif // !CRC_HPP
