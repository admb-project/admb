#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>
#include <thread>
#include <future>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradcalc: public ::testing::Test {};

/*
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
*/
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

  ASSERT_EQ(gradient_structure::GRAD_STACK1->ARR_LIST1->get_max_last_offset(), 0);

  dvar_vector v(1, 4);
  v.initialize();

  ASSERT_EQ(gradient_structure::GRAD_STACK1->ARR_LIST1->get_max_last_offset(), total_size);

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
    gradient_structure::GRAD_STACK1->ARR_LIST1->get_max_last_offset();
  ASSERT_EQ(max_last_offset0, 0);

  size_t size = sizeof(double_and_int);

  dvar_vector v(1, 4);
  unsigned long int max_last_offset =
    gradient_structure::GRAD_STACK1->ARR_LIST1->get_max_last_offset();
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
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

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
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);

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

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);
  dvariable f = 0.0;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);
  f = regression(y,yhat);
  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 3.4512604236817603);

  //ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 13);
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
TEST_F(test_gradcalc, simple_xy)
{
  for (int i = 0; i < 3; ++i)
  {
  ad_exit=&test_ad_exit;

  size_t size = sizeof(double_and_int);
  const long int total_size  = size * 2;

  const unsigned int NUM_RETURN_ARRAYS = 25;

  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);

  gradient_structure gs(total_size);

  ASSERT_TRUE(gradient_structure::GRAD_STACK1 != NULL);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->GRAD_LIST->total_addresses(), 1750);

  independent_variables independents(1, 2);
  independents(1) = 4.07818;
  independents(2) = -1.90909;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->ARR_LIST1->get_max_last_offset(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->ARR_LIST1->get_max_last_offset(), total_size);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->GRAD_LIST->total_addresses(), 1750);
  dvariable f = 0.0;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->GRAD_LIST->total_addresses(), 1751);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 1);

  f = variables(1) * variables(2);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);

  double result = value(f);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  ASSERT_DOUBLE_EQ(result, independents(1) * independents(2));
  ASSERT_DOUBLE_EQ(g(1), -1.90909);
  ASSERT_DOUBLE_EQ(g(2), 4.07818);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->ARR_LIST1->get_max_last_offset(), total_size);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->GRAD_LIST->total_addresses(), 1751);
  }
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);
}
TEST_F(test_gradcalc, operator_multiply_vars_vars)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.7;
  independents(2) = -2.3;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  dvariable f;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  cout << __FILE__ << ':' << __LINE__ << endl;
  f = variables * variables;
  cout << __FILE__ << ':' << __LINE__ << endl;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  double result = value(f);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);
  ASSERT_DOUBLE_EQ(result, 27.38);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
  ASSERT_DOUBLE_EQ(g(-1), 9.4);
  ASSERT_DOUBLE_EQ(g(0), -4.6);
}
TEST_F(test_gradcalc, operator_plus_prevar_prevar)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.7;
  independents(2) = -2.3;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  dvariable f;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  cout << __FILE__ << ':' << __LINE__ << endl;
  f = variables(1) + variables(2);
  cout << __FILE__ << ':' << __LINE__ << endl;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  double result = value(f);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);
  ASSERT_DOUBLE_EQ(result, 2.4);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
  ASSERT_DOUBLE_EQ(g(-1), 1);
  ASSERT_DOUBLE_EQ(g(0), 1);
}

prevariable& fourth(const prevariable& v1);
TEST_F(test_gradcalc, cube_forth)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.7;
  independents(2) = -2.3;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  dvariable f;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  f = cube(variables(1)) + fourth(variables(2));

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);

  double result = value(f);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);
  ASSERT_DOUBLE_EQ(result, 131.8071);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
  ASSERT_DOUBLE_EQ(g(-1), 66.27);
  ASSERT_DOUBLE_EQ(g(0), -48.668);
}
TEST_F(test_gradcalc, thread_simple)
{
  ad_exit=&test_ad_exit;

  std::srand(std::time(nullptr));

  auto f = []()
  {
    gradient_structure gs;

    int random0 = std::rand() % 4;
    int random1 = std::rand() % 5;
    int random2 = std::rand() % 3;

    independent_variables independents(1, 2);
    independents(1) = 4.7;
    independents(2) = -2.3;

    std::this_thread::sleep_for (std::chrono::seconds(random0));

    ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

    // Set gradient_structure::NVAR
    dvar_vector variables(independents);

    ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

    dvariable f;

    ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

    std::this_thread::sleep_for (std::chrono::seconds(random1));
    f = cube(variables(1)) + fourth(variables(2));

    ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);

    double result = value(f);
    ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);
    ASSERT_DOUBLE_EQ(result, 131.8071);

    std::this_thread::sleep_for (std::chrono::seconds(random2));
    dvector g(-1, 0);
    gradcalc(2, g);
    ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
    ASSERT_DOUBLE_EQ(g(-1), 66.27);
    ASSERT_DOUBLE_EQ(g(0), -48.668);
  };
  auto simple = []()
  {
    gradient_structure gs;

    int random0 = std::rand() % 4;
    int random1 = std::rand() % 5;
    int random2 = std::rand() % 3;
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

    std::this_thread::sleep_for (std::chrono::seconds(random0));

    independent_variables independents(1, 2);
    independents.initialize();

    // Set gradient_structure::NVAR
    dvar_vector variables(independents);

    std::this_thread::sleep_for (std::chrono::seconds(random1));

    dvar_vector yhat(1, 10);
    yhat = variables(1) + variables(2) * x;

    dvariable f = 0.0;
    f=regression(y,yhat);

    double result = value(f);

    std::this_thread::sleep_for (std::chrono::seconds(random2));

    dvector g(1, 2);
    gradcalc(2, g);

    ASSERT_DOUBLE_EQ(result, 24.980653039466869);
    ASSERT_DOUBLE_EQ(g(1), -0.7278138528138528);
    ASSERT_DOUBLE_EQ(g(2), -3.6126893939393945);
  };

  std::thread t1(simple);
  std::thread t2(simple);
  std::thread t3(f);
  std::thread t4(simple);
  t1.join();
  t4.join();
  t3.join();
  t2.join();
}
TEST_F(test_gradcalc, funnel_pre)
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

  dvariable f;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  f = (2.0 * x + 3.0 * y) + (pow(x, 2.0) + pow(y, 3.0));

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 60.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(-1), 10.0);
  ASSERT_DOUBLE_EQ(g(0), 30.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
TEST_F(test_gradcalc, funnel_split)
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

  dvariable f, a, b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  a = (2.0 * x + 3.0 * y);
  b = (pow(x, 2.0) + pow(y, 3.0));
  f = a + b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 12);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 60.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 12);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(-1), 10.0);
  ASSERT_DOUBLE_EQ(g(0), 30.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvariable compute_a(dvariable& x, dvariable& y)
{
  dvariable a;
  a = (2.0 * x + 3.0 * y);
  return a;
}
dvariable compute_b(dvariable& x, dvariable& y)
{
  dvariable b;
  b = (pow(x, 2.0) + pow(y, 3.0));
  return b;
}
TEST_F(test_gradcalc, funnel_functions)
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

  dvariable f, a, b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  a = compute_a(x, y);
  b = compute_b(x, y);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 12);

  f = a + b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 14);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 60.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 14);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(-1), 10.0);
  ASSERT_DOUBLE_EQ(g(0), 30.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvariable df_compute_a(dvariable& x, dvariable& y)
{
  dvariable a;
  funnel_dvariable f;
  ad_begin_funnel();
  f = (2.0 * x + 3.0 * y);
  a = f;
  return a;
}
dvariable df_compute_b(dvariable& x, dvariable& y)
{
  dvariable b;
  funnel_dvariable f;
  ad_begin_funnel();
  f = (pow(x, 2.0) + pow(y, 3.0));
  b = f;
  return b;
}
TEST_F(test_gradcalc, funnel_dvariable)
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

  dvariable f, a, b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  a = df_compute_a(x, y);
  b = df_compute_b(x, y);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  f = a + b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);


  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 60.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(-1), 10.0);
  ASSERT_DOUBLE_EQ(g(0), 30.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
TEST_F(test_gradcalc, funnel_set_gradient)
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

  dvariable f, a(17.0), b(43.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);

  //a = df2_compute_a(x, y);
  gradient_structure::GRAD_STACK1->set_gradient_stack(
    default_evaluation,
    &((*a.v).x),
    &((*x.v).x), 2.0,
    &((*y.v).x), 3.0
  );
  //b = df_compute_b(x, y);
  gradient_structure::GRAD_STACK1->set_gradient_stack(
    default_evaluation,
    &((*b.v).x),
    &((*x.v).x), 8.0,
    &((*y.v).x), 27.0
  );

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 6);

  f = a + b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 60.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(-1), 10.0);
  ASSERT_DOUBLE_EQ(g(0), 30.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvariable f_compute_a(dvariable& x, dvariable& y)
{
  dvariable a(17.0);
  gradient_structure::GRAD_STACK1->set_gradient_stack(
    default_evaluation,
    &((*a.v).x),
    &((*x.v).x), 2.0,
    &((*y.v).x), 3.0
  );
  return a;
}
dvariable f_compute_b(dvariable& x, dvariable& y)
{
  dvariable b(43.0);
  gradient_structure::GRAD_STACK1->set_gradient_stack(
    default_evaluation,
    &((*b.v).x),
    &((*x.v).x), 8.0,
    &((*y.v).x), 27.0
  );
  return b;
}
TEST_F(test_gradcalc, funnel_set_gradient_function)
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

  dvariable f, a, b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  a = f_compute_a(x, y);
  b = f_compute_b(x, y);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  f = a + b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 60.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(-1), 10.0);
  ASSERT_DOUBLE_EQ(g(0), 30.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvariable tf_compute_a(dvariable& x, dvariable& y)
{
  dvariable a(17.0);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  entry->func = default_evaluation;
  entry->dep_addr = &((*a.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = 2.0;
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = 3.0;
  gradient_structure::GRAD_STACK1->ptr++;
  
  return a;
}
dvariable tf_compute_b(dvariable& x, dvariable& y)
{
  dvariable b(43.0);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  entry->func = default_evaluation;
  entry->dep_addr = &((*b.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = 8.0;
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = 27.0;
  gradient_structure::GRAD_STACK1->ptr++;

  return b;
}
TEST_F(test_gradcalc, funnel_set_gradient_thread_function)
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

  dvariable f, a, b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  a = tf_compute_a(x, y);
  b = tf_compute_b(x, y);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  f = a + b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 60.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(-1), 10.0);
  ASSERT_DOUBLE_EQ(g(0), 30.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
dvariable async_compute_a(dvariable& x, dvariable& y)
{
  dvariable a(17.0);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  gradient_structure::GRAD_STACK1->ptr++;

  std::future<dvector> gradients =
    std::async(std::launch::async, []()
    {
      int random = std::rand() % 5;
      std::this_thread::sleep_for(std::chrono::seconds(random));

      dvector g(1, 2);
      g(1) = 2.0;
      g(2) = 3.0;
      return g;
    });
  dvector g = gradients.get();

  entry->func = default_evaluation;
  entry->dep_addr = &((*a.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = 2.0;
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = 3.0;
  
  return a;
}
dvariable async_compute_b(dvariable& x, dvariable& y)
{
  dvariable b(43.0);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  gradient_structure::GRAD_STACK1->ptr++;

  std::future<dvector> gradients =
    std::async(std::launch::async, []()
    {
      int random = std::rand() % 5;
      std::this_thread::sleep_for(std::chrono::seconds(random));

      dvector g(1, 2);
      g(1) = 8.0;
      g(2) = 27.0;
      return g;
    });
  dvector g = gradients.get();

  entry->func = default_evaluation;
  entry->dep_addr = &((*b.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);

  return b;
}
TEST_F(test_gradcalc, funnel_async)
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

  dvariable f, a, b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 2);

  a = async_compute_a(x, y);
  b = async_compute_b(x, y);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 8);

  f = a + b;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 60.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 10);

  dvector g(-1, 0);
  gradcalc(2, g);
  ASSERT_DOUBLE_EQ(g(-1), 10.0);
  ASSERT_DOUBLE_EQ(g(0), 30.0);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);
}
