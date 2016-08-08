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
/*
TEST_F(test_init_adstring, allocate)
{
  init_adstring s;

  ASSERT_EQ(NULL, ad_comm::global_datafile);

  cifstream cif("test_init_adstring.dat");
  ad_comm::global_datafile = &cif;

  s.allocate("name");
  ASSERT_STREQ("name", s.get_name());
  ASSERT_EQ(22, s.size());
  ASSERT_STREQ("__test_init_adstring__", (char*)s);

  ad_comm::global_datafile = NULL;
}
*/
