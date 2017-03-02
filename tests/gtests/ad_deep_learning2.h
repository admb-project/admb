#include <vector>
#include <cmath>
#include <numeric>

class neural_network2
{
std::pair<std::vector<double>, std::vector<double>> _weights; 

public:
/**
Default constructor
*/
neural_network2()
{
}

/**
Destructor
*/
~neural_network2()
{
}

void set_weights(const std::vector<double>& layer1_weights, const std::vector<double>& layer2_weights)
{
  _weights.first = layer1_weights;
  _weights.second = layer2_weights;
}

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
    std::pair<std::vector<double>, std::vector<double>> outputs = think(training_set_inputs);

    //Calculate the error for layer 2 (The difference between the desired output
    //and the predicted output)
    std::vector<double> sigmoid_derivatives2 = sigmoid_derivatives(outputs.second);
    for (int j = 0; j < training_set_outputs_size; ++j)
    {
      double layer2_error = training_set_outputs[j] - outputs.second[j];
      layer2_delta[j] = layer2_error * sigmoid_derivatives2[j];
    }

    //Calculate the error for layer 1 (By looking at the weights in layer 1,
    //we can determine by how much layer 1 contributed to the error in layer 2).
    int index = 0;
    size_t size = layer2_delta.size() * _weights.second.size();
    std::vector<double> layer1_error(size);
    for (int j = 0; j < layer2_delta.size(); ++j)
    {
      double value = layer2_delta[j];
      for (int k = 0; k < _weights.second.size(); ++k)
      {
        layer1_error[index] = value * _weights.second[k];
        ++index;
      }
    }
    std::vector<double> sigmoid_derivatives1 = sigmoid_derivatives(outputs.first);
    std::vector<double> layer1_delta(size);
    for (int j = 0; j < size; ++j)
    {
      layer1_delta[j] = layer1_error[j] * sigmoid_derivatives1[j];
    }

    //Calculate how much to adjust the weights by
    std::vector<double> layer1_adjustments = dot_transposed(training_set_inputs, layer1_delta, 7);
    std::vector<double> layer2_adjustments = dot_transposed(outputs.first, layer2_delta, 7);

    //Adjust the weights.
    for (int j = 0; j < _weights.first.size(); ++j)
    {
      _weights.first[j] += layer1_adjustments[j];
    }
    for (int j = 0; j < _weights.second.size(); ++j)
    {
      _weights.second[j] += layer2_adjustments[j];
    }
  }
}
std::pair<std::vector<double>, std::vector<double>> think(const std::vector<double>& inputs) const
{
  std::pair<std::vector<double>, std::vector<double>> outputs;

  outputs.first = think(inputs, _weights.first, 3);
  outputs.second = think(outputs.first, _weights.second, 4);

  return outputs;
}
std::pair<std::vector<double>, std::vector<double>> get_weights() const
{
  return _weights;
}

private:
std::vector<double> sigmoid_derivatives(const std::vector<double>& x) const
{
  std::vector<double> results(x.size());
  auto iterator = std::begin(results);
  for (auto xi: x)
  {
    *iterator = xi * (1.0 - xi);
    ++iterator;
  }
  return results;
}
std::vector<double> sigmoid(const std::vector<double>& x) const
{
  std::vector<double> results(x.size());
  auto iterator = std::begin(results);
  for (auto xi: x)
  {
    *iterator = 1.0 / (std::exp(-xi) + 1.0);
    ++iterator;
  }
  return results;
}
std::vector<double> dot(const std::vector<double>& a, const std::vector<double>& b, const size_t n) const
{
  const size_t m = a.size() / n;
  const size_t p = b.size() / n;
  const size_t size = m * p;

  std::vector<double> result(size);
  std::vector<double> col(n);

  auto ai = a.begin();
  auto di = result.begin();

  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < p; ++j)
    {
      int w = j;
      for (int k = 0; k < n; ++k)
      {
        col[k] = b[w];
        w += p;
      }
      *di = std::inner_product(ai, ai + n, col.begin(), 0.0);
      ++di;
    }
    ai += n;
  }
  return result;
}
std::vector<double> dot_transposed(const std::vector<double>& a, const std::vector<double>& b, const size_t n) const
{
  const int size = a.size();
  std::vector<double> a_transposed(size);

  int index = 0;
  int columns = size / n;
  for (int i = 0; i < columns; ++i)
  {
    int j = i;
    while (j < size)
    {
      a_transposed[index] = a[j];
      j += columns;
      ++index;
    }
  }

  return dot(a_transposed, b, n);
}
std::vector<double> think(const std::vector<double>& inputs, const std::vector<double>& weights, const size_t n) const
{
  return sigmoid(dot(inputs, weights, n));
}

};
