#include <gtest/gtest.h>
#include <admodel.h>
#include <contrib.h>
#include <df1b2fun.h>
#include <adrndeff.h>
#include "scalefactor.htp"

extern "C"  {
  void ad_boundf(int i);
}
extern long int arrmblsize;

class test_scalefactor: public ::testing::Test {};

TEST_F(test_scalefactor, run)
{
  int scalefactor(int argc, char* argv[]);
  //scalefactor(argc, argv);
}

TEST_F(test_scalefactor, run2)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
#if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__)  || defined(__MSVC32__)
  if (!arrmblsize) arrmblsize=150000;
#else
  if (!arrmblsize) arrmblsize=25000;
#endif
  int argc = 1;
  char* argv[] = { (char*)"./scalefactor" };

  df1b2variable::noallocate=1;
  df1b2_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;

  function_minimizer::random_effects_flag=1;
  df1b2variable::noallocate=0;
  mp.preliminary_calculations();
  mp.userfunction();

  //mp.computations(argc,argv);
}
