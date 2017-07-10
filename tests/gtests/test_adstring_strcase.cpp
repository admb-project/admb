#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adstring.hpp>

class test_adstring: public ::testing::Test {};

/**
 * Tests for errors in "void adstring::to_lower(void)"
 */
TEST_F(test_adstring, strcase_01)
{
  adstring a = "abc-123";
  a.to_upper();
  adstring expected = "ABC-123";
  EXPECT_STREQ((char*)expected, (char*)a);
}
/**
 * Tests for errors in "adstring to_upper(adstring& s)"
 */
TEST_F(test_adstring, strcase_02)
{
  adstring a = "abc-123";
  adstring b = to_upper(a);
  adstring expected = "ABC-123";
  EXPECT_STREQ((char*)expected, (char*)b);
}
/**
 * Tests for errors in "void adstring::to_upper(void)"
 */
TEST_F(test_adstring, strcase_03)
{
  adstring a = "ABC-123";
  a.to_lower();
  adstring expected = "abc-123";
  EXPECT_STREQ((char*)expected, (char*)a);
}
/**
 * Tests for errors in "adstring to_lower(adstring& s)"
 */
TEST_F(test_adstring, strcase_04)
{
  adstring a = "ABC-123";
  adstring b = to_lower(a);
  adstring expected = "abc-123";
  EXPECT_STREQ((char*)expected, (char*)b);
}
/**
 * Tests for errors in "adstring_array to_lower(adstring_array& s)"
 */
TEST_F(test_adstring, strcase2_05)
{
  adstring_array a(1, 3);
  a(1) = "ABC-123";
  a(2) = "ABC-123";
  a(3) = "ABC-123";
  adstring_array b = to_lower(a);
  adstring expected = "abc-123";
  EXPECT_STREQ((char*)expected, (char*)b(1));
  EXPECT_STREQ((char*)expected, (char*)b(2));
  EXPECT_STREQ((char*)expected, (char*)b(3));
}
/**
 * Tests for errors in "adstring_array to_upper(adstring_array& s)"
 */
TEST_F(test_adstring, strcase2_06)
{
  adstring_array a(1, 3);
  a(1) = "abc-123";
  a(2) = "abc-123";
  a(3) = "abc-123";
  adstring_array b = to_upper(a);
  adstring expected = "ABC-123";
  EXPECT_STREQ((char*)expected, (char*)b(1));
  EXPECT_STREQ((char*)expected, (char*)b(2));
  EXPECT_STREQ((char*)expected, (char*)b(3));
}
