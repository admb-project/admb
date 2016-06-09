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
  double* _thetaprime;
  double* _rprime;
  double*  _gradprime;
  double _logpprime;

  void f(const double)
  {
  }
public:
  leapfrog();
  ~leapfrog();

  void compute
  (
    const size_t D,
    double* theta, 
    double* r,
    double* grad,
    double epsilon,
    int f
  );

  double* get_thetaprime() const;
  double* get_rprime() const;
  double* get_gradprime() const;
  double get_logpprime() const;
};
leapfrog::leapfrog():
  _thetaprime(NULL),
  _rprime(NULL),
  _gradprime(NULL),
  _logpprime(0)
{
}
leapfrog::~leapfrog()
{
  if (_rprime != NULL)
  {
    delete [] _rprime;
    _rprime = NULL;
  }
  if (_thetaprime != NULL)
  {
    delete [] _thetaprime;
    _thetaprime = NULL;
  }
  if (_gradprime != NULL)
  {
    delete [] _gradprime;
    _gradprime = NULL;
  }
}
double* leapfrog::get_thetaprime() const
{
  return _thetaprime;
}
double* leapfrog::get_rprime() const
{
  return _rprime;
}
double* leapfrog::get_gradprime() const
{
  return _gradprime;
}
double leapfrog::get_logpprime() const
{
  return _logpprime;
}
void leapfrog::compute
(
  const size_t D,
  double* theta, 
  double* r,
  double* grad,
  double epsilon,
  int f
)
{
  if (_rprime != NULL)
  {
    delete [] _rprime;
    _rprime = NULL;
  }
  _rprime = new double[D];
  for (size_t d = 0; d < D; ++d)
  {
    _rprime[d] = r[d] + 0.5 * epsilon * grad[d];
  }
  if (_thetaprime != NULL)
  {
    delete [] _thetaprime;
    _thetaprime = NULL;
  }
  _thetaprime = new double[D];
  for (size_t d = 0; d < D; ++d)
  {
    _thetaprime[d] = theta[d] + epsilon * _rprime[d];
  }
  if (_gradprime != NULL)
  {
    delete [] _gradprime;
    _gradprime = NULL;
  }
  _gradprime = new double[D];
  //[logpprime, gradprime] = f(thetaprime);
  for (size_t d = 0; d < D; ++d)
  {
    _gradprime[d] = 0;
  }
  for (size_t d = 0; d < D; ++d)
  {
    _rprime[d] += 0.5 * epsilon * _gradprime[d];
  }
}

typedef double** matrix;

class nuts
{
  matrix _samples;
  leapfrog _leapfrog;

  double exprnd(double d);

  void build_tree
  (
    const size_t D,
    double* theta,
    double* r,
    double* grad,
    double logu,
    int v,
    int j,
    double epsilon,
    int f
  );
public:
  nuts();
  ~nuts();

  void compute
  (
    const double epsilon,
    const size_t M,
    const vector<double>& theta0
  );

  matrix get_samples()
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
void nuts::build_tree
(
  const size_t D,
  double* theta,
  double* r,
  double* grad,
  double logu,
  int v,
  int j,
  double epsilon,
  int f
)
{
  if (j == 0)
  {
    //Base case: Take a single leapfrog step in the direction v.
    _leapfrog.compute(D, theta, r, grad, v * epsilon, f);
    //joint = logpprime - 0.5 * (rprime * rprime');
    double joint = 0;
    double* rprime = _leapfrog.get_rprime();
    for (size_t d = 0; d < D; ++d)
    {
      joint += rprime[d] * 2.0;
    }
    joint *= -0.5;
    joint += _leapfrog.get_logpprime();
    //Is the new point in the slice?
    bool nprime = logu < joint;
    //Is the simulation wildly inaccurate?
    bool sprime = (logu - 1000) < joint;
    //Set the return values---minus=plus for all things here, since the
    //"tree" is of depth 0.
/*
    thetaminus = thetaprime;
    thetaplus = thetaprime;
    rminus = rprime;
    rplus = rprime;
    gradminus = gradprime;
    gradplus = gradprime;
*/
  }
  else
  {
    //Recursion: Implicitly build the height j-1 left and right subtrees.
    build_tree(D, theta, r, grad, logu, v, j - 1, epsilon, f);
  }
}
void nuts::compute
(
  const double epsilon,
  const size_t M,
  const vector<double>& theta0
)
{
  size_t D = theta0.size();
  _samples = new double*[M];
  for (int m = 0; m < M; ++m)
  {
    double* v = new double[M];
    for (int d = 0; d < D; ++d)
    {
      v[d] = 0;
    }
    _samples[m] = v;
  }
  for (int d = 0; d < D; ++d)
  {
    _samples[0][d] = theta0[d];
  }

  //f
  double logp = 0;
  double grad = 0;

  double* r0 = new double[D];
  double* thetaminus = new double[D];
  double* thetaplus = new double[D];
  double* rminus = new double[D];
  double* rplus = new double[D];
  double* gradminus = new double[D];
  double* gradplus = new double[D];
  for (int m = 1; m < M; ++m)
  {
    //Resample momenta.
    for (int d = 0; d < D; ++d)
    {
      r0[d] = (rand() % 100) * 0.01;
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
    for (int d = 0; d < D; ++d)
    {
      gradminus[d] = grad;
      gradplus[d] = grad;
    }

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
    int s = 10;
    while (s > 0)
    {
      //Choose a direction. -1=backwards, 1=forwards.
      int v = rand() % 2 - 1;

      int f;
      //Double the size of the tree.
      if (v == -1)
      {
        build_tree(D, thetaminus, rminus, gradminus, logu, v, j, epsilon, f);
      }
      else
      {
        build_tree(D, thetaplus, rplus, gradplus, logu, v, j, epsilon, f);
      }

      --s;
    }
  }
  delete [] gradminus;
  gradminus = NULL;
  delete [] gradplus;
  gradplus = NULL;
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

  double epsilon = 0.5;
  size_t M = 5;
  size_t D = 3;
  vector<double> theta0;
  theta0.push_back(1);
  theta0.push_back(2);
  theta0.push_back(3);
  o.compute(epsilon, M, theta0);
  double** m = o.get_samples();

  ASSERT_DOUBLE_EQ(m[0][0], 1);
  ASSERT_DOUBLE_EQ(m[0][1], 2);
  ASSERT_DOUBLE_EQ(m[0][2], 3);
  for (int i = 1; i < M; ++i)
  {
    for (int j = 0; j < D; ++j)
    {
      //ASSERT_DOUBLE_EQ(m[i][j], 0);
    }
  }
}
TEST_F(test_nuts, leapfrog)
{
  leapfrog o;
  ASSERT_TRUE(o.get_thetaprime() == NULL);
  ASSERT_TRUE(o.get_rprime() == NULL);
  ASSERT_TRUE(o.get_gradprime() == NULL);
  ASSERT_DOUBLE_EQ(o.get_logpprime(), 0);

  const size_t D = 2;
  double thetaprime[D] = {0, 0};
  double rprime[D] = {0, 0};
  double gradprime[D] = {0, 0};
  o.compute(D, &thetaprime[0], &rprime[0], &gradprime[0], 1, -1);
  for (size_t d = 0; d < D; ++d)
  {
    ASSERT_DOUBLE_EQ(o.get_thetaprime()[d], 0);
    ASSERT_DOUBLE_EQ(o.get_rprime()[d], 0);
    ASSERT_DOUBLE_EQ(o.get_gradprime()[d], 0);
  }
  ASSERT_DOUBLE_EQ(o.get_logpprime(), 0);

  thetaprime[0] = 1;
  thetaprime[1] = 1;
  rprime[0] = 1;
  rprime[1] = 1;
  gradprime[0] = 1;
  gradprime[1] = 1;
  o.compute(D, &thetaprime[0], &rprime[0], &gradprime[0], 1, -1);
  for (size_t d = 0; d < D; ++d)
  {
    ASSERT_DOUBLE_EQ(o.get_thetaprime()[d], 2.5);
    ASSERT_DOUBLE_EQ(o.get_rprime()[d], 1.5);
    ASSERT_DOUBLE_EQ(o.get_gradprime()[d], 0);
  }
  ASSERT_DOUBLE_EQ(o.get_logpprime(), 0);
}
