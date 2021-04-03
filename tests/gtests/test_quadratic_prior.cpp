#include <gtest/gtest.h>
#include <df1b2fun.h>

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
