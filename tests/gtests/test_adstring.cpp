#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adstring.hpp>
#include <admodel.h>
#include <climits>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_adstring: public ::testing::Test {};

TEST_F(test_adstring, default_constructor)
{
  adstring a;

  EXPECT_EQ(0, length(a));
  EXPECT_EQ(0, a.size());
  EXPECT_EQ(0, a.buff_size());
  //clist length includes '\0'
  EXPECT_EQ(1, a.length());
}
TEST_F(test_adstring, assignment_operator_adstring)
{
  adstring a;
  a = "tests_adstring";

  EXPECT_EQ(14, length(a));
  EXPECT_EQ(14, a.size());
  EXPECT_EQ(14, a.buff_size());
  //clist length includes '\0'
  //JCA: Should be 15?
  EXPECT_EQ(1, a.length());
}
TEST_F(test_adstring, assignment_operator_char)
{
  adstring a;
  const char c = 'c';
  a = c;

  char a1 = a[size_t(1)];
  EXPECT_EQ('c', a1);
  EXPECT_EQ(1, length(a));
  EXPECT_EQ(1, a.size());
  EXPECT_EQ(1, a.buff_size());
  //clist length includes '\0'
  //JCA: Should be 15?
  EXPECT_EQ(1, a.length());
}
TEST_F(test_adstring, to_upper_and_lower)
{
  adstring a;
  a = "tests_adstring";
  a.to_upper();

  EXPECT_EQ('T', a(1));
  EXPECT_EQ('E', a(2));
  EXPECT_EQ('S', a(3));
  EXPECT_EQ('T', a(4));
  EXPECT_EQ('S', a(5));
  EXPECT_EQ('_', a(6));
  EXPECT_EQ('A', a(7));
  EXPECT_EQ('D', a(8));
  EXPECT_EQ('S', a(9));
  EXPECT_EQ('T', a(10));
  EXPECT_EQ('R', a(11));
  EXPECT_EQ('I', a(12));
  EXPECT_EQ('N', a(13));
  EXPECT_EQ('G', a(14));

  a.to_lower();

  EXPECT_EQ('t', a(1));
  EXPECT_EQ('e', a(2));
  EXPECT_EQ('s', a(3));
  EXPECT_EQ('t', a(4));
  EXPECT_EQ('s', a(5));
  EXPECT_EQ('_', a(6));
  EXPECT_EQ('a', a(7));
  EXPECT_EQ('d', a(8));
  EXPECT_EQ('s', a(9));
  EXPECT_EQ('t', a(10));
  EXPECT_EQ('r', a(11));
  EXPECT_EQ('i', a(12));
  EXPECT_EQ('n', a(13));
  EXPECT_EQ('g', a(14));
}
TEST_F(test_adstring, val_vs_atoi)
{
  adstring a;
  a = "98765";

  EXPECT_EQ(98765, atoi(a));
  EXPECT_EQ(98765, val(a));

  int v = -1, code;
  val(a, v, code);
  EXPECT_EQ(98765, v);
  EXPECT_EQ(0, code);
}
TEST_F(test_adstring, val_vs_atoi_non_number)
{
  adstring a;
  a = "abc";

  EXPECT_EQ(0, atoi(a));

  int v = -1, code;
  val(a, v, code);
  EXPECT_EQ(-1, v);
  EXPECT_EQ(1, code);
}
TEST_F(test_adstring, str)
{
  const int number = 123456789;
  adstring a;
  a = str(number);

  EXPECT_EQ('1', a(1));
  EXPECT_EQ('2', a(2));
  EXPECT_EQ('3', a(3));
  EXPECT_EQ('4', a(4));
  EXPECT_EQ('5', a(5));
  EXPECT_EQ('6', a(6));
  EXPECT_EQ('7', a(7));
  EXPECT_EQ('8', a(8));
  EXPECT_EQ('9', a(9));
}
TEST_F(test_adstring, operator_plus_equal)
{
  adstring a;
  a = "1234";

  EXPECT_EQ('1', a(1));
  EXPECT_EQ('2', a(2));
  EXPECT_EQ('3', a(3));
  EXPECT_EQ('4', a(4));

  a += "abcd";

  EXPECT_EQ('1', a(1));
  EXPECT_EQ('2', a(2));
  EXPECT_EQ('3', a(3));
  EXPECT_EQ('4', a(4));
  EXPECT_EQ('a', a(5));
  EXPECT_EQ('b', a(6));
  EXPECT_EQ('c', a(7));
  EXPECT_EQ('d', a(8));
}
TEST_F(test_adstring, substring)
{
  adstring a;
  a = "1234adcd";

  adstring substring;
  substring = "4ad";

  EXPECT_EQ(4, pos(substring, a));

  adstring b;
  b = a(4, 6);
  EXPECT_EQ('4', b(1));
  EXPECT_EQ('a', b(2));
  EXPECT_EQ('d', b(3));
}
TEST_F(test_adstring, operator_substring)
{
  adstring a;
  a = "1234adcd";

  adstring b;
  b = a(3, 6);

  EXPECT_EQ(false, a == b);
  EXPECT_EQ(true, b == adstring("34ad"));
  EXPECT_EQ(4, length(b));
}
TEST_F(test_adstring, operator_equalequal)
{
  adstring a;
  a = "1234adcd";

  adstring b;
  b = "4ad";

  adstring c;
  c = a;

  EXPECT_EQ(true, a == a);
  EXPECT_EQ(false, a == b);
  EXPECT_EQ(true, a == c);
}
TEST_F(test_adstring, operator_notequal)
{
  adstring a;
  a = "1234adcd";

  adstring b;
  b = "4ad";

  adstring c;
  c = a;

  EXPECT_EQ(false, a != a);
  EXPECT_EQ(true, a != b);
  EXPECT_EQ(false, a != c);
}
TEST_F(test_adstring, val_hexadecimal)
{
  adstring a("0x2E6");
  int actual = val(a);
  EXPECT_EQ(742, actual);
}
TEST_F(test_adstring, val_integer)
{
  adstring a("-742");
  int actual = val(a);
  EXPECT_EQ(-742, actual);
}
TEST_F(test_adstring, chr)
{
  int c = (int)'c';
  adstring actual = chr(c);
  EXPECT_STREQ("c", (char*)actual);
}
#ifndef _WIN32
TEST_F(test_adstring, chr_uchar_max_plus_1)
{
  int c = (int)UCHAR_MAX + 1;
  EXPECT_DEATH(chr(c), "Assertion");
}
TEST_F(test_adstring, chr_negative)
{
  int c = -1;
  EXPECT_DEATH(chr(c), "Assertion");
}
TEST_F(test_adstring, itoa)
{
  int i = 701;
  adstring actual = itoa(i, 10);
  EXPECT_STREQ((char*)"701", (char*)actual);

  adstring negative = itoa(-i, 10);
  EXPECT_STREQ((char*)"-701", (char*)negative);

  adstring actualrneg = itoa(i, -10);
  EXPECT_STREQ((char*)"701", (char*)actualrneg);

  adstring negativerneg = itoa(-i, -10);
  EXPECT_STREQ((char*)"-701", (char*)negativerneg);

  adstring base2 = itoa(i, 2);
  EXPECT_STREQ((char*)"1010111101", (char*)base2);

  adstring negbase2 = itoa(-i, 2);
  EXPECT_STREQ((char*)"-1010111101", (char*)negbase2);

#ifndef OPT_LIB
  EXPECT_DEATH(itoa(i, 0), "Assertion");
  EXPECT_DEATH(itoa(i, 1), "Assertion");
#endif
}
TEST_F(test_adstring, itoa_INT_MAX)
{
  adstring int_min = itoa(INT_MIN, 10);
  EXPECT_STREQ((char*)"-2147483648", (char*)int_min);

  adstring actual = itoa(INT_MAX, 10);
  EXPECT_STREQ((char*)"2147483647", (char*)actual);

  adstring negative = itoa(-INT_MAX, 10);
  EXPECT_STREQ((char*)"-2147483647", (char*)negative);
}
TEST_F(test_adstring, itoa_INT_MAX_base2)
{
  adstring int_min = itoa(INT_MIN, 2);
  EXPECT_STREQ((char*)"-10000000000000000000000000000000", (char*)int_min);

  adstring actual = itoa(INT_MAX, 2);
  EXPECT_STREQ((char*)"1111111111111111111111111111111", (char*)actual);

  adstring negative = itoa(-INT_MAX, 2);
  EXPECT_STREQ((char*)"-1111111111111111111111111111111", (char*)negative);
}
#endif
TEST_F(test_adstring, realloc)
{
  adstring a("-742");
  char expected[] = "Reallocation.";
  a.realloc(expected);
  EXPECT_STREQ(expected, (char*)a);
}
TEST_F(test_adstring, clist_length_with_max_zero)
{
  adstring b;
  EXPECT_EQ(-1, b.length(0));
  adstring a(b);
  EXPECT_EQ(-1, a.length(0));
}
TEST_F(test_adstring, clist_length_with_max_one)
{
  adstring b;
  EXPECT_EQ(1, b.length(1));
  adstring a(b);
  EXPECT_EQ(-1, a.length(1));
}
TEST_F(test_adstring, clist_chain_list)
{
  adstring a;
  EXPECT_EQ(1, a.length());
  adstring b(a);
  EXPECT_EQ(2, b.length());
  adstring c(b);
  EXPECT_EQ(3, c.length());
  EXPECT_STREQ((char*)a, (char*)b);
  EXPECT_STREQ((char*)a, (char*)c);
}
TEST_F(test_adstring, clist_nested_destructors)
{
  adstring a;
  EXPECT_EQ(1, a.length());
  {
    adstring b(a);
    EXPECT_EQ(2, b.length());
    {
      adstring c(b);
      EXPECT_EQ(3, c.length());
    }
    EXPECT_EQ(2, b.length());
  }
  EXPECT_EQ(1, a.length());
}
#ifndef __MINGW32__
TEST_F(test_adstring, str_greater_than_zero)
{
  adstring str(double x, int minwidth, int decplaces);

  double x = 12345.12345678901234567890;
  adstring a = str(x, 6, 0);
  EXPECT_STREQ((char*)a, (char*)" 12345");
  a = str(x, 5, 0);
  EXPECT_STREQ((char*)a, (char*)"12345");
  a = str(x, 4, 0);
  EXPECT_STREQ((char*)a, (char*)"12345");
  a = str(x, 3, 0);
  EXPECT_STREQ((char*)a, (char*)"12345");
  a = str(x, 2, 0);
  EXPECT_STREQ((char*)a, (char*)"12345");
  a = str(x, 1, 0);
  EXPECT_STREQ((char*)a, (char*)"12345");
  a = str(x, 0, 0);
  EXPECT_STREQ((char*)a, (char*)"12345");

  a = str(x, 8, 1);
  EXPECT_STREQ((char*)"  12345.1", (char*)a);
  a = str(x, 7, 1);
  EXPECT_STREQ((char*)" 12345.1", (char*)a);
  a = str(x, 6, 1);
  EXPECT_STREQ((char*)"12345.1", (char*)a);
  a = str(x, 5, 1);
  EXPECT_STREQ((char*)"12345.1", (char*)a);
  a = str(x, 4, 1);
  EXPECT_STREQ((char*)"12345.1", (char*)a);
  a = str(x, 3, 1);
  EXPECT_STREQ((char*)"12345.1", (char*)a);
  a = str(x, 2, 1);
  EXPECT_STREQ((char*)"12345.1", (char*)a);
  a = str(x, 1, 1);
  EXPECT_STREQ((char*)"12345.1", (char*)a);
  a = str(x, 0, 1);
  EXPECT_STREQ((char*)"12345.1", (char*)a);

  a = str(x, 8, 2);
  EXPECT_STREQ((char*)"  12345.12", (char*)a);
  a = str(x, 7, 2);
  EXPECT_STREQ((char*)" 12345.12", (char*)a);
  a = str(x, 6, 2);
  EXPECT_STREQ((char*)"12345.12", (char*)a);
  a = str(x, 5, 2);
  EXPECT_STREQ((char*)"12345.12", (char*)a);
  a = str(x, 4, 2);
  EXPECT_STREQ((char*)"12345.12", (char*)a);
  a = str(x, 3, 2);
  EXPECT_STREQ((char*)"12345.12", (char*)a);
  a = str(x, 2, 2);
  EXPECT_STREQ((char*)"12345.12", (char*)a);
  a = str(x, 1, 2);
  EXPECT_STREQ((char*)"12345.12", (char*)a);
  a = str(x, 0, 2);
  EXPECT_STREQ((char*)"12345.12", (char*)a);

  a = str(x, 8, 12);
  EXPECT_STREQ((char*)"  12345.12345678901", (char*)a);
  a = str(x, 7, 12);
  EXPECT_STREQ((char*)" 12345.12345678901", (char*)a);
  a = str(x, 6, 12);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 5, 12);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 4, 12);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 3, 12);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 2, 12);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 1, 12);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 0, 12);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);

  a = str(x, 8, 11);
  EXPECT_STREQ((char*)"  12345.12345678901", (char*)a);
  a = str(x, 7, 11);
  EXPECT_STREQ((char*)" 12345.12345678901", (char*)a);
  a = str(x, 6, 11);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 5, 11);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 4, 11);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 3, 11);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 2, 11);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 1, 11);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);
  a = str(x, 0, 11);
  EXPECT_STREQ((char*)"12345.12345678901", (char*)a);

  a = str(x, 8, 10);
  EXPECT_STREQ((char*)"  12345.1234567890", (char*)a);
  a = str(x, 7, 10);
  EXPECT_STREQ((char*)" 12345.1234567890", (char*)a);
  a = str(x, 6, 10);
  EXPECT_STREQ((char*)"12345.1234567890", (char*)a);
  a = str(x, 5, 10);
  EXPECT_STREQ((char*)"12345.1234567890", (char*)a);
  a = str(x, 4, 10);
  EXPECT_STREQ((char*)"12345.1234567890", (char*)a);
  a = str(x, 3, 10);
  EXPECT_STREQ((char*)"12345.1234567890", (char*)a);
  a = str(x, 2, 10);
  EXPECT_STREQ((char*)"12345.1234567890", (char*)a);
  a = str(x, 1, 10);
  EXPECT_STREQ((char*)"12345.1234567890", (char*)a);
  a = str(x, 0, 10);
  EXPECT_STREQ((char*)"12345.1234567890", (char*)a);

  a = str(x, 18, -1);
  EXPECT_STREQ((char*)"  1.2345123457e+04", (char*)a);
  a = str(x, 17, -1);
  EXPECT_STREQ((char*)" 1.2345123457e+04", (char*)a);
  a = str(x, 16, -1);
  EXPECT_STREQ((char*)" 1.234512346e+04", (char*)a);

  a = str(x, 10, -1);
  EXPECT_STREQ((char*)" 1.235e+04", (char*)a);
  a = str(x, 9, -1);
  EXPECT_STREQ((char*)" 1.23e+04", (char*)a);
  a = str(x, 8, -1);
  EXPECT_STREQ((char*)" 1.2e+04", (char*)a);
  a = str(x, 7, -1);
  EXPECT_STREQ((char*)"   1e+04", (char*)a);
  a = str(x, 6, -1);
  EXPECT_STREQ((char*)"1.234512e+04", (char*)a);
  a = str(x, 5, -1);
  EXPECT_STREQ((char*)"1.234512e+04", (char*)a);
  a = str(x, 4, -1);
  EXPECT_STREQ((char*)"1.234512e+04", (char*)a);
  a = str(x, 3, -1);
  EXPECT_STREQ((char*)"1.234512e+04", (char*)a);
  a = str(x, 2, -1);
  EXPECT_STREQ((char*)"1.234512e+04", (char*)a);
  a = str(x, 1, -1);
  EXPECT_STREQ((char*)"1.234512e+04", (char*)a);
  a = str(x, 0, -1);
  EXPECT_STREQ((char*)"1.234512e+04", (char*)a);
}
TEST_F(test_adstring, str_less_than_zero)
{
  adstring str(double x, int minwidth, int decplaces);

  double x = 0.12345678901234567890;
  adstring a = str(x, 18, -1);
  EXPECT_STREQ((char*)"  1.2345678901e-01", (char*)a);
  a = str(x, 17, -1);
  EXPECT_STREQ((char*)" 1.2345678901e-01", (char*)a);
  a = str(x, 16, -1);
  EXPECT_STREQ((char*)" 1.234567890e-01", (char*)a);
  a = str(x, 9, -1);
  EXPECT_STREQ((char*)" 1.23e-01", (char*)a);
  a = str(x, 8, -1);
  EXPECT_STREQ((char*)" 1.2e-01", (char*)a);
  a = str(x, 7, -1);
  EXPECT_STREQ((char*)"   1e-01", (char*)a);
  a = str(x, 6, -1);
  EXPECT_STREQ((char*)"1.234568e-01", (char*)a);
  a = str(x, 5, -1);
  EXPECT_STREQ((char*)"1.234568e-01", (char*)a);
  a = str(x, 4, -1);
  EXPECT_STREQ((char*)"1.234568e-01", (char*)a);
  a = str(x, 1, -1);
  EXPECT_STREQ((char*)"1.234568e-01", (char*)a);
  a = str(x, 0, -1);
  EXPECT_STREQ((char*)"1.234568e-01", (char*)a);

  a = str(x, 8, 12);
  EXPECT_STREQ((char*)"      0.12345678901", (char*)a);
  a = str(x, 7, 12);
  EXPECT_STREQ((char*)"     0.12345678901", (char*)a);
  a = str(x, 6, 12);
  EXPECT_STREQ((char*)"    0.12345678901", (char*)a);
  a = str(x, 5, 12);
  EXPECT_STREQ((char*)"   0.12345678901", (char*)a);
  a = str(x, 4, 12);
  EXPECT_STREQ((char*)"  0.12345678901", (char*)a);
  a = str(x, 3, 12);
  EXPECT_STREQ((char*)" 0.12345678901", (char*)a);
  a = str(x, 2, 12);
  EXPECT_STREQ((char*)"0.12345678901", (char*)a);
  a = str(x, 1, 12);
  EXPECT_STREQ((char*)"0.12345678901", (char*)a);
  a = str(x, 0, 12);
  EXPECT_STREQ((char*)"0.12345678901", (char*)a);

  a = str(x, 8, 11);
  EXPECT_STREQ((char*)"      0.12345678901", (char*)a);
  a = str(x, 7, 11);
  EXPECT_STREQ((char*)"     0.12345678901", (char*)a);
  a = str(x, 6, 11);
  EXPECT_STREQ((char*)"    0.12345678901", (char*)a);
  a = str(x, 5, 11);
  EXPECT_STREQ((char*)"   0.12345678901", (char*)a);
  a = str(x, 4, 11);
  EXPECT_STREQ((char*)"  0.12345678901", (char*)a);
  a = str(x, 3, 11);
  EXPECT_STREQ((char*)" 0.12345678901", (char*)a);
  a = str(x, 2, 11);
  EXPECT_STREQ((char*)"0.12345678901", (char*)a);
  a = str(x, 1, 11);
  EXPECT_STREQ((char*)"0.12345678901", (char*)a);

  a = str(x, 8, 10);
  EXPECT_STREQ((char*)"      0.1234567890", (char*)a);
  a = str(x, 7, 10);
  EXPECT_STREQ((char*)"     0.1234567890", (char*)a);
  a = str(x, 6, 10);
  EXPECT_STREQ((char*)"    0.1234567890", (char*)a);
  a = str(x, 5, 10);
  EXPECT_STREQ((char*)"   0.1234567890", (char*)a);
  a = str(x, 4, 10);
  EXPECT_STREQ((char*)"  0.1234567890", (char*)a);
  a = str(x, 3, 10);
  EXPECT_STREQ((char*)" 0.1234567890", (char*)a);
  a = str(x, 2, 10);
  EXPECT_STREQ((char*)"0.1234567890", (char*)a);
  a = str(x, 1, 10);
  EXPECT_STREQ((char*)"0.1234567890", (char*)a);

  a = str(x, 8, 9);
  EXPECT_STREQ((char*)"      0.123456789", (char*)a);
  a = str(x, 7, 9);
  EXPECT_STREQ((char*)"     0.123456789", (char*)a);
  a = str(x, 6, 9);
  EXPECT_STREQ((char*)"    0.123456789", (char*)a);
  a = str(x, 5, 9);
  EXPECT_STREQ((char*)"   0.123456789", (char*)a);
  a = str(x, 4, 9);
  EXPECT_STREQ((char*)"  0.123456789", (char*)a);
  a = str(x, 3, 9);
  EXPECT_STREQ((char*)" 0.123456789", (char*)a);
  a = str(x, 2, 9);
  EXPECT_STREQ((char*)"0.123456789", (char*)a);
  a = str(x, 1, 9);
  EXPECT_STREQ((char*)"0.123456789", (char*)a);
}
#endif
TEST_F(test_adstring, default_constructor_int)
{
  adstring a(10);

  EXPECT_EQ(0, length(a));
  EXPECT_EQ(0, a.size());
  EXPECT_EQ(10, a.buff_size());
  //clist length includes '\0'
  EXPECT_EQ(1, a.length());
}
TEST_F(test_adstring, default_constructor_unsigned_char)
{
  unsigned char ub = 'a';
  adstring a(ub);

  EXPECT_EQ(1, length(a));
  EXPECT_EQ(1, a.size());
  EXPECT_EQ(1, a.buff_size());
  //clist length includes '\0'
  EXPECT_EQ(1, a.length());
  EXPECT_EQ(ub, a(1));
}
TEST_F(test_adstring, default_constructor_unsigned_char_array)
{
  unsigned char t[] = "abc\0";
  adstring a(t);

  EXPECT_EQ(3, length(a));
  EXPECT_EQ(3, a.size());
  EXPECT_EQ(3, a.buff_size());
  //clist length includes '\0'
  EXPECT_EQ(1, a.length());
  EXPECT_EQ('a', a(1));
  EXPECT_EQ('b', a(2));
  EXPECT_EQ('c', a(3));
}
TEST_F(test_adstring, operator_plus_char)
{
  adstring u("-742");
  char v = 'v';
  adstring actual = u + v;
  EXPECT_STREQ("-742v", actual);
}
TEST_F(test_adstring, operator_plus_unsigned_char)
{
  adstring u("-742");
  unsigned char v = 'v';
  adstring actual = u + v;
  EXPECT_STREQ("-742v", actual);
}
TEST_F(test_adstring, constructor_zero)
{
  ad_exit=&test_ad_exit;
  ASSERT_ANY_THROW({
    adstring u(0);
  });
}
TEST_F(test_adstring, constructor_not_one)
{
  ad_exit=&test_ad_exit;
  ASSERT_ANY_THROW({
    adstring u(0, 1);
  });
}
TEST_F(test_adstring, str2)
{
  adstring a;
  str(1234, a);
  EXPECT_STREQ("1234", a);
  adstring b;
  str(-1234, b);
  EXPECT_STREQ("-1234", b);
}
TEST_F(test_adstring, unsignedchar_plus_adstring)
{
  const unsigned char u('u');
  adstring v("-742");

  adstring result = u + v;
  EXPECT_STREQ("u-742", result);
}
TEST_F(test_adstring, unsignedchararray_plus_adstring)
{
  const unsigned char v[] = "abc";

  adstring u("-742");

  adstring result = v + u;

  EXPECT_STREQ("abc-742", result);
}
TEST_F(test_adstring, adstring_plus_unsignedchararray)
{
  const unsigned char v[] = "abc";

  adstring u("-742");

  adstring result = u + v;
  EXPECT_STREQ("-742abc", result);
}
TEST_F(test_adstring, comparison)
{
  adstring a("abcd");
  adstring b("abcd");
  adstring c("efgh");

  ASSERT_TRUE(a == b);
  ASSERT_TRUE(a == a);
  ASSERT_TRUE(b == b);
  ASSERT_FALSE(a == c);
  ASSERT_FALSE(c == a);
  ASSERT_FALSE(b == c);
  ASSERT_FALSE(c == b);
}
TEST_F(test_adstring, constcomparison)
{
  const adstring a("abcd");
  const adstring b("abcd");
  const adstring c("efgh");

  ASSERT_TRUE(a == b);
  ASSERT_TRUE(a == a);
  ASSERT_TRUE(b == b);
  ASSERT_FALSE(a == c);
  ASSERT_FALSE(c == a);
  ASSERT_FALSE(b == c);
  ASSERT_FALSE(c == b);
}
TEST_F(test_adstring, errorunsignedchar)
{
  ad_exit=&test_ad_exit;

  adstring a("abcd");

  ASSERT_ANY_THROW({
    a[0];
  });
  ASSERT_ANY_THROW({
    a[5];
  });
  ASSERT_EQ('a', a[1]);
  ASSERT_EQ('b', a[2]);
  ASSERT_EQ('c', a[3]);
  ASSERT_EQ('d', a[4]);
}
TEST_F(test_adstring, errormaxlimit)
{
  ad_exit=&test_ad_exit;

  ofstream ofs("maxlimit.txt");
  for (int i = 0; i <= 1025; ++i)
  {
    ofs << "i";
  }
  ofs.close();

  adstring a;

  ifstream ifs("maxlimit.txt");
  ASSERT_ANY_THROW({
    ifs >> a;
  });
  ifs.close();
}
TEST_F(test_adstring, init_adstring_allocate)
{
  ad_exit=&test_ad_exit;

  ofstream ofs("maxlimit.txt");
   ofs << "idkjfskjdfklsjkljdfsk";
  ofs.close();

  init_adstring a;

  ASSERT_TRUE(ad_comm::global_datafile == NULL);

  cifstream ifs("maxlimit.txt");
  
  ad_comm::global_datafile = &ifs;

  a.allocate("name_tag");

  ad_comm::global_datafile = NULL;

  ifs.close();

  EXPECT_STREQ("idkjfskjdfklsjkljdfsk", (char*)a);

}
TEST_F(test_adstring, init_line_adstring_allocate)
{
  ad_exit=&test_ad_exit;

  ofstream ofs("maxlimit.txt");
  ofs << "idkjfskjdfklsjkljdfsk";
  ofs.close();

  init_line_adstring a;

  ASSERT_TRUE(ad_comm::global_datafile == NULL);

  cifstream ifs("maxlimit.txt");
  
  ad_comm::global_datafile = &ifs;

  a.allocate("name_tag");

  ad_comm::global_datafile = NULL;

  ifs.close();

  EXPECT_STREQ("idkjfskjdfklsjkljdfsk", (char*)a);
}
