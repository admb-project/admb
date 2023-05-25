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
/*
TEST_F(test_thread_funnel, create_sub_tuple_A)
{
  Ai = 0;
  gradient_structure gs;


  dvar_vector vs(1, 4);
  vs.initialize();

  int index = 1;

  auto t = create_sub_tuple(vs, index, vs[4]); 
}
*/
TEST_F(test_thread_funnel, lambda_capture_reference)
{
  Ai = 0;
  A a;
  Ai = 0;
  auto f = [&a]()
  {
    const A* p = &a;
    EXPECT_EQ(Ai, 0);
  };
  EXPECT_EQ(Ai, 0);

  Ai = 0;
  f();
  EXPECT_EQ(Ai, 0);
  Ai = 0;
}
TEST_F(test_thread_funnel, lambda_capture_copy)
{
  Ai = 0;
  A a;
  Ai = 0;
  auto f = [a]()
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
TEST_F(test_thread_funnel, gradient_structure2x)
{
  DF_FILE::id = 0;
  grad_stack::id = 0;

  gradient_structure gs;
  EXPECT_TRUE(gradient_structure::get() == &gs);
  EXPECT_TRUE(gradient_structure::fp == gs.get_fp());
  EXPECT_TRUE(gradient_structure::GRAD_STACK1 == gs.get_GRAD_STACK1());
  EXPECT_TRUE(DF_FILE::id == 1);
  EXPECT_STREQ(gs.get_fp()->cmpdif_file_name, "cmpdiff1.tmp");
  gs.get_fp()->fwrite(double(4.5));
  EXPECT_TRUE(gs.get_fp()->offset == sizeof(double));
  double v1, v2;
  gs.get_GRAD_STACK1()->set_gradient_stack(default_evaluation0, &v1);
  gs.get_GRAD_STACK1()->set_gradient_stack(default_evaluation0, &v2);
  EXPECT_TRUE(gs.get_GRAD_STACK1()->total() == 2);
  EXPECT_TRUE(grad_stack::id == 1);
  EXPECT_STREQ(gs.get_GRAD_STACK1()->gradfile_name, "gradfil11.tmp");
  EXPECT_STREQ(gs.get_GRAD_STACK1()->gradfile_name1, "gradfil11.tmp");
  EXPECT_STREQ(gs.get_GRAD_STACK1()->gradfile_name2, "gradfil21.tmp");
  EXPECT_STREQ(gs.get_GRAD_STACK1()->var_store_file_name, "varssave1.tmp");

  gradient_structure gs2;
  EXPECT_TRUE(gradient_structure::get() == &gs2);
  EXPECT_TRUE(gradient_structure::fp == gs2.get_fp());
  EXPECT_TRUE(gradient_structure::GRAD_STACK1 == gs2.get_GRAD_STACK1());
  EXPECT_TRUE(DF_FILE::id == 2);
  EXPECT_STREQ(gs2.get_fp()->cmpdif_file_name, "cmpdiff2.tmp");
  gs2.get_fp()->fwrite(int(4));
  EXPECT_TRUE(gs2.get_fp()->offset == sizeof(int));
  EXPECT_TRUE(gs.get_fp()->offset == sizeof(double));
  double v3, v4, v5;
  gs2.get_GRAD_STACK1()->set_gradient_stack(default_evaluation0, &v3);
  gs2.get_GRAD_STACK1()->set_gradient_stack(default_evaluation0, &v4);
  gs2.get_GRAD_STACK1()->set_gradient_stack(default_evaluation0, &v5);
  EXPECT_TRUE(gs2.get_GRAD_STACK1()->total() == 3);
  EXPECT_TRUE(gs.get_GRAD_STACK1()->total() == 2);
  EXPECT_TRUE(grad_stack::id == 2);
  EXPECT_STREQ(gs2.get_GRAD_STACK1()->gradfile_name, "gradfil12.tmp");
  EXPECT_STREQ(gs2.get_GRAD_STACK1()->gradfile_name1, "gradfil12.tmp");
  EXPECT_STREQ(gs2.get_GRAD_STACK1()->gradfile_name2, "gradfil22.tmp");
  EXPECT_STREQ(gs2.get_GRAD_STACK1()->var_store_file_name, "varssave2.tmp");
}
