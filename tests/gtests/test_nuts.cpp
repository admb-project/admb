#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <gtest/gtest.h>

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::pow;
using std::stack;
using std::queue;

class test_nuts: public ::testing::Test {};

//global nfevals;
//int nfevals = 0;

double urand()
{
  std::random_device rd;
  std::mt19937 gen(rd());

  // values near the mean are the most likely
  // standard deviation affects the dispersion of generated values from the mean
  std::uniform_real_distribution<double> d(0.0, 1.0);
  return d(gen);
}
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
//[logpprime, gradprime] = f(thetaprime);
void f(const size_t D, const double* theta, double& logp, double* grad)
{
  //Precision matrix with covariance [1, 1.98; 1.98, 4].
  //A = [50.251256, -24.874372; -24.874372, 12.562814];
  //A = inv([1, 1.98; 1.98, 4]);
  double A[2][2];
  A[0][0] = 50.251256;
  A[0][1] = -24.874372;
  A[1][0] = -24.874372;
  A[1][1] = 12.562814;

  //grad = -theta * A;
  for (int d = 0; d < D; ++d)
  {
    grad[d] = 0;
    for (int j = 0; j < D; ++j)
    {
      grad[d] -= theta[j] * A[d][j];
    }
  }
  //logp = 0.5 * grad * theta';
  logp = 0;
  for (int d = 0; d < D; ++d)
  {
    logp += grad[d] * theta[d];
  }
  logp *= 0.5;
}

typedef double** matrix;
class nuts
{
public:
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
  f(_D, _thetaprime, _logpprime, _gradprime);
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
    //[_thetaprime, _rprime, _gradprime, _logpprime] =
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
      int nprime2 = _nprime;
      bool sprime2 = _sprime;
      double logpprime2 = _logpprime;
      for (size_t d = 0; d < _D; ++d)
      {
        _thetaprime2[d] = _thetaprime[d];
        _gradprime2[d] = _gradprime[d];
      }
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
      assert(_nprime + nprime2 != 0);
      if (urand() > nprime2 / (_nprime + nprime2))
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
      _sprime = _sprime && sprime2 && stop_criterion(_thetaminus, _thetaplus, _rminus, _rplus);
    }
  }
}
void nuts::compute
(
  const double epsilon,
  const vector<double>& theta0
)
{
  //samples = zeros(M, D);
  for (int m = 1; m < _M; ++m)
  {
    for (int d = 0; d < _D; ++d)
    {
      _samples[m][d] = 0;
    }
  }
  //[logp grad] = f(theta0);
  double logp = 0;
  f(_D, theta0.data(), logp, _grad);
  //samples(1, :) = theta0;
  for (int d = 0; d < _D; ++d)
  {
    _samples[0][d] = theta0[d];
  }
  //for m = 2:M,
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
    int s = 1;
    while (s == 1)
    {
      //Choose a direction. -1=backwards, 1=forwards.
      int v = rand() % 2 - 1;
      //Double the size of the tree.
      if (v == -1)
      {
        //[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime, gradprime, logpprime, nprime, sprime]
        build_tree(_thetaminus, _rminus, _gradminus, logu, v, j, epsilon);
      }
      else
      {
        //[~, ~, ~, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime]
        build_tree(_thetaplus, _rplus, _gradplus, logu, v, j, epsilon);
      }
      //Use Metropolis-Hastings to decide whether or not to move to a
      //point from the half-tree we just generated.
      if (_sprime && (urand() < _nprime / n))
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
      //Increment depth.
      ++j;
    }
  }
}
/*
TEST_F(test_nuts, urand)
{
  for (int i = 0; i < 10; ++i)
  {
    double v = urand();
    ASSERT_TRUE(0 <= v && v <= 1.0);
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
TEST_F(test_nuts, f)
{
  size_t M = 10;
  size_t D = 2;
  nuts o(M, D);
  double theta[2];
  theta[0] = -0.366410276756522;
  theta[1] = 0.673482475958359;
  f(D, theta, o._logpprime, o._gradprime);
  ASSERT_DOUBLE_EQ(o._logpprime, -12.360661901158696);
  ASSERT_DOUBLE_EQ(o._gradprime[0], 35.165030260792108);
  ASSERT_DOUBLE_EQ(o._gradprime[1], -17.575060606389016);
}
TEST_F(test_nuts, stop_criterion)
{
  size_t M = 10;
  size_t D = 2;
  nuts o(M, D);
  double thetaminus[D];
  double thetaplus[D];
  double rminus[D];
  double rplus[D];
  thetaminus[0] = -1.565063190275075;
  thetaminus[1] = -1.812857295920611;
  thetaplus[0] = 3.667092345825298;
  thetaplus[1] = -3.455291001162557;
  rminus[0] = 2.076135004939211;
  rminus[1] = 0.753976334819958;
  rplus[0] = -57.091736422018627;
  rplus[1] = 30.371331922488640;
  ASSERT_FALSE(o.stop_criterion(&thetaminus[0], &thetaplus[0], &rminus[0], &rplus[0]));
}
TEST_F(test_nuts, build_tree)
{
  size_t M = 10;
  size_t D = 2;
  nuts o(M, D);
  double theta[2];
  theta[0] = 0.376950536732441;
  theta[1] = 1.180567568820727;
  double r[2];
  r[0] = -0.311157552075058;
  r[1] = 0.907531121741474;
  double grad[2];
  grad[0] = 10.423638957303069;
  grad[1] = -5.454842905244590;
  double logu = -2.736214127195197;
  int v = 1;
  int j = 3;
  double epsilon = 0.191665695786453;
  o.build_tree(theta, r, grad, logu, v, j, epsilon);
}
*/
/*
TEST_F(test_nuts, build_tree2)
{
  size_t M = 5;
  size_t D = 2;
  nuts o(M, D);
  double theta[2];
  theta[0] = -1.184149365398408;
  theta[1] = -1.879783074522205;
  double r[2];
  r[0] = -1.250274784716743;
  r[1] = -0.177547924046123;
  double grad[2];
  grad[0] = 12.746569427903886;
  grad[1] = -5.839606692913332;
  double logu = -3.907755346153537;
  int v = 1;
  int j = 0;
  double epsilon = 0.196260851195362;
  o.build_tree(theta, r, grad, logu, v, j, epsilon);
  ASSERT_DOUBLE_EQ(o._thetaprime[0], -1.184041127901299);
  ASSERT_DOUBLE_EQ(o._thetaprime[1], -2.027094705857849);
  ASSERT_DOUBLE_EQ(o._rprime[0], 0.89126626313958324);
  ASSERT_DOUBLE_EQ(o._rprime[1], -1.141764966641634);
  ASSERT_DOUBLE_EQ(o._gradprime[0], 9.0768460399582551);
  ASSERT_DOUBLE_EQ(o._gradprime[1], -3.9862657286396512);
  ASSERT_EQ(o._sprime, 1);
  ASSERT_EQ(o._nprime, 1);
  ASSERT_DOUBLE_EQ(o._logpprime, -1.543893231081825);
}
*/
/*
TEST_F(test_nuts, compute)
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
*/

int _D(2);
int _nfevals = 0;
double _rprime[2];
double _thetaprime[2];
double _gradprime[2];
double _logpprime;

void correlated_normal(double* theta)
{
  //A = [50.251256, -24.874372; -24.874372, 12.562814];
  double A[2][2];
  A[0][0] = 50.251256;
  A[0][1] = -24.874372;
  A[1][0] = -24.874372;
  A[1][1] = 12.562814;

  double grad[2];
  //grad = -theta * A;
  for (int d = 0; d < _D; ++d)
  {
    grad[d] = 0;
    for (int j = 0; j < _D; ++j)
    {
      grad[d] -= theta[j] * A[d][j];
    }
  }
  for (int d = 0; d < _D; ++d)
  {
    _gradprime[d] = grad[d];
  }
  //logp = 0.5 * grad * theta';
  double logp = 0;
  for (int d = 0; d < _D; ++d)
  {
    logp += grad[d] * theta[d];
  }
  logp *= 0.5;
  _logpprime = logp;

  //[logpprime, gradprime] = f(thetaprime);
}
void f(double* theta)
{
  correlated_normal(theta);
}
void leapfrog
(
  double* theta,
  double* r,
  double* grad,
  double epsilon
)
{
  //rprime = r + 0.5 * epsilon * grad;
  for (int d = 0; d < _D; ++d)
  {
    _rprime[d] = r[d] + 0.5 * epsilon * grad[d];
  }
  //thetaprime = theta + epsilon * rprime;
  for (int d = 0; d < _D; ++d)
  {
    _thetaprime[d] = theta[d] + epsilon * _rprime[d];
  }
  //[logpprime, gradprime] = f(thetaprime);
  f(_thetaprime);
  //rprime = rprime + 0.5 * epsilon * gradprime;
  for (int d = 0; d < _D; ++d)
  {
    _rprime[d] += 0.5 * epsilon * _gradprime[d];
  }

  //nfevals = nfevals + 1;
  ++_nfevals;
}
double find_reasonable_epsilon
(
  double* theta0,
  double* grad0,
  double logp0,
  double* r0
)
{
  double epsilon = 1;

  //Figure out what direction we should be moving epsilon.
  //[~, rprime, ~, logpprime] = leapfrog(theta0, r0, grad0, epsilon, f);
  leapfrog(theta0, r0, grad0, epsilon);

  //acceptprob = exp(logpprime - logp0 - 0.5 * (rprime * rprime' - r0 * r0'));
  double acceptprob = std::exp(_logpprime - logp0 - 0.5 * (_rprime[0] * _rprime[0] + _rprime[1] * _rprime[1] - r0[0] * r0[0] - r0[1] * r0[1]));

  //a = 2 * (acceptprob > 0.5) - 1;
  int a = acceptprob > 0.5 ? 1 : -1;

  //Keep moving epsilon in that direction until acceptprob crosses 0.5.
  //while (acceptprob^a > 2^(-a))
  while (pow(acceptprob, a) > pow(2.0, -a))
  {
    //epsilon = epsilon * 2^a;
    epsilon *= pow(2.0, a);

    //[~, rprime, ~, logpprime] = leapfrog(theta0, r0, grad0, epsilon, f);
    leapfrog(theta0, r0, grad0, epsilon);

    //acceptprob = exp(logpprime - logp0 - 0.5 * (rprime * rprime' - r0 * r0'));
    acceptprob = std::exp(_logpprime - logp0 - 0.5 * (_rprime[0] * _rprime[0] + _rprime[1] * _rprime[1] - r0[0] * r0[0] - r0[1] * r0[1]));
  }

  return epsilon;
}

bool stop_criterion
(
  double* thetaminus,
  double* thetaplus,
  double* rminus,
  double* rplus
)
{
  bool criterion = false;

  //thetavec = thetaplus - thetaminus;
  double thetavec[2];
  for (int d = 0; d < _D; ++d)
  {
    thetavec[d] = thetaplus[d] - thetaminus[d];
  }

  //criterion = (thetavec * rminus' >= 0) && (thetavec * rplus' >= 0);
  criterion = (thetavec[0] * rminus[0] + thetavec[1] * rminus[1] >= 0)
              && (thetavec[0] * rplus[0] + thetavec[1] * rplus[1] >= 0);

  return criterion;
}

double _thetaminus[2];
double _rminus[2];
double _gradminus[2];
double _thetaplus[2];
double _rplus[2];
double _gradplus[2];
int _nprime;
int _sprime;
double _alphaprime;
int _nalphaprime;

queue<double> _random_numbers;
double _rand()
{
  if (_random_numbers.empty())
  {
    return 0.5;
  }
  double random_number = _random_numbers.front();
  _random_numbers.pop();
  return random_number;
}
double exprnd(const int m)
{
  return _rand();
}
void build_tree(
  double* theta,
  double* r,
  double* grad,
  double logu,
  int v,
  int j,
  double epsilon,
  double joint0
)
{
  if (j == 0)
  {
    //% Base case: Take a single leapfrog step in the direction v.
    //[thetaprime, rprime, gradprime, logpprime] = leapfrog(theta, r, grad, v*epsilon, f);
    leapfrog(theta, r, grad, v * epsilon);

    //joint = logpprime - 0.5 * (rprime * rprime');
    double joint = _logpprime;
    for (size_t d = 0; d < _D; ++d)
    {
      joint -= 0.5 * _rprime[d] * _rprime[d];
    }

    //% Is the new point in the slice?
    //nprime = logu < joint;
    _nprime = logu < joint;

    //% Is the simulation wildly inaccurate?
    //sprime = logu - 1000 < joint;
    _sprime = (logu - 1000) < joint;

    //% Set the return values---minus=plus for all things here, since the
    //% "tree" is of depth 0.
    for (int d = 0; d < _D; ++d)
    {
      //thetaminus = thetaprime;
      _thetaminus[d] = _thetaprime[d];

      //thetaplus = thetaprime;
      _thetaplus[d] = _thetaprime[d];

      //rminus = rprime;
      _rminus[d] = _rprime[d];

      //rplus = rprime;
      _rplus[d] = _rprime[d];

      //gradminus = gradprime;
      _gradminus[d] = _gradprime[d];

      //gradplus = gradprime;
      _gradplus[d] = _gradprime[d];
    }

    //% Compute the acceptance probability.
    //alphaprime = min(1, exp(logpprime - 0.5 * (rprime * rprime') - joint0));
    double v = std::exp(joint - joint0);
    _alphaprime = v < 1.0 ? v : 1.0;

    //nalphaprime = 1;
    _nalphaprime = 1;
  }
  else
  {
    //% Recursion: Implicitly build the height j-1 left and right subtrees.
    //[thetaminus, rminus, gradminus, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime, alphaprime, nalphaprime] = ...
    build_tree(theta, r, grad, logu, v, j - 1, epsilon, joint0);

    //% No need to keep going if the stopping criteria were met in the first
    //% subtree.
    if (_sprime == 1)
    {
      double thetaminus[2] = { _thetaminus[0], _thetaminus[1]};
      double rminus[2] = { _rminus[0], _rminus[1]};
      double gradminus[2] = { _gradminus[0], _gradminus[1]};
      double thetaplus[2] = { _thetaplus[0], _thetaplus[1]};
      double rplus[2] = { _rplus[0], _rplus[1]};
      double gradplus[2] = { _gradplus[0], _gradplus[1]};
      double thetaprime[2] = { _thetaprime[0], _thetaprime[1]};
      double gradprime[2] = { _gradprime[0], _gradprime[1]};
      double logpprime = _logpprime;
      int nprime = _nprime;
      bool sprime = _sprime;
      double alphaprime = _alphaprime;
      int nalphaprime = _nalphaprime;
      if (v == -1)
      {
        //[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime2, gradprime2, logpprime2, nprime2, sprime2, alphaprime2, nalphaprime2] = ...
        build_tree(thetaminus, rminus, gradminus, logu, v, j - 1, epsilon, joint0);
        thetaminus[0] = _thetaminus[0];
        thetaminus[1] = _thetaminus[1];
        rminus[0] = _rminus[0];
        rminus[1] = _rminus[1];
        gradminus[0] = _gradminus[0];
        gradminus[1] = _gradminus[1];
      }
      else
      {
        //[~, ~, ~, thetaplus, rplus, gradplus, thetaprime2, gradprime2, logpprime2, nprime2, sprime2, alphaprime2, nalphaprime2] = ...
        build_tree(thetaplus, rplus, gradplus, logu, v, j - 1, epsilon, joint0);
        thetaplus[0] = _thetaplus[0];
        thetaplus[1] = _thetaplus[1];
        rplus[0] = _rplus[0];
        rplus[1] = _rplus[1];
        gradplus[0] = _gradplus[0];
        gradplus[1] = _gradplus[1];
      }//end
      double thetaprime2[2] = { _thetaprime[0], _thetaprime[1]};
      double gradprime2[2] = { _gradprime[0], _gradprime[1]};
      double logpprime2 = _logpprime;
      int nprime2 = _nprime;
      bool sprime2 = _sprime;
      double alphaprime2 = _alphaprime;
      int nalphaprime2 = _nalphaprime;

      //% Choose which subtree to propagate a sample up from.
      double random_number = _rand();
      if (nprime + nprime2 != 0 && random_number < double(nprime2) / double(nprime + nprime2))
      {
        for (int d = 0; d < _D; ++d)
        {
          //thetaprime = thetaprime2;
          _thetaprime[d] = thetaprime2[d];

          //gradprime = gradprime2;
          _gradprime[d] = gradprime2[d];
        }
        _logpprime = logpprime2;
      }
      else
      {
        for (int d = 0; d < _D; ++d)
        {
          //thetaprime = thetaprime;
          _thetaprime[d] = thetaprime[d];

          //gradprime = gradprime;
          _gradprime[d] = gradprime[d];
        }
        _logpprime = logpprime;
      }

      //% Update the number of valid points.
      //nprime = nprime + nprime2;
      _nprime = nprime + nprime2;

      //% Update the stopping criterion.
      _sprime = sprime && sprime2 && stop_criterion(thetaminus, thetaplus, rminus, rplus);

      //% Update the acceptance probability statistics.
      //alphaprime = alphaprime + alphaprime2;
      _alphaprime = alphaprime + alphaprime2;

      //nalphaprime = nalphaprime + nalphaprime2;
      _nalphaprime = nalphaprime + nalphaprime2;

      _thetaminus[0] = thetaminus[0];
      _thetaminus[1] = thetaminus[1];
      _rminus[0] = rminus[0];
      _rminus[1] = rminus[1];
      _gradminus[0] = gradminus[0];
      _gradminus[1] = gradminus[1];

      _thetaplus[0] = thetaplus[0];
      _thetaplus[1] = thetaplus[1];
      _rplus[0] = rplus[0];
      _rplus[1] = rplus[1];
      _gradplus[0] = gradplus[0];
      _gradplus[1] = gradplus[1];
    }//end
  }
}

TEST_F(test_nuts, leapfrog)
{
  ifstream ifs("test_nuts.txt");
  ASSERT_TRUE(ifs.good());

  double theta[2];
  double r[2];
  double grad[2];
  double epsilon;
  int nfevals = 1;
  double thetaprime[2];
  double rprime[2];
  double gradprime[2];
  double logpprime;

  int num = 0;
  while (!ifs.eof())
  {
    std::string line;
    std::getline(ifs, line);
    if (line.compare("leapfrog begin") == 0)
    {
      ++num;
      for (int i = 0; i < 4; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> theta[0] >> theta[1];
      }
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> r[0] >> r[1];
      }
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> grad[0] >> grad[1];
      }
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> epsilon;
      }
      for (int i = 0; i < 10; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> nfevals;
      }
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> thetaprime[0] >> thetaprime[1];
      }
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> rprime[0] >> rprime[1];
      }
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> gradprime[0] >> gradprime[1];
      }
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
      }
      {
        istringstream iss(line);
        iss >> logpprime;
      }
      for (int i = 0; i < 2; ++i)
      {
        std::getline(ifs, line);
      }

      ASSERT_EQ(line.compare("leapfrog end"), 0);
      leapfrog(theta, r, grad, epsilon);

      ASSERT_EQ(num, nfevals);
      ASSERT_EQ(_nfevals, nfevals);

      const double range = nfevals == 5 || nfevals == 6 ? 0.0000001 : 0.0000000001;
      ASSERT_NEAR(gradprime[0], _gradprime[0], range);
      ASSERT_NEAR(gradprime[1], _gradprime[1], range);
      ASSERT_NEAR(thetaprime[0], _thetaprime[0], range);
      ASSERT_NEAR(thetaprime[1], _thetaprime[1], range);
      ASSERT_NEAR(rprime[0], _rprime[0], range);
      ASSERT_NEAR(rprime[1], _rprime[1], range);
      ASSERT_NEAR(logpprime, _logpprime, range);
    }
  }
  ifs.close();
}
TEST_F(test_nuts, find_reasonable_epsilon)
{
  ifstream ifs("test_nuts.txt");
  ASSERT_TRUE(ifs.good());
  while (!ifs.eof())
  {
    std::string line;
    std::getline(ifs, line);
    if (line.compare("find_reasonable_epsilon begin") == 0)
    {
      double theta0[2];
      double grad0[2];
      double logp0 = 0;
      double r0[2];
      double epsilon = 0;
      {
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        istringstream iss(line);
        iss >> theta0[0] >> theta0[1];
      }
      {
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        istringstream iss(line);
        iss >> grad0[0] >> grad0[1];
      }
      {
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        istringstream iss(line);
        iss >> logp0;
      }
      {
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        std::getline(ifs, line);
        istringstream iss(line);
        iss >> r0[0] >> r0[1];
      }
      for (int i = 0; i < 3; ++i)
      {
        std::getline(ifs, line);
      }
      while (line.compare("leapfrog begin") == 0)
      {
        for (int i = 0; i < 53; ++i)
        {
          std::getline(ifs, line);
        }
      }
      ASSERT_EQ(line.compare("epsilon ="), 0);
      {
        std::getline(ifs, line);
        std::getline(ifs, line);
        istringstream iss(line);
        iss >> epsilon;
      }
      for (int i = 0; i < 3; ++i)
      {
        std::getline(ifs, line);
      }
      ASSERT_EQ(line.compare("find_reasonable_epsilon end"), 0);

      //Compare C++
      double result = find_reasonable_epsilon(theta0, grad0, logp0, r0);
      ASSERT_DOUBLE_EQ(result, epsilon);
    }
  }
  ifs.close();
}
TEST_F(test_nuts, top_build_tree)
{
  //input
  double theta[2];
  double r[2];
  double grad[2];
  double logu;
  int v;
  int j;
  double epsilon;
  double joint0;
  //output
  double thetaminus[2];
  double thetaplus[2];
  double rminus[2];
  double rplus[2];
  double gradminus[2];
  double gradplus[2];
  double thetaprime[2];
  double gradprime[2];
  double logpprime;
  int nprime;
  bool sprime;
  double alpha;
  int nalpha;

  ifstream ifs("test_nuts.txt");
  ASSERT_TRUE(ifs.good());

  while (!ifs.eof())
  {
    std::string line;
    std::getline(ifs, line);
    if (line.compare("build_tree main start") == 0)
    {
      while (!_random_numbers.empty()) _random_numbers.pop();
      {
        for (int i = 0; i < 4; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> theta[0] >> theta[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> r[0] >> r[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> grad[0] >> grad[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> logu;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> v;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> j;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> epsilon;
      }
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> joint0;
      }
      for (int i = 0; i < 3; ++i)
      {
        std::getline(ifs, line);
      }
      ASSERT_EQ(line.compare("build_tree main start end"), 0);
    }
    else if (line.compare("build_tree main end") == 0)
    {
      if (v == -1)
      {
        {
          for (int i = 0; i < 4; ++i)
          {
            std::getline(ifs, line);
          }
          istringstream iss(line);
          iss >> thetaminus[0] >> thetaminus[1];
        }
        {
          for (int i = 0; i < 5; ++i)
          {
            std::getline(ifs, line);
          }
          istringstream iss(line);
          iss >> rminus[0] >> rminus[1];
        }
        {
          for (int i = 0; i < 5; ++i)
          {
            std::getline(ifs, line);
          }
          istringstream iss(line);
          iss >> gradminus[0] >> gradminus[1];
        }
      }
      else
      {
        {
          for (int i = 0; i < 4; ++i)
          {
            std::getline(ifs, line);
          }
          istringstream iss(line);
          iss >> thetaplus[0] >> thetaplus[1];
        }
        {
          for (int i = 0; i < 5; ++i)
          {
            std::getline(ifs, line);
          }
          istringstream iss(line);
          iss >> rplus[0] >> rplus[1];
        }
        {
          for (int i = 0; i < 5; ++i)
          {
            std::getline(ifs, line);
          }
          istringstream iss(line);
          iss >> gradplus[0] >> gradplus[1];
        }
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> thetaprime[0] >> thetaprime[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> gradprime[0] >> gradprime[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> logpprime;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> nprime;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> sprime;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> alpha;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> nalpha;
      }
      for (int i = 0; i < 3; ++i)
      {
        std::getline(ifs, line);
      }
      ASSERT_EQ(line.compare("build_tree main end end"), 0);

      build_tree(theta, r, grad, logu, v, j, epsilon, joint0);
      if (j == 0)
      {
        ASSERT_EQ(1, _nalphaprime);
      }
      else
      {
        ASSERT_EQ(sprime, _sprime);
        ASSERT_EQ(nprime, _nprime);
        ASSERT_EQ(nalpha, _nalphaprime);

        const double range = 0.000001;
        ASSERT_NEAR(alpha, _alphaprime, range);
        ASSERT_NEAR(logpprime, _logpprime, range);
        ASSERT_NEAR(thetaprime[0], _thetaprime[0], range);
        ASSERT_NEAR(thetaprime[1], _thetaprime[1], range);
        ASSERT_NEAR(gradprime[0], _gradprime[0], range);
        ASSERT_NEAR(gradprime[1], _gradprime[1], range);

        if (v == -1)
        {
          ASSERT_NEAR(thetaminus[0], _thetaminus[0], range);
          ASSERT_NEAR(thetaminus[1], _thetaminus[1], range);
          ASSERT_NEAR(rminus[0], _rminus[0], range);
          ASSERT_NEAR(rminus[1], _rminus[1], range);
          ASSERT_NEAR(gradminus[0], _gradminus[0], range);
          ASSERT_NEAR(gradminus[1], _gradminus[1], range);
        }
        else
        {
          ASSERT_NEAR(thetaplus[0], _thetaplus[0], range);
          ASSERT_NEAR(thetaplus[1], _thetaplus[1], range);
          ASSERT_NEAR(rplus[0], _rplus[0], range);
          ASSERT_NEAR(rplus[1], _rplus[1], range);
          ASSERT_NEAR(gradplus[0], _gradplus[0], range);
          ASSERT_NEAR(gradplus[1], _gradplus[1], range);
        }
      }
    }
    else if (line.compare("random_number =") == 0)
    {
      std::getline(ifs, line);
      std::getline(ifs, line);
      istringstream iss(line);
      double random_number = -1;
      iss >> random_number;
      if (!(random_number < 0))
      {
        _random_numbers.push(random_number);
      }
    }
  }
  ifs.close();
}
TEST_F(test_nuts, build_tree)
{
  double theta[2];
  double r[2];
  double grad[2];
  double logu;
  int v;
  int j;
  double epsilon;
  double joint0;
  double thetaminus[2];
  double rminus[2];
  double gradminus[2];
  double thetaplus[2];
  double rplus[2];
  double gradplus[2];
  double thetaprime[2];
  double gradprime[2];
  double logpprime;
  int nprime;
  bool sprime;
  double alphaprime;
  int nalphaprime;

  stack<int> s;

  ifstream ifs("test_nuts.txt");
  ASSERT_TRUE(ifs.good());
  while (!ifs.eof())
  {
    std::string line;
    std::getline(ifs, line);
    if (line.compare("build_tree main start") == 0)
    {
      ASSERT_TRUE(s.empty());
      for (int i = 0; i < 47; ++i)
      {
        std::getline(ifs, line);
      }
      ASSERT_EQ(line.compare("build_tree main start end"), 0);
    }
    else if (line.compare("build_tree main end") == 0)
    {
      while (!s.empty())
      {
        s.pop();
      }
      ASSERT_TRUE(s.empty());
      for (int i = 0; i < 52; ++i)
      {
        std::getline(ifs, line);
      }
      ASSERT_EQ(line.compare("build_tree main end end"), 0);
    }
    else if (line.substr(0, 16).compare("build_tree begin") == 0)
    {
      istringstream iss(line.substr(17));
      int inj;
      iss >> inj;
      s.push(inj);
      {
        for (int i = 0; i < 4; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> theta[0] >> theta[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> r[0] >> r[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> grad[0] >> grad[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> logu;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> v;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> j;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> epsilon;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> joint0;
      }
      std::getline(ifs, line);
      if (inj == 0)
      {
        std::getline(ifs, line);
        std::getline(ifs, line);
        ASSERT_EQ(line.compare("leapfrog begin"), 0);
        for (int i = 0; i < 51; ++i)
        {
          std::getline(ifs, line);
        }
        ASSERT_EQ(line.compare("leapfrog end"), 0);
      }
    }
    else if (line.substr(0, 14).compare("build_tree end") == 0)
    {
      istringstream iss(line.substr(15));
      int inj;
      iss >> inj;
      ASSERT_EQ(inj, s.top());
      s.pop();
      std::getline(ifs, line);
      ASSERT_EQ(line.substr(0, 23).compare("build_tree output begin"), 0);
      {
        for (int i = 0; i < 4; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> thetaminus[0] >> thetaminus[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> rminus[0] >> rminus[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> gradminus[0] >> gradminus[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> thetaplus[0] >> thetaplus[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> rplus[0] >> rplus[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> gradplus[0] >> gradplus[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> thetaprime[0] >> thetaprime[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> gradprime[0] >> gradprime[1];
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> logpprime;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> nprime;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> sprime;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> alphaprime;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> nalphaprime;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        double random_number = -1;
        iss >> random_number;
        if (!(random_number < 0))
        {
          _random_numbers.push(random_number);
        }
      }
      for (int i = 0; i < 2; ++i)
      {
        std::getline(ifs, line);
      }
      ASSERT_EQ(line.substr(0, 21).compare("build_tree output end"), 0);

      //Compare C++
      build_tree(theta, r, grad, logu, v, j, epsilon, joint0);

      if (inj == 0)
      {
        const double range = 0.000001;
        ASSERT_NEAR(thetaminus[0], _thetaminus[0], range);
        ASSERT_NEAR(thetaminus[1], _thetaminus[1], range);
        ASSERT_NEAR(rminus[0], _rminus[0], range);
        ASSERT_NEAR(rminus[1], _rminus[1], range);
        ASSERT_NEAR(gradminus[0], _gradminus[0], range);
        ASSERT_NEAR(gradminus[1], _gradminus[1], range);
        ASSERT_NEAR(thetaplus[0], _thetaplus[0], range);
        ASSERT_NEAR(thetaplus[1], _thetaplus[1], range);
        ASSERT_NEAR(rplus[0], _rplus[0], range);
        ASSERT_NEAR(rplus[1], _rplus[1], range);
        ASSERT_NEAR(gradplus[0], _gradplus[0], range);
        ASSERT_NEAR(gradplus[1], _gradplus[1], range);
        ASSERT_NEAR(thetaprime[0], _thetaprime[0], range);
        ASSERT_NEAR(thetaprime[1], _thetaprime[1], range);
        ASSERT_NEAR(gradprime[0], _gradprime[0], range);
        ASSERT_NEAR(gradprime[1], _gradprime[1], range);
        ASSERT_NEAR(logpprime, _logpprime, range);
        ASSERT_EQ(nprime, _nprime);
        ASSERT_EQ(sprime, _sprime);
        ASSERT_NEAR(alphaprime, _alphaprime, range);
        ASSERT_EQ(nalphaprime, _nalphaprime);
      }
    }
  }
  ASSERT_EQ(s.size(), 0);
  //ASSERT_EQ(_random_numbers.size(), 0);
}
//function [samples, epsilon] = nuts_da(f, M, Madapt, theta0, delta)
double _samples[1000][2];
double _epsilon;
void nuts_da(const int M, const int Madapt, double* theta0, const double delta)
{
  _nfevals = 0;

  //D = length(theta0);
  //samples = zeros(M+Madapt, D);
  double samples[1000][2];
  int imax = (M + Madapt) / _D;
  for (int i = 0; i < 1000; ++i)
  {
    for (int j = 0; j < _D; ++j)
    {
      samples[i][j] = 0;
    }
  }

  //[logp grad] = f(theta0);
  f(theta0);
  double logp = _logpprime;
  double grad[2];
  grad[0] = _gradprime[0];
  grad[1] = _gradprime[1];

  //samples(1, :) = theta0;
  samples[0][0] = theta0[0];
  samples[0][1] = theta0[1];

  //% Choose a reasonable first epsilon by a simple heuristic.
  //epsilon = find_reasonable_epsilon(theta0, grad, logp, f);
  double r0[2];
  r0[0] = _rand();
  r0[1] = _rand();

  double epsilon = find_reasonable_epsilon(theta0, grad, logp, r0);

  //% Parameters to the dual averaging algorithm.
  //gamma = 0.05;
  double gamma = 0.05;

  //t0 = 10;
  int t0 = 10;

  //kappa = 0.75;
  double kappa = 0.75;

  //mu = log(10*epsilon);
  double mu = log(epsilon * 10);

  //% Initialize dual averaging algorithm.
  //epsilonbar = 1;
  double epsilonbar = 1;

  //Hbar = 0;
  double Hbar = 0;

  //for m = 2:M+Madapt,
  int mmax = M + Madapt;
  for (int m = 1; m < mmax; ++m)
  //for (int m = 1; m <= 600 - 1; ++m)
  {
    //% Resample momenta.
    //r0 = randn(1, D);
    r0[0] = _rand();
    r0[1] = _rand();

    //% Joint log-probability of theta and momenta r.
    double joint = logp - 0.5 * (r0[0] * r0[0] + r0[1] * r0[1]);

    //% Resample u ~ uniform([0, exp(joint)]).
    //% Equivalent to (log(u) - joint) ~ exponential(1).
    double logu = joint - exprnd(1);

    //% Initialize tree.
    //thetaminus = samples(m-1, :);
    _thetaminus[0] = samples[m - 1][0];
    _thetaminus[1] = samples[m - 1][1];
    //thetaplus = samples(m-1, :);
    _thetaplus[0] = samples[m - 1][0];
    _thetaplus[1] = samples[m - 1][1];
    //rminus = r0;
    _rminus[0] = r0[0];
    _rminus[1] = r0[1];
    //rplus = r0;
    _rplus[0] = r0[0];
    _rplus[1] = r0[1];
    //gradminus = grad;
    _gradminus[0] = grad[0];
    _gradminus[1] = grad[1];
    //gradplus = grad;
    _gradplus[0] = grad[0];
    _gradplus[1] = grad[1];

    //% Initial height j = 0.
    //j = 0;
    int j = 0;

    //% If all else fails, the next sample is the previous sample.
    //samples(m, :) = samples(m-1, :);
    samples[m][0] = samples[m - 1][0];
    samples[m][1] = samples[m - 1][1];

    //% Initially the only valid point is the initial point.
    //n = 1;
    int n = 1;

    int nalpha = 1;
    double alpha = 1;
    //% Main loop---keep going until the criterion s == 0.
    //s = 1;
    bool s = true;
    while (s)
    {
      //% Choose a direction. -1=backwards, 1=forwards.
      //v = 2*(rand() < 0.5)-1;
      double value = _rand();
      int v = 2 * (value < 0.5) - 1;

      double thetaplus[2];
      thetaplus[0] = _thetaplus[0];
      thetaplus[1] = _thetaplus[1];
      double rplus[2];
      rplus[0] = _rplus[0];
      rplus[1] = _rplus[1];
      double gradplus[2];
      gradplus[0] = _gradplus[0];
      gradplus[1] = _gradplus[1];
      double thetaminus[2];
      thetaminus[0] = _thetaminus[0];
      thetaminus[1] = _thetaminus[1];
      double rminus[2];
      rminus[0] = _rminus[0];
      rminus[1] = _rminus[1];
      double gradminus[2];
      gradminus[0] = _gradminus[0];
      gradminus[1] = _gradminus[1];

      //% Double the size of the tree.
      if (v == -1)
      {
        //[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime, gradprime, logpprime, nprime, sprime, alpha, nalpha] = ...
        build_tree(_thetaminus, _rminus, _gradminus, logu, v, j, epsilon, joint);

        _thetaplus[0] = thetaplus[0];
        _thetaplus[1] = thetaplus[1];
        _rplus[0] = rplus[0];
        _rplus[1] = rplus[1];
        _gradplus[0] = gradplus[0];
        _gradplus[1] = gradplus[1];
      }
      else
      {
        //[~, ~, ~, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime, alpha, nalpha] = ...
        build_tree(_thetaplus, _rplus, _gradplus, logu, v, j, epsilon, joint);

        _thetaminus[0] = thetaminus[0];
        _thetaminus[1] = thetaminus[1];
        _rminus[0] = rminus[0];
        _rminus[1] = rminus[1];
        _gradminus[0] = gradminus[0];
        _gradminus[1] = gradminus[1];
      }

      alpha = _alphaprime;
      nalpha = _nalphaprime;

      //% Use Metropolis-Hastings to decide whether or not to move to a
      //% point from the half-tree we just generated.
      double rn = _rand();
      if (_sprime == 1 && rn < double(_nprime)/n)
      {
        //samples(m, :) = thetaprime;
        samples[m][0] = _thetaprime[0];
        samples[m][1] = _thetaprime[1];

        //logp = logpprime;
        logp = _logpprime;

        //grad = gradprime;
        grad[0] = _gradprime[0];
        grad[1] = _gradprime[1];
      }

      //% Update number of valid points we've seen.
      //n = n + nprime;
      n += _nprime;

      //% Decide if it's time to stop.
      bool b = stop_criterion(_thetaminus, _thetaplus, _rminus, _rplus);
      s = _sprime && b;

      cout << "mj: " << m << ' ' << j << endl;
      if (j == 0) s = false;

      //% Increment depth.
      //j = j + 1;
      ++j;
    }

    //% Do adaptation of epsilon if we're still doing burn-in.
    //eta = 1 / (m - 1 + t0);
    double eta = 1.0 / (m + t0);


    Hbar = (1 - eta) * Hbar + eta * (delta - alpha / nalpha);

    if (m <= Madapt - 1)
    {
      epsilon = exp(mu - sqrt(m)/gamma * Hbar);

      //eta = (m-1)^-kappa;
      eta = pow(m, -kappa);

      epsilonbar = exp((1 - eta) * log(epsilonbar) + eta * log(epsilon));
    }
    else
    {
      epsilon = epsilonbar;
    }
  }
  //samples = samples(Madapt+1:end, :);
  for (int i = 0; i < 500; ++i)
  {
    _samples[i][0] = samples[500 + i][0];
    _samples[i][1] = samples[500 + i][1];
  }
  _epsilon = epsilon;
}
TEST_F(test_nuts, nuts_da)
{
  _nfevals = 0;

  double epsilon = 0;
  double samples[500][2];
  int M = 0;
  int Madapt = 0;
  double theta0[2];
  double delta = 0.6;

  ifstream ifs("test_nuts.txt");
  ASSERT_TRUE(ifs.good());
  while (!ifs.eof())
  {
    std::string line;
    std::getline(ifs, line);
    if (line.compare("nuts_da begin") == 0)
    {
      std::getline(ifs, line);
      std::getline(ifs, line);
      ASSERT_EQ(line.compare("nuts_da begin parameters"), 0);
      {
        for (int i = 0; i < 9; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> M;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> Madapt;
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> theta0[0] >> theta0[1];
      }
      for (int i = 0; i < 8; ++i)
      {
        std::getline(ifs, line);
      }
      ASSERT_EQ(line.compare("nuts_da end parameters"), 0);
      {
        while (!_random_numbers.empty())
        {
          _random_numbers.pop();
        }
      }
    }
    else if (line.compare("r0 =") == 0)
    {
      std::getline(ifs, line);
      std::getline(ifs, line);
      double random_number;
      istringstream iss(line);
      iss >> random_number;
      _random_numbers.push(random_number);
      iss >> random_number;
      _random_numbers.push(random_number);
    }
    else if (line.compare("rn =") == 0 || line.compare("rexp =") == 0)
    {
      std::getline(ifs, line);
      std::getline(ifs, line);
      double random_number;
      istringstream iss(line);
      iss >> random_number;
      _random_numbers.push(random_number);
    }
    else if (line.compare("nuts_da end") == 0)
    {
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        for (int i = 0; i < 500; ++i)
        {
          std::getline(ifs, line);
          istringstream iss(line);
          iss >> samples[i][0] >> samples[i][1];
        }
      }
      {
        for (int i = 0; i < 5; ++i)
        {
          std::getline(ifs, line);
        }
        istringstream iss(line);
        iss >> epsilon;
      }
      int nfevals = 0;
      for (int i = 0; i < 5; ++i)
      {
        std::getline(ifs, line);
        istringstream iss(line);
        iss >> nfevals;
      }
      for (int i = 0; i < 3; ++i)
      {
        std::getline(ifs, line);
      }
      ASSERT_EQ(line.compare("nuts_da end output"), 0);

      nuts_da(M, Madapt, theta0, delta);

      ASSERT_EQ(_nfevals, nfevals);

      const double range = 0.000001;
      ASSERT_NEAR(_epsilon, epsilon, range);
      for (int i = 0; i < 500; ++i)
      {
        ASSERT_NEAR(_samples[i][0], samples[i][0], range);
        ASSERT_NEAR(_samples[i][1], samples[i][1], range);
      }
    }
  }
}
