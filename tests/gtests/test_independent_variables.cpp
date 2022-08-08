#include <gtest/gtest.h>
#include <fvar.hpp>

class test_independent_variables: public ::testing::Test {};

TEST_F(test_independent_variables, deep_copy_constructor)
{
  independent_variables independents(1, 2);
  independents[1] = 11.5;
  independents[2] = -21.5;
  independent_variables copy(independents);

  ASSERT_EQ(independents.indexmin(), copy.indexmin());
  ASSERT_EQ(independents.indexmax(), copy.indexmax());
  ASSERT_DOUBLE_EQ(independents(1), copy(1));
  ASSERT_DOUBLE_EQ(independents(2), copy(2));
  ASSERT_TRUE(independents.get_v() != copy.get_v());
}
TEST_F(test_independent_variables, assignment_deep_copy)
{
  independent_variables independents(1, 2);
  independents[1] = 11.5;
  independents[2] = -21.5;

  independent_variables copy;
  ASSERT_EQ(copy.indexmin(), 1);
  ASSERT_EQ(copy.indexmax(), 0);
  ASSERT_TRUE(copy.get_v() == nullptr);

  copy.allocate(independents.indexmin(), independents.indexmax());
  copy = independents;

  ASSERT_EQ(independents.indexmin(), copy.indexmin());
  ASSERT_EQ(independents.indexmax(), copy.indexmax());
  ASSERT_DOUBLE_EQ(independents(1), copy(1));
  ASSERT_DOUBLE_EQ(independents(2), copy(2));
  ASSERT_TRUE(independents.get_v() != copy.get_v());
}
TEST_F(test_independent_variables, assignment_shallow_copy)
{
  independent_variables independents(1, 2);
  independents[1] = 11.5;
  independents[2] = -21.5;

  independent_variables copy;
  ASSERT_EQ(copy.indexmin(), 1);
  ASSERT_EQ(copy.indexmax(), 0);
  ASSERT_TRUE(copy.get_v() == nullptr);

  copy = independents;

  ASSERT_EQ(independents.indexmin(), copy.indexmin());
  ASSERT_EQ(independents.indexmax(), copy.indexmax());
  ASSERT_DOUBLE_EQ(independents(1), copy(1));
  ASSERT_DOUBLE_EQ(independents(2), copy(2));
  ASSERT_TRUE(independents.get_v() != copy.get_v());
}
