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

  std::vector<double> layer1_weights = 
  {
    -0.16595599,  0.44064899, -0.99977125, -0.39533485,
    -0.70648822, -0.81532281, -0.62747958, -0.30887855,
    -0.20646505,  0.07763347, -0.16161097,  0.370439,
  };
  //1 by 4 matrix
  std::vector<double> layer2_weights = 
  {
    -0.5910955,
     0.75623487,
    -0.94522481,
     0.34093502
  };

  nn.set_weights(layer1_weights, layer2_weights);

  std::vector<double> expected_weights2 = {-0.591095, 0.756235, -0.945225, 0.340935};
  std::vector<double> expected_weights1 = {-0.165956, 0.440649, -0.999771, -0.395335, -0.706488, -0.815323, -0.62748, -0.308879, -0.206465, 0.0776335, -0.161611, 0.370439};

  std::pair<std::vector<double>, std::vector<double>> weights = nn.get_weights();

  for (int i = 0; i < weights.first.size(); ++i)
  {
    ASSERT_NEAR(weights.first[i], expected_weights1[i], 0.0001);
  }
  for (int i = 0; i < weights.second.size(); ++i)
  {
    ASSERT_NEAR(weights.second[i], expected_weights2[i], 0.0001);
  }

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

  weights.first.clear();
  weights.second.clear();
  weights = nn.get_weights();

  expected_weights1 = {0.312246, 4.57704,  -6.1533,  -8.75835,  0.196769,  -8.74976,  -6.16382,  4.40721,  -0.0332707,  -0.58273,  0.0831918,  -0.397876};
  expected_weights2 = {-8.18851, 10.1321, -21.3353, 9.90935};
  for (int i = 0; i < weights.first.size(); ++i)
  {
    ASSERT_NEAR(weights.first[i], expected_weights1[i], 0.0001);
  }
  for (int i = 0; i < weights.second.size(); ++i)
  {
    ASSERT_NEAR(weights.second[i], expected_weights2[i], 0.0001);
  }

  std::pair<std::vector<double>, std::vector<double>> outputs = nn.think({1, 1, 0});

  std::vector<double> expected_layer1 = {0.624576, 0.0151765, 4.47447e-06, 0.012728};
  for (int i = 0; i < outputs.first.size(); ++i)
  {
    ASSERT_NEAR(outputs.first[i], expected_layer1[i], 0.0001);
  }
  std::vector<double> expected_layer2 = {0.0078876};
  for (int i = 0; i < outputs.second.size(); ++i)
  {
    ASSERT_NEAR(outputs.second[i], expected_layer2[i], 0.0001);
  }
}
TEST_F(test_deep_learning, random_weights)
{
  neural_network2 nn(5, 6);

  std::pair<std::vector<double>, std::vector<double>> weights = nn.get_weights();

  ASSERT_EQ(weights.first.size(), 30);
  ASSERT_EQ(weights.second.size(), 6);
  for (auto value: weights.first)
  {
    ASSERT_TRUE(0.0 <= value && value < 1.0);
  }
  for (auto value: weights.second)
  {
    ASSERT_TRUE(0.0 <= value && value < 1.0);
  }
}
TEST_F(test_deep_learning, random_weights_nnexample2)
{
  neural_network2 nn(3, 4);

  std::pair<std::vector<double>, std::vector<double>> weights = nn.get_weights();

  ASSERT_EQ(weights.first.size(), 12);
  ASSERT_EQ(weights.second.size(), 4);
  for (auto value: weights.first)
  {
    ASSERT_TRUE(0.0 <= value && value < 1.0);
  }
  for (auto value: weights.second)
  {
    ASSERT_TRUE(0.0 <= value && value < 1.0);
  }

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
  size_t iterations = 100000;

  nn.training(training_set_inputs, training_set_outputs, iterations);

  weights.first.clear();
  weights.second.clear();
  weights = nn.get_weights();

  std::pair<std::vector<double>, std::vector<double>> outputs = nn.think({1, 1, 0});

  std::vector<double> expected_layer2 = {0.0078876};
  for (int i = 0; i < outputs.second.size(); ++i)
  {
    ASSERT_NEAR(outputs.second[i], expected_layer2[i], 0.001);
  }
}
