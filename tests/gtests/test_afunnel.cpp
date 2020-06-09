#include <gtest/gtest.h>
#include <fvar.hpp>
#include <future>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_afunnel: public ::testing::Test {};

TEST_F(test_afunnel, future)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  grad_stack* gstack = gradient_structure::GRAD_STACK1;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  std::future<std::pair<double, dvector>> ret = 
    std::async([]()->std::pair<double, dvector>
    {
      double v = 0;
      dvector g(1, 2);

      gradient_structure::GRAD_STACK1 = new grad_stack(10000, 10);
      gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
      {
        independent_variables scoped_independents(1, 2);
        scoped_independents(1) = 4.0;
        scoped_independents(2) = 3.0;

        // Set gradient_structure::NVAR
        dvar_vector scoped_variables(scoped_independents);

        dvariable f(0);

        dvariable a = scoped_variables(1);
        dvariable b = scoped_variables(2);

        f = 4.0 * a + 3.0 * b;

        v = value(f);

        gradcalc(2, g);
      }
      gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
      delete gradient_structure::GRAD_STACK1;
      gradient_structure::GRAD_STACK1 = nullptr;

      return std::make_pair(v, g);;
    });

  std::pair<double, dvector> p = ret.get();
  ASSERT_DOUBLE_EQ(p.first, 25.0);
  ASSERT_DOUBLE_EQ(p.second(1), 4.0);
  ASSERT_DOUBLE_EQ(p.second(2), 3.0);

  ASSERT_TRUE(gstack == gradient_structure::GRAD_STACK1);
}
dvariable start_afunnel(dvariable& x, dvariable& y)
{
  std::future<std::pair<double, dvector>> ret = 
    std::async([]()->std::pair<double, dvector>
    {
      double v = 0;
      dvector g(1, 2);

      gradient_structure::GRAD_STACK1 = new grad_stack(10000, 10);
      gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
      {
        independent_variables scoped_independents(1, 2);
        scoped_independents(1) = 4.0;
        scoped_independents(2) = 3.0;

        // Set gradient_structure::NVAR
        dvar_vector scoped_variables(scoped_independents);

        dvariable f(0);

        dvariable a = scoped_variables(1);
        dvariable b = scoped_variables(2);

        f = 4.0 * a + 3.0 * b;

        v = value(f);

        gradcalc(2, g);
      }
      gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
      delete gradient_structure::GRAD_STACK1;
      gradient_structure::GRAD_STACK1 = nullptr;

      return std::make_pair(v, g);;
    });

  std::pair<double, dvector> p = ret.get();

  dvariable result(p.first);;
  dvector g(p.second);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  entry->func = default_evaluation;
  entry->dep_addr = &((*result.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);

  gradient_structure::GRAD_STACK1->ptr++;

  return result;
}
TEST_F(test_afunnel, start_afunnel)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  grad_stack* gstack = gradient_structure::GRAD_STACK1;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable ret;

  dvariable x = variables(1);
  dvariable y = variables(2);

  ret = start_afunnel(x, y);

  ASSERT_DOUBLE_EQ(value(ret), 25.0);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_DOUBLE_EQ(g(1), 4.0);
  ASSERT_DOUBLE_EQ(g(2), 3.0);

  ASSERT_TRUE(gstack == gradient_structure::GRAD_STACK1);
}
dvariable lambda_afunnel(
  dvariable (*func)(dvariable& x, dvariable& y),
  dvariable& x, dvariable& y)
{
  std::future<std::pair<double, dvector>> ret = 
    std::async([=]()->std::pair<double, dvector>
    {
      double v = 0;
      dvector g(1, 2);

      gradient_structure::GRAD_STACK1 = new grad_stack(10000, 10);
      gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
      {
        independent_variables scoped_independents(1, 2);
        scoped_independents(1) = value(x);
        scoped_independents(2) = value(y);

        // Set gradient_structure::NVAR
        dvar_vector scoped_variables(scoped_independents);

        dvariable f(0);

        dvariable a = scoped_variables(1);
        dvariable b = scoped_variables(2);

        f = func(a, b);

        v = value(f);

        gradcalc(2, g);
      }
      gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
      delete gradient_structure::GRAD_STACK1;
      gradient_structure::GRAD_STACK1 = nullptr;

      return std::make_pair(v, g);
    });

  std::pair<double, dvector> p = ret.get();

  dvariable result(p.first);
  dvector g(p.second);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  entry->func = default_evaluation;
  entry->dep_addr = &((*result.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);

  gradient_structure::GRAD_STACK1->ptr++;

  return result;
}
TEST_F(test_afunnel, lambda_afunnel)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  grad_stack* gstack = gradient_structure::GRAD_STACK1;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable ret;

  dvariable x = variables(1);
  dvariable y = variables(2);

  ret = lambda_afunnel([](dvariable& x, dvariable& y)
  {
    dvariable result;
    result = 4.0 * x + 3.0 * y;
    return result;
  }, x, y);

  ASSERT_DOUBLE_EQ(value(ret), 25.0);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_DOUBLE_EQ(g(1), 4.0);
  ASSERT_DOUBLE_EQ(g(2), 3.0);

  ASSERT_TRUE(gstack == gradient_structure::GRAD_STACK1);
}
TEST_F(test_afunnel, lambda_afunnel_2x)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 2);
  independents(1) = 4.0;
  independents(2) = 3.0;

  grad_stack* gstack = gradient_structure::GRAD_STACK1;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvariable f, a, b;

  dvariable x = variables(1);
  dvariable y = variables(2);

  a = lambda_afunnel([](dvariable& x, dvariable& y)
  {
    dvariable result;
    result = 2.0 * x + 3.0 * y;
    return result;
  }, x, y);
  b = lambda_afunnel([](dvariable& x, dvariable& y)
  {
    dvariable result;
    result = (pow(x, 2.0) + pow(y, 3.0));
    return result;
  }, x, y);

  f = a + b;

  ASSERT_DOUBLE_EQ(value(f), 60.0);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_DOUBLE_EQ(g(1), 10.0);
  ASSERT_DOUBLE_EQ(g(2), 30.0);

  ASSERT_TRUE(gstack == gradient_structure::GRAD_STACK1);
}
