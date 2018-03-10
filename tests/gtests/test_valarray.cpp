#include <gtest/gtest.h>
#include <valarray>
#include <fvar.hpp>

class test_valarray: public ::testing::Test {};

TEST_F(test_valarray, default_constructor)
{
  gradient_structure gs;

  std::valarray<dvariable> array;

  ASSERT_EQ(array.size(), 0);
}
TEST_F(test_valarray, sum)
{
  gradient_structure gs;

  std::valarray<dvariable> array = {1.0, 2.5, 3.4, -2.0, -1.5};
  ASSERT_EQ(array.size(), 5);

  ASSERT_DOUBLE_EQ(value(array.sum()), 3.4);
}
TEST_F(test_valarray, apply)
{
  gradient_structure gs;

  std::valarray<dvariable> array = {1.0, 2.5, 3.4, -2.0, -1.5};
  ASSERT_EQ(array.size(), 5);

  std::valarray<dvariable> result =
    array.apply([](const dvariable& v)
    {
      dvariable vv = v * v;
      return vv;
    });
  ASSERT_DOUBLE_EQ(value(result[0]), 1.0);
  ASSERT_DOUBLE_EQ(value(result[1]), 6.25);
  ASSERT_DOUBLE_EQ(value(result[2]), 11.56);
  ASSERT_DOUBLE_EQ(value(result[3]), 4.0);
  ASSERT_DOUBLE_EQ(value(result[4]), 2.25);
}
TEST_F(test_valarray, shift_does_not_reindex)
{
  gradient_structure gs;

  std::valarray<dvariable> array = {1.0, 2.5, 3.4, -2.0, -1.5};
  ASSERT_EQ(array.size(), 5);

  // Shift to the right one.
  std::valarray<dvariable> result = array.shift(-1);
  ASSERT_EQ(result.size(), 5);

  ASSERT_DOUBLE_EQ(value(result[0]), 1.0);
  ASSERT_DOUBLE_EQ(value(result[1]), 1.0);
  ASSERT_DOUBLE_EQ(value(result[2]), 2.5);
  ASSERT_DOUBLE_EQ(value(result[3]), 3.4);
  ASSERT_DOUBLE_EQ(value(result[4]), -2.0);
}
