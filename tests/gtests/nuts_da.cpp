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
int _nfevals = 0;

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

//function [thetaprime, rprime, gradprime, logpprime] = leapfrog(theta, r, grad, epsilon, f)
std::vector<std::vector<double>>
leapfrog
(
  const std::vector<double>& theta,
  const std::vector<double>& r,
  const std::vector<double>& grad,
  const double epsilon
)
{
  std::vector<std::vector<double>> results(4);

  const int D = theta.size();

  //rprime = r + 0.5 * epsilon * grad;
  std::vector<double> rprime(D);
  for (int d = 0; d < D; ++d)
  {
    rprime[d] = r[d] + 0.5 * epsilon * grad[d];
  }
  //thetaprime = theta + epsilon * rprime;
  std::vector<double> thetaprime(D);
  for (int d = 0; d < D; ++d)
  {
    thetaprime[d] = theta[d] + epsilon * rprime[d];
  }
  //[logpprime, gradprime] = f(thetaprime);
  std::pair<double, std::vector<double>> f(const std::vector<double>& theta);
  std::pair<double, std::vector<double>> p = f(thetaprime);
  vector<double> gradprime = p.second;

  //rprime = rprime + 0.5 * epsilon * gradprime;
  for (int d = 0; d < D; ++d)
  {
    rprime[d] += 0.5 * epsilon * gradprime[d];
  }

  //nfevals = nfevals + 1;
  ++_nfevals;

  results[0] = thetaprime;
  results[1] = rprime;
  results[2] = gradprime;
  std::vector<double> logpprime = {p.first};
  results[3] = logpprime;

  return results;
}
double find_reasonable_epsilon
(
  const std::vector<double>& theta0,
  const std::vector<double>& grad0,
  const double logp0,
  const std::vector<double>& r0
)
{
  double epsilon = 1;

  //Figure out what direction we should be moving epsilon.
  //[~, rprime, ~, logpprime] = leapfrog(theta0, r0, grad0, epsilon, f);
  std::vector<std::vector<double>> results = leapfrog(theta0, r0, grad0, epsilon);
  std::vector<double> rprime = results[1];
  double logpprime = results[3][0];

  //acceptprob = exp(logpprime - logp0 - 0.5 * (rprime * rprime' - r0 * r0'));
  double rprime_rprime = 0;
  double r0_r0 = 0;
  int D = theta0.size();
  for (int d = 0; d < D; ++d)
  {
    rprime_rprime += rprime[d] * rprime[d];
    r0_r0 += r0[d] * r0[d];
  }
  double acceptprob = std::exp(logpprime - logp0 - 0.5 * (rprime_rprime - r0_r0));

  //a = 2 * (acceptprob > 0.5) - 1;
  int a = acceptprob > 0.5 ? 1 : -1;

  //Keep moving epsilon in that direction until acceptprob crosses 0.5.
  //while (acceptprob^a > 2^(-a))
  while (pow(acceptprob, a) > pow(2.0, -a))
  {
    //epsilon = epsilon * 2^a;
    epsilon *= pow(2.0, a);

    //[~, rprime, ~, logpprime] = leapfrog(theta0, r0, grad0, epsilon, f);
    results = leapfrog(theta0, r0, grad0, epsilon);
    rprime = results[1];
    logpprime = results[3][0];

    //acceptprob = exp(logpprime - logp0 - 0.5 * (rprime * rprime' - r0 * r0'));
    rprime_rprime = 0;
    r0_r0 = 0;
    for (int d = 0; d < D; ++d)
    {
      rprime_rprime += rprime[d] * rprime[d];
      r0_r0 += r0[d] * r0[d];
    }
    acceptprob = std::exp(logpprime - logp0 - 0.5 * (rprime_rprime - r0_r0));
  }

  return epsilon;
}

bool stop_criterion
(
  const std::vector<double>& thetaminus,
  const std::vector<double>& thetaplus,
  const std::vector<double>& rminus,
  const std::vector<double>& rplus
)
{
  bool criterion = false;

  const int D = thetaminus.size();
  //thetavec = thetaplus - thetaminus;
  std::vector<double> thetavec(D);
  for (int d = 0; d < D; ++d)
  {
    thetavec[d] = thetaplus[d] - thetaminus[d];
  }

  //criterion = (thetavec * rminus' >= 0) && (thetavec * rplus' >= 0);
  double thetavec_rminus = 0;
  double thetavec_rplus = 0;
  for (int d = 0; d < D; ++d)
  {
    double v = thetavec[d];
    thetavec_rminus += v * rminus[d];
    thetavec_rplus += v * rplus[d];
  }
  criterion = (thetavec_rminus >= 0) && (thetavec_rplus >= 0);

  return criterion;
}

struct btoutput
{
  double thetaminus;
  double rminus;
  double gradminus;
  double thetaplus;
  double rplus;
  double gradplus;
  double thetaprime;
  double gradprime;
  double logpprime;
  int nprime;
  int sprime;
  double alphaprime;
  int nalphaprime;
};

//function [thetaminus, rminus, gradminus, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime, alphaprime, nalphaprime] = ...
//build_tree(theta, r, grad, logu, v, j, epsilon, f, joint0)

btoutput
build_tree
(
  const std::vector<double>& theta,
  const std::vector<double>& r,
  const std::vector<double>& grad,
  const double logu,
  const int v,
  const int j,
  const double epsilon,
  const double joint0
)
{
  btoutput results;

  const int D = theta.size();
  std::vector<double> thetaminus(D);
  std::vector<double> rminus(D);
  std::vector<double> gradminus(D);
  std::vector<double> thetaplus(D);
  std::vector<double> rplus(D);
  std::vector<double> gradplus(D);
  std::vector<double> thetaprime(D);
  std::vector<double> gradprime(D);
  double logpprime;
  int nprime;
  bool sprime;
  double alphaprime;
  int nalphaprime;

  if (j == 0)
  {
    std::vector<double> rprime(D);

    //% Base case: Take a single leapfrog step in the direction v.
    //[thetaprime, rprime, gradprime, logpprime] = leapfrog(theta, r, grad, v*epsilon, f);
    std::vector<std::vector<double>> ret = leapfrog(theta, r, grad, v * epsilon);
    thetaprime = ret[0];
    rprime = ret[1];
    gradprime = ret[2];
    logpprime= ret[3][0];

    //joint = logpprime - 0.5 * (rprime * rprime');
    double joint = logpprime;
    for (size_t d = 0; d < D; ++d)
    {
      joint -= 0.5 * rprime[d] * rprime[d];
    }

    //% Is the new point in the slice?
    //nprime = logu < joint;
    int nprime = logu < joint;

    //% Is the simulation wildly inaccurate?
    //sprime = logu - 1000 < joint;
    sprime = (logu - 1000) < joint;

    //% Set the return values---minus=plus for all things here, since the
    //% "tree" is of depth 0.
    thetaminus = thetaprime;
    thetaplus = thetaprime;
    rminus = rprime;
    rplus = rprime;
    gradminus = gradprime;
    gradplus = gradprime;

    //% Compute the acceptance probability.
    //alphaprime = min(1, exp(logpprime - 0.5 * (rprime * rprime') - joint0));
    double v = std::exp(joint - joint0);
    alphaprime = v < 1.0 ? v : 1.0;

    //nalphaprime = 1;
    nalphaprime = 1;
  }
  else
  {
    //% Recursion: Implicitly build the height j-1 left and right subtrees.
    //[thetaminus, rminus, gradminus, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime, alphaprime, nalphaprime] = ...
    build_tree(theta, r, grad, logu, v, j - 1, epsilon, joint0);

    //% No need to keep going if the stopping criteria were met in the first
    //% subtree.
    if (sprime == 1)
    {
      if (v == -1)
      {
        //[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime2, gradprime2, logpprime2, nprime2, sprime2, alphaprime2, nalphaprime2] = ...
        build_tree(thetaminus, rminus, gradminus, logu, v, j - 1, epsilon, joint0);
      }
      else
      {
        //[~, ~, ~, thetaplus, rplus, gradplus, thetaprime2, gradprime2, logpprime2, nprime2, sprime2, alphaprime2, nalphaprime2] = ...
        build_tree(thetaplus, rplus, gradplus, logu, v, j - 1, epsilon, joint0);
      }//end
      double thetaprime2[2] = { thetaprime[0], thetaprime[1]};
      double gradprime2[2] = { gradprime[0], gradprime[1]};
      double logpprime2 = logpprime;
      int nprime2 = nprime;
      bool sprime2 = sprime;
      double alphaprime2 = alphaprime;
      int nalphaprime2 = nalphaprime;

      //% Choose which subtree to propagate a sample up from.
      double random_number = _rand();
      if (nprime + nprime2 != 0 && random_number < double(nprime2) / double(nprime + nprime2))
      {
        for (int d = 0; d < D; ++d)
        {
          //thetaprime = thetaprime2;
          thetaprime[d] = thetaprime2[d];

          //gradprime = gradprime2;
          gradprime[d] = gradprime2[d];
        }
        logpprime = logpprime2;
      }
      else
      {
        for (int d = 0; d < D; ++d)
        {
          //thetaprime = thetaprime;
          thetaprime[d] = thetaprime[d];

          //gradprime = gradprime;
          gradprime[d] = gradprime[d];
        }
        logpprime = logpprime;
      }

      //% Update the number of valid points.
      //nprime = nprime + nprime2;
      nprime = nprime + nprime2;

      //% Update the stopping criterion.
      sprime = sprime && sprime2 && stop_criterion(thetaminus, thetaplus, rminus, rplus);

      //% Update the acceptance probability statistics.
      //alphaprime = alphaprime + alphaprime2;
      alphaprime = alphaprime + alphaprime2;

      //nalphaprime = nalphaprime + nalphaprime2;
      nalphaprime = nalphaprime + nalphaprime2;
    }//end
  }

  return results;
}

std::pair<double, std::vector<double>> f(const std::vector<double>& theta);
//function [samples, epsilon] = nuts_da(f, M, Madapt, theta0, delta)
double _samples[1000][2];
double _epsilon;
void nuts_da(const int M, const int Madapt, const std::vector<double>& theta0, const double delta)
{
  _nfevals = 0;

  //D = length(theta0);
  int D = theta0.size();
  //samples = zeros(M+Madapt, D);
  double samples[1000][2];
  int imax = (M + Madapt) / D;
  for (int i = 0; i < 1000; ++i)
  {
    for (int j = 0; j < D; ++j)
    {
      samples[i][j] = 0;
    }
  }

  //[logp grad] = f(theta0);
  std::pair<double, std::vector<double>> p = f(theta0);
  double logp = p.first;
  std::vector<double> grad = p.second;

  //samples(1, :) = theta0;
  samples[0][0] = theta0[0];
  samples[0][1] = theta0[1];

  //% Choose a reasonable first epsilon by a simple heuristic.
  //epsilon = find_reasonable_epsilon(theta0, grad, logp, f);
  std::vector<double> r0(D);
  for (int d = 0; d < D; ++d)
  {
    r0[d] = _rand();
  }

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

  std::vector<double> thetaplus(D);
  std::vector<double> rplus(D);
  std::vector<double> gradplus(D);
  std::vector<double> thetaminus(D);
  std::vector<double> rminus(D);
  std::vector<double> gradminus(D);
  std::vector<double> gradprime(D);
  std::vector<double> thetaprime(D);
  int sprime;
  double logpprime;
  int nprime;

  int mmax = M + Madapt;
  for (int m = 1; m < mmax; ++m)
  {
    //% Resample momenta.
    //r0 = randn(1, D);
    for (int d = 0; d < D; ++d)
    {
      r0[d] = _rand();
    }

    //% Joint log-probability of theta and momenta r.
    double r0_r0 = 0;
    for (int d = 0; d < D; ++d)
    {
      r0_r0 += r0[d] * r0[d];
    }
    double joint = logp - 0.5 * (r0_r0);

    //% Resample u ~ uniform([0, exp(joint)]).
    //% Equivalent to (log(u) - joint) ~ exponential(1).
    double logu = joint - exprnd(1);

    //% Initialize tree.
    //thetaminus = samples(m-1, :);
    for (int d = 0; d < D; ++d)
    {
      thetaminus[d] = samples[m - 1][d];
    }
    //thetaplus = samples(m-1, :);
    for (int d = 0; d < D; ++d)
    {
      thetaplus[d] = samples[m - 1][d];
    }
    //rminus = r0;
    for (int d = 0; d < D; ++d)
    {
      rminus[d] = r0[d];
    }
    //rplus = r0;
    for (int d = 0; d < D; ++d)
    {
      rplus[d] = r0[d];
    }
    //gradminus = grad;
    for (int d = 0; d < D; ++d)
    {
      gradminus[d] = grad[d];
    }
    //gradplus = grad;
    for (int d = 0; d < D; ++d)
    {
      gradplus[d] = grad[d];
    }

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

      //% Double the size of the tree.
      if (v == -1)
      {
        //[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime, gradprime, logpprime, nprime, sprime, alpha, nalpha] = ...
        build_tree(thetaminus, rminus, gradminus, logu, v, j, epsilon, joint);
      }
      else
      {
        //[~, ~, ~, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime, alpha, nalpha] = ...
        build_tree(thetaplus, rplus, gradplus, logu, v, j, epsilon, joint);
      }

      //% Use Metropolis-Hastings to decide whether or not to move to a
      //% point from the half-tree we just generated.
      double rn = _rand();
      if (sprime == 1 && rn < double(nprime)/n)
      {
        //samples(m, :) = thetaprime;
        samples[m][0] = thetaprime[0];
        samples[m][1] = thetaprime[1];

        //logp = logpprime;
        logp = logpprime;

        //grad = gradprime;
        grad[0] = gradprime[0];
        grad[1] = gradprime[1];
      }

      //% Update number of valid points we've seen.
      //n = n + nprime;
      n += nprime;

      //% Decide if it's time to stop.
      bool b = stop_criterion(thetaminus, thetaplus, rminus, rplus);
      s = sprime && b;

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
