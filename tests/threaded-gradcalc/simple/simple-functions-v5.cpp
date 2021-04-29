#include <fvar.hpp>
#include <vector>

void get_x(dvector& x, const dvector& array)
{
  x.allocate(array.indexmin(), array.indexmax());
  x = array;
}
template<typename... Args>
void get_x(dvector& x, const dvariable& variable, Args&&... args)
{
  get_x(x, std::forward<Args>(args)...);
}

int get_ptrs(std::vector<double_and_int*>& ptrs, const dvector& array)
{
  return 0;
}
template<typename... Args>
int get_ptrs(std::vector<double_and_int*>& ptrs, const dvariable& variable, Args&&... args)
{
  ptrs.push_back(variable.v);
  return 1 + get_ptrs(ptrs, std::forward<Args>(args)...);
}

template<class ...Args>
dvar_vector compute_gradients(
  std::function<dvariable(const int i, const dvariable& b0, const dvariable& b1, dvector& x)> f, Args&&... args)
{
  dvector x;
  get_x(x, std::forward<Args>(args)...);

  std::vector<double_and_int*> ptrs;
  int max = get_ptrs(ptrs, std::forward<Args>(args)...);
  int min = max > 0 ? 1 : max + 1;

  dvector values(x.indexmin(), x.indexmax());
  dmatrix g(x.indexmin(), x.indexmax(), min, max);

  grad_stack* save = gradient_structure::GRAD_STACK1;
  grad_stack* gradstack = new grad_stack(10000, 10);
  for (int i = x.indexmin(); i <= x.indexmax(); ++i)
  {
    gradient_structure::GRAD_STACK1 = gradstack;
    gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
    {
      independent_variables independents(min, max);
      for (int j = min; j <= max; ++j)
      {
        independents(j) = ptrs[j - 1]->x;
      }

      // Set gradient_structure::NVAR
      dvar_vector variables(independents);

      dvariable result;
      result = f(i, variables(min), variables(max), x);

      values(i) = value(result);

      gradcalc(variables.indexmax(), g(i));
    }
    gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
    gradient_structure::GRAD_STACK1 = nullptr;
  }
  gradient_structure::GRAD_STACK1 = save;
  delete gradstack;
  gradstack = nullptr;

  dvar_vector results(x.indexmin(), x.indexmax());
  results = values;

  for (int i = x.indexmin(); i <= x.indexmax(); ++i)
  {
    int index = 0;
    grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
    entry->func = default_evaluation3;
    entry->dep_addr = &((*results[i].v).x);
    entry->ind_addr1 = &(ptrs[index]->x);
    ++index;
    entry->mult1 = g(i, index);
    entry->ind_addr2 = &(ptrs[index]->x);
    ++index;
    entry->mult2 = g(i, index);
    gradient_structure::GRAD_STACK1->ptr++;
  }
  return results;
}
dvar_vector compute_yhat(dvariable& b0, dvariable& b1, dvector& x)
{
  return compute_gradients([](const int i, const dvariable& b0, const dvariable& b1, dvector& x)->dvariable
  {
    dvariable result = b0 + b1 * x(i);
    return result;
  }, b0, b1, x);
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
