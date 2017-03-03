#include <vector>
#include <cmath>
#include <numeric>
#include <utility>

class neural_network2
{
std::pair<std::vector<double>, std::vector<double>> _weights; 

public:
/** Default constructor */
neural_network2()
{
}
/** Destructor */
~neural_network2()
{
}
void set_weights(
  const std::vector<double>& layer1_weights,
  const std::vector<double>& layer2_weights)
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
  const size_t iterations)
{ 
  std::pair<std::vector<double>, std::vector<double>> sigmoid_derivatives;
  std::pair<std::vector<double>, std::vector<double>> outputs;
  int n = training_set_outputs.size();
  int size = n * _weights.second.size();
  std::vector<double> error(size);
  std::pair<std::vector<double>, std::vector<double>> deltas;
  deltas.second.resize(n);
  deltas.first.resize(size);

  for (int i = 0; i < iterations; ++i)
  {
    //Pass the training set through our neural network.
    outputs = think(training_set_inputs);

    //Calculate the error for layer 2 (The difference between the desired output
    //and the predicted output)
    sigmoid_derivatives.second = compute_sigmoid_derivatives(outputs.second);
    auto p_training_set_outputs = training_set_outputs.begin();
    auto p_outputs_second = outputs.second.begin();
    auto p_sigmoid_derivatives_second = sigmoid_derivatives.second.begin();
    for (auto delta_second = deltas.second.begin(); delta_second != deltas.second.end(); ++delta_second)
    {
      double error = *p_training_set_outputs - *p_outputs_second;
      *delta_second = *p_sigmoid_derivatives_second * error;
      ++p_sigmoid_derivatives_second;
      ++p_training_set_outputs;
      ++p_outputs_second;
    }

    //Calculate the error for layer 1 (By looking at the weights in layer 1,
    //we can determine by how much layer 1 contributed to the error in layer 2).
    auto p_error = error.begin();
    for (auto delta_second: deltas.second)
    {
      for (auto weight_second: _weights.second)
      {
        *p_error = delta_second * weight_second;
        ++p_error;
      }
    }

    sigmoid_derivatives.first = compute_sigmoid_derivatives(outputs.first);
    p_error = error.begin();
    auto p_sigmoid_derivatives_first = sigmoid_derivatives.first.begin();
    for (auto delta_first = deltas.first.begin(); delta_first != deltas.first.end(); ++delta_first)
    {
      double error = *p_error;
      *delta_first = *p_sigmoid_derivatives_first * error;
      ++p_error;
      ++p_sigmoid_derivatives_first;
    }
    adjust_weights(_weights.first, training_set_inputs, deltas.first, n);
    adjust_weights(_weights.second, outputs.first, deltas.second, n);
  }
}
std::pair<std::vector<double>, std::vector<double>> think(
  const std::vector<double>& inputs) const
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
std::vector<double> compute_sigmoid_derivatives(const std::vector<double>& x) const
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
std::vector<double> dot(
  const std::vector<double>& a,
  const std::vector<double>& b,
  const size_t n) const
{
  const size_t m = a.size() / n;
  const size_t p = b.size() / n;
  const size_t size = m * p;

  std::vector<double> result(size);
  std::vector<double> col(n);

  auto di = result.begin();
  for (auto ai  = a.begin(); ai != a.end(); ai += n)
  {
    auto end = b.begin() + p;
    for (auto pi  = b.begin(); pi != end; ++pi)
    {
      auto bi = pi;
      for (auto ci  = col.begin(); ci != col.end(); ++ci)
      {
        *ci = *bi;
        bi += p;
      }
      *di = std::inner_product(ai, ai + n, col.begin(), 0.0);
      ++di;
    }
  }
  return result;
}
std::vector<double> dot_transposed(
  const std::vector<double>& a,
  const std::vector<double>& b,
  const size_t n) const
{
  const int size = a.size();
  std::vector<double> a_transposed(size);

  auto ati = a_transposed.begin();

  int columns = size / n;
  auto end = a.begin() + columns;
  for (auto ai  = a.begin(); ai != end; ++ai)
  {
    auto bi = ai;
    auto biend = bi + columns * n;
    while (bi != biend)
    {
      *ati = *bi;
      ++ati;

      bi += columns;
    }
  }
  return dot(a_transposed, b, n);
}
void adjust_weights(
  std::vector<double>& weights,
  const std::vector<double>& a,
  const std::vector<double>& b,
  const size_t n)
{
  //Calculate how much to adjust the weights by
  std::vector<double> adjustments = dot_transposed(a, b, n);

  //Adjust the weights.
  auto wi = weights.begin();
  for (auto value: adjustments)
  {
    *wi += value;
    ++wi;
  }
}
std::vector<double> think(
  const std::vector<double>& inputs,
  const std::vector<double>& weights,
  const size_t n) const
{
  return sigmoid(dot(inputs, weights, n));
}
};
