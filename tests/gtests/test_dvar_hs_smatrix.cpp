#include <gtest/gtest.h>
#include <fvar.hpp>
#define XCONST const
#include <hs.h>

class test_dvar_hs_smatrix: public ::testing::Test {};

TEST_F(test_dvar_hs_smatrix, default_constructor)
{
  gradient_structure gs;
  dvar_hs_smatrix data(4, 4);

  //data.print();
  //data.print_pattern();
  //data.trace_log();
  //data.print_trans_zeros();
}
