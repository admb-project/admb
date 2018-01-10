#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar_vector_position: public ::testing::Test {};

TEST_F(test_dvar_vector_position, default_constructor)
{
  dvar_vector_position pos;

  ASSERT_EQ(pos.min, 0);
  ASSERT_EQ(pos.max, -1);
  ASSERT_TRUE(pos.va == nullptr);
}
TEST_F(test_dvar_vector_position, constructor_dvar_vector_empty)
{
  dvar_vector empty;
  dvar_vector_position pos(empty);

  ASSERT_EQ(pos.min, 0);
  ASSERT_EQ(pos.max, -1);
  ASSERT_TRUE(pos.va == nullptr);
}
TEST_F(test_dvar_vector_position, constructor_dvar_vector)
{
  gradient_structure gs;

  dvar_vector v(2, 5);
  dvar_vector_position pos(v);

  ASSERT_EQ(pos.min, 2);
  ASSERT_EQ(pos.max, 5);
  ASSERT_TRUE(pos.va == v.va);
}
TEST_F(test_dvar_vector_position, constructor_dvar_vector_copy)
{
  gradient_structure gs;

  dvar_vector v(2, 5);
  dvar_vector_position pos(v);
  dvar_vector_position copy(pos);

  ASSERT_EQ(pos.min, copy.min);
  ASSERT_EQ(pos.max, copy.max);
  ASSERT_TRUE(pos.va == copy.va);
}
TEST_F(test_dvar_vector_position, element_access)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar_vector v(2, 5);
  v(2) = 6.3;
  v(3) = 7.3;
  v(4) = 8.3;
  v(5) = 9.3;
  dvar_vector_position pos(v);

  ASSERT_ANY_THROW({
    pos(1);
  });
  ASSERT_ANY_THROW({
    pos(6);
  });
  ASSERT_DOUBLE_EQ(pos(2), 6.3);
  ASSERT_DOUBLE_EQ(pos(3), 7.3);
  ASSERT_DOUBLE_EQ(pos(4), 8.3);
  ASSERT_DOUBLE_EQ(pos(5), 9.3);
}
