#include <future>
#include <vector>
#include <fvar.hpp>

size_t ngradients = 5;
gradient_structure** gradients = nullptr;
double total_funnel_time = 0;
double* get_total_funnel_time()
{
  return &total_funnel_time;
}
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
void add_futures(std::future<std::pair<double, dvector>>&& f)
{
  futures.push_back(std::move(f));
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
gradient_structure* get_gradient()
{
  if (id == 0)
  {
    add_pairs();
    id = 1;
  }
  gradient_structure* gs = gradients[id];
  ++id;
  if (id >= ngradients)
  {
    id = 0;
  }
  return gs;
}
