#include <gtest/gtest.h>
#include <fvar.hpp>

class test_move_dvar_vector: public ::testing::Test {};

TEST_F(test_move_dvar_vector, copies)
{
  gradient_structure gs;

  dvar_vector a(1, 2);
  ASSERT_EQ(a.get_ncopies(), 0);

  dvar_vector b(a);
  ASSERT_EQ(a.get_ncopies(), 1);
  ASSERT_EQ(b.get_ncopies(), 1);

  dvar_vector c(b);
  ASSERT_EQ(a.get_ncopies(), 2);
  ASSERT_EQ(b.get_ncopies(), 2);
  ASSERT_EQ(c.get_ncopies(), 2);
}
TEST_F(test_move_dvar_vector, moves)
{
  gradient_structure gs;

  dvar_vector a(1, 2);
  ASSERT_EQ(a.get_ncopies(), 0);

  dvar_vector b(std::move(a));
  ASSERT_EQ(a.get_ncopies(), 0);
  ASSERT_EQ(b.get_ncopies(), 1);

  dvar_vector c(std::move(b));
  ASSERT_EQ(a.get_ncopies(), 0);
  ASSERT_EQ(b.get_ncopies(), 0);
  ASSERT_EQ(c.get_ncopies(), 1);
}
