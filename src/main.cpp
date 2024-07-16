#if (TEST == 1)
#include "device_tests/master_bus.hpp"
#include "device_tests/slave_bus.hpp"
#endif // ! TEST

int
main ()
{
#if (TEST == 1)
  master_bus_test::bus_byte_size ();
  slave_bus_tests::bus_byte_size ();
  slave_bus_tests::bus_bit_size ();
#endif // !TEST
  return 0;
}
