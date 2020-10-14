#include <fvar.hpp>

dvar_vector compute_yhat(dvariable& b0, dvariable& b1, dvector& x)
{
  dvar_vector yhat(x.indexmin(), x.indexmax());
  //yhat = b0 + b1 * x;
  yhat = value(b0) + value(b1) * x;

  b0.save_prevariable_position();
  b1.save_prevariable_position();
  yhat.save_dvar_vector_position();
  x.save_dvector_value();
  x.save_dvector_position();
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    dvector_position x_pos = restore_dvector_position();
    dvector x = restore_dvector_value(x_pos);
    dvar_vector_position yhat_pos = restore_dvar_vector_position();
    prevariable_position b1_pos = restore_prevariable_position();
    prevariable_position b0_pos = restore_prevariable_position();
    dvector dfyhat = restore_dvar_vector_derivatives(yhat_pos);
    save_double_derivative(dfyhat * x, b1_pos);
    save_double_derivative(sum(dfyhat), b0_pos);
  });
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
