#include <gtest/gtest.h>
#include <fvar.hpp>
#include "thread_funnel5.h"

class test_thread_funnel: public ::testing::Test {};


int Ai = 0;
struct A
{
  A()
  {
    Ai = -1;
  }
  A(const A&)
  {
    Ai = 1;
  }
};
TEST_F(test_thread_funnel, lambda_capture)
{
  Ai = 0;
  A a;
  Ai = 0;
  auto f = [=, &a]()
  {
    const A* p = &a;
    EXPECT_EQ(Ai, 0);
  };
  EXPECT_EQ(Ai, 1);

  Ai = 0;
  f();
  EXPECT_EQ(Ai, 0);
  Ai = 0;
}
TEST_F(test_thread_funnel, set_independent_variables_A)
{
  independent_variables independents(1, 4);
  independents.initialize();

  Ai = 0;
  int index = set_independent_variables(independents, A());
  EXPECT_EQ(index, 1);
  EXPECT_EQ(Ai, -1);
  Ai = 0;

  gradient_structure gs;
  dvariable v(4.5);
  EXPECT_DOUBLE_EQ(independents[1], 0.0);
  index = set_independent_variables(independents, v);
  EXPECT_EQ(index, 2);
  EXPECT_DOUBLE_EQ(independents[1], 4.5);
  Ai = 0;
}
TEST_F(test_thread_funnel, get_addresses_A)
{
  std::vector<double*> addresses;
  get_addresses(addresses, A());
  EXPECT_EQ(addresses.size(), 0);
  EXPECT_EQ(Ai, -1);
  addresses.clear();

  Ai = 0;

  A a;
  get_addresses(addresses, a);
  EXPECT_EQ(addresses.size(), 0);
  EXPECT_EQ(Ai, -1);
  addresses.clear();

  Ai = 0;
}
TEST_F(test_thread_funnel, get_addresses_int)
{
  std::vector<double*> addresses;

  get_addresses(addresses, 5);
  EXPECT_EQ(addresses.size(), 0);
  addresses.clear();

  get_addresses(addresses, 5);
  EXPECT_EQ(addresses.size(), 0);
  addresses.clear();

  get_addresses(addresses, 5, 0, 4);
  EXPECT_EQ(addresses.size(), 0);
  addresses.clear();
}
TEST_F(test_thread_funnel, get_addresses_dvariable)
{
  std::vector<double*> addresses;

  gradient_structure gs;

  get_addresses(addresses, dvariable());
  EXPECT_EQ(addresses.size(), 1);
  EXPECT_TRUE(addresses[0] != nullptr);
  addresses.clear();

  dvariable v;
  get_addresses(addresses, v);
  EXPECT_EQ(addresses.size(), 1);
  EXPECT_TRUE(addresses[0] != nullptr);
  EXPECT_TRUE(addresses[0] == &((v.v)->x));
  addresses.clear();

  get_addresses(addresses, v, v, 4, v);
  EXPECT_EQ(addresses.size(), 3);
  EXPECT_TRUE(addresses[0] == &((v.v)->x));
  EXPECT_TRUE(addresses[1] == &((v.v)->x));
  EXPECT_TRUE(addresses[2] == &((v.v)->x));
  addresses.clear();
}
