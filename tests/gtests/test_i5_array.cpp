#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_i5_array: public ::testing::Test {};

TEST_F(test_i5_array, default)
{
  i5_array a;
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i5_array, 1xint)
{
  i5_array a(2, 5);
  ASSERT_EQ(4, a.hslicesize());
  ASSERT_EQ(2, a.indexmin());
  ASSERT_EQ(5, a.indexmax());
  ASSERT_EQ(1, a(2).indexmin());
  ASSERT_EQ(0, a(2).indexmax());
  ASSERT_EQ(1, a(3).indexmin());
  ASSERT_EQ(0, a(3).indexmax());
  ASSERT_EQ(1, a(4).indexmin());
  ASSERT_EQ(0, a(4).indexmax());
  ASSERT_EQ(1, a(5).indexmin());
  ASSERT_EQ(0, a(5).indexmax());
}
TEST_F(test_i5_array, 1xintinvalid)
{
  i5_array a(5, 2);
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i5_array, 5xint)
{
  i5_array a;
  a.allocate(1, 5, 1, 4, 1, 3, 1, 2, 1, 1);
  ASSERT_EQ(5, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(5, a.indexmax());
  for (int i = 1; i <= 5; ++i)
  {
    ASSERT_EQ(1, a(i).indexmin());
    ASSERT_EQ(4, a(i).indexmax());
    for (int j = 1; j <= 4; ++j)
    {
      ASSERT_EQ(1, a(i, j).indexmin());
      ASSERT_EQ(3, a(i, j).indexmax());
      for (int k = 1; k <= 3; ++k)
      {
        ASSERT_EQ(1, a(i, j, k).indexmin());
        ASSERT_EQ(2, a(i, j, k).indexmax());
        for (int w = 1; w <= 2; ++w)
        {
          ASSERT_EQ(1, a(i, j, k, w).indexmin());
          ASSERT_EQ(1, a(i, j, k, w).indexmax());
        }
      }
    }
  }
}
TEST_F(test_i5_array, allocate1xint)
{
  i5_array a;
  a.allocate(2, 5);
  ASSERT_EQ(4, a.hslicesize());
  ASSERT_EQ(2, a.indexmin());
  ASSERT_EQ(5, a.indexmax());
  ASSERT_EQ(1, a(2).indexmin());
  ASSERT_EQ(0, a(2).indexmax());
  ASSERT_EQ(1, a(3).indexmin());
  ASSERT_EQ(0, a(3).indexmax());
  ASSERT_EQ(1, a(4).indexmin());
  ASSERT_EQ(0, a(4).indexmax());
  ASSERT_EQ(1, a(5).indexmin());
  ASSERT_EQ(0, a(5).indexmax());
}
TEST_F(test_i5_array, deallocate)
{
  i5_array a;
  a.allocate(1, 5, 1, 4, 1, 3, 1, 2, 1, 1);
  a.deallocate();
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i5_array, equals)
{
  i5_array a;
  a.allocate(1, 5, 1, 4, 1, 3, 1, 2, 1, 1);

  int count = 0;
  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      for (int k = 1; k <= 3; ++k)
      {
        for (int w = 1; w <= 2; ++w)
        {
          a(i, j, k, w, 1) = count;
          ++count;
        }
      }
    }
  }
  count = 0;
  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      for (int k = 1; k <= 3; ++k)
      {
        for (int w = 1; w <= 2; ++w)
        {
          ASSERT_EQ(a(i, j, k, w, 1), count);
          ++count;
        }
      }
    }
  }
}
TEST_F(test_i5_array, elemerror)
{
  i5_array a(2, 5);
  ASSERT_ANY_THROW({
    a.elem(1);
  });
  ASSERT_ANY_THROW({
    a.elem(6);
  });
}
TEST_F(test_i5_array, elembracketerror)
{
  i5_array a(2, 5);
  ASSERT_ANY_THROW({
    a[1];
  });
  ASSERT_ANY_THROW({
    a[6];
  });
}
TEST_F(test_i5_array, constelemerror)
{
  const i5_array a(2, 5);
  ASSERT_ANY_THROW({
    a.elem(1);
  });
  ASSERT_ANY_THROW({
    a.elem(6);
  });
}
TEST_F(test_i5_array, inputoutput)
{
  i5_array a(1, 5);
  a(2).allocate(1, 4, 1, 3, 1, 2, 1, 1);

  a(2, 1, 1, 1, 1) = 1;
  a(2, 1, 1, 2, 1) = 2;
  a(2, 1, 2, 1, 1) = 3;
  a(2, 1, 2, 2, 1) = 4;
  a(2, 1, 3, 1, 1) = 5;
  a(2, 1, 3, 2, 1) = 6;
  a(2, 2, 1, 1, 1) = 7;
  a(2, 2, 1, 2, 1) = 8;
  a(2, 2, 2, 1, 1) = 9;
  a(2, 2, 2, 2, 1) = 10;
  a(2, 2, 3, 1, 1) = 11;
  a(2, 2, 3, 2, 1) = 12;
  a(2, 3, 1, 1, 1) = 13;
  a(2, 3, 1, 2, 1) = 14;
  a(2, 3, 2, 1, 1) = 15;
  a(2, 3, 2, 2, 1) = 16;
  a(2, 3, 3, 1, 1) = 17;
  a(2, 3, 3, 2, 1) = 18;

  ofstream output("test_i5_array.txt");
  output << a;
  output.close();

  i5_array b(1, 5);
  b(2).allocate(1, 4, 1, 3, 1, 2, 1, 1);

  ifstream input("test_i5_array.txt");
  input >> b;
  input.close();

  ASSERT_EQ(a(2, 1, 1, 1, 1), 1);
  ASSERT_EQ(a(2, 1, 1, 2, 1), 2);
  ASSERT_EQ(a(2, 1, 2, 1, 1), 3);
  ASSERT_EQ(a(2, 1, 2, 2, 1), 4);
  ASSERT_EQ(a(2, 1, 3, 1, 1), 5);
  ASSERT_EQ(a(2, 1, 3, 2, 1), 6);
  ASSERT_EQ(a(2, 2, 1, 1, 1), 7);
  ASSERT_EQ(a(2, 2, 1, 2, 1), 8);
  ASSERT_EQ(a(2, 2, 2, 1, 1), 9);
  ASSERT_EQ(a(2, 2, 2, 2, 1), 10);
  ASSERT_EQ(a(2, 2, 3, 1, 1), 11);
  ASSERT_EQ(a(2, 2, 3, 2, 1), 12);
  ASSERT_EQ(a(2, 3, 1, 1, 1), 13);
  ASSERT_EQ(a(2, 3, 1, 2, 1), 14);
  ASSERT_EQ(a(2, 3, 2, 1, 1), 15);
  ASSERT_EQ(a(2, 3, 2, 2, 1), 16);
  ASSERT_EQ(a(2, 3, 3, 1, 1), 17);
  ASSERT_EQ(a(2, 3, 3, 2, 1), 18);
}
TEST_F(test_i5_array, copyempty)
{
  i5_array empty;
  ASSERT_EQ(0, empty.get_ncopies());
  i5_array copy(empty);
  ASSERT_EQ(0, copy.hslicesize());
  ASSERT_EQ(1, copy.hslicemin());
  ASSERT_EQ(0, copy.hslicemax());
  ASSERT_EQ(0, copy.get_ncopies());
  ASSERT_EQ(0, empty.get_ncopies());
}
TEST_F(test_i5_array, copynonempty)
{
  i5_array nonempty(1, 1);
  ASSERT_EQ(0, nonempty.get_ncopies());
  i5_array copy(nonempty);
  ASSERT_EQ(1, copy.hslicesize());
  ASSERT_EQ(1, copy.hslicemin());
  ASSERT_EQ(1, copy.hslicemax());
  ASSERT_EQ(1, copy.get_ncopies());
  ASSERT_EQ(1, nonempty.get_ncopies());
}
TEST_F(test_i5_array, deallocatecopies)
{
  i5_array a;
  a.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  i5_array firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  i5_array secondcopy(a);
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
