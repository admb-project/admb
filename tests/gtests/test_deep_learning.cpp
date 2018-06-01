#include <cmath>
#include <gtest/gtest.h>

class test_deep_learning: public ::testing::Test {};

double sigmoid(const double x)
{
  return 1.0 / (1.0 + std::exp(-x));
}
double dfsigmoid(const double x)
{
  return x * (1.0 - x);
}
void neural_network(double* layer)
{
  double data[4][4];
  data[0][0] = 0;
  data[0][1] = 0;
  data[0][2] = 1;
  data[0][3] = 0;
  data[1][0] = 0;
  data[1][1] = 1;
  data[1][2] = 1;
  data[1][3] = 0;
  data[2][0] = 1;
  data[2][1] = 0;
  data[2][2] = 1;
  data[2][3] = 1;
  data[3][0] = 1;
  data[3][1] = 1;
  data[3][2] = 1;
  data[3][3] = 1;

  double weights[3];
  weights[0] = -0.16595599;
  weights[1] = 0.44064899;
  weights[2] = -0.99977125;

  double errors[4];
  double slopes[4];
  for (int i = 0; i < 10000; ++i)
  {
    //Transformed data and weights to probability
    for (int j = 0; j < 4; ++j)
    {
      double x = 0;
      for (int k = 0; k < 3; ++k)
      {
        x += data[j][k] * weights[k];
      }
      layer[j] = sigmoid(x);
    }
    //Compute error difference from data and current values
    for (int j = 0; j < 4; ++j)
    {
      errors[j] = data[j][3] - layer[j];
    }
    //Compute slopes from derivatives
    for (int j = 0; j < 4; ++j)
    {
      slopes[j] = dfsigmoid(layer[j]);
    }
    //Update weights
    for (int j = 0; j < 3; ++j)
    {
      for (int k = 0; k < 4; ++k)
      {
        weights[j] += data[k][j] * errors[k] * slopes[k]; 
      }
    }
  }
  std::cout << "Output After Training:\n";
  for (int j = 0; j < 4; ++j)
  {
    std::cout << layer[j] << " ";
  }
  std::cout << std::endl;
}
TEST_F(test_deep_learning, example)
{
  double layer[4];
  neural_network(&layer[0]);

  ASSERT_NEAR(0.00966449, layer[0], 0.00001); 
  ASSERT_NEAR(0.00786506, layer[1], 0.00001);
  ASSERT_NEAR(0.993589, layer[2], 0.00001);
  ASSERT_NEAR(0.99212, layer[3], 0.00001);
}
