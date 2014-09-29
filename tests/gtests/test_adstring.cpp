#include <gtest/gtest.h>
#include <adstring.hpp>
#include <climits>

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
#endif
TEST_F(test_adstring, realloc)
{
  adstring a("-742"); 
  char expected[] = "Reallocation."; 
  a.realloc(expected);
  EXPECT_STREQ(expected, (char*)a);
}
