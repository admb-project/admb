/** Copyright (c) 2016 ADMB Foundation */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include "nuts_da.h"

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::pow;
using std::stack;
using std::queue;

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

  int mmax = M + Madapt;
  for (int m = 1; m < mmax; ++m)
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

    //cout << "m:" << (m + 1) << " nfevals:" << _nfevals << endl;
    //if ((m + 1) == 57) //58
    //{
      //break;
    //}
  }
  //samples = samples(Madapt+1:end, :);
  for (int i = 0; i < 500; ++i)
  {
    _samples[i][0] = samples[500 + i][0];
    _samples[i][1] = samples[500 + i][1];
  }
  _epsilon = epsilon;
}
