#include <gtest/gtest.h>
#include "fvar.hpp"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_arr_list: public ::testing::Test {};

TEST_F(test_arr_list, initial_state)
{
  ASSERT_TRUE(gradient_structure::ARR_LIST1 == NULL);
}
TEST_F(test_arr_list, scoped_state)
{
  {
    gradient_structure gs;
    ASSERT_TRUE(gradient_structure::ARR_LIST1 != NULL);
    ASSERT_EQ(gradient_structure::ARR_LIST1->get_number_arr_links(), 0);
  }
  ASSERT_TRUE(gradient_structure::ARR_LIST1 == NULL);
}
TEST_F(test_arr_list, constructor_state)
{
  independent_variables independents(1, 1);
  independents(1) = 4.07817738582;

  gradient_structure gs;

  ASSERT_EQ(gradient_structure::ARR_LIST1->get_number_arr_links(), 0);
  dvar_vector variables(independents);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_number_arr_links(), 1);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last(), variables.link_ptr);
  ASSERT_TRUE(gradient_structure::ARR_LIST1->get_last()->get_prev() == NULL);
  ASSERT_TRUE(gradient_structure::ARR_LIST1->get_last()->get_next() == NULL);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_status(), 1);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_size(), sizeof(double_and_int));
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_offset(), 0);
}
TEST_F(test_arr_list, constructor4_state)
{
  independent_variables independents(1, 4);

  gradient_structure gs;

  ASSERT_EQ(gradient_structure::ARR_LIST1->get_number_arr_links(), 0);
  dvar_vector variables(independents);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_number_arr_links(), 1);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last(), variables.link_ptr);
  ASSERT_TRUE(gradient_structure::ARR_LIST1->get_last()->get_prev() == NULL);
  ASSERT_TRUE(gradient_structure::ARR_LIST1->get_last()->get_next() == NULL);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_status(), 1);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_size(), sizeof(double_and_int) * 4);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_offset(), 0);
}
TEST_F(test_arr_list, two_arrays_state)
{
  independent_variables independents(1, 4);
  independent_variables independents2(1, 8);

  gradient_structure gs;

  dvar_vector variables(independents);
  dvar_vector variables2(independents2);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_number_arr_links(), 2);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last(), variables2.link_ptr);
  ASSERT_TRUE(gradient_structure::ARR_LIST1->get_last()->get_prev() == variables.link_ptr);
  ASSERT_TRUE(gradient_structure::ARR_LIST1->get_last()->get_next() == NULL);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_status(), 1);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_size(), sizeof(double_and_int) * 8);
  ASSERT_EQ(gradient_structure::ARR_LIST1->get_last()->get_offset(), sizeof(double_and_int) * 4);
}
