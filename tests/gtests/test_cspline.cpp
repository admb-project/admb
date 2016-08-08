#include <gtest/gtest.h>
#include <admodel.h>

class test_cspline: public ::testing::Test {};

TEST_F(test_cspline, output)
{
  dvector x(1,10);
  dvector xx(1,20);
  dvector y(1,10);
  dvector eps(1,10);

  x.fill_seqadd(1,1);
  xx.fill_seqadd(1,0.5);
  random_number_generator rng(101);
  eps.fill_randn(rng);

  y=square(x)+eps;
  cout << x << endl;
  cout << xx << endl;
  cout << y << endl;

  cubic_spline_function* f = new cubic_spline_function(x,y);

  cout << (*f)(10.0) << endl;
  cout << (*f)(xx) << endl;
  cout << (*f)(x) << endl;

  dvector results = y - (*f)(x);

  ASSERT_DOUBLE_EQ(0, results(1));
  ASSERT_DOUBLE_EQ(0, results(2));
  ASSERT_DOUBLE_EQ(0, results(3));
  ASSERT_DOUBLE_EQ(0, results(4));
  ASSERT_DOUBLE_EQ(0, results(5));
  ASSERT_DOUBLE_EQ(0, results(6));
  ASSERT_DOUBLE_EQ(0, results(7));
  ASSERT_DOUBLE_EQ(0, results(8));
  ASSERT_DOUBLE_EQ(0, results(9));
  ASSERT_DOUBLE_EQ(0, results(10));

  delete f;
  f = NULL;
}
