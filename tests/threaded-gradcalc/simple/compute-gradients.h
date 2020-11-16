#include <tuple>

auto build_tuple(const dvar_vector& variables, const int index, const double arg)
{
  return std::make_tuple(std::move(arg));
}
template<typename... Args>
auto build_tuple(const dvar_vector& variables, const int index, const dvariable& variable, Args&&... args)
{
  auto t = build_tuple(variables, index + 1, std::forward<Args>(args)...);
  dvariable v = variables(index);
  return std::tuple_cat(std::make_tuple(std::move(v)), t);
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
template<class ...Args, size_t ...S>
dvariable compute_gradients(
  const typename parameters<std::function<dvariable(Args...)>>::types& f, Args&&... args)
{
  dvariable result;

  std::vector<double_and_int*> ptrs;
  const int total_variables = get_ptrs(ptrs, std::forward<Args>(args)...);
  if (total_variables > 0)
  {
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
        //auto t2 = std::make_tuple(std::move(b0), std::move(b1), std::get<2>(t));
        auto t = build_tuple(variables, 1, std::forward<Args>(args)...);
        f_result = std::apply(f, t);
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
