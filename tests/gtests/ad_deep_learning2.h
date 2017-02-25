#include <vector>
#include <cmath>
#include <numeric>

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
neural_network2()
{
  //4 by 3 matrix
  _layer1.synaptic_weights =
  {
    0.16595599, 0.44064899, -0.99977125, -0.39533485,
    -0.70648822, -0.81532281, -0.62747958, -0.30887855,
    -0.20646505, 0.07763347, -0.16161097, 0.370439,
  };
  //1 by 4 matrix
  _layer2.synaptic_weights =
  {
    -0.5910955,
    0.75623487,
    -0.94522481,
    0.34093502
  };
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

/**
We train the neural network through a process of trial and error.
Adjusting the synaptic weights each time.

\param
\param
\param
*/
void training(
  std::vector<double>& training_set_inputs,
  std::vector<double>& training_set_outputs,
  const size_t iterations
)
{ 
  const size_t training_set_outputs_size = training_set_outputs.size();
  std::vector<double> layer2_delta(training_set_outputs_size);

  for (int i = 0; i < iterations; ++i)
  {
    //Pass the training set through our neural network.
    think(training_set_inputs);

    //Calculate the error for layer 2 (The difference between the desired output
    //and the predicted output)
    std::vector<double> sigmoid_derivatives2 = sigmoid_derivatives(_output_from_layer2);
    for (int j = 0; j < training_set_outputs_size; ++j)
    {
      double layer2_error = training_set_outputs[j] - _output_from_layer2[j];
      layer2_delta[j] = layer2_error * sigmoid_derivatives2[j];
    }

    //Calculate the error for layer 1 (By looking at the weights in layer 1,
    //we can determine by how much layer 1 contributed to the error in layer 2).
    int index = 0;
    size_t size = layer2_delta.size() * _layer2.synaptic_weights.size();
    std::vector<double> layer1_error(size);
    for (int j = 0; j < layer2_delta.size(); ++j)
    {
      double value = layer2_delta[j];
      for (int k = 0; k < _layer2.synaptic_weights.size(); ++k)
      {
        layer1_error[index] = value * _layer2.synaptic_weights[k];
        ++index;
      }
    }
    std::vector<double> sigmoid_derivatives1 = sigmoid_derivatives(_output_from_layer1);
    std::vector<double> layer1_delta(size);
    for (int j = 0; j < size; ++j)
    {
      layer1_delta[j] = layer1_error[j] * sigmoid_derivatives1[j];
    }

    //Calculate how much to adjust the weights by
    std::vector<double> layer1_adjustment = dot_transposed(training_set_inputs, layer1_delta, 7);
    std::vector<double> layer2_adjustment = dot_transposed(_output_from_layer1, layer2_delta, 7);

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
  _output_from_layer1.clear();
  _output_from_layer1 = think(inputs, _layer1.synaptic_weights, 3);
  _output_from_layer2.clear();
  _output_from_layer2 = think(_output_from_layer1, _layer2.synaptic_weights, 4);
}

private:
std::vector<double> sigmoid_derivatives(const std::vector<double>& x) const
{
  size_t size = x.size();
  std::vector<double> results(size);
  for (int i = 0; i < size; ++i)
  {
    results[i] = x[i] * (1.0 - x[i]);
  }
  return results;
}
std::vector<double> sigmoid(const std::vector<double>& x) const
{
  size_t size = x.size();
  std::vector<double> results(size);
  for (int i = 0; i < size; ++i)
  {
    results[i] = 1.0 / (1 + std::exp(-x[i]));
  }
  return results;
}
std::vector<double> dot(const std::vector<double>& a, const std::vector<double>& b, const size_t n) const
{
  const size_t m = a.size() / n;
  const size_t p = b.size() / n;
  const size_t size = m * p;
  std::vector<double> result(size);
 
  std::vector<double> row(n);
  std::vector<double> col(n);

  int r = 0;
  int index = 0;
  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      row[j] = a[r];
      ++r;
    }
    for (int j = 0; j < p; ++j)
    {
      int w = j;
      for (int k = 0; k < n; ++k)
      {
        col[k] = b[w];
        w += p;
      }
      result[index] = std::inner_product(row.begin(), row.end(), col.begin(), 0.0);
      ++index;
    }
  }
  return result;
}
std::vector<double> dot_transposed(const std::vector<double>& a, const std::vector<double>& b, const size_t n) const
{
  std::vector<double> a_tranposed(a.size());
  return dot(a_tranposed, b, n);
}
std::vector<double> think(const std::vector<double>& inputs, const std::vector<double>& weights, const size_t n) const
{
  return sigmoid(dot(inputs, weights, n));
}

};
