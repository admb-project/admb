#include <gtest/gtest.h>

class test_adstring: public ::testing::Test {};
class test_fmm_control: public ::testing::Test {};

#include <fvar.hpp>
#include <adstring.hpp>
#include "test_adstring_strcase.cpp"
#include "test_fmm_control.cpp"

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
