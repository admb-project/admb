#include <gtest/gtest.h>
#include "admodel.h"

class test_init_line_adstring: public ::testing::Test {};

TEST_F(test_init_line_adstring, constructor)
{
  init_line_adstring s;

  ASSERT_STREQ("", s.get_name());
  ASSERT_EQ(0, s.size());
  ASSERT_STREQ("", (char*)s);
}
/*
TEST_F(test_init_line_adstring, allocate)
{
  init_line_adstring s;

  ASSERT_EQ(NULL, ad_comm::global_datafile);

  cifstream cif("test_init_line_adstring.dat");
  ad_comm::global_datafile = &cif;

  s.allocate("name");
  ASSERT_STREQ("name", s.get_name());
  ASSERT_EQ(28, s.size());
  ASSERT_STREQ("__test_init_line_adstring__\n", (char*)s);

  ad_comm::global_datafile = NULL;
}
*/
