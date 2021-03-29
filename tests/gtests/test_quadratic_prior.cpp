#include <gtest/gtest.h>
#include <df1b2fun.h>

class test_quadratic_prior: public ::testing::Test {};

class my_quadratic_prior: public quadratic_prior
{
public:
  void set_old_style_flag() {}
  void get_cM() {}
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
