#ifndef __THREAD_FUNNEL_H__
#define __THREAD_FUNNEL_H__

#include <tuple>
#include <vector>
#include <future>
#include <fvar.hpp>

size_t get_addresses(std::vector<double*>& addresses, dvariable const& arg)
{
  addresses.push_back(&((*arg.v).x));
  return 1;
}
template<typename T>
size_t get_addresses(std::vector<double*>& addresses, T arg)
{
  return 0;
}
template<typename ...Ts>
size_t get_addresses(std::vector<double*>& addresses, Ts&&... args)
{
  return (get_addresses(addresses, std::forward<Ts>(args)) + ...);
}

void set_independent_variables(independent_variables& independents, int& index, const dvariable& arg)
{
  independents(index) = value(arg);
  ++index;
}
template<typename T>
void set_independent_variables(independent_variables& independents, int& index, T arg)
{
}
template<typename ...Ts>
void set_independent_variables(independent_variables& independents, Ts... args)
{
  int index = independents.indexmin();
  (set_independent_variables(independents, index, args), ...);
}

std::tuple<dvariable const&> create_tuple(std::vector<dvariable>& variables, int index, dvariable const& arg)
{
  return std::tie(variables[index]);
}
template<typename Arg>
std::tuple<Arg> create_tuple(std::vector<dvariable>& variables, int& index, Arg&& arg)
{
  return std::tie(arg);
}
template<typename Arg, typename ...Args>
std::tuple<Arg, Args...> create_tuple(std::vector<dvariable>& variables, int& index, Arg&& arg, Args&&... args)
{
  std::tuple<Arg> t = std::tie(arg);
  std::tuple<Args...> t2 = create_tuple(variables, index, std::forward<Args>(args)...);
  return std::tuple_cat(t, t2);
}
template<typename ...Args>
std::tuple<dvariable const&, Args...> create_tuple(std::vector<dvariable>& variables, int& index, dvariable const& arg, Args&&... args)
{
  std::tuple<dvariable const&> t = std::tie(variables[index]);
  ++index;
  std::tuple<Args...> t2 = create_tuple(variables, index, std::forward<Args>(args)...);
  return std::tuple_cat(t, t2);
}
template<typename ...Args>
std::tuple<Args...> create_tuple(std::vector<dvariable>& variables, Args&&... args)
{
  int index = 0;
  std::tuple<Args...> t = create_tuple(variables, index, std::forward<Args>(args)...);
  return std::tuple_cat(t);
}

gradient_structure* get_gradient();
template<class F, class ...Args>
std::future<std::tuple<double, dvector, std::vector<double*>>> thread_funnel(F&& func, Args&&... args)
{
  std::vector<double*> addresses;
  size_t nvar = get_addresses(addresses, std::forward<Args>(args)...);

  gradient_structure* gs = get_gradient();
  return std::async(std::launch::async, [=]()->std::tuple<double, dvector, std::vector<double*>>
  {
    gradient_structure::_instance = gs;

    double v = 0;
    dvector g(1, nvar);
    {
      independent_variables scoped_independents(1, nvar);
      set_independent_variables(scoped_independents, args...);

      // Set gradient_structure::NVAR
      dvar_vector scoped_variables(scoped_independents);

      std::vector<dvariable> variables;
      for (int i = 1; i <= nvar; ++i)
      {
        variables.push_back(std::move(scoped_variables(i)));
      }

      dvariable f(0);

      std::tuple<Args...> t = create_tuple(variables, std::forward<Args>(args)...);
      f = std::apply(func, t);

      v = value(f);

      gradcalc(nvar, g);
    }

    return std::make_tuple(v, g, addresses);
  });
}
template<class ...Args>
dvariable to_dvariable(std::tuple<double, dvector, std::vector<double*>>& t, Args&& ...args)
{
  gradient_structure* gs = gradient_structure::get();
  grad_stack* GRAD_STACK1 = gs->GRAD_STACK1;

  dvariable var = std::get<0>(t);
  dvector g = std::get<1>(t);
  std::vector<double*> a = std::get<2>(t);

  int i = 0;
  int j = 1;
  while (j <= g.indexmax())
  {
    grad_stack_entry* entry = GRAD_STACK1->ptr;

    entry->dep_addr = j == g.indexmin() ? &((*var.v).x) : NULL;

    entry->ind_addr1 = a[i];
    ++i;
    entry->mult1 = g(j);
    ++j;
    entry->ind_addr2 = a[i];
    ++i;
    entry->mult2 = g(j);
    ++j;

    entry->func = j > g.indexmax() ? default_evaluation4ind : NULL;

    GRAD_STACK1->ptr++;
  }

  return var;
}
void add_futures(std::future<std::tuple<double, dvector, std::vector<double*>>>&& f);
template<class F, class ...Args>
void funnel(F&& func, Args&&... args)
{
  gradient_structure* gs = gradient_structure::get();

  std::future<std::tuple<double, dvector, std::vector<double*>>> f =
    thread_funnel(func, std::forward<Args>(args)...);
  add_futures(std::move(f));

  gradient_structure::_instance = gs;
}
std::vector<std::tuple<double, dvector, std::vector<double*>>>* get_tuples();
template<class ...Args>
void get_results(dvar_vector& results, Args&&... args)
{
  std::vector<std::tuple<double, dvector, std::vector<double*>>>* tuples = get_tuples();

  const int size = tuples->size();
  if (size > 0)
  {
    int j = 0;
    for (int k = results.indexmin(); k <= results.indexmax(); ++k)
    {
      results(k) = to_dvariable(tuples->at(j), std::forward<Args>(args)...);
      ++j;
    }
    tuples->clear();
  }
}
#endif
