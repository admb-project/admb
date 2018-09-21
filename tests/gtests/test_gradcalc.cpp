#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>


extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradcalc: public ::testing::Test {};

TEST_F(test_gradcalc, gradient_size_intmax)
{
  ad_exit=&test_ad_exit;

  const long int size = sizeof(double_and_int);
  long int total_size  = INT_MAX;
  //compute size should that is not big enough
  long int extra = total_size % size;
  total_size -= extra;
  gradient_structure gs(INT_MAX);

  double_and_int* ptr =
    (double_and_int*)gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  memset(ptr, 0, total_size);
  for (int i = 0; i < total_size; i += size)
  {
    ASSERT_DOUBLE_EQ(ptr->x, 0);   
    ++ptr;
  }
  ptr = (double_and_int*)gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  memset(ptr, 1, total_size);
  for (int i = 0; i < total_size; i += size)
  {
    ptr->x = 0.0;
    ++ptr;
  }
  ptr = (double_and_int*)gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  for (int i = 0; i < total_size; i += size)
  {
    ASSERT_DOUBLE_EQ(ptr->x, 0);   
    ++ptr;
  }
}
TEST_F(test_gradcalc, gradient_size_small_array_memblock_base)
{
  ad_exit=&test_ad_exit;

  const long int size = sizeof(double_and_int);
  const long int total_size  = size * 2;
  gradient_structure gs(total_size);

  double_and_int* ptr =
    (double_and_int*)gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  memset(ptr, 0, total_size);

  for (int i = 0; i < total_size; i += size)
  {
    ASSERT_DOUBLE_EQ(ptr->x, 0);   
    ++ptr;
  }
}
TEST_F(test_gradcalc, dvar_vector)
{
  ad_exit=&test_ad_exit;

  const long int size = sizeof(double_and_int);
  const long int total_size  = size * 4;
  gradient_structure gs(total_size);

  ASSERT_EQ(gradient_structure::ARR_LIST1->get_max_last_offset(), 0);

  dvar_vector v(1, 4);
  v.initialize();

  ASSERT_EQ(gradient_structure::ARR_LIST1->get_max_last_offset(), total_size);

  double_and_int* ptr =
    (double_and_int*)gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  for (int i = 0; i < total_size; i += size)
  {
    ASSERT_DOUBLE_EQ(ptr->x, 0);   
    ++ptr;
  }

  v(1) = -1.5;
  v(2) = 4.5;
  v(3) = 1.5;
  v(4) = -8.5;
  ptr = (double_and_int*)gradient_structure::get_ARRAY_MEMBLOCK_BASE();

  ASSERT_DOUBLE_EQ(ptr->x, value(v(1)));
  ++ptr;

  ASSERT_DOUBLE_EQ(ptr->x, value(v(2)));
  ++ptr;

  ASSERT_DOUBLE_EQ(ptr->x, value(v(3)));
  ++ptr;

  ASSERT_DOUBLE_EQ(ptr->x, value(v(4)));

  ptr = (double_and_int*)gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  memset(ptr, 0, total_size);
  for (int i = 0; i < total_size; i += size)
  {
    ASSERT_DOUBLE_EQ(ptr->x, 0);   
    ++ptr;
  }

  /*
  unsigned long int max_last_offset0 =
    gradient_structure::ARR_LIST1->get_max_last_offset();
  ASSERT_EQ(max_last_offset0, 0);

  size_t size = sizeof(double_and_int);

  dvar_vector v(1, 4);
  unsigned long int max_last_offset =
    gradient_structure::ARR_LIST1->get_max_last_offset();
  ASSERT_EQ(max_last_offset, 4 * size);
  for (unsigned int i = 0; i < (max_last_offset/size); i++)
  {
     tmp->x = 0;
     tmp++;
  }

  memset(gradient_structure::ARRAY_MEMBLOCK_BASE,
         0, gradient_structure::ARRAY_MEMBLOCK_SIZE);
  */
}
TEST_F(test_gradcalc, nvarzero)
{
  ad_exit=&test_ad_exit;

  dvector g;

  //ASSERT_EQ(0, gradient_structure::NVAR);

  ASSERT_ANY_THROW({
    gradcalc(1, g);
  });
}
TEST_F(test_gradcalc, simple)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

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

  independent_variables independents(1, 2);
  independents.initialize();

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvar_vector yhat(1, 10);
  yhat = variables(1) + variables(2) * x;

  dvariable f = 0.0;
  f=regression(y,yhat);

  double result = value(f);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_DOUBLE_EQ(result, 24.980653039466869);
  ASSERT_DOUBLE_EQ(g(1), -0.7278138528138528);
  ASSERT_DOUBLE_EQ(g(2), -3.6126893939393945);

}
TEST_F(test_gradcalc, simple_final)
{
  ad_exit=&test_ad_exit;

  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);

  gradient_structure gs;

  ASSERT_TRUE(gradient_structure::GRAD_STACK1 != NULL);

  const unsigned int NUM_RETURN_ARRAYS = 25;
  unsigned int expected_total = //1750
    NUM_RETURN_ARRAYS * gradient_structure::RETURN_ARRAYS_SIZE;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total);

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

  independent_variables independents(1, 2);
  independents(1) = 4.07818;
  independents(2) = 1.90909;

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvar_vector yhat(1, 10);
  yhat = variables(1) + variables(2) * x;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 3);

  ASSERT_DOUBLE_EQ(value(yhat(1)), independents(1) + independents(2) * x(1));
  ASSERT_DOUBLE_EQ(value(yhat(2)), independents(1) + independents(2) * x(2));
  ASSERT_DOUBLE_EQ(value(yhat(3)), independents(1) + independents(2) * x(3));
  ASSERT_DOUBLE_EQ(value(yhat(4)), independents(1) + independents(2) * x(4));
  ASSERT_DOUBLE_EQ(value(yhat(5)), independents(1) + independents(2) * x(5));
  ASSERT_DOUBLE_EQ(value(yhat(6)), independents(1) + independents(2) * x(6));
  ASSERT_DOUBLE_EQ(value(yhat(7)), independents(1) + independents(2) * x(7));
  ASSERT_DOUBLE_EQ(value(yhat(8)), independents(1) + independents(2) * x(8));
  ASSERT_DOUBLE_EQ(value(yhat(9)), independents(1) + independents(2) * x(9));
  ASSERT_DOUBLE_EQ(value(yhat(10)), independents(1) + independents(2) * x(10));

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 3);
  dvariable f = 0.0;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 4);
  f=regression(y,yhat);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 14);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 3.4512604236817603);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 14);
  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  ASSERT_DOUBLE_EQ(g(1), value(variables(1)));
  ASSERT_DOUBLE_EQ(g(2), value(variables(2)));

  ASSERT_DOUBLE_EQ(value(f), 0.0);
  ASSERT_DOUBLE_EQ(independents(1), 4.07818);
  ASSERT_DOUBLE_EQ(independents(2), 1.90909);
  ASSERT_DOUBLE_EQ(value(yhat(1)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(2)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(3)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(4)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(5)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(6)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(7)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(8)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(9)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(10)), 0.0);
}
