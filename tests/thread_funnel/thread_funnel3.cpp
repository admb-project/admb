#include <future>
#include <fvar.hpp>
#include "thread_funnel3.h"

size_t ngradients = 5;
size_t get_ngradients()
{
  return ngradients;
}
gradient_structure** gradients = nullptr;
gradient_structure** get_gradients()
{
  return gradients;
}

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
int* get_id()
{
  return &id;
}
std::vector<std::future<std::pair<double, dvector>>> futures;
std::vector<std::future<std::pair<double, dvector>>>* get_futures()
{
  return &futures;
}
std::vector<std::pair<double, dvector>> pairs;
std::vector<std::pair<double, dvector>>* get_pairs()
{
  return &pairs;
}
void add_pairs()
{
  gradient_structure* gs = gradient_structure::get();

  gradient_structure::_instance = nullptr;
  int jmax = futures.size();
  for (int j = 0; j < jmax; ++j)
  {
    futures[j].wait();

    std::pair<double, dvector> p = futures[j].get();

    pairs.push_back(std::move(p));
  }
  futures.clear();

  gradient_structure::_instance = gs;
}
