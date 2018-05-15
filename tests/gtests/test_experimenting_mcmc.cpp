#include <gtest/gtest.h>
#include <fstream>
#include <cmath>
#include <random>

double target(const double x)
{
  return x < 0 ? 0.0 : std::exp(-x);
}

void sample(double* x)
{
  std::default_random_engine generator;
  std::normal_distribution<double> rnorm(0.0, 1.0);
  std::uniform_real_distribution<double> runif(0.0,1.0);

  //this is just a starting value, which I've set arbitrarily to 3
  x[0] = 3;
  for(int i = 1; i < 1000; ++i)
  {
    double currentx = x[i-1];
    double proposedx = currentx + rnorm(generator);
    double A = target(proposedx) / target(currentx);
    //accept move with probabily min(1,A)
    //otherwise "reject" move, and stay where we are
    x[i] = runif(generator) < A ? proposedx : currentx;
  }
}

class test_experimenting_mcmc: public ::testing::Test {};

TEST_F(test_experimenting_mcmc, target)
{
  ASSERT_NEAR(target(1.0), 0.3678794, 1e-7);
  ASSERT_DOUBLE_EQ(target(0.0), 1.0);
  ASSERT_DOUBLE_EQ(target(-1.0), 0.0);
}
TEST_F(test_experimenting_mcmc, sample)
{
  double x[1000];
  sample(&x[0]);

  int counts[12];
  for (int i = 0; i < 12; ++i)
  {
    counts[i] = 0;
  }
  
  ASSERT_DOUBLE_EQ(x[0], 3.0);

  for (int i = 0; i < 1000; ++i)
  {
    double xi = x[i];
    if (xi < 0.5)
      { ++counts[0]; }
    else if (xi < 1.0)
      { ++counts[1]; }
    else if (xi < 1.5)
      { ++counts[2]; }
    else if (xi < 2.0)
      { ++counts[3]; }
    else if (xi < 2.5)
      { ++counts[4]; }
    else if (xi < 3.0)
      { ++counts[5]; }
    else if (xi < 3.5)
      { ++counts[6]; }
    else if (xi < 4.0)
      { ++counts[7]; }
    else if (xi < 4.5)
      { ++counts[8]; }
    else if (xi < 5.0)
      { ++counts[9]; }
    else if (xi < 5.5)
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

  std::ofstream ofs("test_experimenting_mcmc_sample.txt");
  for (int i = 0; i < 1000; ++i)
  {
    ofs << x[i] << ' ';
  }
  ofs << std::endl;
  ofs.close();
}
