#include <gtest/gtest.h>
#include <fvar.hpp>

class test_df_file:public ::testing::Test {};

TEST_F(test_df_file, signs)
{
  int x = 5;
  int* y = &x;
  int z = 0;

  z =- *y;

  ASSERT_EQ(-x, z);
}
/*
TEST_F(test_df_file, strtok)
{
  char args[100];
  strcpy(args, "afdk dkfjdk dkfjkdj kdsjfk dkjfkj\0");
  cout << args << endl;
  char* ca2 = strtok(args, " ");
  cout << "\"" << ca2 << "\"" << endl;
  char* ca3 = strtok(NULL, " ");
  cout << "\"" << ca3 << "\"" << endl;
  char* ca4 = strtok('\0', " ");
  cout << "\"" << ca4 << "\"" << endl;
  //char* ca5 = strtok((char*)"\0", " ");
  //cout << "\"" << ca5 << "\"" << endl;
}
*/
TEST_F(test_df_file, allocate_UULONG_MAX)
{
  unsigned long long int size = ULLONG_MAX;
  ASSERT_EQ(ULLONG_MAX, size);
  char* array = 0;
  ASSERT_NO_THROW(array = new char[size]);
  delete [] array;
  array = 0;
}
TEST_F(test_df_file, instance_LONG_MAX)
{
  DF_FILE dffile;
  dffile.buff = new char[LONG_MAX];
}
/*
TEST_F(test_df_file, instance_LLONG_MAX)
{
  ASSERT_NO_THROW(DF_FILE df_file(LLONG_MAX));
}
TEST_F(test_df_file, instance_ULLONG_MAX)
{
  ASSERT_NO_THROW(DF_FILE df_file(ULLONG_MAX));
}
*/
