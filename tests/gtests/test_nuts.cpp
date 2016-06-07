#include <gtest/gtest.h>

class test_nuts: public ::testing::Test {};

//global nfevals;
int nfevals = 0;

class leapfrog
{
  double _thetaprime;
  double _rprime;
  double _gradprime;
  double _logpprime;

  void f(const double)
  {
  }
public:
  leapfrog();

  void compute
  (
    double theta, 
    double r,
    double grad,
    double epsilon
  );

  double get_thetaprime() const;
  double get_rprime() const;
  double get_gradprime() const;
  double get_logpprime() const;
};
leapfrog::leapfrog():
  _thetaprime(0),
  _rprime(0),
  _gradprime(0),
  _logpprime(0)
{
}
double leapfrog::get_thetaprime() const
{
  return _thetaprime;
}
double leapfrog::get_rprime() const
{
  return _rprime;
}
double leapfrog::get_gradprime() const
{
  return _gradprime;
}
double leapfrog::get_logpprime() const
{
  return _logpprime;
}
void leapfrog::compute
(
  double theta, 
  double r,
  double grad,
  double epsilon
)
{
  _rprime = r + 0.5 * epsilon * grad;
  _thetaprime = theta + epsilon * _rprime;
  //[logpprime, gradprime] = f(thetaprime);
  f(_thetaprime);
  _rprime += 0.5 * epsilon * _gradprime;
}

int build_tree(int j)
{
  if (j == 0)
  {
    return j;
  }
  else
  {
    return build_tree(j - 1);
  }
}

TEST_F(test_nuts, leapfrog)
{
  leapfrog o;
  ASSERT_DOUBLE_EQ(o.get_thetaprime(), 0);
  ASSERT_DOUBLE_EQ(o.get_rprime(), 0);
  ASSERT_DOUBLE_EQ(o.get_gradprime(), 0);
  ASSERT_DOUBLE_EQ(o.get_logpprime(), 0);

  o.compute(1, 1, 1, 1);
  ASSERT_DOUBLE_EQ(o.get_thetaprime(), 2.5);
  ASSERT_DOUBLE_EQ(o.get_rprime(), 1.5);
  ASSERT_DOUBLE_EQ(o.get_gradprime(), 0);
  ASSERT_DOUBLE_EQ(o.get_logpprime(), 0);

  o.compute(1, 1, 1, 1);
  ASSERT_DOUBLE_EQ(o.get_thetaprime(), 2.5);
  ASSERT_DOUBLE_EQ(o.get_rprime(), 1.5);
  ASSERT_DOUBLE_EQ(o.get_gradprime(), 0);
  ASSERT_DOUBLE_EQ(o.get_logpprime(), 0);

  o.compute(0, 0, 0, 0);
  ASSERT_DOUBLE_EQ(o.get_thetaprime(), 0);
  ASSERT_DOUBLE_EQ(o.get_rprime(), 0);
  ASSERT_DOUBLE_EQ(o.get_gradprime(), 0);
  ASSERT_DOUBLE_EQ(o.get_logpprime(), 0);
}

TEST_F(test_nuts, build_tree)
{
  int j = 5;
  ASSERT_EQ(build_tree(j), 0);
}
