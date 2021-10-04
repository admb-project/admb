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
std::vector<std::future<std::pair<double, dvector>>> futures;
dvar_vector funnels(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
{
  auto start = std::chrono::high_resolution_clock::now();

  const int min = a.indexmin();
  const int max = a.indexmax();
  dvar_vector results(min, max);

  gradient_structure* gs = gradient_structure::get();

  for (int i = min; i <= max; ++i)
  {
    int id = (i % 4) + 1;
    gradient_structure::_instance = gradients[id];
    std::future<std::pair<double, dvector>> f =
      thread_funnel(func, tau, nu, sigma, beta, a(i), nsteps);
    futures.push_back(std::move(f));
    gradient_structure::_instance = nullptr;

    futures[0].wait();

    std::pair<double, dvector> p = futures[0].get();

    gradient_structure::_instance = gs;
    results(i) = to_dvariable(p, tau, nu, sigma, beta);
    gradient_structure::_instance = nullptr;

    futures.clear();
  }
  gradient_structure::_instance = gs;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  double count = elapsed.count();
  std::cout << "Funnel time: " << count <<  endl;
  total_funnel_time += count;

  return results;
}
