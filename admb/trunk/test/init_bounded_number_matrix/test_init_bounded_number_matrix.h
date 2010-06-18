#include <gtest/gtest.h>

#include <admodel.h>
#include <init_bounded_number_matrix.htp>

class test_init_bounded_number_matrix: public ::testing::Test {};

TEST_F(test_init_bounded_number_matrix, test1)
{
  FAIL();
}
TEST_F(test_init_bounded_number_matrix, test2)
{
  SUCCEED();
}

extern "C"  {
  void ad_boundf(int i);
}

long int arrmblsize=0;

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  #if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__)  || defined(__MSVC32__)
      if (!arrmblsize) arrmblsize=150000;
  #else
      if (!arrmblsize) arrmblsize=25000;
  #endif

  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.computations(argc,argv);

  std::cout << std::endl;

  return RUN_ALL_TESTS();
}

#define main tplmain
#define arrmblsize tplarrmblsize
