#include <fvar.hpp>

dvar_vector compute_yhat(dvariable& b0, dvariable& b1, dvector& x)
{
  dvector values(x.indexmin(), x.indexmax());
  dmatrix g(x.indexmin(), x.indexmax(), 1, 2);

  grad_stack* save = gradient_structure::GRAD_STACK1;
  grad_stack* gradstack = new grad_stack(10000, 10);
  for (int i = x.indexmin(); i <= x.indexmax(); ++i)
  {
    gradient_structure::GRAD_STACK1 = gradstack;
    gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
    {
      independent_variables independents(1, 2);
      independents(1) = value(b0);
      independents(2) = value(b1);

      // Set gradient_structure::NVAR
      dvar_vector variables(independents);

      dvariable result;
      result = variables(1) + variables(2) * x(i);

      values(i) = value(result);

      gradcalc(variables.indexmax(), g(i));
    }
    gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
    gradient_structure::GRAD_STACK1 = nullptr;
  }
  gradient_structure::GRAD_STACK1 = save;
  delete gradstack;
  gradstack = nullptr;

  dvar_vector yhat(x.indexmin(), x.indexmax());
  yhat = values;

  for (int i = x.indexmin(); i <= x.indexmax(); ++i)
  {
    grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
    entry->func = default_evaluation3;
    entry->dep_addr = &((*yhat[i].v).x);
    entry->ind_addr1 = &((*b0.v).x);
    entry->mult1 = g(i, 1);
    entry->ind_addr2 = &((*b1.v).x);
    entry->mult2 = g(i, 2);
    gradient_structure::GRAD_STACK1->ptr++;
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
