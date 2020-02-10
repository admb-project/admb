#include <gtest/gtest.h>
#include <fvar.hpp>

class test_autodif: public ::testing::Test {};

TEST_F(test_autodif, gradcalc_no_independant_variables)
{
  //Should test for initial state.
  //ASSERT_EQ(gradient_structure::NVAR, 0);

  const int nvar = 1;
  dvector g(1, nvar);

  ASSERT_ANY_THROW(
    gradcalc(nvar, g);
  );
}
/*
  gradient_structure gs(1500);

  independent_variables variables(1, nvar);
  dvar_vector x(variables);

  dvariable variable = sum(x);

  double f = value(variable);
  dvector g(1, nvar);
*/

TEST_F(test_autodif, dvar_vector_with_no_gradient_structure)
{
  const int nvar = 1;
  independent_variables variables(1, nvar);
  ASSERT_ANY_THROW(
      dvar_vector x(variables);
  );
}
TEST_F(test_autodif, reinitialize_grad_stack1_scoped)
{
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);
  {
    gradient_structure gs(1500);
    ASSERT_TRUE(gradient_structure::GRAD_STACK1 != NULL);

    const int nvar = 1;
    independent_variables variables(1, nvar);
    dvar_vector x(variables);
    ASSERT_TRUE(gradient_structure::GRAD_STACK1 != NULL);
  }
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);
}
/*
TEST_F(test_autodif, dvar_vector3)
{
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);
  gradient_structure gs(1500);
  const int nvar = 1;
  independent_variables variables(1, nvar);
  variables[1] = 10;
  dvar_vector x(variables);
  
  ASSERT_DOUBLE_EQ(value(x[1]), 10);

  dvariable f = sum(x);
  double result  = value(f);
  ASSERT_DOUBLE_EQ(result, 10);

  dvector g(1, nvar);
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 != NULL);
  ASSERT_TRUE(gradient_structure::GRAD_STACK1->ptr != NULL);
  //sgradcalc.cpp:158
  // *gradient_structure::GRAD_STACK1->ptr->dep_addr = 1;
  gradcalc(nvar, g);
}
*/
