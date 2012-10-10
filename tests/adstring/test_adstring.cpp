#include <gtest/gtest.h>

class test_adstring: public ::testing::Test {};

#include <fvar.hpp>
#include <adstring.hpp>
#include "tools99_strcase.cpp"

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
