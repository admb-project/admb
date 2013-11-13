#include <gtest/gtest.h>
#include <fvar.hpp>
#include <new>
//using std::new;

class test_df_file:public ::testing::Test {};

TEST_F(test_df_file, signs)
{
  int x = 5;
  int* y = &x;
  int z = 0;

  z =- *y;

  ASSERT_EQ(-x, z);
}
TEST_F(test_df_file, strtok)
{
  char args[100];
  strcpy(args, "aaaa bbbb cccc dddd eeee ffff gggg\0");
  ASSERT_STREQ("aaaa", strtok(args, " "));
  ASSERT_STREQ("bbbb", strtok(NULL, " "));
  ASSERT_STREQ("cccc", strtok('\0', " "));
  //Does not work -> strtok((char*)"\0", " ")
}
TEST_F(test_df_file, allocate_INT_MAX)
{
  int size = INT_MAX;
  ASSERT_EQ(INT_MAX, size);
  char* a = 0;
  ASSERT_NO_THROW(a = new char[size]);
  delete [] a;
  a = 0;
}
TEST_F(test_df_file, instance_INT_MAX)
{
  ASSERT_NO_THROW(DF_FILE instance(INT_MAX));
}
TEST_F(test_df_file, allocate_INT_MAX_plus_1)
{
  ASSERT_LT(INT_MAX, LONG_MAX);
  ASSERT_LT(LONG_MAX, SIZE_MAX);
  ASSERT_EQ(SIZE_MAX, ULONG_MAX);
  size_t size = INT_MAX + 1;
  ASSERT_LT(size, SIZE_MAX);
  char* a = new char[size];
  if (a != 0)
  {
    delete [] a;
    a = 0;
  }
}
