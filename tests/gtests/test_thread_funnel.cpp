#include <gtest/gtest.h>
#include <fvar.hpp>
#include <future>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_thread_funnel: public ::testing::Test {};

TEST_F(test_thread_funnel, f_equal_x_times_values2)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvector values(1, 3);
  values(1) = -1.5;
  values(2) =  2.4;
  values(3) =  0.7;

  independent_variables independents(1, 1);
  independents(1) = 2.0;
  dvar_vector variables(independents);
  dvariable x = variables(1);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 1);

  //double v = value(x);

  dvar_vector f(1, 3);
  f = x * values;
  //cout << value(f) << endl;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);

  f.save_dvar_vector_position();
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    dvar_vector_position f_pos = restore_dvar_vector_position();
    dvector g(1, 3);
    g = 1;
    g.save_dvector_derivatives(f_pos);
  });

  dvariable total;
  total = 0.0;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 5);
  //cout << v << endl;

  dvector g(1, 1);
  gradcalc(1, g);
  cout << "$ " << g << endl;
  cout << "$ " << value(f) << endl;
  /*
  dvector f_values = value(f);

  dmatrix g(1, 3, 1, 1);
  g.initialize();
  gradcalc(1, g(1));
  cout << g << endl;
  ASSERT_EQ(g(1, 1), -1.5);
  ASSERT_EQ(g(2, 1), 2.4);
  ASSERT_EQ(g(3, 1), 0.7);
  */
}
TEST_F(test_thread_funnel, f_equal_x_times_values)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvector values(1, 3);
  values(1) = -1.5;
  values(2) =  2.4;
  values(3) =  0.7;

  independent_variables independents(1, 1);
  independents(1) = 2.0;
  dvar_vector variables(independents);
  dvariable x = variables(1);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 1);

  dvar_vector f(1, 3);
  f = x * values;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);

  dvariable total;
  total = sum(f);

  dvector g(1, 1);
  gradcalc(1, g);

  ASSERT_DOUBLE_EQ(g(1), sum(values));
}
TEST_F(test_thread_funnel, f_equal_x_times_values_weird)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvector values(1, 3);
  values(1) = -1.5;
  values(2) =  2.4;
  values(3) =  0.7;

  independent_variables independents(1, 1);
  independents(1) = 2.0;
  dvar_vector variables(independents);
  dvariable x = variables(1);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 1);

  dvar_vector f(1, 3);
  f = x * values;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);

  dvariable total;
  total = f(2) + f(3);

  dvector g(1, 1);
  gradcalc(1, g);

  ASSERT_DOUBLE_EQ(g(1), values(2) + values(3));
}
dvar_vector adjoint_yhat(dvariable& b0, dvariable& b1, dvector& x);

dvar_vector compute_yhat_v2(dvariable& b0, dvariable& b1, dvector& x)
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
dvariable compute_v3(
  std::function<dvariable(const dvector& y, const dvar_vector& yhat)> f,
  const dvector& y, const dvar_vector& yhat)
{
  double v = 0;
  dvector g(yhat.indexmin(), yhat.indexmax());

  grad_stack* save = gradient_structure::GRAD_STACK1;
  gradient_structure::GRAD_STACK1 = new grad_stack(10000, 10);;
  gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
  {
    independent_variables independents(yhat.indexmin(), yhat.indexmax());
    independents = value(yhat);
    dvar_vector variables(independents);
    dvariable ret = regression(y, variables);
    v = value(ret);
    gradcalc(g.indexmax(), g);
  };
  gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
  delete gradient_structure::GRAD_STACK1;
  gradient_structure::GRAD_STACK1 = nullptr;

  gradient_structure::GRAD_STACK1 = save;
  save = nullptr;

  dvariable result = v;
  yhat.save_dvar_vector_position();
  g.save_dvector_value();
  g.save_dvector_position();
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    dvector_position g_pos = restore_dvector_position();
    dvector g = restore_dvector_value(g_pos);
    dvar_vector_position yhat_pos = restore_dvar_vector_position();
    g.save_dvector_derivatives(yhat_pos);
  });

  return result;
}
TEST_F(test_thread_funnel, compute_v3)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable b0(variables(1));
  dvariable b1(variables(2));

  dvector x(1, 10);
  x(1) = -1;
  x(2) =  0;
  x(3) =  1;
  x(4) =  2;
  x(5) =  3;
  x(6) =  4;
  x(7) =  5;
  x(8) =  6;
  x(9) =  7;
  x(10) = 8;

  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;

  dvar_vector yhat(1, 10);
  yhat = compute_yhat_v2(b0, b1, x);

  dvariable f;
  f = compute_v3([](const dvector& y, const dvar_vector& yhat)->dvariable
  {
    return regression(y, yhat);
  }, y, yhat);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 16.251872459637859);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.4496124031007755);
  ASSERT_DOUBLE_EQ(g(2), 8.5620155038759709);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvariable compute_v2(
  std::function<dvariable(const dvector& y, const dvar_vector& yhat)> f,
  const dvector& y, const dvar_vector& yhat)
{
  double v = 0;
  dvector g(yhat.indexmin(), yhat.indexmax());

  grad_stack* save = gradient_structure::GRAD_STACK1;
  gradient_structure::GRAD_STACK1 = new grad_stack(10000, 10);;
  gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
  {
    independent_variables independents(yhat.indexmin(), yhat.indexmax());
    independents = value(yhat);
    dvar_vector variables(independents);
    dvariable ret = regression(y, variables);
    v = value(ret);
    gradcalc(g.indexmax(), g);
  };
  gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
  delete gradient_structure::GRAD_STACK1;
  gradient_structure::GRAD_STACK1 = nullptr;

  gradient_structure::GRAD_STACK1 = save;
  save = nullptr;

  dvariable result = v;
  yhat.save_dvar_vector_position();
  g.save_dvector_value();
  g.save_dvector_position();
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    dvector_position g_pos = restore_dvector_position();
    dvector g = restore_dvector_value(g_pos);
    dvar_vector_position yhat_pos = restore_dvar_vector_position();
    g.save_dvector_derivatives(yhat_pos);
  });

  return result;
}
TEST_F(test_thread_funnel, compute_v2)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable b0(variables(1));
  dvariable b1(variables(2));

  dvector x(1, 10);
  x(1) = -1;
  x(2) =  0;
  x(3) =  1;
  x(4) =  2;
  x(5) =  3;
  x(6) =  4;
  x(7) =  5;
  x(8) =  6;
  x(9) =  7;
  x(10) = 8;

  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;

  dvar_vector yhat(1, 10);
  yhat = adjoint_yhat(b0, b1, x);

  dvariable f;
  f = compute_v2([](const dvector& y, const dvar_vector& yhat)->dvariable
  {
    return regression(y, yhat);
  }, y, yhat);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 16.251872459637859);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.4496124031007755);
  ASSERT_DOUBLE_EQ(g(2), 8.5620155038759709);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvariable compute(
  std::function<dvariable(const dvector& y, const dvar_vector& yhat)> f,
  const dvector& y, const dvar_vector& yhat)
{
  return f(y, yhat);
}
TEST_F(test_thread_funnel, compute)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable b0(variables(1));
  dvariable b1(variables(2));

  dvector x(1, 10);
  x(1) = -1;
  x(2) =  0;
  x(3) =  1;
  x(4) =  2;
  x(5) =  3;
  x(6) =  4;
  x(7) =  5;
  x(8) =  6;
  x(9) =  7;
  x(10) = 8;

  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;

  dvar_vector yhat(1, 10);
  yhat = adjoint_yhat(b0, b1, x);

  dvariable f;
  f = compute([](const dvector& y, const dvar_vector& yhat)->dvariable
  {
    return regression(y, yhat);
  }, y, yhat);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 16.251872459637859);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.4496124031007755);
  ASSERT_DOUBLE_EQ(g(2), 8.5620155038759709);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvar_vector adjoint_yhat(dvariable& b0, dvariable& b1, dvector& x)
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
TEST_F(test_thread_funnel, adjoint_yhat)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable b0(variables(1));
  dvariable b1(variables(2));

  dvector x(1, 10);
  x(1) = -1;
  x(2) =  0;
  x(3) =  1;
  x(4) =  2;
  x(5) =  3;
  x(6) =  4;
  x(7) =  5;
  x(8) =  6;
  x(9) =  7;
  x(10) = 8;

  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;

  dvar_vector yhat(1, 10);
  yhat = adjoint_yhat(b0, b1, x);

  dvariable f;
  f = regression(y, yhat);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 16.251872459637859);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.4496124031007755);
  ASSERT_DOUBLE_EQ(g(2), 8.5620155038759709);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvariable gradcalc_regression(const dvector& obs, const dvar_vector& pred)
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
TEST_F(test_thread_funnel, gradcalc_yhat)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable b0(variables(1));
  dvariable b1(variables(2));

  dvector x(1, 10);
  x(1) = -1;
  x(2) =  0;
  x(3) =  1;
  x(4) =  2;
  x(5) =  3;
  x(6) =  4;
  x(7) =  5;
  x(8) =  6;
  x(9) =  7;
  x(10) = 8;

  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;

  dvar_vector yhat(1, 10);
  yhat = adjoint_yhat(b0, b1, x);

  dvariable f;
  f = gradcalc_regression(y, yhat);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 16.251872459637859);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.4496124031007755);
  ASSERT_DOUBLE_EQ(g(2), 8.5620155038759709);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvar_vector manual_yhat(dvariable& b0, dvariable& b1, dvector& x)
{
  dvar_vector yhat(1, 10);
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    cout << __FILE__ << ':' << __LINE__ << endl;
  });
  //yhat = b0 + b1 * x;
  yhat = value(b0) + value(b1) * x;

  b0.save_prevariable_position();
  b1.save_prevariable_position();
  gradient_structure::GRAD_STACK1->set_gradient_stack(
  []()
  {
    cout << __FILE__ << ':' << __LINE__ << endl;
    prevariable_position b1_pos = restore_prevariable_position();
    prevariable_position b0_pos = restore_prevariable_position();
    save_double_derivative(8.5620155038759709, b1_pos);
    save_double_derivative(1.4496124031007755, b0_pos);
  });
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    cout << __FILE__ << ':' << __LINE__ << endl;
  });
  return yhat;
}
TEST_F(test_thread_funnel, manual_yhat)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable b0(variables(1));
  dvariable b1(variables(2));

  dvector x(1, 10);
  x(1) = -1;
  x(2) =  0;
  x(3) =  1;
  x(4) =  2;
  x(5) =  3;
  x(6) =  4;
  x(7) =  5;
  x(8) =  6;
  x(9) =  7;
  x(10) = 8;

  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;

  dvar_vector yhat(1, 10);
  yhat = manual_yhat(b0, b1, x);

  dvariable f;
  f = regression(y, yhat);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 16.251872459637859);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.4496124031007755);
  ASSERT_DOUBLE_EQ(g(2), 8.5620155038759709);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvar_vector compute_yhat(dvariable& b0, dvariable& b1, dvector& x)
{
  dvar_vector yhat(1, 10);
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    cout << __FILE__ << ':' << __LINE__ << endl;
  });
  //yhat = b0 + b1 * x;
  yhat = value(b0) + value(b1) * x;

  b0.save_prevariable_position();
  b1.save_prevariable_position();
  yhat.save_dvar_vector_position();
  x.save_dvector_value();
  x.save_dvector_position();
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    cout << __FILE__ << ':' << __LINE__ << endl;
    dvector_position x_pos = restore_dvector_position();
    dvector x = restore_dvector_value(x_pos);
    dvar_vector_position yhat_pos = restore_dvar_vector_position();
    prevariable_position b1_pos = restore_prevariable_position();
    prevariable_position b0_pos = restore_prevariable_position();
    dvector dfyhat = restore_dvar_vector_derivatives(yhat_pos);
    double result = 0;
    for (int i = x.indexmax(); i >= x.indexmin(); --i)
    {
      result += dfyhat(i) * x(i);
    }
    double dfb1 = restore_prevariable_derivative(b1_pos);
    double dfb0 = restore_prevariable_derivative(b0_pos);
    save_double_derivative(result, b1_pos);
    save_double_derivative(sum(dfyhat), b0_pos);
  });
  gradient_structure::GRAD_STACK1->set_gradient_stack([]()
  {
    cout << __FILE__ << ':' << __LINE__ << endl;
  });
  return yhat;
}
TEST_F(test_thread_funnel, compute_yhat)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable b0(variables(1));
  dvariable b1(variables(2));

  dvector x(1, 10);
  x(1) = -1;
  x(2) =  0;
  x(3) =  1;
  x(4) =  2;
  x(5) =  3;
  x(6) =  4;
  x(7) =  5;
  x(8) =  6;
  x(9) =  7;
  x(10) = 8;
  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;
  dvar_vector yhat(1, 10);

  yhat = compute_yhat(b0, b1, x);

  dvariable f;
  f = regression(y, yhat);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 16.251872459637859);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.4496124031007755);
  ASSERT_DOUBLE_EQ(g(2), 8.5620155038759709);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
TEST_F(test_thread_funnel, simple)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable b0(variables(1));
  dvariable b1(variables(2));

  dvector x(1, 10);
  x(1) = -1;
  x(2) =  0;
  x(3) =  1;
  x(4) =  2;
  x(5) =  3;
  x(6) =  4;
  x(7) =  5;
  x(8) =  6;
  x(9) =  7;
  x(10) = 8;
  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;
  dvar_vector yhat(1, 10);

  yhat = b0 + b1 * x;

  dvariable f;
  f = regression(y, yhat);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 16.251872459637859);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.4496124031007755);
  ASSERT_DOUBLE_EQ(g(2), 8.5620155038759709);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
TEST_F(test_thread_funnel, gradcalc)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable x(variables(1));
  dvariable y(variables(2));

  dvar_vector vec(1, 2);
  vec(1) = x;
  vec(2) = y;

  dvariable f;

  f = sum(vec);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 7.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 1.0);
  ASSERT_DOUBLE_EQ(g(2), 1.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
TEST_F(test_thread_funnel, gradcalc_novalue)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

/*
  dvar_vector vec(1, 2);
  vec(2) = y;
  vec(1) = x;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);
*/

  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 0.0);
  ASSERT_DOUBLE_EQ(g(2), 0.0);
  ASSERT_DOUBLE_EQ(value(variables(1)), 4.0);
  ASSERT_DOUBLE_EQ(value(variables(2)), 3.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  dvariable x(variables(1));
  dvariable y(variables(2));

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(1), 0.0);
  ASSERT_DOUBLE_EQ(g(2), 1.0);
  ASSERT_DOUBLE_EQ(value(variables(1)), 0.0);
  ASSERT_DOUBLE_EQ(value(variables(2)), 1.0);
}
TEST_F(test_thread_funnel, grad_stack1)
{
  auto start = std::chrono::high_resolution_clock::now();

  grad_stack* grad_stack1 = new grad_stack(10000, 10);

  delete grad_stack1;
  grad_stack1 = nullptr;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time (resource allocation): " << elapsed.count() <<  endl;
}
TEST_F(test_thread_funnel, grad_stack4)
{
  auto start = std::chrono::high_resolution_clock::now();

  grad_stack* grad_stack1 = new grad_stack(10000, 10);
  grad_stack* grad_stack2 = new grad_stack(10000, 10);
  grad_stack* grad_stack3 = new grad_stack(10000, 10);
  grad_stack* grad_stack4 = new grad_stack(10000, 10);

  delete grad_stack1;
  grad_stack1 = nullptr;
  delete grad_stack2;
  grad_stack2 = nullptr;
  delete grad_stack3;
  grad_stack3 = nullptr;
  delete grad_stack4;
  grad_stack4 = nullptr;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time (resource allocation): " << elapsed.count() <<  endl;
}
/*
TEST_F(test_thread_funnel, empty_grad_stack_entrys)
{
  grad_stack* grad_stack1 = new grad_stack(0, 10);

  ASSERT_TRUE(grad_stack1->true_ptr_first == nullptr);
  ASSERT_TRUE(grad_stack1->ptr_first == nullptr);
  ASSERT_TRUE(grad_stack1->ptr_last == nullptr);
  ASSERT_TRUE(grad_stack1->ptr == nullptr);
  ASSERT_TRUE(grad_stack1->length == 0);
  ASSERT_TRUE(grad_stack1->true_length == 0);

  delete grad_stack1;
  grad_stack1 = nullptr;
}
TEST_F(test_thread_funnel, copy)
{
  auto start = std::chrono::high_resolution_clock::now();

  grad_stack* grad_stack1 = new grad_stack(10000, 10);

  {
    cout << grad_stack1->ptr_first << ' ' << grad_stack1->ptr_last << endl;
    cout << grad_stack1->total() << endl;

    grad_stack copy(*grad_stack1);
  }

  delete grad_stack1;
  grad_stack1 = nullptr;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time (resource allocation): " << elapsed.count() <<  endl;
}
*/
