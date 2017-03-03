#include <vector>
#include <cmath>
#include <numeric>

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
  const size_t n = training_set_outputs.size();
  std::vector<double> layer2_delta(n);

  for (int i = 0; i < iterations; ++i)
  {
    //Pass the training set through our neural network.
    std::pair<std::vector<double>, std::vector<double>> outputs =
      think(training_set_inputs);

    //Calculate the error for layer 2 (The difference between the desired output
    //and the predicted output)
    std::vector<double> sigmoid_derivatives2 =
      sigmoid_derivatives(outputs.second);

    auto p_training_set_outputs = training_set_outputs.begin();
    auto p_outputs_second = outputs.second.begin();
    auto p_sigmoid_derivatives2 = sigmoid_derivatives2.begin();
    for (auto delta = layer2_delta.begin(); delta != layer2_delta.end(); ++delta)
    {
      *delta =
        (*p_training_set_outputs - *p_outputs_second) * *p_sigmoid_derivatives2;
      ++p_training_set_outputs;
      ++p_outputs_second;
      ++p_sigmoid_derivatives2;
    }

    //Calculate the error for layer 1 (By looking at the weights in layer 1,
    //we can determine by how much layer 1 contributed to the error in layer 2).
    size_t size = layer2_delta.size() * _weights.second.size();
    std::vector<double> layer1_error(size);
    auto p_layer1_error = layer1_error.begin();
    for (auto delta: layer2_delta)
    {
      for (auto weight: _weights.second)
      {
        *p_layer1_error = delta * weight;
        ++p_layer1_error;
      }
    }
    std::vector<double> sigmoid_derivatives1 =
      sigmoid_derivatives(outputs.first);

    std::vector<double> layer1_delta(size);
    p_layer1_error = layer1_error.begin();
    auto p_sigmoid_derivatives1 = sigmoid_derivatives1.begin();
    for (auto delta = layer1_delta.begin(); delta != layer1_delta.end(); ++delta)
    {
      *delta = *p_layer1_error * *p_sigmoid_derivatives1;
      ++p_layer1_error;
      ++p_sigmoid_derivatives1;
    }
    adjust_weights(_weights.first, training_set_inputs, layer1_delta, n);
    adjust_weights(_weights.second, outputs.first, layer2_delta, n);
  }
}
std::pair<std::vector<double>, std::vector<double>> think(
  const std::vector<double>& inputs) const
{
  std::pair<std::vector<double>, std::vector<double>> outputs;

  const size_t n = _weights.first.size() / _weights.second.size();
  outputs.first = think(inputs, _weights.first, n);
  outputs.second = think(outputs.first, _weights.second, _weights.second.size());

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
  auto iterator = results.begin();
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
  auto iterator = results.begin();
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
