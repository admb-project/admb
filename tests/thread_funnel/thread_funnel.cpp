#include <future>
#include <fvar.hpp>
#include "thread_funnel.h"

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
dvariable to_dvariable(
  std::pair<double, dvector>& p,
  const dvariable& x, const dvariable& y,
  const dvariable& u, const dvariable& v)
{
  gradient_structure* gs = gradient_structure::get();
  grad_stack* GRAD_STACK1 = gs->GRAD_STACK1;

  dvariable var(p.first);
  dvector g(p.second);

  grad_stack_entry* entry = GRAD_STACK1->ptr;
  entry->func = NULL;
  entry->dep_addr = &((*var.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);
  GRAD_STACK1->ptr++;
  grad_stack_entry* entry2 = GRAD_STACK1->ptr;
  entry2->func = default_evaluation4ind;
  entry2->ind_addr1 = &((*u.v).x);
  entry2->mult1 = g(3);
  entry2->ind_addr2 = &((*v.v).x);
  entry2->mult2 = g(4);
  GRAD_STACK1->ptr++;

  return var;
}

dvar_vector funnel(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
{
  auto start = std::chrono::high_resolution_clock::now();

  const int min = a.indexmin();
  const int max = a.indexmax();
  dvar_vector results(min, max);

  gradient_structure* gs = gradient_structure::get();

  for (int i = min; i < max; i += 4)
  {
    gradient_structure::_instance = gradients[1];
    std::future<std::pair<double, dvector>> f = 
      thread_funnel(func, tau, nu, sigma, beta, a(i), nsteps);
    gradient_structure::_instance = nullptr;

    gradient_structure::_instance = gradients[2];
    std::future<std::pair<double, dvector>> f2 = 
      thread_funnel(func, tau, nu, sigma, beta, a(i + 1), nsteps);
    gradient_structure::_instance = nullptr;

    gradient_structure::_instance = gradients[3];
    std::future<std::pair<double, dvector>> f3 = 
      thread_funnel(func, tau, nu, sigma, beta, a(i + 2), nsteps);
    gradient_structure::_instance = nullptr;

    gradient_structure::_instance = gradients[4];
    std::future<std::pair<double, dvector>> f4 = 
      thread_funnel(func, tau, nu, sigma, beta, a(i + 3), nsteps);
    gradient_structure::_instance = nullptr;

    f.wait();
    f2.wait();
    f3.wait();
    f4.wait();

    std::pair<double, dvector> p = f.get();
    std::pair<double, dvector> p2 = f2.get();
    std::pair<double, dvector> p3 = f3.get();
    std::pair<double, dvector> p4 = f4.get();

    gradient_structure::_instance = gs;
    results(i) = to_dvariable(p, tau, nu, sigma, beta);
    results(i + 1) = to_dvariable(p2, tau, nu, sigma, beta);
    results(i + 2) = to_dvariable(p3, tau, nu, sigma, beta);
    results(i + 3) = to_dvariable(p4, tau, nu, sigma, beta);
    gradient_structure::_instance = nullptr;
  }

  {
    gradient_structure::_instance = gradients[1];
    std::future<std::pair<double, dvector>> f = 
      thread_funnel(func, tau, nu, sigma, beta, a(max), nsteps);
    gradient_structure::_instance = nullptr;

    f.wait();

    std::pair<double, dvector> p = f.get();

    gradient_structure::_instance = gs;
    results(max) = to_dvariable(p, tau, nu, sigma, beta);
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
