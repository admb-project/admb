#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adstring.hpp>

void test_ad_exit(const int exit_code);

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
  EXPECT_STREQ((char*)b(1), "one");
  EXPECT_STREQ((char*)b(2), "two");
  EXPECT_STREQ((char*)b(3), "three");
  EXPECT_STREQ((char*)b(4), "four");
}
TEST_F(test_adstring_array, constindex)
{
  adstring_array a(1, 4);
  a(1) = "one";
  a(2) = "two";
  a(3) = "three";
  a(4) = "four";

  const adstring_array b = a;

  EXPECT_EQ(b.indexmin(), 1);
  EXPECT_EQ(b.indexmax(), 4);
  EXPECT_STREQ((const char*)b(1), "one");
  EXPECT_STREQ((const char*)b(2), "two");
  EXPECT_STREQ((const char*)b(3), "three");
  EXPECT_STREQ((const char*)b(4), "four");
#ifdef DEBUG
  EXPECT_DEATH(b(5), "Assertion");
#endif
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
#include <cifstrem.h>
TEST_F(test_adstring_array, ifstream)
{
  adstring a1 = "one";
  adstring a2 = "two";
  adstring a3 = "three";

  adstring_array a;
  a += a1;
  a += a2;
  a += a3;

  ofstream ofs("test_adstring_array.txt");
  ofs << a;
  ofs.close();

  adstring_array ret(1, 4);
  ifstream ifs("test_adstring_array.txt");
  ifs >> ret;
  ifs.close();

  EXPECT_STREQ((char*)a1, (char*)ret(1));
  EXPECT_STREQ((char*)a2, (char*)ret(2));
  EXPECT_STREQ((char*)a3, (char*)ret(3));

  adstring_array ret2(1, 4);
  cifstream cifs("test_adstring_array.txt");
  cifs >> ret2;
  cifs.close();

  EXPECT_STREQ((char*)a1, (char*)ret2(1));
  EXPECT_STREQ((char*)a2, (char*)ret2(2));
  EXPECT_STREQ((char*)a3, (char*)ret2(3));
}
TEST_F(test_adstring_array, allocate_min_greaterthan_max)
{
  ad_exit=&test_ad_exit;
  adstring_array a;
  ASSERT_ANY_THROW({
    a.allocate(4, 1);
  });
}
TEST_F(test_adstring_array, null_index1)
{
  ad_exit=&test_ad_exit;
  adstring_array a;
  ASSERT_ANY_THROW({
    a(1);
  });
  ASSERT_ANY_THROW({
    a[1];
  });
}
TEST_F(test_adstring_array, const_null_index1)
{
  ad_exit=&test_ad_exit;
  const adstring_array a;
  ASSERT_ANY_THROW({
    a[1];
  });
  ASSERT_ANY_THROW({
    a(1);
  });
}
