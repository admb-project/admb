#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dependent_variables_information: public ::testing::Test {};

TEST_F(test_dependent_variables_information, sizeconstructor)
{
  dependent_variables_information depvars(1);
  ASSERT_EQ(depvars.max_num_dependent_variables, 1);
  ASSERT_EQ(depvars.depvar_count, 0);
  ASSERT_EQ(depvars.grad_buffer_position.indexmin(), 1);
  ASSERT_EQ(depvars.grad_buffer_position.indexmax(), 1);
  ASSERT_TRUE(depvars.grad_buffer_position(1) == NULL);
  ASSERT_EQ(depvars.cmpdif_buffer_position.indexmin(), 1);
  ASSERT_EQ(depvars.cmpdif_buffer_position.indexmax(), 1);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_buffer_position(1), 0);
  ASSERT_EQ(depvars.grad_file_position.indexmin(), 1);
  ASSERT_EQ(depvars.grad_file_position.indexmax(), 1);
  ASSERT_DOUBLE_EQ(depvars.grad_file_position(1), 0);
  ASSERT_EQ(depvars.cmpdif_file_position.indexmin(), 1);
  ASSERT_EQ(depvars.cmpdif_file_position.indexmax(), 1);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_position(1), 0);
  ASSERT_EQ(depvars.grad_file_count.indexmin(), 1);
  ASSERT_EQ(depvars.grad_file_count.indexmax(), 1);
  ASSERT_DOUBLE_EQ(depvars.grad_file_count(1), 0);
  ASSERT_EQ(depvars.cmpdif_file_count.indexmin(), 1);
  ASSERT_EQ(depvars.cmpdif_file_count.indexmax(), 1);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_count(1), 0);
}
TEST_F(test_dependent_variables_information, size5constructor)
{
  dependent_variables_information depvars(5);
  ASSERT_EQ(depvars.max_num_dependent_variables, 5);
  ASSERT_EQ(depvars.depvar_count, 0);
  ASSERT_EQ(depvars.grad_buffer_position.indexmin(), 1);
  ASSERT_EQ(depvars.grad_buffer_position.indexmax(), 5);
  ASSERT_TRUE(depvars.grad_buffer_position(1) == NULL);
  ASSERT_TRUE(depvars.grad_buffer_position(2) == NULL);
  ASSERT_TRUE(depvars.grad_buffer_position(3) == NULL);
  ASSERT_TRUE(depvars.grad_buffer_position(4) == NULL);
  ASSERT_TRUE(depvars.grad_buffer_position(5) == NULL);
  ASSERT_EQ(depvars.cmpdif_buffer_position.indexmin(), 1);
  ASSERT_EQ(depvars.cmpdif_buffer_position.indexmax(), 5);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_buffer_position(1), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_buffer_position(2), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_buffer_position(3), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_buffer_position(4), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_buffer_position(5), 0);
  ASSERT_EQ(depvars.grad_file_position.indexmin(), 1);
  ASSERT_EQ(depvars.grad_file_position.indexmax(), 5);
  ASSERT_DOUBLE_EQ(depvars.grad_file_position(1), 0);
  ASSERT_DOUBLE_EQ(depvars.grad_file_position(2), 0);
  ASSERT_DOUBLE_EQ(depvars.grad_file_position(3), 0);
  ASSERT_DOUBLE_EQ(depvars.grad_file_position(4), 0);
  ASSERT_DOUBLE_EQ(depvars.grad_file_position(5), 0);
  ASSERT_EQ(depvars.cmpdif_file_position.indexmin(), 1);
  ASSERT_EQ(depvars.cmpdif_file_position.indexmax(), 5);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_position(1), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_position(2), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_position(3), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_position(4), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_position(5), 0);
  ASSERT_EQ(depvars.grad_file_count.indexmin(), 1);
  ASSERT_EQ(depvars.grad_file_count.indexmax(), 5);
  ASSERT_DOUBLE_EQ(depvars.grad_file_count(1), 0);
  ASSERT_DOUBLE_EQ(depvars.grad_file_count(2), 0);
  ASSERT_DOUBLE_EQ(depvars.grad_file_count(3), 0);
  ASSERT_DOUBLE_EQ(depvars.grad_file_count(4), 0);
  ASSERT_DOUBLE_EQ(depvars.grad_file_count(5), 0);
  ASSERT_EQ(depvars.cmpdif_file_count.indexmin(), 1);
  ASSERT_EQ(depvars.cmpdif_file_count.indexmax(), 5);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_count(1), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_count(2), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_count(3), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_count(4), 0);
  ASSERT_DOUBLE_EQ(depvars.cmpdif_file_count(5), 0);
}
TEST_F(test_dependent_variables_information, DEPVARS_INFO)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  {
    gradient_structure gs;
    ASSERT_TRUE(gradient_structure::get()->DEPVARS_INFO != NULL);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->max_num_dependent_variables, gradient_structure::NUM_DEPENDENT_VARIABLES);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->depvar_count, 0);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->grad_buffer_position.indexmin(), 1);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->grad_buffer_position.indexmax(), gradient_structure::NUM_DEPENDENT_VARIABLES);
    for (int i = 1; i <= gradient_structure::NUM_DEPENDENT_VARIABLES; ++i)
    {
      ASSERT_TRUE(gradient_structure::get()->DEPVARS_INFO->grad_buffer_position(i) == NULL);
    }
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_buffer_position.indexmin(), 1);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_buffer_position.indexmax(), gradient_structure::NUM_DEPENDENT_VARIABLES);
    for (int i = 1; i <= gradient_structure::NUM_DEPENDENT_VARIABLES; ++i)
    {
      ASSERT_DOUBLE_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_buffer_position(i), 0);
    }
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->grad_file_position.indexmin(), 1);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->grad_file_position.indexmax(), gradient_structure::NUM_DEPENDENT_VARIABLES);
    for (int i = 1; i <= gradient_structure::NUM_DEPENDENT_VARIABLES; ++i)
    {
      ASSERT_DOUBLE_EQ(gradient_structure::get()->DEPVARS_INFO->grad_file_position(i), 0);
    }
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_file_position.indexmin(), 1);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_file_position.indexmax(), gradient_structure::NUM_DEPENDENT_VARIABLES);
    for (int i = 1; i <= gradient_structure::NUM_DEPENDENT_VARIABLES; ++i)
    {
      ASSERT_DOUBLE_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_file_position(i), 0);
    }
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->grad_file_count.indexmin(), 1);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->grad_file_count.indexmax(), gradient_structure::NUM_DEPENDENT_VARIABLES);
    for (int i = 1; i <= gradient_structure::NUM_DEPENDENT_VARIABLES; ++i)
    {
      ASSERT_DOUBLE_EQ(gradient_structure::get()->DEPVARS_INFO->grad_file_count(i), 0);
    }
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_file_count.indexmin(), 1);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_file_count.indexmax(), gradient_structure::NUM_DEPENDENT_VARIABLES);
    for (int i = 1; i <= gradient_structure::NUM_DEPENDENT_VARIABLES; ++i)
    {
      ASSERT_DOUBLE_EQ(gradient_structure::get()->DEPVARS_INFO->cmpdif_file_count(i), 0);
    }
  }
  ASSERT_TRUE(gradient_structure::get() == NULL);
}
TEST_F(test_dependent_variables_information, save_dependent_variable_position)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  {
    gradient_structure gs;
    dvariable v;
    gradient_structure::save_dependent_variable_position(v);
    ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->depvar_count, 1);
  }
}
TEST_F(test_dependent_variables_information, save_dependent_variable_position_error)
{
  gradient_structure gs;

  for (int i = 1; i <= gradient_structure::NUM_DEPENDENT_VARIABLES; ++i)
  {
    dvariable v;
    gradient_structure::save_dependent_variable_position(v);
  }
  ASSERT_EQ(gradient_structure::get()->DEPVARS_INFO->depvar_count, gradient_structure::NUM_DEPENDENT_VARIABLES);

  ad_exit=&test_ad_exit;
  dvariable v2;
  ASSERT_THROW(gradient_structure::save_dependent_variable_position(v2), int);
}
