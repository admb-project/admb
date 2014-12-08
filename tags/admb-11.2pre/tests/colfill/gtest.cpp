#include <gtest/gtest.h>

class test_colfill: public ::testing::Test {};

#ifndef main
  #define main mymain
#endif
#include "colfill.cpp"
#undef main

TEST_F(test_colfill, run)
{
  int argc = 2;
  char* argv[] = { (char*)"colfill", (char*)"-nohess" };
  mymain(argc, argv);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
