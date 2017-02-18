#include <vector>
#include <cmath>

class neural_network
{
std::vector<double> _weights;

public:

/**
Default constructor
*/
neural_network()
{
  _weights = { -0.16595599, 0.44064899, -0.99977125};
}

/**
Destructor
*/
~neural_network()
{
}

std::vector<double>& get_weights()
  { return _weights; }

void training(std::vector<double>& inputs, std::vector<double>& outputs, const size_t iterations)
{
  for (int i = 0; i < iterations; ++i)
  {
    std::vector<double> results = think(inputs);
    std::vector<double> errors(3);
    for (int j = 0; j < 4; ++j)
    {
      errors[j] = outputs[j] - results[j];
    }
    std::vector<double> derivatives = sigmoid_derivatives(results);
    std::vector<double> n(4);
    for (int j = 0; j < 4; ++j)
    {
      n[j] = errors[j] * derivatives[j];
    }
    std::vector<double> adjustments(3);
    for (int j = 0; j < 3; ++j)
    {
      double value = inputs[j] * n[0]
        + inputs[j + 3] * n[1]
        + inputs[j + 6] * n[2]
        + inputs[j + 9] * n[3];
      adjustments[j] = value;
    }
    for (int j = 0; j < 3; ++j)
    {
      _weights[j] += adjustments[j];
    }
  }
}
std::vector<double> think(const std::vector<double>& inputs) const
{
  std::vector<double> results(4);
 
  size_t index = 0;
  for (int i = 0; i < inputs.size(); i += 3)
  {
    double value = inputs[i] * _weights[0]
      + inputs[i + 1] * _weights[1]
      + inputs[i + 2] * _weights[2];
    results[index] = value;
    ++index;
  }

  return sigmoid(results);
}

private:
std::vector<double> sigmoid_derivatives(const std::vector<double>& x) const
{
  std::vector<double> results(4);
  for (int i = 0; i < 4; ++i)
  {
    results[i] = x[i] * (1.0 - x[i]);
  }
  return results;
}
std::vector<double> sigmoid(const std::vector<double>& x) const
{
  std::vector<double> results(4);
  for (int i = 0; i < 4; ++i)
  {
    results[i] = 1.0 / (1 + std::exp(-x[i]));
  }
  return results;
}

};
