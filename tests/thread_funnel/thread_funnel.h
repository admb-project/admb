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

      dvariable f(0);

      dvariable _tau = scoped_variables(1);
      dvariable _nu = scoped_variables(2);
      dvariable _sigma = scoped_variables(3);
      dvariable _beta = scoped_variables(4);

      std::tuple<Args...> t = std::make_tuple(args...);
      double ai = std::get<4>(t);
      int nsteps = std::get<5>(t);
      std::tuple<Args&&...> t2 = std::forward_as_tuple(_tau, _nu, _sigma, _beta, ai, nsteps);
      f = std::apply(func, t2);

      v = value(f);

      gradcalc(nvar, g);
    }
    //gradient_structure::get()->GRAD_STACK1->deallocate_RETURN_ARRAYS();

    return std::make_pair(v, g);
  });
}
