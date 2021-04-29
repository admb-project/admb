#include <fvar.hpp>
#include <vector>
#include <tuple>

double get_xi(const double xi)
{
  return xi;
}
template<typename... Args>
double get_xi(const dvariable& variable, Args&&... args)
{
  return get_xi(std::forward<Args>(args)...);
}
int get_ptrs(std::vector<double_and_int*>& ptrs, const double arg)
{
  return 0;
}
template<typename... Args>
int get_ptrs(std::vector<double_and_int*>& ptrs, const dvariable& variable, Args&&... args)
{
  ptrs.push_back(variable.v);
  return 1 + get_ptrs(ptrs, std::forward<Args>(args)...);
}
template <typename T>
struct parameters
{
  typedef T types;
};
template<std::size_t I, class ...Args>
decltype(auto) nth(Args&&... args)
{
  return std::get<I>(std::forward_as_tuple(std::forward<Args>(args)...));
}
/*
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '),...);
    std::cout << '\n';
}
template<typename Tuple, std::size_t... I>
auto copy_tuple_impl(const Tuple& other, std::index_sequence<I...>)
{
    return std::make_tuple(other[I]...);
}
template<typename ...Args, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto copy_tuple(const std::tuple<Args...>& t)
{
    return copy_tuple_impl(t, Indices{});
}
*/
/*
template<class T> T deep_copy(const T& t);
template<class T> T* deep_copy(T* tp);
template<class... Ts> std::tuple<Ts...> deep_copy(const std::tuple<Ts...>&);

template<class T>
T deep_copy(const T& t) { return t; }

template<class T>
T* deep_copy(T* tp) { return new T(deep_copy(*tp)); }

template<class... Ts, size_t... Is>
std::tuple<Ts...> deep_copy_impl(const std::tuple<Ts...>& t, std::index_sequence<Is...>) {
    //return std::tuple<Ts...>{std::get<Is>(t)...};
    return std::make_tuple({deep_copy(std::get<Is>(t)),...});
}

template<class... Ts>
std::tuple<Ts...> deep_copy(const std::tuple<Ts...>& t) {
    return deep_copy_impl(t, std::index_sequence_for<Ts...>());
}
*/
template<class ...Args, size_t ...S>
dvariable compute_gradients(
  const typename parameters<std::function<dvariable(Args...)>>::types& f, Args&&... args)
{
  /*
  cout << "b0: " << nth<0>(std::forward<Args>(args)...).v << endl;
  cout << "b1: " << nth<1>(std::forward<Args>(args)...).v << endl;
  cout << "xi: " << nth<2>(std::forward<Args>(args)...) << endl;

  auto args_tuple = std::forward_as_tuple(args...);
  cout << "*b0: " << std::get<0>(args_tuple).v << endl;
  cout << "*b1: " << std::get<1>(args_tuple).v << endl;
  cout << "*xi: " << std::get<2>(args_tuple) << endl;

  std::tuple<std::remove_reference(Args...)> copy{};
  //auto copy = deep_copy(args_tuple);
  cout << "**b0: " << std::get<0>(copy).v << endl;
  cout << "**b1: " << std::get<1>(copy).v << endl;
  cout << "**xi: " << std::get<2>(copy) << endl;
  */

  dvariable result;

  std::vector<double_and_int*> ptrs;
  const int total_variables = get_ptrs(ptrs, std::forward<Args>(args)...);
  if (total_variables > 0)
  {
    //const double xi = get_xi(std::forward<Args>(args)...);
    const int min = 1;

    double result_value = 0;
    dvector g(min, total_variables);

    grad_stack* save = gradient_structure::GRAD_STACK1;
    grad_stack* gradstack = new grad_stack(10000, 10);
    {
      gradient_structure::GRAD_STACK1 = gradstack;
      gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
      {
        independent_variables independents(min, total_variables);
        for (int j = min; j <= total_variables; ++j)
        {
          independents(j) = ptrs[j - 1]->x;
        }

        // Set gradient_structure::NVAR
        dvar_vector variables(independents);
    
        dvariable f_result;
        auto t = std::make_tuple(args...);
        f_result = std::apply(f, t);

        //print_sequence(std::make_integer_sequence<size_t, 3>{});

/*
        std::tuple<Args...> copy = std::make_tuple(std::forward<Args>(args)...);
  cout << "b0: " << std::get<0>(copy).v << endl;
  cout << "b1: " << std::get<1>(copy).v << endl;
  cout << "xi: " << std::get<2>(copy) << endl;
*/
        //f_result = f(std::forward<Args>(args)...);
        //f_result = f(std::forward<dvariable>(copy)...);

        result_value = value(f_result);

        gradcalc(total_variables, g);
      }
      gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
      gradient_structure::GRAD_STACK1 = nullptr;
    }
    gradient_structure::GRAD_STACK1 = save;
    delete gradstack;
    gradstack = nullptr;

    result = result_value;
    {
      int index = 0;
      grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
      entry->dep_addr = &((*result.v).x);
      entry->ind_addr1 = &(ptrs[index]->x);
      ++index;
      entry->mult1 = g(index);
      if (total_variables > 1)
      {
        entry->ind_addr2 = &(ptrs[index]->x);
        ++index;
        entry->mult2 = g(index);
        entry->func = default_evaluation3;
      }
      else
      {
        entry->ind_addr2 = nullptr;
        entry->mult2 = 0.0;
        entry->func = default_evaluation1;
      }
      gradient_structure::GRAD_STACK1->ptr++;
    }
  }
  return result;
}
dvar_vector compute_yhat(dvariable& b0, dvariable& b1, dvector& x)
{
  dvar_vector yhat(x.indexmin(), x.indexmax());
  for (int i = yhat.indexmin(); i <= yhat.indexmax(); ++i)
  {
    cout << value(b0) << ' ' << value(b1) << ' ' << x(i) << endl;
    yhat[i] = compute_gradients([](const dvariable& b0, const dvariable& b1, const double xi)->dvariable
    {
      dvariable result = b0 + b1 * xi;
      return result;
    }, b0, b1, x(i));
    /*
    yhat[i] = compute_gradients([](const dvariable& b1, const double xi)->dvariable
    {
      dvariable result = b1 * xi;
      return result;
    }, b1, x(i));
    */
  }
  return yhat;
}
dvariable compute_regression(const dvector& obs, const dvar_vector& pred)
{
  //dvariable result = regression(obs, pred);

  double v = 0;
  dvector g(pred.indexmin(), pred.indexmax());

  grad_stack* save = gradient_structure::GRAD_STACK1;
  gradient_structure::GRAD_STACK1 = new grad_stack(10000, 10);;
  gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
  {
    independent_variables independents(pred.indexmin(), pred.indexmax());
    independents = value(pred);
    dvar_vector variables(independents);
    dvariable ret = regression(obs, variables);
    v = value(ret);
    gradcalc(g.indexmax(), g);
  };
  gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
  delete gradient_structure::GRAD_STACK1;
  gradient_structure::GRAD_STACK1 = nullptr;

  gradient_structure::GRAD_STACK1 = save;
  save = nullptr;

  dvariable result = v;
  pred.save_dvar_vector_position();
  g.save_dvector_value();
  g.save_dvector_position();
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    dvector_position g_pos = restore_dvector_position();
    dvector g = restore_dvector_value(g_pos);
    dvar_vector_position pred_pos = restore_dvar_vector_position();
    g.save_dvector_derivatives(pred_pos);
  });

  return result;
}
