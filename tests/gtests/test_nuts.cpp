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

double randn()
{
  std::random_device rd;
  std::mt19937 gen(rd());
 
  // values near the mean are the most likely
  // standard deviation affects the dispersion of generated values from the mean
  std::normal_distribution<> d(0,1);
  return d(gen);
}
double exprnd(double p)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  // if particles decay once per second on average,
  // how much time, in seconds, until the next one?
  std::exponential_distribution<> d(p);
  return d(gen);
}

typedef double** matrix;
class nuts
{
  matrix _samples;
  double* _thetaminus;
  double* _thetaplus;
  double* _thetaprime;
  double* _rminus;
  double* _rplus;
  double* _rprime;
  double* _gradprime;
  double _logpprime;
  double* _gradminus;
  double* _gradplus;
  int _nprime;
  bool _sprime;
  void f(const double*) {}
  bool stop_criterion
  (
    const size_t D,
    double* thetaminus,
    double* thetaplus,
    double* rminus,
    double* rplus
  );
  void leapfrog
  (
    const size_t D,
    double* theta, 
    double* r,
    double* grad,
    double epsilon
  );
  void build_tree
  (
    const size_t D,
    double* theta,
    double* r,
    double* grad,
    double logu,
    int v,
    int j,
    double epsilon
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
/**
Default constructor
*/
nuts::nuts():
  _thetaprime(NULL),
  _rprime(NULL),
  _gradprime(NULL),
  _logpprime(0),
  _nprime(0),
  _sprime(false)
{
}
/**
Destructor
*/
nuts::~nuts()
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
bool nuts::stop_criterion
(
  const size_t D,
  double* thetaminus,
  double* thetaplus,
  double* rminus,
  double* rplus
)
{
  double* thetavec = new double[D];
  for (size_t d = 0; d < D; ++d)
  {
    thetavec[d] = thetaplus[d] - thetaminus[d];
  }
  double minus = 0;
  double plus = 0;
  for (size_t d = 0; d < D; ++d)
  {
    minus += thetavec[d] * thetaminus[d];
    plus += thetavec[d] * thetaplus[d];
  }
  return minus >= 0 && plus >= 0;
}
void nuts::leapfrog
(
  const size_t D,
  double* theta, 
  double* r,
  double* grad,
  double epsilon
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
  f(_thetaprime);

  for (size_t d = 0; d < D; ++d)
  {
    _gradprime[d] = 0;
  }
  for (size_t d = 0; d < D; ++d)
  {
    _rprime[d] += 0.5 * epsilon * _gradprime[d];
  }
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
  double epsilon
)
{
  if (j == 0)
  {
    //Base case: Take a single leapfrog step in the direction v.
    leapfrog(D, theta, r, grad, v * epsilon);
    //joint = logpprime - 0.5 * (rprime * rprime');
    double joint = 0;
    for (size_t d = 0; d < D; ++d)
    {
      joint += _rprime[d] * 2.0;
    }
    joint *= -0.5;
    joint += _logpprime;
    //Is the new point in the slice?
    _nprime = logu < joint;
    //Is the simulation wildly inaccurate?
    _sprime = (logu - 1000) < joint;
    //Set the return values---minus=plus for all things here, since the
    //"tree" is of depth 0.
    for (size_t d = 0; d < D; ++d)
    {
      _thetaminus[d] = _thetaprime[d];
      _thetaplus[d] = _thetaprime[d];
      _rminus[d] = _rprime[d];
      _rplus[d] = _rprime[d];
      _gradminus[d] = _gradprime[d];
      _gradplus[d] = _gradprime[d];
    }
  }
  else
  {
    //Recursion: Implicitly build the height j-1 left and right subtrees.
    //[thetaminus, rminus, gradminus, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime]
    build_tree(D, theta, r, grad, logu, v, j - 1, epsilon);
    //No need to keep going if the stopping criteria were met in the first
    //subtree.
    if (_sprime == 1)
    {
      int nprime2 = 0;
      bool sprime2 = false;
      if (v == -1)
      {
        //[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime2, gradprime2, logpprime2, nprime2, sprime2]
        build_tree(D, _thetaminus, _rminus, _gradminus, logu, v, j - 1, epsilon);
      }
      else
      {
        //[~, ~, ~, thetaplus, rplus, gradplus, thetaprime2, gradprime2, logpprime2, nprime2, sprime2]
        build_tree(D, _thetaplus, _rplus, _gradplus, logu, v, j - 1, epsilon);
      }
/*
      % Choose which subtree to propagate a sample up from.
      if (rand() < nprime2 / (nprime + nprime2))
            thetaprime = thetaprime2;
            gradprime = gradprime2;
            logpprime = logpprime2;
      end
*/
      //Update the number of valid points.
      _nprime += nprime2;
      //Update the stopping criterion.
      _sprime = sprime2 && stop_criterion(D, _thetaminus, _thetaplus, _rminus, _rplus);
    }
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

  for (int m = 0; m < M; ++m)
  {
    for (int d = 0; d < D; ++d)
    {
      cout <<  _samples[m][d] << ' ';
    }
    cout <<  endl;
  }
 
  double logp = 0;
  double* grad = new double[D];
  f(theta0.data());

  double* r0 = new double[D];
  _thetaminus = new double[D];
  _thetaplus = new double[D];
  _rminus = new double[D];
  _rplus = new double[D];
  _gradminus = new double[D];
  _gradplus = new double[D];
  for (int m = 1; m < M; ++m)
  {
    //Resample momenta.
    for (int d = 0; d < D; ++d)
    {
      r0[d] = randn();
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
      _thetaminus[d] = value;
      _thetaplus[d] = value;
    }
    for (int d = 0; d < D; ++d)
    {
      int value = r0[d];
      _rminus[d] = value;
      _rplus[d] = value;
    }
    for (int d = 0; d < D; ++d)
    {
      _gradminus[d] = grad[d];
      _gradplus[d] = grad[d];
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
      //Double the size of the tree.
      if (v == -1)
      {
        build_tree(D, _thetaminus, _rminus, _gradminus, logu, v, j, epsilon);
      }
      else
      {
        build_tree(D, _thetaplus, _rplus, _gradplus, logu, v, j, epsilon);
      }
      //Use Metropolis-Hastings to decide whether or not to move to a
      //point from the half-tree we just generated.
      if (_sprime && (n * rand() < _nprime))
      {
        for (int d = 0; d < D; ++d)
        {
          //samples(m, :) = thetaprime;
          _samples[m][d] = _thetaprime[d];
          grad[d] = _gradprime[d];
        }
        logp = _logpprime;
      }
      //Update number of valid points we've seen.
      n += _nprime;
      //Decide if it's time to stop.
      s = _sprime && stop_criterion(D, _thetaminus, _thetaplus, _rminus, _rplus);
      s = 0;
      //Increment depth.
      ++j;
    }
  }
  delete [] grad;
  grad = NULL;
  delete [] _gradminus;
  _gradminus = NULL;
  delete [] _gradplus;
  _gradplus = NULL;
  delete [] _rminus;
  _rminus = NULL;
  delete [] _rplus;
  _rplus = NULL;
  delete [] _thetaminus;
  _thetaminus = NULL;
  delete [] _thetaplus;
  _thetaplus = NULL;
  delete [] r0;
  r0 = NULL;
}

TEST_F(test_nuts, nuts)
{
  nuts o;

  double epsilon = 0.5;
  size_t M = 10;
  size_t D = 2;
  vector<double> theta0;
  theta0.push_back(randn());
  theta0.push_back(randn());
  o.compute(epsilon, M, theta0);
  double** m = o.get_samples();

  ASSERT_DOUBLE_EQ(m[0][0], theta0[0]);
  ASSERT_DOUBLE_EQ(m[0][1], theta0[1]);
  for (int i = 1; i < M; ++i)
  {
    for (int j = 0; j < D; ++j)
    {
      //ASSERT_DOUBLE_EQ(m[i][j], 0);
    }
  }
  m = NULL;
}
/*
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
*/
