#include <gtest/gtest.h>
#include <fvar.hpp>

class test_dvar4_array: public ::testing::Test {};

TEST_F(test_dvar4_array, assignment)
{
  gradient_structure gs;
  dvar4_array a(1, 2, 1, 2, 1, 2, 1, 2);
  a.initialize();

  d4_array b(1, 2, 1, 2, 1, 2, 1, 2);

  int count = 1;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          b(i, j, k, l) = count;
          ++count;
        }
      }
    }
  }

  a = b;

  count = 1;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          ASSERT_DOUBLE_EQ(b(i, j, k, l), static_cast<double>(count));
          ++count;
        }
      }
    }
  }
}
TEST_F(test_dvar4_array, constructor_2)
{
  gradient_structure gs;
  dvar4_array a(1, 2);

  ASSERT_TRUE(!a(1));
  ASSERT_TRUE(!a(2));
}
TEST_F(test_dvar4_array, inputoutput)
{
  gradient_structure gs;

  dvar4_array b(1, 2, 1, 2, 1, 2, 1, 2);

  int count = 1;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          b(i, j, k, l) = count;
          ++count;
        }
      }
    }
  }

  uostream& operator<<(const uostream& output, const dvar4_array& varr4);

  uostream output("varr4.txt");
  operator<<(output, b);
  output.close();

  dvar4_array a(1, 2, 1, 2, 1, 2, 1, 2);
  a.initialize();

  uistream& operator>>(const uistream& output, const dvar4_array& varr4);

  uistream input("varr4.txt");
  operator>>(input, a);
  input.close();

  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          ASSERT_DOUBLE_EQ(value(a(i, j, k, l)), value(b(i, j, k, l)));
        }
      }
    }
  }
}
TEST_F(test_dvar4_array, inputoutput2)
{
  gradient_structure gs;

  dvar4_array b(1, 2, 1, 2, 1, 2, 1, 2);

  int count = 1;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          b(i, j, k, l) = count;
          ++count;
        }
      }
    }
  }

  ofstream output("varr4.txt");
  operator<<(output, b);
  output.close();

  dvar4_array a(1, 2, 1, 2, 1, 2, 1, 2);
  a.initialize();

  ifstream input("varr4.txt");
  operator>>(input, a);
  input.close();

  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          ASSERT_DOUBLE_EQ(value(a(i, j, k, l)), value(b(i, j, k, l)));
        }
      }
    }
  }
}
TEST_F(test_dvar4_array, deallocatecopies)
{
  gradient_structure gs;

  dvar4_array a(1, 2, 1, 2, 1, 2, 1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  dvar4_array firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  dvar4_array secondcopy(a);
  ASSERT_EQ(2, a.get_ncopies());
  ASSERT_EQ(2, firstcopy.get_ncopies());
  ASSERT_EQ(2, secondcopy.get_ncopies());

  firstcopy.deallocate();
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(1, secondcopy.get_ncopies());

  secondcopy.deallocate();
  ASSERT_EQ(0, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(0, secondcopy.get_ncopies());
}
