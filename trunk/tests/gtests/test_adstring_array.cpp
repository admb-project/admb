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
TEST_F(test_adstring_array, append_distinct)
{
  adstring a1 = "one";
  adstring a2 = "two";
  adstring a3 = "three";

  adstring_array a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.indexmin(), 0);
  EXPECT_EQ(a.indexmax(), 0);

  a.append_distinct(a1);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.indexmin(), 1);
  EXPECT_EQ(a.indexmax(), 1);
  EXPECT_STREQ((char*)a1, (char*)a(1));

  a.append_distinct(a2);
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.indexmin(), 1);
  EXPECT_EQ(a.indexmax(), 2);
  EXPECT_STREQ((char*)a2, (char*)a(2));

  a.append_distinct(a3);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.indexmin(), 1);
  EXPECT_EQ(a.indexmax(), 3);
  EXPECT_STREQ((char*)a3, (char*)a(3));

  a.append_distinct(a2);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.indexmin(), 1);
  EXPECT_EQ(a.indexmax(), 4);
  EXPECT_STREQ((char*)a1, (char*)a(1));
  EXPECT_STREQ((char*)a2, (char*)a(2));
  EXPECT_STREQ((char*)a3, (char*)a(3));
  EXPECT_STREQ((char*)a2, (char*)a(4));
}
TEST_F(test_adstring_array, operator_plus_equal)
{
  adstring a1 = "one";
  adstring a2 = "two";
  adstring a3 = "three";

  adstring_array a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.indexmin(), 0);
  EXPECT_EQ(a.indexmax(), 0);

  a += a1;
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.indexmin(), 1);
  EXPECT_EQ(a.indexmax(), 1);
  EXPECT_STREQ((char*)a1, (char*)a(1));

  a += a2;
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.indexmin(), 1);
  EXPECT_EQ(a.indexmax(), 2);
  EXPECT_STREQ((char*)a2, (char*)a(2));

  a += a3;
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.indexmin(), 1);
  EXPECT_EQ(a.indexmax(), 3);
  EXPECT_STREQ((char*)a3, (char*)a(3));

  a += a2;
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.indexmin(), 1);
  EXPECT_EQ(a.indexmax(), 4);
  EXPECT_STREQ((char*)a1, (char*)a(1));
  EXPECT_STREQ((char*)a2, (char*)a(2));
  EXPECT_STREQ((char*)a3, (char*)a(3));
  EXPECT_STREQ((char*)a2, (char*)a(4));
}
