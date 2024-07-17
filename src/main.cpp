#include "interfaces/interface.hpp"

#if (TEST == 1)
#include "crc_test/crc_test.hpp"
#include "device_test/master_test.hpp"
#include "device_test/slave_test.hpp"
#endif // ! TEST

int
main ()
{
#if (TEST == 1)
  master_bus_test::bus_byte_size ();
  slave_bus_tests::bus_byte_size ();
  slave_bus_tests::bus_bit_size ();
  crc_test::hash_test ();
#endif // !TEST
  interface<16> intr;
  intr.get_package_from_slave ();
  intr.send_package_to_master ();
  return 0;
}
