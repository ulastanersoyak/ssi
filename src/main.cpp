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
  biss8 intr;
  for (int i = 0; i < 10; ++i)
    {
      intr.get_package_from_slave ();
      intr.send_package_to_master ();
      std::println ("\n");
    }
  return 0;
}
