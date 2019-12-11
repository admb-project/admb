#include <gtest/gtest.h>
#include <stdint.h>
#include <limits.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

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
  ASSERT_STREQ("cccc", strtok(NULL, " "));
  ASSERT_STREQ("dddd", strtok(NULL, " "));
  ASSERT_STREQ("eeee", strtok(NULL, " "));
  ASSERT_STREQ("ffff", strtok(NULL, " "));
  ASSERT_STREQ("gggg", strtok(NULL, " "));
  ASSERT_TRUE(strtok(NULL, " ") == NULL);
}
TEST_F(test_df_file, allocate_INT_MAX)
{
  size_t size = INT_MAX/2;
  char* a = 0;
  ASSERT_NO_THROW(a = new char[size]);
  delete [] a;
  a = 0;
}
TEST_F(test_df_file, constructor_size)
{
  ad_exit=&test_ad_exit;
  ad_comm::argc = 0;
  ASSERT_NO_THROW(DF_FILE df_file(INT_MAX/2));
}
TEST_F(test_df_file, union_sizeof)
{
  DF_FILE df_file(INT_MAX/2);
  ASSERT_EQ(sizeof(df_file.fourb), sizeof(df_file.offset));
  ad_comm::argc = 0;
}
TEST_F(test_df_file, constructor_max)
{
  ad_exit=&test_ad_exit;
  ASSERT_ANY_THROW(
#if defined(_MSC_VER) || defined(__MINGW64__)
    size_t maxsize = std::numeric_limits<unsigned int>::max();
#elif defined(__x86_64)
    size_t maxsize = std::numeric_limits<OFF_T>::max();
#else
    size_t maxsize = std::numeric_limits<size_t>::max();
#endif
    maxsize -= sizeof(OFF_T) - 1;
    DF_FILE df_file(maxsize)
  );
}
TEST_F(test_df_file, constructor_max_limit)
{
  ad_exit=&test_ad_exit;
#if defined(_MSC_VER)
  ASSERT_NO_THROW(
    size_t maxsize = std::numeric_limits<unsigned int>::max();
#elif defined(__MINGW64__)
  ASSERT_ANY_THROW(
    size_t maxsize = std::numeric_limits<unsigned int>::max();
#elif defined(__x86_64)
  ASSERT_ANY_THROW(
    size_t maxsize = std::numeric_limits<OFF_T>::max();
#else
  ASSERT_ANY_THROW(
    size_t maxsize = std::numeric_limits<size_t>::max();
#endif
    maxsize -= sizeof(OFF_T);
    DF_FILE df_file(maxsize + 1)
  );
}
TEST_F(test_df_file, allocate_max)
{
  size_t size = INT_MAX/2;
  try
  {
    char* p = new char[size];
    delete [] p;
    p = 0;
  }
  catch(...)
  {
    FAIL();
  }
}
TEST_F(test_df_file, write_read_int)
{
  size_t sizeofint = sizeof(int);
  DF_FILE buffer(sizeofint);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  gradient_structure::no_derivatives = 0;

  const int expected = __LINE__;
  buffer.fwrite(expected);
  ASSERT_EQ(sizeofint, buffer.offset);
  ASSERT_EQ(sizeofint, buffer.toffset);

  int integer = 0;
  buffer.fread(integer);
  ASSERT_EQ(expected, integer);
}
TEST_F(test_df_file, write_read_int_asvoidpointer)
{
  size_t sizeofint = sizeof(int);
  DF_FILE buffer(sizeofint);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  gradient_structure::no_derivatives = 0;

  const int expected = __LINE__;
  buffer.fwrite(&expected, sizeofint);

  ASSERT_EQ(sizeofint, buffer.offset);
  ASSERT_EQ(sizeofint, buffer.toffset);

  int integer = 0;
  buffer.fread(&integer, sizeofint);
  ASSERT_EQ(expected, integer);
}
TEST_F(test_df_file, write_read_double)
{
  const size_t us = sizeof(size_t) + 2;
  size_t sizeofdouble = sizeof(double);
  DF_FILE buffer(sizeofdouble + us);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  gradient_structure::no_derivatives = 0;

  const double expected = 11.34567;
  buffer.fwrite(expected);
  ASSERT_EQ(sizeofdouble, buffer.offset);
  ASSERT_EQ(sizeofdouble, buffer.toffset);

  double value = 0;
  buffer.fread(value);
  ASSERT_EQ(expected, value);
}
TEST_F(test_df_file, write_read_double_asvoidpointer)
{
  const size_t us = sizeof(size_t) + 2;
  size_t sizeofdouble = sizeof(double);
  DF_FILE buffer(sizeofdouble + us);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  gradient_structure::no_derivatives = 0;

  const double expected = 11.34567;
  buffer.fwrite(&expected, sizeofdouble);
  ASSERT_EQ(sizeofdouble, buffer.offset);
  ASSERT_EQ(sizeofdouble, buffer.toffset);

  double value = 0;
  buffer.fread(&value, sizeofdouble);
  ASSERT_EQ(expected, value);
}
TEST_F(test_df_file, memcpy_ptr)
{
  const size_t size = sizeof(uintptr_t);
  char array[size];

  size_t expected = __LINE__;
  uintptr_t src = (uintptr_t)&expected;
  memcpy(&array, &src, size); 

  uintptr_t dst;
  memcpy(&dst, &array, size); 

  ASSERT_EQ(src, dst);

  size_t* value = (size_t*)dst;
  ASSERT_EQ(expected, *value);
}
TEST_F(test_df_file, write_read_voidpointer_asvoidpointer)
{
  const size_t us = sizeof(size_t) + 2;
  size_t size = sizeof(uintptr_t);
  DF_FILE buffer(size + us);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  gradient_structure::no_derivatives = 0;

  size_t expected = __LINE__;
  uintptr_t src = (uintptr_t)&expected;
  buffer.fwrite(&src, size);
  ASSERT_EQ(size, buffer.offset);
  ASSERT_EQ(size, buffer.toffset);

  uintptr_t dst;
  buffer.fread(&dst, size);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  ASSERT_EQ(src, dst);

  size_t* value = (size_t*)dst;
  ASSERT_EQ(expected, *value);
}
TEST_F(test_df_file, write_read_voidpointer)
{
  const size_t us = sizeof(size_t) + 2;
  size_t size = sizeof(uintptr_t);
  DF_FILE buffer(size + us);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  gradient_structure::no_derivatives = 0;

  size_t expected = __LINE__;
  buffer.fwrite((void*)&expected);
  ASSERT_EQ(size, buffer.offset);
  ASSERT_EQ(size, buffer.toffset);

/*
  size_t* actual = 0;
  buffer.fread((void*)&actual);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  ASSERT_EQ(expected, actual);
*/
}
TEST_F(test_df_file, write_read_int_bigbuffer)
{
  //const size_t us = sizeof(size_t) + 2;
  const size_t size = sizeof(int) * 2;

  DF_FILE buffer(size);

  const int expected = __LINE__;
  buffer.fwrite(expected);
  ASSERT_EQ(sizeof(int), buffer.offset);
  ASSERT_EQ(sizeof(int), buffer.toffset);

  int integer = 0;
  buffer.fread(integer);
  ASSERT_EQ(expected, integer);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);
}
TEST_F(test_df_file, write_read_int_3x_bigbuffer)
{
  //const size_t us = sizeof(size_t) + 2;
  const size_t size = sizeof(int) * 10;

  DF_FILE buffer(size);

  const int expected = __LINE__;
  buffer.fwrite(expected);
  ASSERT_EQ(sizeof(int), buffer.offset);
  ASSERT_EQ(sizeof(int), buffer.toffset);

  const int expected2 = __LINE__;
  buffer.fwrite(expected2);
  ASSERT_EQ(sizeof(int) * 2, buffer.offset);
  ASSERT_EQ(sizeof(int) * 2, buffer.toffset);

  const int expected3 = __LINE__;
  buffer.fwrite(expected3);
  ASSERT_EQ(sizeof(int) * 3, buffer.offset);
  ASSERT_EQ(sizeof(int) * 3, buffer.toffset);

  int integer3 = 0;
  buffer.fread(integer3);
  ASSERT_EQ(expected3, integer3);
  ASSERT_EQ(sizeof(int) * 2, buffer.offset);
  ASSERT_EQ(sizeof(int) * 2, buffer.toffset);

  int integer2 = 0;
  buffer.fread(integer2);
  ASSERT_EQ(expected2, integer2);
  ASSERT_EQ(sizeof(int), buffer.offset);
  ASSERT_EQ(sizeof(int), buffer.toffset);

  int integer = 0;
  buffer.fread(integer);
  ASSERT_EQ(expected, integer);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);
}
TEST_F(test_df_file, write_read_int_3x_exactbuffer)
{
  const size_t us = sizeof(size_t) + 2;
  const size_t size = sizeof(int) * 3 + us;

  DF_FILE buffer(size);

  const int expected = __LINE__;
  buffer.fwrite(expected);
  ASSERT_EQ(sizeof(int), buffer.offset);
  ASSERT_EQ(sizeof(int), buffer.toffset);

  const int expected2 = __LINE__;
  buffer.fwrite(expected2);
  ASSERT_EQ(sizeof(int) * 2, buffer.offset);
  ASSERT_EQ(sizeof(int) * 2, buffer.toffset);

  const int expected3 = __LINE__;
  buffer.fwrite(expected3);
  ASSERT_EQ(sizeof(int) * 3, buffer.offset);
  ASSERT_EQ(sizeof(int) * 3, buffer.toffset);

  int integer3 = 0;
  buffer.fread(integer3);
  ASSERT_EQ(expected3, integer3);
  ASSERT_EQ(sizeof(int) * 2, buffer.offset);
  ASSERT_EQ(sizeof(int) * 2, buffer.toffset);

  int integer2 = 0;
  buffer.fread(integer2);
  ASSERT_EQ(expected2, integer2);
  ASSERT_EQ(sizeof(int), buffer.offset);
  ASSERT_EQ(sizeof(int), buffer.toffset);

  int integer = 0;
  buffer.fread(integer);
  ASSERT_EQ(expected, integer);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);
}
TEST_F(test_df_file, write_read_int_3x_nobuffer)
{
  const size_t size = sizeof(int);

  DF_FILE buffer(size);

  const int expected = __LINE__;
  buffer.fwrite(expected);
  ASSERT_EQ(sizeof(int), buffer.offset);
  ASSERT_EQ(sizeof(int), buffer.toffset);

  const int expected2 = __LINE__;
  buffer.fwrite(expected2);
  ASSERT_EQ(sizeof(int), buffer.offset);
  ASSERT_EQ(sizeof(int), buffer.toffset);

  const int expected3 = __LINE__;
  buffer.fwrite(expected3);
  ASSERT_EQ(sizeof(int), buffer.offset);
  ASSERT_EQ(sizeof(int), buffer.toffset);

  int integer3 = 0;
  buffer.fread(integer3);
  ASSERT_EQ(expected3, integer3);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  int integer2 = 0;
  buffer.fread(integer2);
  ASSERT_EQ(expected2, integer2);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);

  int integer = 0;
  buffer.fread(integer);
  ASSERT_EQ(expected, integer);
  ASSERT_EQ(0, buffer.offset);
  ASSERT_EQ(0, buffer.toffset);
}
TEST_F(test_df_file, write_read_double2)
{
  const size_t us = sizeof(size_t) + 2;

  DF_FILE buffer(sizeof(double) + us);
  const double expected = __LINE__;
  buffer.fwrite(expected);

  double number = 0;
  buffer.fread(number);
  ASSERT_EQ(expected, number);
}
TEST_F(test_df_file, write_read_char_array11)
{
  const size_t us = sizeof(size_t) + 2;
  DF_FILE buffer(us + 11);
  const char expected[11] = "12345-6789";
  buffer.fwrite(expected, 11);

  char array[11] = "\0";
  buffer.fread(&array[0], 11);
  ASSERT_STREQ(expected, array);
}
