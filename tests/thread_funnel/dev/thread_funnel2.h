#include <tuple>
#include <vector>
#include <future>
#include <fvar.hpp>

size_t count_variables(const dvariable& arg)
{
  return 1;
}
template<typename T>
size_t count_variables(T arg)
{
  return 0;
}
template<typename T, typename ...Ts>
size_t count_variables(T arg, Ts... args)
{
  return count_variables(args...);
}
template<typename ...Ts>
size_t count_variables(const dvariable& arg, Ts... args)
{
  return count_variables(args...) + 1;
}

void set_independent_variables(independent_variables& independents, int index, const dvariable& arg)
{
  independents(index) = value(arg);
}
template<typename T>
void set_independent_variables(independent_variables& independents, int index, T arg)
{
}
template<typename T, typename ...Ts>
void set_independent_variables(independent_variables& independents, int index, T arg, Ts... args)
{
  set_independent_variables(independents, index, args...);
}
template<typename ...Ts>
void set_independent_variables(independent_variables& independents, int index, const dvariable& arg, Ts... args)
{
  independents(index) = value(arg);
  set_independent_variables(independents, index + 1, args...);
}

std::tuple<dvariable const&> create_tuple(std::vector<dvariable>& variables, int index, dvariable const& arg)
{
  return std::tie(variables[index]);
}
template<typename Arg>
std::tuple<Arg> create_tuple(std::vector<dvariable>& variables, int index, Arg&& arg)
{
  return std::tie(arg);
}
template<typename Arg, typename ...Args>
std::tuple<Arg, Args...> create_tuple(std::vector<dvariable>& variables, int index, Arg&& arg, Args&&... args)
{
  std::tuple<Arg> t = std::tie(arg);
  std::tuple<Args...> t2 = create_tuple(variables, index, args...);
  return std::tuple_cat(t, t2);
}
template<typename ...Args>
std::tuple<dvariable const&, Args...> create_tuple(std::vector<dvariable>& variables, int index, dvariable const& arg, Args&&... args)
{
  std::tuple<dvariable const&> t = std::tie(variables[index]);
  std::tuple<Args...> t2 = create_tuple(variables, index + 1, args...);
  return std::tuple_cat(t, t2);
}
template<typename ...Args>
std::tuple<Args...> create_tuple(std::vector<dvariable>& variables, Args&&... args)
{
  std::tuple<Args...> t = create_tuple(variables, 0, args...);
  return std::tuple_cat(t);
}
template<class F, class ...Args>
std::future<std::pair<double, dvector>> thread_funnel(F&& func, Args&&... args)
{
  gradient_structure* gs = gradient_structure::get();
  return std::async(std::launch::async, [=]()->std::pair<double, dvector>
  {
    gradient_structure::_instance = gs;

    size_t nvar = count_variables(args...);

    double v = 0;
    dvector g(1, nvar);

    //gradient_structure::get()->GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
    {
      independent_variables scoped_independents(1, nvar);
      set_independent_variables(scoped_independents, 1, args...);

      // Set gradient_structure::NVAR
      dvar_vector scoped_variables(scoped_independents);

      std::vector<dvariable> variables;
      for (int i = 1; i <= nvar; ++i)
      {
        variables.push_back(std::move(scoped_variables(i)));
      }

      dvariable f(0);

      std::tuple<Args...> t = create_tuple(variables, args...);
      f = std::apply(func, t);

      v = value(f);

      gradcalc(nvar, g);
    }
    //gradient_structure::get()->GRAD_STACK1->deallocate_RETURN_ARRAYS();

    return std::make_pair(v, g);
  });
}
template<class ...Args>
void to_dvariable(double* dep_addr, std::pair<double, dvector>& p, Args&& ...args)
{
  gradient_structure* gs = gradient_structure::get();
  grad_stack* GRAD_STACK1 = gs->GRAD_STACK1;

  *dep_addr = p.first;
  dvector g(p.second);

  std::tuple<Args&&...> t = std::forward_as_tuple(args...);
  dvariable const& x = std::get<0>(t);
  dvariable const& y = std::get<1>(t);
  dvariable const& u = std::get<2>(t);
  dvariable const& v = std::get<3>(t);

  grad_stack_entry* entry = GRAD_STACK1->ptr;
  entry->func = NULL;
  entry->dep_addr = dep_addr;
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
}

gradient_structure* get_gradient();
void add_futures(std::future<std::pair<double, dvector>>&& f);

void wait_futures();

template<class F, class ...Args>
void funnel(F&& func, Args&&... args)
{
  gradient_structure* gs = gradient_structure::get();

  gradient_structure::_instance = get_gradient();

  std::future<std::pair<double, dvector>> future_pair =
    thread_funnel(func, args...);

  add_futures(std::move(future_pair));
  wait_futures();

  gradient_structure::_instance = gs;
}
