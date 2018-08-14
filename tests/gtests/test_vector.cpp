#include <gtest/gtest.h>
#include <fvar.hpp>

class test_vector: public ::testing::Test {};

TEST_F(test_vector, default_constructor)
{
  gradient_structure gs;

  std::vector<dvariable> array;

  ASSERT_EQ(array.size(), 0);
}
TEST_F(test_vector, sumdoubles)
{
  std::vector<double> array = {1.0, 2.0, 3.4};
  ASSERT_EQ(array.size(), 3);
  double sum = 0;
  for (const double value: array)
  {
    sum += value;
  }
  ASSERT_DOUBLE_EQ(sum, 6.4);
}
TEST_F(test_vector, sum)
{
  gradient_structure gs;

  std::vector<dvariable> array = {1.0, 2.0, 3.4};
  ASSERT_EQ(array.size(), 3);
  dvariable sum;
  for (const dvariable& value: array)
  {
    sum += value;
  }
  ASSERT_DOUBLE_EQ(value(sum), 6.4);

  std::vector<dvariable> array2 = {0.0, 1.0, 2.5, 3.4, -2.0, -1.5};
  ASSERT_EQ(array2.size(), 6);
  dvariable sum2;
  for (const dvariable& value: array2)
  {
    sum2 += value;
  }
  ASSERT_DOUBLE_EQ(value(sum2), 3.4);
}
TEST_F(test_vector, apply)
{
  gradient_structure gs;

  std::vector<dvariable> array = {1.0, 2.5, 3.4, -2.0, -1.5};
  ASSERT_EQ(array.size(), 5);

  std::vector<dvariable> result;
  std::for_each(array.begin(), array.end(),
    [&result](dvariable& v)
    {
      dvariable vv = v * v;
      result.push_back(vv);
    }
  );
  ASSERT_DOUBLE_EQ(value(result[0]), 1.0);
  ASSERT_DOUBLE_EQ(value(result[1]), 6.25);
  ASSERT_DOUBLE_EQ(value(result[2]), 11.56);
  ASSERT_DOUBLE_EQ(value(result[3]), 4.0);
  ASSERT_DOUBLE_EQ(value(result[4]), 2.25);
}
template<typename _Tp>
_Tp my_vector_sum(const _Tp* __f, const _Tp* __l)
    {
      _Tp __r = _Tp();
      while (__f != __l)
      __r += *__f++;
      return __r;
    }
TEST_F(test_vector, my_vector_sum)
{
  gradient_structure gs;

  double expected = 0.0;

  dvariable a;
  ASSERT_DOUBLE_EQ(value(a), expected);

  std::vector<dvariable> array = {1.125, 2.0, 3.4};

  dvariable d;
  ASSERT_DOUBLE_EQ(value(d), expected);

  dvariable result = my_vector_sum<dvariable>(&array[0], &array[0] + 3);
  ASSERT_DOUBLE_EQ(value(result), 6.525);
}
