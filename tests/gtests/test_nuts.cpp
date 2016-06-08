#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <random>
#include <gtest/gtest.h>

using std::cout;
using std::endl;
using std::vector;

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
typedef vector<vector<double> > matrix;

class nuts
{
  matrix _samples;

  double exprnd(double d);
public:
  nuts();
  ~nuts();

  void compute
  (
    const size_t M,
    const vector<double>& theta0
  );

  matrix& get_samples()
  {
    return _samples;
  }
};
nuts::nuts()
{
}
nuts::~nuts()
{
}
double nuts::exprnd(double p)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  // if particles decay once per second on average,
  // how much time, in seconds, until the next one?
  std::exponential_distribution<> d(p);
  return d(gen);
}
void nuts::compute
(
  const size_t M,
  const vector<double>& theta0
)
{
  size_t D = theta0.size();
  for (int m = 0; m < M; ++m)
  {
    vector<double> v;
    for (int d = 0; d < D; ++d)
    {
      v.push_back(0);
    }
    _samples.push_back(v);
  }
  for (int d = 0; d < D; ++d)
  {
    _samples[0][d] = theta0[d];
  }

  //f
  double logp = 0;
  double grad = 0;

  int* r0 = new int[D];
  double* thetaminus = new double[D];
  double* thetaplus = new double[D];
  int* rminus = new int[D];
  int* rplus = new int[D];
  for (int m = 1; m < M; ++m)
  {
    //Resample momenta.
    for (int d = 0; d < D; ++d)
    {
      r0[d] = rand();
    }
    //Joint log-probability of theta and momenta r.
    double joint = 0;
    for (int d = 0; d < D; ++d)
    {
      joint += r0[d] * r0[d];
    }
    joint *= -0.5;
    joint += logp;
    //Resample u ~ uniform([0, exp(joint)]).
    //Equivalent to (log(u) - joint) ~ exponential(1).
    double logu = joint - exprnd(1);
    //Initialize tree.
    for (int d = 0; d < D; ++d)
    {
      double value = _samples[m - 1][d];
      thetaminus[d] = value;
      thetaplus[d] = value;
    }
    for (int d = 0; d < D; ++d)
    {
      int value = r0[d];
      rminus[d] = value;
      rplus[d] = value;
    }
    double gradminus = grad;
    double gradplus = grad;

    //Initial height.
    int j = 0;
    //If all else fails, the next sample is the previous sample.
    for (int d = 0; d < D; ++d)
    {
      _samples[m][d] = _samples[m - 1][d];
    }
    //Initially the only valid point is the initial point.
    int n = 1;
    //Main loop---keep going until the criterion s == 0.
    int s = 1;
  }
  delete [] rminus;
  rminus = NULL;
  delete [] rplus;
  rplus = NULL;
  delete [] thetaminus;
  thetaminus = NULL;
  delete [] thetaplus;
  thetaplus = NULL;
  delete [] r0;
  r0 = NULL;
}

TEST_F(test_nuts, nuts)
{
  nuts o;

  size_t M = 5;
  size_t D = 3;
  vector<double> theta0;
  theta0.push_back(1);
  theta0.push_back(2);
  theta0.push_back(3);
  o.compute(M, theta0);
  matrix m = o.get_samples();

  ASSERT_EQ(m.size(), M);
  ASSERT_DOUBLE_EQ(m[0][0], 1);
  ASSERT_DOUBLE_EQ(m[0][1], 2);
  ASSERT_DOUBLE_EQ(m[0][2], 3);
  for (int i = 1; i < m.size(); ++i)
  {
    vector<double>& v = m[i];
    ASSERT_EQ(v.size(), D);
    for (int j = 0; j < v.size(); ++j)
    {
      //ASSERT_DOUBLE_EQ(v[j], 0);
    }
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
