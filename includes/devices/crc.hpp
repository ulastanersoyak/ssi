#ifndef CRC_HPP
#define CRC_HPP

#include <array>
#include <cstdint>

template <std::uint8_t data_width>
[[nodiscard]] constexpr std::uint16_t
crc16_hash (const std::array<std::uint8_t, data_width> &bit_array) noexcept
{
  std::uint16_t crc = 0xFFFF;
  constexpr std::uint16_t polynomial = 0xA001;

  for (std::uint8_t byte : bit_array)
    {
      crc ^= byte;

      for (std::size_t j = 0; j < bit_array.size (); ++j)
        {
          if (crc & 0x0001U)
            {
              crc = static_cast<std::uint16_t> ((crc >> 1U)) ^ polynomial;
            }
          else
            {
              crc >>= 1U;
            }
        }
    }
  return crc;
}
#endif // !CRC_HPP
