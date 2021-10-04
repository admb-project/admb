#include <future>
#include <fvar.hpp>
#include "thread_funnel3.h"

size_t ngradients = 5;
gradient_structure** gradients = nullptr;

double total_funnel_time = 0;
double allocation_time = 0;
double deallocation_time = 0;

void allocate_gradients()
{
  gradient_structure* gs = gradient_structure::get();

  auto start = std::chrono::high_resolution_clock::now();

  gradients = new gradient_structure*[ngradients];

  gradients[0] = nullptr;
  for (int i = 1; i < ngradients; ++i)
  {
    gradients[i] = new gradient_structure(10000, i);
  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  allocation_time = elapsed.count();

  gradient_structure::_instance = gs;
  gs = nullptr;
}
void deallocate_gradients()
{
  gradient_structure* gs = gradient_structure::get();
  gradient_structure::_instance = nullptr;

  cout << "Total Funnel time: " << total_funnel_time << endl;
  auto start = std::chrono::high_resolution_clock::now();

  gradients[0] = nullptr;
  for (int i = 1; i < ngradients; ++i)
  {
    delete gradients[i];
    gradients[i] = nullptr;
  }
  delete [] gradients;
  gradients = nullptr;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  deallocation_time = elapsed.count();
  std::cout << "Resource time: " << (deallocation_time + allocation_time)  <<  endl;

  gradient_structure::_instance = gs;
}
int id = 1;
std::vector<std::future<std::pair<double, dvector>>> futures;
std::vector<std::pair<double, dvector>> pairs;
void add_pairs()
{
  int jmax = futures.size();
  for (int j = 0; j < jmax; ++j)
  {
    futures[j].wait();

    std::pair<double, dvector> p = futures[j].get();

    pairs.push_back(std::move(p));
  }
  futures.clear();
}
template<class F, class ...Args>
void funnel(F&& func, Args&&... args)
{
  gradient_structure::_instance = gradients[id];
  std::future<std::pair<double, dvector>> f =
    thread_funnel(func, std::forward<Args>(args)...);
  futures.push_back(std::move(f));
  gradient_structure::_instance = nullptr;

  ++id;
  if (id >= ngradients)
  {
    id = 1;
  }
}
dvar_vector funnels(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
{
  auto start = std::chrono::high_resolution_clock::now();

  const int min = a.indexmin();
  const int max = a.indexmax();
  dvar_vector results(min, max);

  gradient_structure* gs = gradient_structure::get();

  int n = ngradients - 1;
  int k = min;
  for (int i = min; i <= max; ++i)
  {
    funnel(func, tau, nu, sigma, beta, a(i), nsteps);

    int id2 = (i % n) + 1;
    if (id2 == n || i == max)
    {
      add_pairs();
    }
  }
  for (int k = min; k < max; ++k)
  {
    gradient_structure::_instance = gs;
    results(k) = to_dvariable(pairs[k - 1], tau, nu, sigma, beta);
    gradient_structure::_instance = nullptr;
  }
  gradient_structure::_instance = gs;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  double count = elapsed.count();
  std::cout << "Funnel time: " << count <<  endl;
  total_funnel_time += count;

  return results;
}
