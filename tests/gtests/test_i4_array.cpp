#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_i4_array: public ::testing::Test {};

TEST_F(test_i4_array, default)
{
  i4_array a;
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i4_array, inputoutput)
{
  i4_array a(1, 4);
  a(2).allocate(1, 3, 1, 2, 1, 1);

  a(2, 1, 1, 1) = 1;
  a(2, 1, 2, 1) = 2;
  a(2, 2, 1, 1) = 3;
  a(2, 2, 2, 1) = 4;
  a(2, 3, 1, 1) = 5;
  a(2, 3, 2, 1) = 6;

  ofstream output("test_i4_array.txt");
  output << a;
  output.close();

  i4_array b(1, 4);
  b(2).allocate(1, 3, 1, 2, 1, 1);

  ifstream input("test_i4_array.txt");
  input >> b;
  input.close();

  ASSERT_EQ(b(2, 1, 1, 1), 1);
  ASSERT_EQ(b(2, 1, 2, 1), 2);
  ASSERT_EQ(b(2, 2, 1, 1), 3);
  ASSERT_EQ(b(2, 2, 2, 1), 4);
  ASSERT_EQ(b(2, 3, 1, 1), 5);
  ASSERT_EQ(b(2, 3, 2, 1), 6);
}
