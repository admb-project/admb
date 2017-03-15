#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <cmath>
#include <gtest/gtest.h>
#include <queue>
#include "nuts_da.h"

using std::cout;
using std::endl;
using std::queue;
using std::stack;
using std::ifstream;
using std::istringstream;
using std::queue;

extern queue<double> _random_numbers;
double _rand();

class test_nuts: public ::testing::Test {};

double urand();
double randn();
double exprnd(double p);
//[logpprime, gradprime] = f(thetaprime);
void f(const size_t D, const double* theta, double& logp, double* grad);
extern int _D;
//global nfevals;
extern int _nfevals;
extern double _rprime[2];
extern double _thetaprime[2];
extern double _gradprime[2];
extern double _logpprime;
void correlated_normal(double* theta);
void f(double* theta);
double find_reasonable_epsilon
(
  double* theta0,
  double* grad0,
  double logp0,
  double* r0
);
bool stop_criterion
(
  double* thetaminus,
  double* thetaplus,
  double* rminus,
  double* rplus
);
extern double _thetaminus[2];
extern double _rminus[2];
extern double _gradminus[2];
extern double _thetaplus[2];
extern double _rplus[2];
extern double _gradplus[2];
extern int _nprime;
extern int _sprime;
extern double _alphaprime;
extern int _nalphaprime;
double exprnd(const int m);
void build_tree(
  double* theta,
  double* r,
  double* grad,
  double logu,
  int v,
  int j,
  double epsilon,
  double joint0
);
extern double _samples[1000][2];
extern double _epsilon;

std::pair<double, std::vector<double>>
correlated_normal(const std::vector<double>& theta)
{
  const int D = theta.size();

  //A = [50.251256, -24.874372; -24.874372, 12.562814];
  double A[2][2];
  A[0][0] = 50.251256;
  A[0][1] = -24.874372;
  A[1][0] = -24.874372;
  A[1][1] = 12.562814;

  std::vector<double> grad(D);
  //grad = -theta * A;
  for (int d = 0; d < D; ++d)
  {
    grad[d] = 0;
    for (int j = 0; j < D; ++j)
    {
      grad[d] -= theta[j] * A[d][j];
    }
  }
  std::vector<double> gradprime(D);
  for (int d = 0; d < D; ++d)
  {
    gradprime[d] = grad[d];
  }
  //logp = 0.5 * grad * theta';
  double logp = 0;
  for (int d = 0; d < D; ++d)
  {
    logp += grad[d] * theta[d];
  }
  logp *= 0.5;
  double logpprime = logp;

  return std::make_pair(logpprime, gradprime);
}

//[logpprime, gradprime] = f(thetaprime);
std::pair<double, std::vector<double>>
f(const std::vector<double>& theta)
{
  return correlated_normal(theta);
}

TEST_F(test_nuts, urand)
{
  for (int i = 0; i < 10; ++i)
  {
    double v = urand();
    ASSERT_TRUE(0 <= v && v <= 1.0);
  }
}
std::vector<std::vector<double>>
leapfrog
(
  const std::vector<double>& theta,
  const std::vector<double>& r,
  const std::vector<double>& grad,
  const double epsilon
);
TEST_F(test_nuts, leapfrog)
{
  ifstream ifs("test_nuts.txt");
  ASSERT_TRUE(ifs.good());

  //input
  std::vector<double> theta(2);
  std::vector<double> r(2);
  std::vector<double> grad(2);
  double epsilon;
  int nfevals = 1;
  //output
  std::vector<double> thetaprime(2);
  std::vector<double> rprime(2);
  std::vector<double> gradprime(2);
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
      std::vector<std::vector<double>> results = leapfrog(theta, r, grad, epsilon);

      ASSERT_EQ(num, nfevals);
      ASSERT_EQ(_nfevals, nfevals);

      const double range = 0.0000001;
      ASSERT_NEAR(thetaprime[0], results[0][0], range);
      ASSERT_NEAR(thetaprime[1], results[0][1], range);
      ASSERT_NEAR(rprime[0], results[1][0], range);
      ASSERT_NEAR(rprime[1], results[1][1], range);
      ASSERT_NEAR(gradprime[0], results[2][0], range);
      ASSERT_NEAR(gradprime[1], results[2][1], range);
      ASSERT_NEAR(logpprime, results[3][0], range);
    }
  }
  ifs.close();
}
double find_reasonable_epsilon
(
  const std::vector<double>& theta0,
  const std::vector<double>& grad0,
  const double logp0,
  const std::vector<double>& r0
);
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
      std::vector<double> theta0(2);
      std::vector<double> grad0(2);
      double logp0 = 0;
      std::vector<double> r0(2);
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
/*
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
    else if (line.compare("random_number =") == 0)
    {
      std::getline(ifs, line);
      std::getline(ifs, line);
      double random_number;
      istringstream iss(line);
      iss >> random_number;
      if (!(random_number < 0))
      {
        _random_numbers.push(random_number);
      }
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

      std::vector<double> v(theta0, theta0 + sizeof(theta0) / sizeof(double) );
      nuts_da(M, Madapt, v, delta);

      ASSERT_TRUE(_random_numbers.size() == 0);

      ASSERT_EQ(_nfevals, nfevals);

      const double range = 0.0000001;
      ASSERT_NEAR(_epsilon, epsilon, range);
      for (int i = 0; i < 500; ++i)
      {
        ASSERT_NEAR(_samples[i][0], samples[i][0], range);
        ASSERT_NEAR(_samples[i][1], samples[i][1], range);
      }
      cout << "epsilon: " << _epsilon << ' ' << epsilon << ' ' << std::abs(_epsilon - epsilon) << endl;
      cout << "nfevals: " << _nfevals << ' ' << nfevals << endl;
      for (int i = 0; i < 500; ++i)
      {
        cout << "i2: " << _samples[i][0] << ' ' <<  samples[i][0] << endl;
        cout << "i1: " << _samples[i][1] << ' ' <<  samples[i][1] << endl;
      }
    }
  }
}
*/
