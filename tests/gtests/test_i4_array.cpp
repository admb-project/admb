#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

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
TEST_F(test_i4_array, emptyi3array)
{
  i4_array a(1, 4);
  ASSERT_FALSE(allocated(a(1)));
  ASSERT_FALSE(allocated(a(2)));
  ASSERT_FALSE(allocated(a(3)));
  ASSERT_FALSE(allocated(a(4)));
}
TEST_F(test_i4_array, invalidindexesi3array)
{
  i4_array a(4, 1);
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i4_array, initializeemptyi3array)
{
  ad_exit=&test_ad_exit;

  ASSERT_NO_THROW({
    i4_array a(1, 4);
    a.initialize();
  });
  ASSERT_NO_THROW({
    i4_array b;
    b.initialize();
  });
}
TEST_F(test_i4_array, copyempty)
{
  i4_array empty;
  i4_array copy(empty);
  ASSERT_EQ(0, copy.hslicesize());
  ASSERT_EQ(1, copy.indexmin());
  ASSERT_EQ(0, copy.indexmax());
  ASSERT_EQ(0, copy.get_ncopies());
}
TEST_F(test_i4_array, copynonempty)
{
  i4_array a(1, 4);
  ASSERT_EQ(0, a.get_ncopies());
  i4_array copy(a);
  ASSERT_EQ(4, copy.hslicesize());
  ASSERT_EQ(1, copy.indexmin());
  ASSERT_EQ(4, copy.indexmax());
  ASSERT_EQ(&a(1), &copy(1));
  ASSERT_EQ(&a(2), &copy(2));
  ASSERT_EQ(&a(3), &copy(3));
  ASSERT_EQ(&a(4), &copy(4));
  ASSERT_EQ(1, copy.get_ncopies());
  ASSERT_EQ(1, a.get_ncopies());
}
TEST_F(test_i4_array, construct4intx)
{
  i4_array a(1, 4, 1, 3, 1, 2, 1, 1);

  ASSERT_EQ(1, a.hslicemin());
  ASSERT_EQ(4, a.hslicemax());
  ASSERT_EQ(4, a.hslicesize());
  ASSERT_EQ(1, a(1).slicemin());
  ASSERT_EQ(3, a(1).slicemax());
  ASSERT_EQ(3, a(1).slicesize());
  ASSERT_EQ(1, a(2).slicemin());
  ASSERT_EQ(3, a(2).slicemax());
  ASSERT_EQ(3, a(2).slicesize());
  ASSERT_EQ(1, a(3).slicemin());
  ASSERT_EQ(3, a(3).slicemax());
  ASSERT_EQ(3, a(3).slicesize());
  ASSERT_EQ(1, a(4).slicemin());
  ASSERT_EQ(3, a(4).slicemax());
  ASSERT_EQ(3, a(4).slicesize());
  ASSERT_EQ(1, a(1, 1).rowmin());
  ASSERT_EQ(2, a(1, 1).rowmax());
  ASSERT_EQ(2, a(1, 1).rowsize());
  ASSERT_EQ(1, a(2, 1).rowmin());
  ASSERT_EQ(2, a(2, 1).rowmax());
  ASSERT_EQ(2, a(2, 1).rowsize());
  ASSERT_EQ(1, a(3, 1).rowmin());
  ASSERT_EQ(2, a(3, 1).rowmax());
  ASSERT_EQ(2, a(3, 1).rowsize());
  ASSERT_EQ(1, a(4, 1).rowmin());
  ASSERT_EQ(2, a(4, 1).rowmax());
  ASSERT_EQ(2, a(4, 1).rowsize());
  ASSERT_EQ(1, a(1, 2).rowmin());
  ASSERT_EQ(2, a(1, 2).rowmax());
  ASSERT_EQ(2, a(1, 2).rowsize());
  ASSERT_EQ(1, a(2, 2).rowmin());
  ASSERT_EQ(2, a(2, 2).rowmax());
  ASSERT_EQ(2, a(2, 2).rowsize());
  ASSERT_EQ(1, a(3, 2).rowmin());
  ASSERT_EQ(2, a(3, 2).rowmax());
  ASSERT_EQ(2, a(3, 2).rowsize());
  ASSERT_EQ(1, a(4, 2).rowmin());
  ASSERT_EQ(2, a(4, 2).rowmax());
  ASSERT_EQ(2, a(4, 2).rowsize());
  ASSERT_EQ(1, a(1, 1, 1).indexmin());
  ASSERT_EQ(1, a(1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 1).size());
  ASSERT_EQ(1, a(2, 1, 1).indexmin());
  ASSERT_EQ(1, a(2, 1, 1).indexmax());
  ASSERT_EQ(1, a(2, 1, 1).size());
  ASSERT_EQ(1, a(3, 1, 1).indexmin());
  ASSERT_EQ(1, a(3, 1, 1).indexmax());
  ASSERT_EQ(1, a(3, 1, 1).size());
  ASSERT_EQ(1, a(4, 1, 1).indexmin());
  ASSERT_EQ(1, a(4, 1, 1).indexmax());
  ASSERT_EQ(1, a(4, 1, 1).size());
  ASSERT_EQ(1, a(1, 2, 1).indexmin());
  ASSERT_EQ(1, a(1, 2, 1).indexmax());
  ASSERT_EQ(1, a(1, 2, 1).size());
  ASSERT_EQ(1, a(2, 2, 1).indexmin());
  ASSERT_EQ(1, a(2, 2, 1).indexmax());
  ASSERT_EQ(1, a(2, 2, 1).size());
  ASSERT_EQ(1, a(3, 2, 1).indexmin());
  ASSERT_EQ(1, a(3, 2, 1).indexmax());
  ASSERT_EQ(1, a(3, 2, 1).size());
  ASSERT_EQ(1, a(4, 2, 1).indexmin());
  ASSERT_EQ(1, a(4, 2, 1).indexmax());
  ASSERT_EQ(1, a(4, 2, 1).size());

/*
  int value = 0;
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      for (int k = 1; k <= 3; ++k)
      {
        for (int l = 1; l <= 3; ++l)
        {
          a(i, j, k, l) = value;
          ++value;
        }
      }
    }
  }
*/
}
