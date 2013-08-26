#include <gtest/gtest.h>
#include <fvar.hpp>

class tests_msimple: public ::testing::Test {};

#define main msimple_main
#include "msimple.cpp"

TEST_F(tests_msimple, msimple_main)
{
  int argc = 1;
  char* argv[] = {"msimple"};
  msimple_main(argc, argv);
}
