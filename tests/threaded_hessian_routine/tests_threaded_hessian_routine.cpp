#include <iostream>
#include <thread>
#include <gtest/gtest.h>

#define main simple
#include <simple.cpp>
#undef main

class tests_threaded: public ::testing::Test 
{
protected:
  tests_threaded() {
  }
  virtual ~tests_threaded() {
  }
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

int simple(int argc, char* argv[]);

/*
TEST(tests_threaded, simple)
{
  char* argv[] = { "simple/simple" };
  simple(1, argv);
}

TEST(tests_threaded, simple_computations)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.computations(argc,argv);
}

TEST(tests_threaded, simple_hess_routine)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.hess_routine();
}

TEST(tests_threaded, simple_hess_routine_noparallel)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.hess_routine_noparallel();
}
*/

TEST(tests_threaded, simple_hess_routine_threaded)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.hess_routine_threaded();
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
