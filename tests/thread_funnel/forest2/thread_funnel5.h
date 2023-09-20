#ifndef __THREAD_FUNNEL_H__
#define __THREAD_FUNNEL_H__

#include <tuple>
#include <vector>
#include <future>
#include <fvar.hpp>

void add_address(std::vector<double*>& addresses, const dvariable& arg)
{
  addresses.push_back(&((*arg.v).x));
}
template<typename T>
void add_address(std::vector<double*>& addresses, const T& arg)
{
}
template<typename ...Ts>
void get_addresses(std::vector<double*>& addresses, Ts&&... args)
{
  (add_address(addresses, args), ...);
}
void set_independent_variable(independent_variables& independents, int& index, const dvariable& arg)
{
  independents(index) = value(arg);
  ++index;
}
template<typename T>
void set_independent_variable(independent_variables& independents, int& index, const T& arg)
{
}
template<typename ...Ts>
int set_independent_variables(independent_variables& independents, Ts&&... args)
{
  int index = independents.indexmin();
  (set_independent_variable(independents, index, args), ...);

  return index;
}
std::tuple<const dvariable&> create_tuple_element(std::vector<dvariable>& variables, int& index, const dvariable& arg)
{
  return std::tie(variables[index++]);
}
template<typename Arg>
std::tuple<const Arg&> create_tuple_element(std::vector<dvariable>& variables, int& index, const Arg& arg)
{
  return std::tie(arg);
}
template<typename ...Args>
std::tuple<const Args&...> create_tuple(std::vector<dvariable>& variables, Args&&... args)
{
  int index = 0;
  std::tuple<const Args&...> t = std::tuple_cat(create_tuple_element(variables, index, args)...);
  return std::move(t);
}
gradient_structure* get_gradient();
template<class F, class ...Args>
std::tuple<double, dvector, std::vector<double*>>
thread_funnel(F&& func, Args&&... args)
{
  gradient_structure* gs = get_gradient();
  //return std::async(std::launch::async, [gs, &func, &args...]()->std::tuple<double, dvector, std::vector<double*>>
  //{
    std::vector<double*> addresses;
    get_addresses(addresses, std::forward<Args>(args)...);

    gradient_structure::_instance = gs;
    gradient_structure::fp = gs->get_fp();
    gradient_structure::GRAD_STACK1 = gs->get_GRAD_STACK1();

    double v = 0;
    const size_t nvar = addresses.size();
    dvector g(1, nvar);
    {
      independent_variables scoped_independents(1, nvar);
      set_independent_variables(scoped_independents, std::forward<Args>(args)...);

      // Set gradient_structure::NVAR
      dvar_vector scoped_variables(scoped_independents);

      std::vector<dvariable> variables;
      for (int i = nvar; i >= 1; --i)
      {
        variables.push_back(std::move(scoped_variables(i)));
      }

      dvariable f(0);

      std::tuple<const Args&...> t = create_tuple(variables, std::forward<Args>(args)...);
      f = std::apply(func, t);

      v = value(f);

      gradcalc(nvar, g);
    }

    return std::make_tuple(v, g, std::move(addresses));
  //});
}
void add_futures(std::future<std::tuple<double, dvector, std::vector<double*>>>&& f);
void add_tuple(std::tuple<double, dvector, std::vector<double*>>&& t);

template<class F, class ...Args>
void funnel(F&& func, Args&&... args)
{
  gradient_structure* gs = gradient_structure::get();

  //std::future<std::tuple<double, dvector, std::vector<double*>>> f =
  std::tuple<double, dvector, std::vector<double*>> t =
    thread_funnel(func, std::forward<Args>(args)...);
  //add_futures(std::move(f));
  add_tuple(std::move(t));

  gradient_structure::_instance = gs;
  gradient_structure::fp = gs->get_fp();
  gradient_structure::GRAD_STACK1 = gs->get_GRAD_STACK1();
}
void get_results(dvar_vector& results);
#endif
