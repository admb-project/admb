#include <fvar.hpp>
#include <vector>
#include "compute-gradients.h"

dvar_vector compute_yhat(dvariable& b0, dvariable& b1, dvector& x)
{
  //yhat = b0 + b1 * x;

  dvar_vector yhat(x.indexmin(), x.indexmax());
  for (int i = yhat.indexmin(); i <= yhat.indexmax(); ++i)
  {
    yhat[i] = compute_gradients([](const dvariable& b0, const dvariable& b1, const double xi)->dvariable
    {
      dvariable result = b0 + b1 * xi;
      return result;
    }, b0, b1, x(i));
  }
  return yhat;
}
dvariable compute_regression(const dvector& obs, const dvar_vector& pred)
{
  //result = regression(obs, pred);

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
