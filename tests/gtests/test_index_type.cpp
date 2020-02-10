#include <gtest/gtest.h>
#include <fvar.hpp>

class test_index_type: public ::testing::Test {};

TEST_F(test_index_type, constructor_for_number_index)
{
  int expected = 5;
  index_type c(expected);

  ASSERT_EQ(c.indexmin(), 1);
  ASSERT_EQ(c.indexmax(), 1);
  ASSERT_EQ(c.isinteger(), 0);
  ASSERT_EQ(c.dimension(), 0);
  ASSERT_EQ(c.integer(), expected);
  ASSERT_EQ(c[c.indexmin()].integer(), expected);
  ASSERT_EQ(c[c.indexmax()].integer(), expected);
}
TEST_F(test_index_type, constructor_for_vector_index)
{
  ivector expected(1, 5);
  expected(1) = __LINE__;
  expected(2) = __LINE__;
  expected(3) = __LINE__;
  expected(4) = __LINE__;
  expected(5) = __LINE__;
  index_type c(expected);

  ASSERT_EQ(c.indexmin(), 1);
  ASSERT_EQ(c.indexmax(), 5);
  ASSERT_EQ(c.isinteger(), 1);
  ASSERT_EQ(c.dimension(), 1);
  ASSERT_EQ(c[1].integer(), expected(1));
  ASSERT_EQ(c[2].integer(), expected(2));
  ASSERT_EQ(c[3].integer(), expected(3));
  ASSERT_EQ(c[4].integer(), expected(4));
  ASSERT_EQ(c[5].integer(), expected(5));

  try
  {
    c.integer();
  }
  catch (const int exit_code)          
  {   
    return;
  }
  FAIL();
}
TEST_F(test_index_type, constructor_for_matrix_index)
{
  imatrix expected(1, 5, 2, 3);
  expected(1, 2) = __LINE__;
  expected(1, 3) = __LINE__;
  expected(2, 2) = __LINE__;
  expected(2, 3) = __LINE__;
  expected(3, 2) = __LINE__;
  expected(3, 3) = __LINE__;
  expected(4, 2) = __LINE__;
  expected(4, 3) = __LINE__;
  expected(5, 2) = __LINE__;
  expected(5, 3) = __LINE__;
  index_type c(expected);

  ASSERT_EQ(c.indexmin(), expected.rowmin());
  ASSERT_EQ(c.indexmax(), expected.rowmax());
  ASSERT_EQ(c.isinteger(), 1);
  ASSERT_EQ(c.dimension(), 2);

  ASSERT_EQ(c[1][2].integer(), expected(1, 2));
  ASSERT_EQ(c[1][3].integer(), expected(1, 3));
  ASSERT_EQ(c[2][2].integer(), expected(2, 2));
  ASSERT_EQ(c[2][3].integer(), expected(2, 3));
  ASSERT_EQ(c[3][2].integer(), expected(3, 2));
  ASSERT_EQ(c[3][3].integer(), expected(3, 3));
  ASSERT_EQ(c[4][2].integer(), expected(4, 2));
  ASSERT_EQ(c[4][3].integer(), expected(4, 3));
  ASSERT_EQ(c[5][2].integer(), expected(5, 2));
  ASSERT_EQ(c[5][3].integer(), expected(5, 3));

  try
  {
    c.integer();
  }
  catch (const int exit_code)          
  {   
    return;
  }
  FAIL();
}
TEST_F(test_index_type, constructor_for_i3_array_index)
{
  i3_array expected(1, 5, 2, 3, 4, 5);
  expected.initialize();

  index_type c(expected);

  ASSERT_EQ(c.indexmin(), expected.slicemin());
  ASSERT_EQ(c.indexmax(), expected.slicemax());
  ASSERT_EQ(c.isinteger(), 1);
  ASSERT_EQ(c.dimension(), 3);

  ASSERT_EQ(c[2][3][4].integer(), expected(2, 3, 4));


  try
  {
    c.integer();
  }
  catch (const int exit_code)          
  {   
    return;
  }
  FAIL();
}
TEST_F(test_index_type, constructor_for_i4_array_index)
{
  i4_array expected;
  expected.allocate(1, 5, 2, 3, 4, 5, 6, 7);
  expected.initialize();

  index_type c(expected);

  ASSERT_EQ(c.indexmin(), expected.slicemin());
  ASSERT_EQ(c.indexmax(), expected.slicemax());
  ASSERT_EQ(c.isinteger(), 1);
  ASSERT_EQ(c.dimension(), 4);

  ASSERT_EQ(c[2][3][4][6].integer(), expected(2, 3, 4, 6));


  try
  {
    c.integer();
  }
  catch (const int exit_code)          
  {   
    return;
  }
  FAIL();
}
