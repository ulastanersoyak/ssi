#include "interfaces/interface.hpp"

#if (TEST == 1)
#include "device_test/master_test.hpp"
#include "device_test/slave_test.hpp"
#endif // ! TEST

int
main ()
{
#if (TEST == 1)
  master_bus_test::bus_byte_size ();
  slave_bus_tests::bus_bit_size ();
#endif // !TEST
  biss16 intr;
  std::uint8_t counter{ 0 };
  constexpr auto transmit_count{ 20 };
  for (int i = 0; i < transmit_count; ++i)
    {
      bool is_crc_passed = intr.get_package_from_slave ();
      if (is_crc_passed)
        {
          bool is_crc_passed = intr.send_package_to_master ();
          if (is_crc_passed)
            {
              ++counter;
            }
        }
      std::println ("\n");
    }
  std::println ("{}/{} data transmitted successfully\n", counter,
                transmit_count);
  return 0;
}
