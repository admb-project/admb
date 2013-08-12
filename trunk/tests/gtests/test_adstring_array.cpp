#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adstring.hpp>

class test_adstring_array: public ::testing::Test {};

TEST_F(test_adstring_array, equals)
{
  adstring_array a(1, 4);
  a(1) = "one";
  a(2) = "two";
  a(3) = "three";
  a(4) = "four";
  adstring_array b;
  b = a;

  EXPECT_EQ(b.indexmin(), 1);
  EXPECT_EQ(b.indexmax(), 4);
  EXPECT_EQ(b(1), adstring("one"));
  EXPECT_EQ(b(2), adstring("two"));
  EXPECT_EQ(b(3), adstring("three"));
  EXPECT_EQ(b(4), adstring("four"));
}
