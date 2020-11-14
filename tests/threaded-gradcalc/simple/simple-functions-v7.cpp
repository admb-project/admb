#include <fvar.hpp>
#include <vector>
#include <tuple>

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
  auto t = std::make_tuple(args...);

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
        dvariable b0 = variables(1);
        dvariable b1 = variables(2);
    
        dvariable f_result;
        auto t2 = std::make_tuple(std::move(b0), std::move(b1), std::move(std::get<2>(t)));
        f_result = std::apply(f, t2);
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
