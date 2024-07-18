#ifndef CRC_HPP
#define CRC_HPP

#include <array>
#include <cstdint>

// https://stackoverflow.com/questions/10564491/function-to-calculate-a-crc16-checksum
template <std::uint8_t data_width>
[[nodiscard]] constexpr auto
crc_hash (const std::array<std::uint8_t, data_width> &bit_array) noexcept
{
  static_assert (data_width == 1 || data_width == 8 || data_width == 16
                     || data_width == 32,
                 "data_width must be 1, 8, 16, or 32");
  std::uint16_t crc_polynomial;
  auto size = bit_array.size ();
  // https://users.ece.cmu.edu/~koopman/crc/
  if constexpr (data_width == 1 || data_width == 8)
    {
      crc_polynomial = 0xe7;
    }
  else
    {
      crc_polynomial = 0x8005;
    }

  std::uint16_t out = 0;
  std::uint8_t bits_read = 0;
  for (std::size_t i = 0; i < size; ++i)
    {
      out <<= 8;
      out |= bit_array[i];
      for (int j = 0; j < 8; ++j)
        {
          std::uint32_t msb = out >> (data_width - 1); // msb
          out <<= 1;
          if (msb)
            {
              out ^= crc_polynomial; // xor if msb is set
            }
        }
    }
  return out;
}

#endif // !CRC_HPP
