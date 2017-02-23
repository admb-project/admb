#include <iostream>
#include <gtest/gtest.h>
#include "ad_deep_learning.h"
#include "ad_deep_learning2.h"

class test_deep_learning: public ::testing::Test {};

TEST_F(test_deep_learning, nnexample)
{
  neural_network nn;

  std::vector<double> weights = nn.get_weights();
  ASSERT_DOUBLE_EQ(weights[0], -0.16595599);
  ASSERT_DOUBLE_EQ(weights[1], 0.44064899);
  ASSERT_DOUBLE_EQ(weights[2], -0.99977125);

  std::vector<double> inputs = 
  {
    0, 0, 1,
    1, 1, 1,
    1, 0, 1,
    0, 1, 1
  };
  std::vector<double> outputs = {0, 1, 1, 0};
  size_t iterations = 10000;

  nn.training(inputs, outputs, iterations);

  std::vector<double> new_weights = nn.get_weights();
  ASSERT_NEAR(new_weights[0], 9.67299303, 0.000001);
  ASSERT_NEAR(new_weights[1], -0.2078435, 0.000001);
  ASSERT_NEAR(new_weights[2], -4.62963669, 0.000001);
}
TEST_F(test_deep_learning, nnexample2)
{
  neural_network2 nn;

/*
  std::vector<double> weights = nn.get_weights();
  ASSERT_DOUBLE_EQ(weights[0], -0.16595599);
  ASSERT_DOUBLE_EQ(weights[1], 0.44064899);
  ASSERT_DOUBLE_EQ(weights[2], -0.99977125);
*/

  std::vector<double> training_set_inputs =
  {
    0, 0, 1,
    0, 1, 1,
    1, 0, 1,
    0, 1, 0,
    1, 0, 0,
    1, 1, 1,
    0, 0, 0
  };
  std::vector<double> training_set_outputs = {0, 1, 1, 1, 1, 0, 0};
  size_t iterations = 60000;

  nn.training(training_set_inputs, training_set_outputs, iterations);

/*
  std::vector<double> new_weights = nn.get_weights();
  ASSERT_NEAR(new_weights[0], 9.67299303, 0.000001);
  ASSERT_NEAR(new_weights[1], -0.2078435, 0.000001);
  ASSERT_NEAR(new_weights[2], -4.62963669, 0.000001);
*/
}
