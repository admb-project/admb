#include <gtest/gtest.h>
#include <fvar.hpp>
#include <future>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_funnels: public ::testing::Test {};

TEST_F(test_funnels, simple)
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

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  dvar_vector yhat(1, 10);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  yhat = variables(1) + variables(2) * x;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);

  dvariable f = 0.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);

  funnel_dvariable Integral;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);

  ad_begin_funnel();

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 5);

  dvariable tmp;
  tmp = regression(y,yhat);

  ASSERT_TRUE(gradient_structure::GRAD_STACK1->total() >= 13);

  Integral = tmp;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 5);

  f = Integral;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 6);

  double result = value(f);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_DOUBLE_EQ(result, 24.980653039466869);
  ASSERT_DOUBLE_EQ(g(1), -0.7278138528138528);
  ASSERT_DOUBLE_EQ(g(2), -3.6126893939393945);
}
dvariable async_a(dvariable& x, dvariable& y)
{
  dvariable a(17.0);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  gradient_structure::GRAD_STACK1->ptr++;

  std::future<dvector> gradients =
    std::async([]()
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
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);

  return a;
}
dvariable async_b(dvariable& x, dvariable& y)
{
  dvariable b(43.0);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  gradient_structure::GRAD_STACK1->ptr++;

  std::future<dvector> gradients =
    std::async([]()
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
TEST_F(test_funnels, async_gradcalc)
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

  a = async_a(x, y);
  b = async_b(x, y);

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
dvariable async2_a(dvariable& x, dvariable& y)
{
  dvariable a(17.0);

  grad_stack* stack = gradient_structure::GRAD_STACK1;
  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  gradient_structure::GRAD_STACK1->ptr++;

  std::future<dvector> gradients =
    std::async([]()
    {
      gradient_structure::GRAD_STACK1 = new grad_stack();

      int random = std::rand() % 5;
      std::this_thread::sleep_for(std::chrono::seconds(random));

      delete gradient_structure::GRAD_STACK1;
      gradient_structure::GRAD_STACK1 = nullptr;

      dvector g(1, 2);
      g(1) = 2.0;
      g(2) = 3.0;
      return g;
    });
  dvector g = gradients.get();

  gradient_structure::GRAD_STACK1 = stack;

  entry->func = default_evaluation;
  entry->dep_addr = &((*a.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);

  return a;
}
dvariable async2_b(dvariable& x, dvariable& y)
{
  dvariable b(43.0);

  grad_stack* stack = gradient_structure::GRAD_STACK1;
  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  gradient_structure::GRAD_STACK1->ptr++;

  std::future<dvector> gradients =
    std::async([]()
    {
      gradient_structure::GRAD_STACK1 = new grad_stack();

      int random = std::rand() % 5;
      std::this_thread::sleep_for(std::chrono::seconds(random));

      delete gradient_structure::GRAD_STACK1;
      gradient_structure::GRAD_STACK1 = nullptr;

      dvector g(1, 2);
      g(1) = 8.0;
      g(2) = 27.0;
      return g;
    });
  dvector g = gradients.get();

  gradient_structure::GRAD_STACK1 = stack;

  entry->func = default_evaluation;
  entry->dep_addr = &((*b.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);

  return b;
}
TEST_F(test_funnels, async2)
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

  a = async2_a(x, y);
  b = async2_b(x, y);

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
dvariable async3_a(dvariable& x, dvariable& y)
{
  dvariable a(17.0);

  grad_stack* stack = gradient_structure::GRAD_STACK1;
  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  gradient_structure::GRAD_STACK1->ptr++;

  std::future<dvector> gradients =
    std::async([](const double value_x, const double value_y)
    {
      dvector g(1, 2);

      gradient_structure::GRAD_STACK1 = new grad_stack();
      gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
      {
        int random = std::rand() % 5;
        std::this_thread::sleep_for(std::chrono::seconds(random));

        independent_variables independents(1, 2);
        independents(1) = value_x;
        independents(2) = value_y;
        dvar_vector variables(independents);

        dvariable a;
        dvariable x = variables(1);
        dvariable y = variables(2);

        a = 2.0 * x + 3.0 * y;

        double v = value(a);

        gradcalc(2, g);
      }
      delete gradient_structure::GRAD_STACK1;
      gradient_structure::GRAD_STACK1 = nullptr;

      return g;
    }, value(x), value(y));
  dvector g = gradients.get();

  gradient_structure::GRAD_STACK1 = stack;

  entry->func = default_evaluation;
  entry->dep_addr = &((*a.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);

  return a;
}
dvariable async3_b(dvariable& x, dvariable& y)
{
  dvariable b(43.0);

  grad_stack* stack = gradient_structure::GRAD_STACK1;
  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  gradient_structure::GRAD_STACK1->ptr++;

  std::future<dvector> gradients =
    std::async([](const double value_x, const double value_y)
    {
      dvector g(1, 2);

      gradient_structure::GRAD_STACK1 = new grad_stack();
      gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
      {
        int random = std::rand() % 5;
        std::this_thread::sleep_for(std::chrono::seconds(random));

        independent_variables independents(1, 2);
        independents(1) = value_x;
        independents(2) = value_y;
        dvar_vector variables(independents);

        dvariable b;
        dvariable x = variables(1);
        dvariable y = variables(2);

        b = (pow(x, 2.0) + pow(y, 3.0));

        double v = value(b);

        gradcalc(2, g);
      }
      delete gradient_structure::GRAD_STACK1;
      gradient_structure::GRAD_STACK1 = nullptr;

      return g;
    }, value(x), value(y));
  dvector g = gradients.get();

  gradient_structure::GRAD_STACK1 = stack;

  entry->func = default_evaluation;
  entry->dep_addr = &((*b.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);

  return b;
}
TEST_F(test_funnels, async3)
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

  a = async3_a(x, y);
  b = async3_b(x, y);

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
TEST_F(test_funnels, arr_list)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  grad_stack* stack = gradient_structure::GRAD_STACK1;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);
  {
    gradient_structure::GRAD_STACK1 = new grad_stack();
    {
    independent_variables scoped_independents(1, 2);
    scoped_independents(1) = 4.0;
    scoped_independents(2) = 3.0;

    ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

    // Set gradient_structure::NVAR
    dvar_vector scoped_variables(scoped_independents);
    }
    delete gradient_structure::GRAD_STACK1;
    gradient_structure::GRAD_STACK1 = nullptr;
  }

  gradient_structure::GRAD_STACK1 = stack;
}
TEST_F(test_funnels, async_arr_list)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  grad_stack* stack = gradient_structure::GRAD_STACK1;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  std::async([]()
  {
    gradient_structure::GRAD_STACK1 = new grad_stack();
    {
      independent_variables scoped_independents(1, 2);
      scoped_independents(1) = 4.0;
      scoped_independents(2) = 3.0;

      ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

      // Set gradient_structure::NVAR
      dvar_vector scoped_variables(scoped_independents);
    }
    delete gradient_structure::GRAD_STACK1;
    gradient_structure::GRAD_STACK1 = nullptr;
  });

  gradient_structure::GRAD_STACK1 = stack;
}
TEST_F(test_funnels, async_gradcalc2)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  grad_stack* stack = gradient_structure::GRAD_STACK1;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  std::async([]()
  {
    dvector g(1, 2);

    gradient_structure::GRAD_STACK1 = new grad_stack(10000, 10);
    gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
    {
      independent_variables scoped_independents(1, 2);
      scoped_independents(1) = 4.0;
      scoped_independents(2) = 3.0;

      ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

      // Set gradient_structure::NVAR
      dvar_vector scoped_variables(scoped_independents);

      dvariable f(0);

      dvariable a = scoped_variables(1);
      dvariable b = scoped_variables(2);

      f = 4.0 * a + 3.0 * b;

      double v = value(f);

      gradcalc(2, g);
    }
    delete gradient_structure::GRAD_STACK1;
    gradient_structure::GRAD_STACK1 = nullptr;

    ASSERT_DOUBLE_EQ(g(1), 4.0);
    ASSERT_DOUBLE_EQ(g(2), 3.0);
  });

  gradient_structure::GRAD_STACK1 = stack;
}
