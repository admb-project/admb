#include <vector>
#include <cmath>

struct neuron_layer
{
std::vector<double> synaptic_weights;
};

class neural_network2
{
neuron_layer _layer1;
neuron_layer _layer2;
std::vector<double> _output_from_layer1;
std::vector<double> _output_from_layer2;

public:

/**
Default constructor
*/
neural_network2():
  _output_from_layer1({0, 0, 0, 0}),
  _output_from_layer2({0, 0, 0, 0})
{
  //4 by 3 matrix
  _layer1.synaptic_weights =
  {
    -0.16595599, 0.44064899, -0.99977125, -0.39533485,
    -0.70648822, -0.81532281, -0.62747958, -0.30887855,
    -0.20646505, 0.07763347, -0.16161097, 0.370439
  };
  //1 by 4 matrix
  _layer2.synaptic_weights = {-0.5910955, 0.75623487, -0.94522481, 0.34093502};
}

/**
Destructor
*/
~neural_network2()
{
}

/*
std::vector<double>& get_weights()
  { return _weights; }
*/

void training(std::vector<double>& inputs, std::vector<double>& outputs, const size_t iterations)
{
  for (int i = 0; i < iterations; ++i)
  {
    think(inputs);
/*
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
      _layer1.synaptic_weights[j] += adjustments[j];
      _layer2.synaptic_weights[j] += adjustments[j];
    }
*/
  }
}
void think(const std::vector<double>& inputs)
{
  _output_from_layer1 = think(inputs, _layer1.synaptic_weights);
  _output_from_layer2 = think(_output_from_layer1, _layer2.synaptic_weights);
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
std::vector<double> think(const std::vector<double>& inputs, const std::vector<double>& weights) const
{
  const size_t m = 7;
  const size_t n = 3;
  const size_t p = 4;
  const size_t size = m * p;
  std::vector<double> dot(size);
 
  for (int i = 0; i < size; ++i)
  {
  }
/*
  size_t index = 0;
  for (int i = 0; i < inputs.size(); i += 3)
  {
    double value = inputs[i] * weights[0]
      + inputs[i + 1] * weights[1]
      + inputs[i + 2] * weights[2];
    dot[index] = value;
    ++index;
  }
*/

  return sigmoid(dot);
}

};
