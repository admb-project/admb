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
  double* _r0;
  double* _thetaminus;
  double* _thetaplus;
  double* _thetaprime;
  double* _thetaprime2;
  double* _thetavec;
  double* _rminus;
  double* _rplus;
  double* _rprime;
  double* _gradprime;
  double* _gradprime2;
  double _logpprime;
  double* _gradminus;
  double* _gradplus;
  double* _grad;
  int _nprime;
  bool _sprime;
  size_t _M;
  size_t _D;
  void f(const double*) {}
  bool stop_criterion
  (
    double* thetaminus,
    double* thetaplus,
    double* rminus,
    double* rplus
  );
  void leapfrog
  (
    double* theta, 
    double* r,
    double* grad,
    double epsilon
  );
  void build_tree
  (
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
  nuts(const size_t M, const size_t D);
  ~nuts();

  void compute
  (
    const double epsilon,
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
  _r0(NULL),
  _grad(NULL),
  _samples(NULL),
  _thetaprime(NULL),
  _thetaprime2(NULL),
  _thetavec(NULL),
  _rprime(NULL),
  _gradprime(NULL),
  _gradprime2(NULL),
  _logpprime(0),
  _nprime(0),
  _thetaminus(NULL),
  _thetaplus(NULL),
  _rminus(NULL),
  _rplus(NULL),
  _gradminus(NULL),
  _gradplus(NULL),
  _sprime(false)
{
}
nuts::nuts(const size_t M, const size_t D):
  _D(D),
  _M(M)
{
  _grad = new double[_D];
  _thetaminus = new double[_D];
  _thetaplus = new double[_D];
  _rminus = new double[_D];
  _rplus = new double[_D];
  _gradminus = new double[_D];
  _gradplus = new double[_D];
  _r0 = new double[_D];
  _thetavec = new double[_D];
  _rprime = new double[_D];
  _thetaprime = new double[_D];
  _thetaprime2 = new double[_D];
  _gradprime = new double[_D];
  _gradprime2 = new double[_D];
  _samples = new double*[_M];
  for (int m = 0; m < _M; ++m)
  {
    double* v = new double[_M];
    for (int d = 0; d < _D; ++d)
    {
      v[d] = 0;
    }
    _samples[m] = v;
  }
}
/**
Destructor
*/
nuts::~nuts()
{
  if (_grad != NULL)
  {
    delete [] _grad;
    _grad = NULL;
  }
  if (_samples != NULL)
  {
    delete [] _samples;
    _samples = NULL;
  }
  if (_gradprime2 != NULL)
  {
    delete [] _gradprime2;
    _gradprime2 = NULL;
  }
  if (_thetaprime2 != NULL)
  {
    delete [] _thetaprime2;
    _thetaprime2 = NULL;
  }
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
  if (_thetavec != NULL)
  {
    delete [] _thetavec;
    _thetavec = NULL;
  }
  if (_gradprime != NULL)
  {
    delete [] _gradprime;
    _gradprime = NULL;
  }
  if (_r0 != NULL)
  {
    delete [] _r0;
    _r0 = NULL;
  }
  if (_gradminus != NULL)
  {
    delete [] _gradminus;
    _gradminus = NULL;
  }
  if (_gradplus != NULL)
  {
    delete [] _gradplus;
    _gradplus = NULL;
  }
  if (_rminus != NULL)
  {
    delete [] _rminus;
    _rminus = NULL;
  }
  if (_rplus != NULL)
  {
    delete [] _rplus;
    _rplus = NULL;
  }
  if (_thetaminus != NULL)
  {
    delete [] _thetaminus;
    _thetaminus = NULL;
  }
  if (_thetaplus != NULL)
  {
    delete [] _thetaplus;
    _thetaplus = NULL;
  }
}
bool nuts::stop_criterion
(
  double* thetaminus,
  double* thetaplus,
  double* rminus,
  double* rplus
)
{
  for (size_t d = 0; d < _D; ++d)
  {
    _thetavec[d] = thetaplus[d] - thetaminus[d];
  }
  double minus = 0;
  double plus = 0;
  for (size_t d = 0; d < _D; ++d)
  {
    minus += _thetavec[d] * thetaminus[d];
    plus += _thetavec[d] * thetaplus[d];
  }
  return minus >= 0 && plus >= 0;
}
void nuts::leapfrog
(
  double* theta, 
  double* r,
  double* grad,
  double epsilon
)
{
  for (size_t d = 0; d < _D; ++d)
  {
    _rprime[d] = r[d] + 0.5 * epsilon * grad[d];
  }
  for (size_t d = 0; d < _D; ++d)
  {
    _thetaprime[d] = theta[d] + epsilon * _rprime[d];
  }
  //[logpprime, gradprime] = f(thetaprime);
  f(_thetaprime);
  for (size_t d = 0; d < _D; ++d)
  {
    _gradprime[d] = 0;
  }
  for (size_t d = 0; d < _D; ++d)
  {
    _rprime[d] += 0.5 * epsilon * _gradprime[d];
  }
}
void nuts::build_tree
(
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
    leapfrog(theta, r, grad, v * epsilon);
    //joint = logpprime - 0.5 * (rprime * rprime');
    double joint = 0;
    for (size_t d = 0; d < _D; ++d)
    {
      joint += _rprime[d] * _rprime[d];
    }
    joint *= -0.5;
    joint += _logpprime;
    //Is the new point in the slice?
    _nprime = logu < joint;
    //Is the simulation wildly inaccurate?
    _sprime = (logu - 1000) < joint;
    //Set the return values---minus=plus for all things here, since the
    //"tree" is of depth 0.
    for (size_t d = 0; d < _D; ++d)
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
    build_tree(theta, r, grad, logu, v, j - 1, epsilon);
    //No need to keep going if the stopping criteria were met in the first
    //subtree.
    if (_sprime == 1)
    {
      int nprime2 = 0;
      bool sprime2 = false;
      double logpprime2 = 0;
      if (v == -1)
      {
        //[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime2, gradprime2, logpprime2, nprime2, sprime2]
        build_tree(_thetaminus, _rminus, _gradminus, logu, v, j - 1, epsilon);
      }
      else
      {
        //[~, ~, ~, thetaplus, rplus, gradplus, thetaprime2, gradprime2, logpprime2, nprime2, sprime2]
        build_tree(_thetaplus, _rplus, _gradplus, logu, v, j - 1, epsilon);
      }
      //Choose which subtree to propagate a sample up from.
      if (rand() < nprime2 / (_nprime + nprime2))
      {
        for (size_t d = 0; d < _D; ++d)
        {
          _thetaprime[d] = _thetaprime2[d];
          _gradprime[d] = _gradprime2[d];
        }
        _logpprime = logpprime2;
      }
      //Update the number of valid points.
      _nprime += nprime2;
      //Update the stopping criterion.
      _sprime = sprime2 && stop_criterion(_thetaminus, _thetaplus, _rminus, _rplus);
    }
  }
}
void nuts::compute
(
  const double epsilon,
  const vector<double>& theta0
)
{
  for (int d = 0; d < _D; ++d)
  {
    _samples[0][d] = theta0[d];
  }
  for (int m = 1; m < _M; ++m)
  {
    for (int d = 0; d < _D; ++d)
    {
      _samples[m][d] = 0;
    }
  }
  double logp = 0;
  f(theta0.data());

  for (int m = 1; m < _M; ++m)
  {
    //Resample momenta.
    for (int d = 0; d < _D; ++d)
    {
      _r0[d] = randn();
    }
    //Joint log-probability of theta and momenta r.
    double joint = 0;
    for (int d = 0; d < _D; ++d)
    {
      joint += _r0[d] * _r0[d];
    }
    joint *= -0.5;
    joint += logp;
    //Resample u ~ uniform([0, exp(joint)]).
    //Equivalent to (log(u) - joint) ~ exponential(1).
    double logu = joint - exprnd(1);
    //Initialize tree.
    for (int d = 0; d < _D; ++d)
    {
      double value = _samples[m - 1][d];
      _thetaminus[d] = value;
      _thetaplus[d] = value;
    }
    for (int d = 0; d < _D; ++d)
    {
      int value = _r0[d];
      _rminus[d] = value;
      _rplus[d] = value;
    }
    for (int d = 0; d < _D; ++d)
    {
      _gradminus[d] = _grad[d];
      _gradplus[d] = _grad[d];
    }
    //Initial height.
    int j = 0;
    //If all else fails, the next sample is the previous sample.
    for (int d = 0; d < _D; ++d)
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
        build_tree(_thetaminus, _rminus, _gradminus, logu, v, j, epsilon);
      }
      else
      {
        build_tree(_thetaplus, _rplus, _gradplus, logu, v, j, epsilon);
      }
      //Use Metropolis-Hastings to decide whether or not to move to a
      //point from the half-tree we just generated.
      if (_sprime && (n * rand() < _nprime))
      {
        for (int d = 0; d < _D; ++d)
        {
          //samples(m, :) = thetaprime;
          _samples[m][d] = _thetaprime[d];
          _grad[d] = _gradprime[d];
        }
        logp = _logpprime;
      }
      //Update number of valid points we've seen.
      n += _nprime;
      //Decide if it's time to stop.
      s = _sprime && stop_criterion(_thetaminus, _thetaplus, _rminus, _rplus);
      s = 0;
      //Increment depth.
      ++j;
    }
  }
}
TEST_F(test_nuts, default_constructor)
{
  nuts o;
}
TEST_F(test_nuts, constructor_M_D)
{
  size_t M = 10;
  size_t D = 2;
  nuts o(M, D);
}
TEST_F(test_nuts, nuts)
{
  size_t M = 10;
  size_t D = 2;
  nuts o(M, D);
  vector<double> theta0;
  theta0.push_back(randn());
  theta0.push_back(randn());
  double epsilon = 0.5;
  o.compute(epsilon, theta0);
  double** samples = o.get_samples();

  for (int m = 1; m < M; ++m)
  {
    for (int d = 0; d < D; ++d)
    {
      cout <<  samples[m][d] << ' ';
    }
    cout << endl;
  }
  samples = NULL;
}
