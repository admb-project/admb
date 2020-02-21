#include <functional>
#include <gtest/gtest.h>
#include <fstream>
#include <cmath>
#include <random>

double target_unknown(const double x)
{
  return x > 1.0 && x < 5.0 ? std::pow(x, 2.0) : 0;
}
double target_exponential(const double x)
{
  return x < 0 ? 0.0 : std::exp(-x);
}
double target_t_distribution(const double x)
{
  return 1.0 / (1.0 + x * x);
}

void run_sampler_Metropolis_Hastings(
  double* samples,
  std::function<double(const double)> target)
{
  std::default_random_engine generator;

  double mean = 0.0;
  double standard_deviation = 1.0;
  //From Random Normal
  std::normal_distribution<double> rnorm(mean, standard_deviation);
  //From Random Uniform
  std::uniform_real_distribution<double> runif(mean, standard_deviation);

  //this is just a starting value, which I've set arbitrarily to 3
  samples[0] = 3.0;
  for(int t = 0; t < 999; ++t)
  {
    double current = samples[t];
    double proposed = current + rnorm(generator);
    double acceptance = target(proposed) / target(current);
    //accept move with probabily min(1, acceptance)
    //otherwise "reject" move, and stay where we are
    samples[t + 1] = runif(generator) < acceptance ? proposed: current;
  }
}

class test_experimenting_mcmc: public ::testing::Test {};

TEST_F(test_experimenting_mcmc, target_exponential)
{
  ASSERT_NEAR(target_exponential(1.0), 0.3678794, 1e-7);
  ASSERT_DOUBLE_EQ(target_exponential(0.0), 1.0);
  ASSERT_DOUBLE_EQ(target_exponential(-1.0), 0.0);
}
#ifndef _MSC_VER
TEST_F(test_experimenting_mcmc, run_target_exponential)
{
  double samples[1000];
  run_sampler_Metropolis_Hastings(&samples[0], &target_exponential);

  int counts[12];
  for (int i = 0; i < 12; ++i)
  {
    counts[i] = 0;
  }
  
  ASSERT_DOUBLE_EQ(samples[0], 3.0);

  for (int i = 0; i < 1000; ++i)
  {
    double sample = samples[i];
    if (sample < 0.5)
      { ++counts[0]; }
    else if (sample < 1.0)
      { ++counts[1]; }
    else if (sample < 1.5)
      { ++counts[2]; }
    else if (sample < 2.0)
      { ++counts[3]; }
    else if (sample < 2.5)
      { ++counts[4]; }
    else if (sample < 3.0)
      { ++counts[5]; }
    else if (sample < 3.5)
      { ++counts[6]; }
    else if (sample < 4.0)
      { ++counts[7]; }
    else if (sample < 4.5)
      { ++counts[8]; }
    else if (sample < 5.0)
      { ++counts[9]; }
    else if (sample < 5.5)
      { ++counts[10]; }
    else
      { ++counts[11]; }
  }
  ASSERT_TRUE(counts[0] > counts[1]);
  ASSERT_TRUE(counts[1] > counts[2]);
  ASSERT_TRUE(counts[2] > counts[3]);
  ASSERT_TRUE(counts[3] > counts[4]);
  ASSERT_TRUE(counts[5] > counts[6]);
  ASSERT_TRUE(counts[6] > counts[7]);
  ASSERT_TRUE(counts[6] > counts[8]);
  ASSERT_TRUE(counts[6] > counts[9]);
  ASSERT_TRUE(counts[6] > counts[10]);
  ASSERT_TRUE(counts[6] > counts[11]);

/*
  std::ofstream ofs("test_experimenting_mcmc_sample.txt");
  for (int i = 0; i < 1000; ++i)
  {
    ofs << samples[i] << ' ';
  }
  ofs << std::endl;
  ofs.close();
*/
}
#endif
TEST_F(test_experimenting_mcmc, run_target_t_distribution)
{
  double samples[1000];
  run_sampler_Metropolis_Hastings(&samples[0], &target_t_distribution);

  int counts[12];
  for (int i = 0; i < 12; ++i)
  {
    counts[i] = 0;
  }
  
  ASSERT_DOUBLE_EQ(samples[0], 3.0);

  for (int i = 0; i < 1000; ++i)
  {
    double sample = samples[i];
    if (sample < -5.0)
      { ++counts[0]; }
    else if (sample < -4.0)
      { ++counts[1]; }
    else if (sample < -3.0)
      { ++counts[2]; }
    else if (sample < -2.0)
      { ++counts[3]; }
    else if (sample < -1.0)
      { ++counts[4]; }
    else if (sample < 0.0)
      { ++counts[5]; }
    else if (sample < 1.0)
      { ++counts[6]; }
    else if (sample < 2.0)
      { ++counts[7]; }
    else if (sample < 3.0)
      { ++counts[8]; }
    else if (sample < 4.0)
      { ++counts[9]; }
    else if (sample < 5.0)
      { ++counts[10]; }
    else
      { ++counts[11]; }
  }
  //ASSERT_TRUE(counts[0]...counts[1]);
  ASSERT_TRUE(counts[1] < counts[4]);
  ASSERT_TRUE(counts[2] < counts[4]);
  ASSERT_TRUE(counts[3] < counts[4]);
  ASSERT_TRUE(counts[4] < counts[5]);
  //ASSERT_TRUE(counts[5]...counts[6]);
  ASSERT_TRUE(counts[6] > counts[7]);
  ASSERT_TRUE(counts[7] > counts[8]);
  ASSERT_TRUE(counts[8] > counts[9]);
  ASSERT_TRUE(counts[9] < counts[8]);
  ASSERT_TRUE(counts[10] < counts[8]);
  //ASSERT_TRUE(counts[11]...counts[11]);
}
TEST_F(test_experimenting_mcmc, run_target_unknown)
{
  double samples[1000];
  run_sampler_Metropolis_Hastings(&samples[0], &target_unknown);
  ASSERT_DOUBLE_EQ(samples[0], 3.0);

  int counts[10];
  for (int i = 0; i < 10; ++i)
  {
    counts[i] = 0;
  }

  for (int i = 0; i < 1000; ++i)
  {
    double sample = samples[i];
    if (sample < 1.0)
      { ++counts[0]; }
    else if (sample < 1.5)
      { ++counts[1]; }
    else if (sample < 2.0)
      { ++counts[2]; }
    else if (sample < 2.5)
      { ++counts[3]; }
    else if (sample < 3.0)
      { ++counts[4]; }
    else if (sample < 3.5)
      { ++counts[5]; }
    else if (sample < 4.0)
      { ++counts[6]; }
    else if (sample < 4.5)
      { ++counts[7]; }
    else if (sample < 5.0)
      { ++counts[8]; }
    else
      { ++counts[9]; }
  }

  ASSERT_EQ(counts[0], 0);
  ASSERT_EQ(counts[9], 0);

  ASSERT_TRUE(counts[1] < counts[2]);
  ASSERT_TRUE(counts[2] < counts[3]);
  ASSERT_TRUE(counts[3] < counts[4]);
  ASSERT_TRUE(counts[4] < counts[5]);
  ASSERT_TRUE(counts[5] < counts[6]);
  ASSERT_TRUE(counts[6] < counts[7]);
  ASSERT_TRUE(counts[7] < counts[8]);
}
