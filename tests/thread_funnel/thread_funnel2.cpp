#include <future>
#include <fvar.hpp>
#include "thread_funnel2.h"

size_t ngradients = 5;
gradient_structure** gradients = nullptr;
int gradient_index = -1;

std::vector<std::future<std::pair<double, dvector>>> future_results;
//std::vector<dvariable> results;

double total_funnel_time = 0;
double allocation_time = 0;
double deallocation_time = 0;

bool is_last_gradient()
{
  return gradient_index == ngradients;
}
gradient_structure* get_gradient()
{
  if (gradient_index >= ngradients)
  {
    gradient_index = 1;
  }
  return gradients[gradient_index++];
}
void add_futures(std::future<std::pair<double, dvector>>&& future_pair)
{
  future_results.push_back(std::move(future_pair));
}
void wait_futures()
{
  int size = future_results.size();
  for (int i = 0; i < size; ++i)
  {
    future_results[i].wait();
  }
}
template<class ...Args>
void get_results(dvar_vector& results, Args&&... args)
{
  int size = future_results.size();
  for (int i = 0; i < size; ++i)
  {
    std::pair<double, dvector> p = future_results[i].get();
    double* dep_addr = &((*results[i + 1].v).x);
    to_dvariable(dep_addr, p, std::forward<Args>(args)...);
  }
  future_results.clear();
}
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
  gradient_index = 1;

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
  gradient_index = -1;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  deallocation_time = elapsed.count();
  std::cout << "Resource time: " << (deallocation_time + allocation_time)  <<  endl;

  gradient_structure::_instance = gs;
}
dvar_vector funnels(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
{
  auto start = std::chrono::high_resolution_clock::now();
  gradient_structure* gs = gradient_structure::get();

  const int min = a.indexmin();
  const int max = a.indexmax();
  for (int i = min; i <= max; ++i)
  {
    funnel(func, tau, nu, sigma, beta, a(i), nsteps);
  }

  gradient_structure::_instance = gs;
  dvar_vector results(min, max);
  results.initialize();

  get_results(results, tau, nu, sigma, beta);

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  double count = elapsed.count();
  std::cout << "Funnel time: " << count <<  endl;
  total_funnel_time += count;

  return results;
}
