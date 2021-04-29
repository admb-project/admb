#include <tuple>

auto build_tuple(const dvar_vector& variables, const int index, const int arg)
{
  return std::make_tuple(std::move(arg));
}
auto build_tuple(const dvar_vector& variables, const int index, const double arg)
{
  return std::make_tuple(std::move(arg));
}
template<typename... Args>
auto build_tuple(const dvar_vector& variables, const int index, const double& arg, Args&&... args)
{
  auto t = build_tuple(variables, index + 1, std::forward<Args>(args)...);
  return std::tuple_cat(std::make_tuple(std::move(arg)), t);
}
template<typename... Args>
auto build_tuple(const dvar_vector& variables, const int index, const dvariable& variable, Args&&... args)
{
  auto t = build_tuple(variables, index + 1, std::forward<Args>(args)...);
  dvariable v = variables(index);
  return std::tuple_cat(std::make_tuple(std::move(v)), t);
}
int get_ptrs(std::vector<double_and_int*>& ptrs, const int arg)
{
  return 0;
}
int get_ptrs(std::vector<double_and_int*>& ptrs, const double arg)
{
  return 0;
}
template<typename... Args>
int get_ptrs(std::vector<double_and_int*>& ptrs, const double arg, Args&&... args)
{
  return get_ptrs(ptrs, std::forward<Args>(args)...);
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
void default_evaluationNind()
{
  int int_value = restore_int_value();
  cout << int_value << endl;
  default_evaluation4ind();
}
int int_value = 0;
template<class ...Args, size_t ...S>
std::future<std::tuple<double, dvector, std::vector<double_and_int*>>> 
//std::tuple<double, dvector, std::vector<double_and_int*>>
compute_gradients(
  const typename parameters<std::function<dvariable(Args...)>>::types& f, Args&&... args)
{
  return std::async(std::launch::async,
    [=]()->std::tuple<double, dvector, std::vector<double_and_int*>>
    {
      double result_value = 0;
      dvector g;
      std::vector<double_and_int*> ptrs;
      const int total_variables = get_ptrs(ptrs, std::forward<Args>(args)...);
      if (total_variables > 0)
      {
        const int min = 1;

        g.allocate(min, total_variables);

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
      }
      return std::make_tuple(result_value, g, ptrs);
    }
  );
}
dvariable to_dvariable(
  const std::tuple<double, dvector, std::vector<double_and_int*>>& t)
{
  double result_value = 0;
  dvector g;
  std::vector<double_and_int*> ptrs;

  std::tie(result_value, g, ptrs) = t;

  const int total_variables = ptrs.size();

  dvariable result;
  result = result_value;
/*
  {
    grad_stack_entry* entry = nullptr;

    int index = 0;
    while (index < total_variables - 1)
    {
      entry = gradient_structure::GRAD_STACK1->ptr;
      entry->func = nullptr;
      entry->dep_addr = index == 0 ? &((*result.v).x) : nullptr;
      entry->ind_addr1 = &(ptrs[index]->x);
      entry->mult1 = g(index + 1);
      entry->ind_addr2 = &(ptrs[index + 1]->x);
      entry->mult2 = g(index + 2);
      gradient_structure::GRAD_STACK1->ptr++;
      index += 2;
    }
    //save_int_value(345);
    //entry->func = default_evaluationNind;
    entry->func = default_evaluation4ind;
    if (index == total_variables - 1)
    {
      entry->dep_addr = nullptr;
      entry->ind_addr1 = &(ptrs[index]->x);
      entry->mult1 = g(index + 1);
      entry->ind_addr2 = nullptr;
    }
  }
*/
      grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
      entry->func = NULL;
      entry->dep_addr = &((*result.v).x);
      entry->ind_addr1 = &(ptrs[0]->x);
      entry->mult1 = g(1);
      entry->ind_addr2 = &(ptrs[1]->x);
      entry->mult2 = g(2);
      gradient_structure::GRAD_STACK1->ptr++;
      grad_stack_entry* entry2 = gradient_structure::GRAD_STACK1->ptr;
      entry2->func = default_evaluation4ind;
      entry2->ind_addr1 = &(ptrs[2]->x);
      entry2->mult1 = g(3);
      entry2->ind_addr2 = &(ptrs[3]->x);
      entry2->mult2 = g(4);
      gradient_structure::GRAD_STACK1->ptr++;

  //cout << g << endl;
  return result;
}
