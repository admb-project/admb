#include <gtest/gtest.h>
#include <fvar.hpp>

class test_rvalue: public ::testing::Test {};

class derived: public prevariable
{
public:
  derived(): prevariable() {}
  derived(const derived& other): prevariable(new double_and_int)
  {
    v->x = other.v->x;
  }
  derived(const derived&& other): prevariable(std::move(other)) {}
  derived(const double value): prevariable(new double_and_int)
  {
    v->x = value;
  }
  virtual ~derived()
  {
    if (v)
    {
      delete v;
      v = NULL;
    }
  }
  derived& operator=(const derived& other)
  {
    if (v == NULL)
    {
      v = new double_and_int;
    }
    v->x = other.v->x;
    return *this;
  }
  derived& operator=(const derived&& other)
  {
    v = other.v;
    const_cast<derived&>(other).v = NULL;
    return *this;
  }
};
TEST_F(test_rvalue, default_constructor)
{
  derived d;
  ASSERT_TRUE(d.v == NULL);
}
TEST_F(test_rvalue, rvalue_constructor)
{
  derived a(3.5);
  ASSERT_EQ(a.v->x, 3.5);
  derived b(a);
  ASSERT_EQ(b.v->x, 3.5);
  ASSERT_TRUE(a.v != b.v);
  double_and_int* ptr = a.v;
  derived c(std::move(a));;
  ASSERT_TRUE(a.v == NULL);
  ASSERT_TRUE(c.v == ptr);
  ASSERT_EQ(c.v->x, 3.5);
}
TEST_F(test_rvalue, rvalue_assignment)
{
  derived a(3.5);
  ASSERT_EQ(a.v->x, 3.5);
  derived b;
  b = a;
  ASSERT_EQ(b.v->x, 3.5);
  ASSERT_TRUE(a.v != b.v);
  double_and_int* ptr = a.v;
  derived c;
  c = std::move(a);
  ASSERT_TRUE(a.v == NULL);
  ASSERT_TRUE(c.v == ptr);
  ASSERT_EQ(c.v->x, 3.5);
}
