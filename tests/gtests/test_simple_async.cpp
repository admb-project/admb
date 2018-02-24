#include <future>
#include <gtest/gtest.h>
#include <fvar.hpp>
#include <admodel.h>
#include <unistd.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_simple_async: public ::testing::Test {};

TEST_F(test_simple_async, gradcalc_empty)
{
  dvector empty;
  gradcalc(empty.size(), empty);
}
TEST_F(test_simple_async, gradcalc_empty_with_gradient_structure)
{
  gradient_structure gs;

  dvector empty;
  gradcalc(empty.size(), empty);
}
TEST_F(test_simple_async, gradcalc_make_indvar_list_not_called)
{
  ad_exit=&test_ad_exit;

  dvector gradients(1, 2);
  ASSERT_ANY_THROW({
    gradcalc(gradients.size(), gradients);
  });
}
TEST_F(test_simple_async, minimum)
{
  independent_variables independents(1, 2);

  gradient_structure gs;

  dvar_vector variables(independents);

  dvector gradients(1, 2);
  gradcalc(2, gradients);

  ASSERT_DOUBLE_EQ(independents(1), 0);
  ASSERT_DOUBLE_EQ(independents(2), 0);
  ASSERT_DOUBLE_EQ(gradients(1), 0);
  ASSERT_DOUBLE_EQ(gradients(2), 0);
}
TEST_F(test_simple_async, simple_initial_values)
{
  independent_variables independents(1, 2);

  gradient_structure gs;

  dvar_vector variables(independents);

  dvector x(1, 10); 
  x(1) = -1.0;
  x(2) = 0.0;
  x(3) = 1.0;
  x(4) = 2.0;
  x(5) = 3.0;
  x(6) = 4.0;
  x(7) = 5.0;
  x(8) = 6.0;
  x(9) = 7.0;
  x(10) = 8.0;

  dvar_vector yhat(1, 10);
  yhat = variables(1) + variables(2) * x; 

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

  objective_function_value f;
  f = regression(y, yhat);

  dvector gradients(independents.indexmin(), independents.indexmax());
  gradcalc(gradients.size(), gradients);

  ASSERT_DOUBLE_EQ(independents(1), 0);
  ASSERT_DOUBLE_EQ(independents(2), 0);
  ASSERT_DOUBLE_EQ(gradients(1), -0.7278138528138528);
  ASSERT_DOUBLE_EQ(gradients(2), -3.6126893939393945);
}
TEST_F(test_simple_async, dlist_total_addresses)
{
  dlist list;
  ASSERT_EQ(list.total_addresses(), 0);
}
TEST_F(test_simple_async, gradient_structure_only_GRAD_LIST)
{
  ASSERT_TRUE(gradient_structure::GRAD_LIST == NULL);

  gradient_structure gs;

  ASSERT_TRUE(gradient_structure::GRAD_LIST != NULL);

  //Created for return variables and arrays
  //gradstrc.cpp: unsigned int gradient_structure::NUM_RETURN_ARRAYS = 25;
  ASSERT_EQ(gradient_structure::GRAD_LIST->total_addresses(),
            25 * gradient_structure::RETURN_ARRAYS_SIZE);
}
TEST_F(test_simple_async, gradient_structure_only_GRAD_STACK1)
{
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);

  gradient_structure gs;

  ASSERT_TRUE(gradient_structure::GRAD_STACK1 != NULL);
}
TEST_F(test_simple_async, gradient_structure_only_DF_FILE)
{
  ASSERT_TRUE(gradient_structure::get_fp() == NULL);

  gradient_structure gs;

  ASSERT_TRUE(gradient_structure::get_fp() != NULL);
  ASSERT_TRUE(gradient_structure::get_fp()->file_ptr != 0);
  ASSERT_EQ(gradient_structure::get_fp()->offset, 0);
  ASSERT_EQ(gradient_structure::get_fp()->toffset, 0);
  ASSERT_TRUE(gradient_structure::get_fp()->buff != NULL);
  ASSERT_EQ(sizeof(gradient_structure::get_fp()->buff), sizeof(OFF_T));
  ASSERT_STREQ(gradient_structure::get_fp()->cmpdif_file_name, "cmpdiff.tmp");
  OFF_T pos = LSEEK(gradient_structure::get_fp()->file_ptr, 0, SEEK_END);
  ASSERT_EQ(pos, 0);
}
TEST_F(test_simple_async, simple_final_values)
{

  independent_variables independents(1, 2);
  independents(1) = 4.07817738582;
  independents(2) = 1.90909098475;

  gradient_structure gs;

  grad_stack_entry* expected_ptr = gradient_structure::GRAD_STACK1->ptr;
  ASSERT_TRUE(gradient_structure::GRAD_STACK1->ptr == expected_ptr);

  dvar_vector variables(independents);

  dvector x(1, 10); 
  x(1) = -1.0;
  x(2) = 0.0;
  x(3) = 1.0;
  x(4) = 2.0;
  x(5) = 3.0;
  x(6) = 4.0;
  x(7) = 5.0;
  x(8) = 6.0;
  x(9) = 7.0;
  x(10) = 8.0;

  ASSERT_EQ(gradient_structure::get_fp()->toffset, 0);
  ASSERT_EQ(gradient_structure::get_fp()->offset, 0);

  dvar_vector yhat(1, 10);

  yhat = variables(1) + variables(2) * x; 

  OFF_T pos = LSEEK(gradient_structure::get_fp()->file_ptr, 0, SEEK_CUR);
  ASSERT_EQ(pos, 0);

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


  objective_function_value f;
  f = regression(y, yhat);

  //ASSERT_EQ(gradient_structure::GRAD_LIST->total_addresses(),
  //          25 * gradient_structure::RETURN_ARRAYS_SIZE);

  ASSERT_TRUE(gradient_structure::GRAD_STACK1->ptr != expected_ptr);

  ASSERT_EQ(gradient_structure::get_fp()->toffset, 460);
  ASSERT_EQ(gradient_structure::get_fp()->offset, 460);

  dvector gradients(independents.indexmin(), independents.indexmax());

  int total = 0;
  grad_stack_entry* ptr = expected_ptr;
  while (gradient_structure::GRAD_STACK1->ptr != ptr)
  {
    ptr++;
    total++;
  }
  ASSERT_EQ(total, 11);

  gradcalc(gradients.size(), gradients);

  ASSERT_TRUE(gradient_structure::GRAD_STACK1->ptr == expected_ptr);

  ASSERT_EQ(gradient_structure::get_fp()->toffset, 0);
  ASSERT_EQ(gradient_structure::get_fp()->offset, 0);

  ASSERT_EQ(gradient_structure::GRAD_LIST->total_addresses(),
            25 * gradient_structure::RETURN_ARRAYS_SIZE + 3);

  ASSERT_DOUBLE_EQ(independents(1), 4.07817738582);
  ASSERT_DOUBLE_EQ(independents(2), 1.90909098475);
  ASSERT_DOUBLE_EQ(gradients(1), -2.0898189765639064e-05);
  ASSERT_DOUBLE_EQ(gradients(2), -7.0013678170888216e-05);
}
TEST_F(test_simple_async, simple)
{

  independent_variables independents(1, 2);
  independents(1) = 4.07817738582;
  independents(2) = 1.90909098475;

  gradient_structure gs;

  dvar_vector variables(independents);

  dvector x(1, 10); 
  x(1) = -1.0;
  x(2) = 0.0;
  x(3) = 1.0;
  x(4) = 2.0;
  x(5) = 3.0;
  x(6) = 4.0;
  x(7) = 5.0;
  x(8) = 6.0;
  x(9) = 7.0;
  x(10) = 8.0;

  dvar_vector yhat(1, 10);

  yhat = variables(1) + variables(2) * x; 

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

  objective_function_value f;
  f = regression(y, yhat);

  dvector gradients(independents.indexmin(), independents.indexmax());

  gradcalc(gradients.size(), gradients);

  ASSERT_DOUBLE_EQ(independents(1), 4.07817738582);
  ASSERT_DOUBLE_EQ(independents(2), 1.90909098475);
  ASSERT_DOUBLE_EQ(gradients(1), -2.0898189765639064e-05);
  ASSERT_DOUBLE_EQ(gradients(2), -7.0013678170888216e-05);
}
TEST_F(test_simple_async, verysimple)
{
  independent_variables independents(1, 1);
  independents(1) = 4.07817738582;

  gradient_structure gs;

  dvar_vector variables(independents);

  objective_function_value y;

  y = -0.5 * variables(1);

  ASSERT_DOUBLE_EQ(value(y), -0.5 * independents(1));

  dvector gradients(independents.indexmin(), independents.indexmax());

  //In gradcalc sets variables dependant value to 1.
  gradcalc(gradients.size(), gradients);

  ASSERT_DOUBLE_EQ(independents(1), 4.07817738582);
  ASSERT_DOUBLE_EQ(gradients(1), -0.5);
}
TEST_F(test_simple_async, verysimpleab)
{
  independent_variables independents(1, 2);
  independents(1) = 4.07817738582;
  independents(2) = 1.90909098475;

  gradient_structure gs;

  dvar_vector variables(independents);

  dvariable a;
  a = variables(1);

  dvariable b;
  b = 2.0 * variables(2);

  objective_function_value f;

  f = a + b;

  ASSERT_DOUBLE_EQ(value(f), 7.8963593553199996);

  dvector gradients(independents.indexmin(), independents.indexmax());

  //In gradcalc sets variables dependant value to 1.
  gradcalc(gradients.size(), gradients);

  ASSERT_DOUBLE_EQ(independents(1), 4.07817738582);
  ASSERT_DOUBLE_EQ(independents(2), 1.90909098475);
  ASSERT_DOUBLE_EQ(gradients(1), 1.0);
  ASSERT_DOUBLE_EQ(gradients(2), 2.0);
}
TEST_F(test_simple_async, verysimpleaa)
{
  independent_variables independents(1, 1);
  independents(1) = 4.07817738582;

  gradient_structure gs;

  dvar_vector variables(independents);

  dvariable a;
  a = variables(1);

  dvariable b;
  b = 2.0 * variables(1);

  objective_function_value f;

  f = a + b;

  ASSERT_DOUBLE_EQ(value(f), (independents(1) + 2.0 * independents(1)));

  dvector gradients(independents.indexmin(), independents.indexmax());

  //In gradcalc sets variables dependant value to 1.
  gradcalc(gradients.size(), gradients);

  ASSERT_DOUBLE_EQ(independents(1), 4.07817738582);
  ASSERT_DOUBLE_EQ(gradients(1), 3.0);
}
TEST_F(test_simple_async, verysimpleaa_noasync)
{
  independent_variables independents(1, 1);
  independents(1) = 4.07817738582;

  gradient_structure gs;

  dvar_vector variables(independents);

  dvariable a, b;

  auto compute_a =
    [](const dvariable& a)
    {
      dvariable result;
      result = 3.5 * a;
      return result;
    };
  auto compute_b = 
    [](const dvariable& b)
    {
      dvariable result;
      result = 1.5 * b;
      return result;
    };

  ASSERT_EQ(0, gradient_structure::GRAD_STACK1->total());
  a = compute_a(variables(1));
  ASSERT_EQ(4, gradient_structure::GRAD_STACK1->total());
  b = compute_b(variables(1));
  ASSERT_EQ(8, gradient_structure::GRAD_STACK1->total());

  objective_function_value f;

  f = a + b;

  ASSERT_DOUBLE_EQ(value(f), (3.5 * independents(1) + 1.5 * independents(1)));

  dvector gradients(independents.indexmin(), independents.indexmax());

  //jca
  ASSERT_EQ(10, gradient_structure::GRAD_STACK1->total());

  grad_stack_entry* ptr = gradient_structure::GRAD_STACK1->ptr;

  --ptr;
  //10: f = ... in fvar_o10.cpp
  ASSERT_TRUE(ptr->func == &default_evaluation1);

  --ptr;
  //9: a + b ... in fvar_opr.cpp
  ASSERT_TRUE(ptr->func == &default_evaluation4);

  --ptr;
  //4: b = compute_b(variables(1)); in fvar_o10.cpp
  ASSERT_TRUE(ptr->func == &default_evaluation1);

  --ptr;
  //7: result = 
  ASSERT_TRUE(ptr->func == &default_evaluation1);

  --ptr;
  //6: 1.5 * b; in fvar_o10.cpp
  ASSERT_TRUE(ptr->func == &default_evaluation2);

  --ptr;
  //5: called dvariable::dvariable(const prevariable& t)
  ASSERT_TRUE(ptr->func == &default_evaluation1);

  --ptr;
  //4: a = compute_a(variables(1)); in fvar_o10.cpp
  ASSERT_TRUE(ptr->func == &default_evaluation1);

  --ptr;
  //3: result = 
  ASSERT_TRUE(ptr->func == &default_evaluation1);

  --ptr;
  //2: 3.5 * a; in fvar_o10.cpp
  ASSERT_TRUE(ptr->func == &default_evaluation2);

  --ptr;
  //1: called dvariable::dvariable(const prevariable& t)
  ASSERT_TRUE(ptr->func == &default_evaluation1);

  ASSERT_EQ(10, gradient_structure::GRAD_STACK1->total());

  //In gradcalc sets variables dependant value to 1.
  gradcalc(gradients.size(), gradients);

  ASSERT_DOUBLE_EQ(independents(1), 4.07817738582);
  ASSERT_DOUBLE_EQ(gradients(1), 5.0);
}
TEST_F(test_simple_async, verysimpleaa_async_racecondition)
{
  independent_variables independents(1, 1);
  independents(1) = 4.07817738582;

  gradient_structure gs;

  dvar_vector variables(independents);

  dvariable a, b;

  std::future<dvariable> compute_a(
    std::async([](const dvariable& a)
    {
      dvariable result;
      result = 3.5 * a;
      return result;
    } , variables(1)));

  std::future<dvariable> compute_b(
    std::async([](const dvariable& b)
    {
      dvariable result;
      result = 1.5 * b;
      return result;
    } , variables(1)));

  a = compute_a.get();
  b = compute_b.get();

  ASSERT_EQ(12, gradient_structure::GRAD_STACK1->total());

  objective_function_value f;

  f = a + b;

  ASSERT_EQ(14, gradient_structure::GRAD_STACK1->total());

  ASSERT_DOUBLE_EQ(value(f), (3.5 * independents(1) + 1.5 * independents(1)));

  dvector gradients(independents.indexmin(), independents.indexmax());

  //In gradcalc sets variables dependant value to 1.
  gradcalc(gradients.size(), gradients);

  ASSERT_DOUBLE_EQ(independents(1), 4.07817738582);
  ASSERT_DOUBLE_EQ(gradients(1), 5.0);
}
