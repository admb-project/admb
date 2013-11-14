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
TEST_F(test_df_file, instance_INT_MAX_plus_1)
{
  ASSERT_NO_THROW(DF_FILE instance(INT_MAX + 1));
}
/*
TEST_F(test_df_file, allocate_INT_MAX_plus_1)
{
  ASSERT_LT(INT_MAX, LONG_MAX);
  ASSERT_LT(LONG_MAX, SIZE_MAX);
  ASSERT_EQ(SIZE_MAX, ULONG_MAX);
  size_t size = INT_MAX + 1;
  ASSERT_LT(size, SIZE_MAX);
  //Cannot allocate for size > INT_MAX 
  try
  {
    new char[size];
  }
  catch(...)
  {
    return;
  }
  FAIL();
}
*/
TEST_F(test_df_file, write_read_int)
{
  DF_FILE buffer(sizeof(int));
  const int expected = __LINE__;
  buffer.fwrite(expected);
  int integer = 0;
  buffer.fread(integer);
  ASSERT_EQ(expected, integer);
}
TEST_F(test_df_file, write_read_int_3x)
{
  DF_FILE buffer(sizeof(int));

  const int expected = __LINE__;
  buffer.fwrite(expected);

  const int expected2 = __LINE__;
  buffer.fwrite(expected2);

  const int expected3 = __LINE__;
  buffer.fwrite(expected3);

  int integer3 = 0;
  buffer.fread(integer3);
  ASSERT_EQ(expected3, integer3);

  int integer2 = 0;
  buffer.fread(integer2);
  ASSERT_EQ(expected2, integer2);

  int integer = 0;
  buffer.fread(integer);
  ASSERT_EQ(expected, integer);
}
TEST_F(test_df_file, write_read_double)
{
  DF_FILE buffer(sizeof(double));
  const double expected = __LINE__;
  buffer.fwrite(expected);

  double number = 0;
  buffer.fread(number);
  ASSERT_EQ(expected, number);
}
TEST_F(test_df_file, write_read_char_array11)
{
  DF_FILE buffer(50);
  const char expected[11] = "12345-6789";
  buffer.fwrite(expected, 11);

  char array[11] = "\0";
  buffer.fread(&array[0], 11);
  ASSERT_STREQ(expected, array);
}
TEST_F(test_df_file, write_read_ptr)
{
  DF_FILE buffer(50);
  int expected = __LINE__;
  int* ptr = &expected;
  int* number = 0;
  //buffer.fwrite(ptr);
  //buffer.fread(number);
  ASSERT_EQ(&expected, number);
}
