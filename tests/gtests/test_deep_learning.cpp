#include <cmath>
#include <gtest/gtest.h>

class test_deep_learning: public ::testing::Test
{
  double** _data;
public:
  test_deep_learning()
  {
    _data = new double*[4];
    for (int i = 0; i < 4; ++i)
    {
      _data[i] = new double[4];
    }
    _data[0][0] = 0;
    _data[0][1] = 0;
    _data[0][2] = 1;
    _data[0][3] = 0;
    _data[1][0] = 0;
    _data[1][1] = 1;
    _data[1][2] = 1;
    _data[1][3] = 0;
    _data[2][0] = 1;
    _data[2][1] = 0;
    _data[2][2] = 1;
    _data[2][3] = 1;
    _data[3][0] = 1;
    _data[3][1] = 1;
    _data[3][2] = 1;
    _data[3][3] = 1;
  }
  ~test_deep_learning()
  {
    for (int i = 0; i < 4; ++i)
    {
      delete _data[i];
      _data[i] = NULL;
    }
    delete [] _data;
    _data = NULL;
  }

  double** get_data() const { return _data; }
};

double sigmoid(const double x)
{
  return 1.0 / (1.0 + std::exp(-x));
}
double dfsigmoid(const double x)
{
  return x * (1.0 - x);
}
void neural_network_part1(double** data, double* layer)
{
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
/**
Ported from https://iamtrask.github.io/2015/07/12/basic-python-network
*/
void neural_network_two_layers(double** data, double** output_layer)
{
  data[1][3] = 1;
  data[3][3] = 0;

  double hidden_weights[3][4];
  hidden_weights[0][0] = -0.16595599;  
  hidden_weights[0][1] = 0.44064899;
  hidden_weights[0][2] = -0.99977125;
  hidden_weights[0][3] = -0.39533485;
  hidden_weights[1][0] = -0.70648822;
  hidden_weights[1][1] = -0.81532281;
  hidden_weights[1][2] = -0.62747958;
  hidden_weights[1][3] = -0.30887855;
  hidden_weights[2][0] = -0.20646505;
  hidden_weights[2][1] = 0.07763347;
  hidden_weights[2][2] = -0.16161097;
  hidden_weights[2][3] = 0.370439;

  double output_weights[4][1];
  output_weights[0][0] = -0.5910955;
  output_weights[1][0] = 0.75623487;
  output_weights[2][0] = -0.94522481;
  output_weights[3][0] = 0.34093502;

  double hidden_layer[4][4];
  double hidden_deltas[4][4];
  double output_deltas[4][1];
  for (int counts  = 0; counts < 60000; ++counts)
  {
    //Update layers
    for (int k = 0; k < 4; ++k)
    {
      for (int i = 0; i < 4; ++i)
      {
        double x = 0;
        for (int j = 0; j < 3; ++j)
        {
          x += data[k][j] * hidden_weights[j][i];
        }
        hidden_layer[k][i] = sigmoid(x);
      }
    }
    for (int i = 0; i < 4; ++i)
    {
      double x = 0;
      for (int j = 0; j < 4; ++j)
      {
        x += hidden_layer[i][j] * output_weights[j][0];
      }
      output_layer[i][0] = sigmoid(x);
    }
    //Compute deltas using slopes and errors from output layer.
    for (int i = 0; i < 4; ++i)
    {
      double error = data[i][3] - output_layer[i][0];
      output_deltas[i][0] = error * dfsigmoid(output_layer[i][0]);
    }
    //Update weights
    for (int i = 0; i < 4; ++i)
    {
      double x = 0;
      for (int j = 0; j < 4; ++j)
      {
        x += hidden_layer[j][i] * output_deltas[j][0];
      }
      output_weights[i][0] += x;
    }
    for (int k = 0; k < 4; ++k)
    {
      for (int i = 0; i < 3; ++i)
      {
        double x = 0;
        for (int j = 0; j < 4; ++j)
        {
          double error = output_deltas[j][0] * output_weights[k][0];
          double delta = error * dfsigmoid(hidden_layer[j][k]);
          x += data[j][i] * delta;
        }
        hidden_weights[i][k] += x;
      }
    }
  }
  std::cout << "Output After Training:\n";
  for (int i = 0; i < 4; ++i)
  {
    std::cout << output_layer[i][0] << " ";
  }
  std::cout << std::endl;
}
TEST_F(test_deep_learning, part1)
{
  double layer[4];
  neural_network_part1(get_data(), &layer[0]);

  ASSERT_NEAR(0.00966449, layer[0], 0.00001); 
  ASSERT_NEAR(0.00786506, layer[1], 0.00001);
  ASSERT_NEAR(0.993589, layer[2], 0.00001);
  ASSERT_NEAR(0.99212, layer[3], 0.00001);
}
TEST_F(test_deep_learning, two_layers)
{
  double** outputs = new double*[4];
  for (int i = 0; i < 4; ++i)
  {
    outputs[i] = new double[1];
  }

  neural_network_two_layers(get_data(), outputs);

  ASSERT_NEAR(0.00260572, outputs[0][0], 0.00001); 
  ASSERT_NEAR(0.996722, outputs[1][0], 0.00001);
  ASSERT_NEAR(0.997017, outputs[2][0], 0.00001);
  ASSERT_NEAR(0.00386759, outputs[3][0], 0.00001);

  for (int i = 0; i < 4; ++i)
  {
    delete [] outputs[i];
    outputs[i] = NULL;
  }
  delete [] outputs;
  outputs = NULL;
}
