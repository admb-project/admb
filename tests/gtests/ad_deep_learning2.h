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
neural_network2(const size_t m, const size_t n)
{
  _weights.first.resize(m * n);
  _weights.second.resize(n);

  // initialize random seed
  srand (time(NULL));

  double max = 1.0 / RAND_MAX;
  for (auto p = _weights.first.begin(); p != _weights.first.end(); ++p)
  {
    *p = rand() * max; 
  }
  for (auto p = _weights.second.begin(); p != _weights.second.end(); ++p)
  {
    *p = rand() * max; 
  }
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
  std::pair<std::vector<double>, std::vector<double>> deltas;
  std::pair<std::vector<double>, std::vector<double>> outputs;

  size_t n = training_set_outputs.size();
  deltas.second.resize(n);
  deltas.first.resize(n * _weights.second.size());

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
    sigmoid_derivatives.first = compute_sigmoid_derivatives(outputs.first);
    auto p_delta_first = deltas.first.begin();
    auto p_sigmoid_derivatives_first = sigmoid_derivatives.first.begin();
    for (auto delta_second: deltas.second)
    {
      for (auto weight_second: _weights.second)
      {
        double error = delta_second * weight_second;
        *p_delta_first = *p_sigmoid_derivatives_first * error;
        ++p_delta_first;
        ++p_sigmoid_derivatives_first;
      }
    }

    adjust_weights(_weights.first, training_set_inputs, deltas.first, n);
    adjust_weights(_weights.second, outputs.first, deltas.second, n);
  }
}
std::pair<std::vector<double>, std::vector<double>> think(
  const std::vector<double>& inputs) const
{
  std::pair<std::vector<double>, std::vector<double>> outputs;

  const size_t n = _weights.first.size() / _weights.second.size();
  outputs.first = sigmoid(dot(inputs, _weights.first, n));
  outputs.second = sigmoid(dot(outputs.first, _weights.second, _weights.second.size()));

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
  auto p_results = std::begin(results);
  for (auto xi: x)
  {
    *p_results = xi * (1.0 - xi);
    ++p_results;
  }
  return results;
}
std::vector<double> sigmoid(const std::vector<double>& x) const
{
  std::vector<double> results(x.size());
  auto p_results = std::begin(results);
  for (auto xi: x)
  {
    *p_results = 1.0 / (std::exp(-xi) + 1.0);
    ++p_results;
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

  std::vector<double> results(size);
  std::vector<double> col(n);

  auto p_results = results.begin();
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
      *p_results = std::inner_product(ai, ai + n, col.begin(), 0.0);
      ++p_results;
    }
  }
  return results;
}
std::vector<double> dot_transposed(
  const std::vector<double>& a,
  const std::vector<double>& b,
  const size_t n) const
{
  const int size = a.size();
  std::vector<double> a_transposed(size);

  auto p_a_transposed = a_transposed.begin();

  int columns = size / n;
  auto end = a.begin() + columns;
  for (auto p_a  = a.begin(); p_a != end; ++p_a)
  {
    auto bi = p_a;
    auto biend = bi + columns * n;
    while (bi != biend)
    {
      *p_a_transposed = *bi;
      ++p_a_transposed;

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
  auto p_weights = weights.begin();
  for (auto adjustment: adjustments)
  {
    *p_weights += adjustment;
    ++p_weights;
  }
}
};
