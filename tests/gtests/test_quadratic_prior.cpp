#include <gtest/gtest.h>
#include <df1b2fun.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_quadratic_prior: public ::testing::Test {};

class my_quadratic_prior: public quadratic_prior
{
public:
  void set_old_style_flag() {}
  void get_cM(void) {}

  void operator=(const dmatrix& M)
    { quadratic_prior::operator=(M); }
};

TEST_F(test_quadratic_prior, default_constructor)
{
  gradient_structure gs;

  my_quadratic_prior data;

  ASSERT_EQ(data.get_myindex(), 0);

  dvar_matrix M(1, 2, 1, 2);
  M(1, 1) = 1;
  M(1, 2) = 2;
  M(2, 1) = 3;
  M(2, 2) = 4;

  dvar_vector u(1, 2);
  u(1) = 1;
  u(2) = 2;

  data.allocate(M, u, "unused message");

  dvar_matrix pMinv = data.get_Hessian();
  ASSERT_DOUBLE_EQ(value(pMinv(1, 1)), -2.0);
  ASSERT_DOUBLE_EQ(value(pMinv(1, 2)), 1.0);
  ASSERT_DOUBLE_EQ(value(pMinv(2, 1)), 1.5);
  ASSERT_DOUBLE_EQ(value(pMinv(2, 2)), -0.5);

  dvar_vector gradients = data.get_gradient();
  ASSERT_EQ(gradients.indexmin(), 1);
  ASSERT_EQ(gradients.indexmax(), 2);
  //ASSERT_DOUBLE_EQ(value(gradients(1)), 0.0);
  ASSERT_DOUBLE_EQ(value(gradients(2)), 0.5);
}
TEST_F(test_quadratic_prior, assignment_dmatrix)
{
  ASSERT_EQ(laplace_approximation_calculator::where_are_we_flag, 0);
  laplace_approximation_calculator::where_are_we_flag = 2;
  gradient_structure gs;

  my_quadratic_prior data;

  data.old_style_flag = 2;
  ASSERT_EQ(data.old_style_flag, 2);

  ASSERT_EQ(data.get_myindex(), 1);

  dvar_matrix M(1, 2, 1, 2);
  M(1, 1) = 1;
  M(1, 2) = 2;
  M(2, 1) = 3;
  M(2, 2) = 4;

  dvar_vector u(1, 2);
  u(1) = 1;
  u(2) = 2;

  data.allocate(M, u, "unused message");

  dmatrix _M(1, 2, 1, 2);
  _M(1, 1) = -1;
  _M(1, 2) = -2;
  _M(2, 1) = -3;
  _M(2, 2) = -4;

  objective_function_value::pobjfun = new objective_function_value();
  data.operator=(_M);
  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;

  dvar_matrix pMinv = data.get_Hessian();
  ASSERT_DOUBLE_EQ(value(pMinv(1, 1)), -1);
  ASSERT_DOUBLE_EQ(value(pMinv(1, 2)), -2);
  ASSERT_DOUBLE_EQ(value(pMinv(2, 1)), -3);
  ASSERT_DOUBLE_EQ(value(pMinv(2, 2)), -4);

  dvar_vector gradients = data.get_gradient();
  ASSERT_EQ(gradients.indexmin(), 1);
  ASSERT_EQ(gradients.indexmax(), 2);
  ASSERT_DOUBLE_EQ(value(gradients(1)), -5);
  ASSERT_DOUBLE_EQ(value(gradients(2)), -11);

  laplace_approximation_calculator::where_are_we_flag = 0;
  ASSERT_EQ(laplace_approximation_calculator::where_are_we_flag, 0);
}
TEST_F(test_quadratic_prior, allocate_null)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  my_quadratic_prior data;

  dvar_vector empty;
  ASSERT_THROW(data.allocate(empty, "empty"), int);
}
class quadratic_re_penalty2: public quadratic_re_penalty
{
public:
  quadratic_re_penalty2(): quadratic_re_penalty() { }
  void get_cM(void) {}
  void operator=(const dmatrix& M)
  {
    quadratic_re_penalty::operator=(M);
  }
};
TEST_F(test_quadratic_prior, quadratic_re_penalty)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  quadratic_re_penalty2 data;

  ASSERT_EQ(data.old_style_flag, 2);

  dmatrix m(1, 1, 1, 1);
  m.initialize();
  m = 5;

  objective_function_value::pobjfun = new objective_function_value();

  value(*objective_function_value::pobjfun) = 0;
  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0);

  dvar_vector v(1, 1);
  v.initialize();
  v = 1;
  data.allocate(v);
  data = m;

  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 5);

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;
}
TEST_F(test_quadratic_prior, quadratic_re_penalty_not2)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  quadratic_re_penalty2 data;

  ASSERT_EQ(data.old_style_flag, 2);

  dmatrix m(1, 1, 1, 1);
  m.initialize();
  m = 5;

  objective_function_value::pobjfun = new objective_function_value();

  value(*objective_function_value::pobjfun) = 0;
  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0);

  dvar_vector v(1, 1);
  v.initialize();
  v = 1;
  data.allocate(v);

  data.old_style_flag = 0;
  ASSERT_THROW({ data = m; }, int);
  data.old_style_flag = 1;
  ASSERT_THROW({ data = m; }, int);
  data.old_style_flag = 3;
  ASSERT_THROW({ data = m; }, int);

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;
}
class constant_quadratic_re_penalty2: public constant_quadratic_re_penalty
{
public:
  constant_quadratic_re_penalty2(): constant_quadratic_re_penalty() { }
  void get_cM(void) {}
};
TEST_F(test_quadratic_prior, constant_quadratic_re_penalty)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  constant_quadratic_re_penalty2 data;

  ASSERT_EQ(data.old_style_flag, 2);
}
class normal_quadratic_prior2: public normal_quadratic_prior
{
public:
  normal_quadratic_prior2(): normal_quadratic_prior() { }
  void get_cM(void) {}
  void operator=(const dvar_matrix& M)
  {
    normal_quadratic_prior::operator=(M);
  }
};
TEST_F(test_quadratic_prior, normal_quadratic_prior)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  normal_quadratic_prior2 data;

  ASSERT_EQ(data.old_style_flag, 0);

  dvar_matrix m(1, 1, 1, 1);
  m.initialize();
  m = 5;

  objective_function_value::pobjfun = new objective_function_value();

  value(*objective_function_value::pobjfun) = 0;
  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0);

  dvar_vector v(1, 1);
  v.initialize();
  v = 1;
  data.allocate(v);
  data = m;

  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0.90471895621705012);

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;
}
TEST_F(test_quadratic_prior, normal_quadratic_prior_1)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  normal_quadratic_prior2 data;

  ASSERT_EQ(data.old_style_flag, 0);

  dvar_matrix m(1, 1, 1, 1);
  m.initialize();
  m = 5;

  objective_function_value::pobjfun = new objective_function_value();

  value(*objective_function_value::pobjfun) = 0;
  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0);

  dvar_vector v(1, 1);
  v.initialize();
  v = 1;
  data.allocate(v);
  data.old_style_flag = 1;
  data = m;

  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0.2);

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;
}
TEST_F(test_quadratic_prior, normal_quadratic_prior_2)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  normal_quadratic_prior2 data;

  ASSERT_EQ(data.old_style_flag, 0);

  dvar_matrix m(1, 1, 1, 1);
  m.initialize();
  m = 5;

  objective_function_value::pobjfun = new objective_function_value();

  value(*objective_function_value::pobjfun) = 0;
  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0);

  dvar_vector v(1, 1);
  v.initialize();
  v = 1;
  data.allocate(v);
  data.old_style_flag = 2;
  data = m;

  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 5);

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;
}
TEST_F(test_quadratic_prior, normal_quadratic_prior_3)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  normal_quadratic_prior2 data;

  ASSERT_EQ(data.old_style_flag, 0);

  dvar_matrix m(1, 1, 1, 1);
  m.initialize();
  m = 5;

  objective_function_value::pobjfun = new objective_function_value();

  value(*objective_function_value::pobjfun) = 0;
  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0);

  dvar_vector v(1, 1);
  v.initialize();
  v = 1;
  data.allocate(v);
  data.old_style_flag = 3;
  ASSERT_THROW({ data = m; }, int);

  ASSERT_DOUBLE_EQ(value(*objective_function_value::pobjfun), 0);

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;
}
