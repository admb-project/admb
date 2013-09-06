#include <gtest/gtest.h>
#include <fvar.hpp>

class tests_msimple: public ::testing::Test {};

#define main msimple_main
#include "msimple.cpp"

extern "C" {
  void test_ad_boundf(int i)
  {
    throw i;
  }
}
TEST_F(tests_msimple, msimple_main_cleanups)
{
  int argc = 1;
  char* argv[] = {"msimple"};
  msimple_main(argc, argv);
  ad_set_new_handler();
  ad_exit=&test_ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;
  try
  {
    initial_params::varsptr.reinitialize();
    model_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;
    //mp.preliminary_calculations();
    //mp.computations(argc,argv);
    initial_params::nvarcalc();
  } 
  catch (int i)
  {
    FAIL();
  }
}
TEST_F(tests_msimple, msimple_main)
{
  int argc = 1;
  char* argv[] = {"msimple"};
  initial_params::varsptr.reinitialize();
  ASSERT_EQ(0, initial_params::varsptr[0]);
  ASSERT_EQ(0, initial_params::varsptr[1]);

  msimple_main(argc, argv);
}
TEST_F(tests_msimple, msimple_main_test_for_cleanups_files)
{
  int argc = 1;
  char* argv[] = {"msimple"};
  initial_params::varsptr.reinitialize();
  msimple_main(argc, argv);
  initial_params::varsptr.reinitialize();
  msimple_main(argc, argv);
}
TEST_F(tests_msimple, msimple_main_contents)
{
  int argc = 1;
  char* argv[] = {"msimple"};
  //msimple_main(argc, argv);
  ad_set_new_handler();
  ad_exit=&test_ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;
  try
  {
    initial_params::varsptr.reinitialize();
    model_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;
    mp.preliminary_calculations();
    mp.computations(argc,argv);
  } 
  catch (int i)
  {
    FAIL();
  }
}
TEST_F(tests_msimple, msimple_main_model_parameters)
{
  int argc = 1;
  char* argv[] = {"msimple"};
  ad_set_new_handler();
  ad_exit=&test_ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;
  try
  {
    initial_params::varsptr.reinitialize();
    model_parameters mp(arrmblsize,argc,argv);
  } 
  catch (int i)
  {
    FAIL();
  }
}
class test_named_dvar_vector: public named_dvar_vector 
{ 
public:
  void allocate()
  {
    int nthread = 1;
    named_dvar_vector::allocate(1, nthread, "ff");
  }
};
TEST_F(tests_msimple, msimple_param_vector_nogradient_structure_in_scope)
{
  test_named_dvar_vector ff;
  try
  {
    ff.allocate();
  } 
  catch (int i)
  {
    //Expect exception
    return;
  }
  FAIL();
}
class test_ad_comm: public ad_comm
{ 
public:
  test_ad_comm(int argc, char* argv[]): ad_comm(argc, argv)
  {
  }
};
TEST_F(tests_msimple, msimple_param_vector)
{
  gradient_structure gs(150000L);
  int argc = 1;
  char* argv[] = {"msimple"};
  test_ad_comm ad(argc, argv);
  test_named_dvar_vector ff;
}
TEST_F(tests_msimple, msimple_new_arr_link)
{
  arr_link p;
}
TEST_F(tests_msimple, msimple_param_vector_allocate)
{
  gradient_structure gs(150000L);
  int argc = 1;
  char* argv[] = {"msimple"};
  test_ad_comm ad(argc, argv);
  test_named_dvar_vector ff;
  try
  {
    ff.allocate();
  } 
  catch (int i)
  {
    FAIL();
  }
}
