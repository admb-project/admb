#include <gtest/gtest.h>
#include "admodel.h"

class test_init_adstring: public ::testing::Test {};

TEST_F(test_init_adstring, constructor)
{
  init_adstring s;

  ASSERT_STREQ("", s.get_name());
  ASSERT_EQ(0, s.size());
  ASSERT_STREQ("", (char*)s);
}
TEST_F(test_init_adstring, allocate)
{
  ofstream ofs("test_init_adstring.dat");
  ofs << "## ignore\n";
  ofs << "__test_init_adstring__\n";
  ofs.close();

  ASSERT_EQ(NULL, ad_comm::global_datafile);

  cifstream cif("test_init_adstring.dat");
  ad_comm::global_datafile = &cif;

  init_adstring s;
  s.allocate("name");
  ASSERT_STREQ("name", s.get_name());
  ASSERT_EQ(22, s.size());
  ASSERT_STREQ("__test_init_adstring__", (char*)s);

  cif.close();
  ad_comm::global_datafile = NULL;
}
