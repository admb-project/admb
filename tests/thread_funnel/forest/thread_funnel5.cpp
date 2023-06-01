#include <future>
#include <vector>
#include <unistd.h>
#include <fvar.hpp>

double total_funnel_time = 0;
double allocation_time = 0;
double deallocation_time = 0;

size_t ngradients = 5;
gradient_structure** gradients = nullptr;

void allocate_gradients()
{
  gradient_structure* gs = gradient_structure::get();

  auto start = std::chrono::high_resolution_clock::now();

  gradients = new gradient_structure*[ngradients];

  for (int i = 0; i < ngradients; ++i)
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

  cout << "Total Funnel time: " << total_funnel_time << endl;
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < ngradients; ++i)
  {
    delete gradients[i];
    gradients[i] = nullptr;
  }
  delete [] gradients;
  gradients = nullptr;

  gradient_structure::_instance = gs;
  gradient_structure::fp = gs->get_fp();
  gradient_structure::GRAD_STACK1 = gs->get_GRAD_STACK1();

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  deallocation_time = elapsed.count();
  std::cout << "Resource time: " << (deallocation_time + allocation_time)  <<  endl;
}
int id = 1;
std::vector<std::future<std::tuple<double, dvector, std::vector<double*>>>> futures;
std::vector<std::tuple<double, dvector, std::vector<double*>>> tuples;
void add_tuples()
{
  for (std::future<std::tuple<double, dvector, std::vector<double*>>>& f : futures)
  {
    f.wait();

    tuples.push_back(std::move(f.get()));
  }
  futures.clear();
}
void add_futures(std::future<std::tuple<double, dvector, std::vector<double*>>>&& f)
{
  futures.push_back(std::move(f));
  if (id == 0)
  {
    add_tuples();
  }
}
gradient_structure* get_gradient()
{
  if (id == 0)
  {
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
void funnel_evaluation_end()
{
}
void funnel_evaluation_nindependents()
{
  gradient_structure* gs = gradient_structure::get();
  grad_stack* GRAD_STACK1 = gs->GRAD_STACK1;
  grad_stack_entry* grad_ptr = GRAD_STACK1->ptr;

  double z = 0;
  if (grad_ptr->dep_addr)
  {
    z = *grad_ptr->dep_addr;
    *grad_ptr->dep_addr = 0.0;
  }
  do
  {
    // there are n independent variables
    grad_ptr = GRAD_STACK1->ptr;
    if (grad_ptr->ind_addr1)
    {
      *(grad_ptr->ind_addr1) += z * grad_ptr->mult1;
    }
    if (grad_ptr->ind_addr2)
    {
      *(grad_ptr->ind_addr2) += z * grad_ptr->mult2;
    }
    if (GRAD_STACK1->ptr-- == GRAD_STACK1->ptr_first)
    {
      // back up the file one buffer size and read forward
      OFF_T offset = (OFF_T)(sizeof(grad_stack_entry) * GRAD_STACK1->length);
      OFF_T lpos = LSEEK(GRAD_STACK1->_GRADFILE_PTR, -offset, SEEK_CUR);
      GRAD_STACK1->read_grad_stack_buffer(lpos);
    }
  } while (GRAD_STACK1->ptr->func != funnel_evaluation_end);
}
dvariable to_dvariable(std::tuple<double, dvector, std::vector<double*>>& t)
{
  gradient_structure* gs = gradient_structure::get();
  grad_stack* GRAD_STACK1 = gs->GRAD_STACK1;

  dvariable var = std::get<0>(t);
  dvector g = std::get<1>(t);
  double** a = std::get<2>(t).data();

  // Mark end
  GRAD_STACK1->ptr->func = funnel_evaluation_end;
  GRAD_STACK1->ptr++;

  int i = 0;
  int j = 1;
  int min = g.indexmin();
  int max = g.indexmax();
  while (j <= max)
  {
    grad_stack_entry* entry = GRAD_STACK1->ptr;

    entry->ind_addr1 = a[i];
    ++i;
    entry->mult1 = g(j);
    ++j;
    if (j <= max)
    {
      entry->ind_addr2 = a[i];
      ++i;
      entry->mult2 = g(j);
      ++j;
    }
    else
    {
      entry->ind_addr2 = nullptr;
      entry->mult2 = 0;
    }
    if (j > max)
    {
      entry->dep_addr = &((*var.v).x);
      entry->func = funnel_evaluation_nindependents;
    }
    else
    {
      entry->dep_addr = nullptr;
      entry->func = nullptr;
    }
    GRAD_STACK1->ptr++;
  }

  return var;
}
void get_results(dvar_vector& results)
{
  add_tuples();

  if (tuples.size() > 0)
  {
    int i = results.indexmin();
    for (std::tuple<double, dvector, std::vector<double*>>& t: tuples)
    {
      results(i) = to_dvariable(t);
      ++i;
    }
    tuples.clear();
  }
}
