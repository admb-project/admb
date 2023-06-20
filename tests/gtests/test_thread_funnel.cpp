#include <chrono>
#include <gtest/gtest.h>
#include <fvar.hpp>
#include <thread_funnel5.h>

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
TEST_F(test_thread_funnel, nvarcalc)
{
  gradient_structure gs;

  dvariable a;
  dvariable b;
  dvariable c;

  EXPECT_EQ(3, nvarcalc(a, 0, 3, 4, b, -1, 0.0, 'a', c, "AAAA"));
}
TEST_F(test_thread_funnel, xinit)
{
  gradient_structure gs;

  dvariable a;
  a = 4.5;
  dvariable b;
  b = 1.2;
  dvariable c;
  c = -0.5;

  int nvar = nvarcalc(a, 0, 3, 4, b, -1, 0.0, 'a', c, "AAAA");

  independent_variables independents(1, nvar);
  independents.initialize();

  xinit(independents, a, 0, 3, 4, b, -1, 0.0, 'a', c, "AAAA");

  EXPECT_DOUBLE_EQ(independents[1], 4.5);
  EXPECT_DOUBLE_EQ(independents[2], 1.2);
  EXPECT_DOUBLE_EQ(independents[3], -0.5);
}
TEST_F(test_thread_funnel, thread_xinit)
{
  auto a = std::async([]()
  {
  gradient_structure gs;

  dvariable a;
  a = 4.5;
  dvariable b;
  b = 1.2;
  dvariable c;
  c = -0.5;

  int nvar = nvarcalc(a, 0, 3, 4, b, -1, 0.0, 'a', c, "AAAA");

  independent_variables independents(1, nvar);
  independents.initialize();

  xinit(independents, a, 0, 3, 4, b, -1, 0.0, 'a', c, "AAAA");

  EXPECT_DOUBLE_EQ(independents[1], 4.5);
  EXPECT_DOUBLE_EQ(independents[2], 1.2);
  EXPECT_DOUBLE_EQ(independents[3], -0.5);
  });
  a.wait();
}
TEST_F(test_thread_funnel, thread_xinit_10)
{
  unsigned int id = gradient_structure::id;
  for (int i = 1; i <= 10; ++i)
  {
    //Capturing 'i' is bad because it changes when lambda function
    //accesses instance.  Here it does not matter.  Since async 'a'
    //will wait at the end of the loop, lambda will be executed 
    //sequentially instead of in parallel. 
    auto a = std::async([&id, &i]()
    {
      gradient_structure gs;
      EXPECT_EQ(id + i, gradient_structure::id);

      dvariable a;
      a = 4.5;
      dvariable b;
      b = 1.2;
      dvariable c;
      c = -0.5;

      int nvar = nvarcalc(a, 0, 3, 4, b, -1, 0.0, 'a', c, "AAAA");

      independent_variables independents(1, nvar);
      independents.initialize();

      xinit(independents, a, 0, 3, 4, b, -1, 0.0, 'a', c, "AAAA");

      EXPECT_DOUBLE_EQ(independents[1], 4.5);
      EXPECT_DOUBLE_EQ(independents[2], 1.2);
      EXPECT_DOUBLE_EQ(independents[3], -0.5);
    });
    a.wait();
  }
}
TEST_F(test_thread_funnel, test_arr_list)
{
  gradient_structure gs;
  gs.ARR_LIST1->arr_new(1);
}
TEST_F(test_thread_funnel, test_arr_list2)
{
  gradient_structure* gs = new gradient_structure();
  gs->ARR_LIST1->arr_new(1);
  delete gs;
  gs = nullptr;
}
TEST_F(test_thread_funnel, pool)
{
  using namespace std::chrono_literals;

  unsigned int id = gradient_structure::id;

  gradient_structure** gradients = new gradient_structure*[10];
  for (int i = 0; i < 10; ++i)
  {
    gradients[i] = new gradient_structure();
  }
  EXPECT_EQ(id + 10, gradient_structure::id);

  std::vector<std::future<double>> futures;

  for (int i = 0; i < 10; ++i)
  {
    // Use function parameter to copy memory for the thread 
    auto f = std::async([&gradients](const int i)
    {
      gradient_structure* gs = gradients[i];
      gradient_structure::_instance = gs;
      gradient_structure::fp = gs->get_fp();
      gradient_structure::GRAD_STACK1 = gs->get_GRAD_STACK1();

      independent_variables independents(1, 1);

      independents[1] = 0.5;

      dvar_vector variables(independents);

      dvariable result = i * variables[1];

      dvector g(1, 1);

      gradcalc(1, g);

      std::this_thread::sleep_for((std::rand() % 5) * 1000ms);

      return g(1);
    }, i);
    //f.wait();
    futures.emplace_back(std::move(f));
  }

  int index = 0;
  for (auto& f : futures)
  {
    ASSERT_EQ((int)f.get(), index);
    ++index;
  }

  delete [] gradients;
  gradients = nullptr;
}
