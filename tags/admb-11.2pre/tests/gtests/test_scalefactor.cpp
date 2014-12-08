#include <gtest/gtest.h>
#include <df1b2fun.h>

class test_scalefactor: public ::testing::Test {};

TEST_F(test_scalefactor, run)
{
  adpool* save = df1b2variable::pool;
  df1b2variable::pool = 0;
  {
    adpool pool;
    df1b2variable::pool = &pool;

    int argc = 1;
    char* argv[] = { (char*)"./scalefactor" };

    int scalefactor(int argc, char* argv[]);
    scalefactor(argc, argv);

    df1b2variable::pool = 0;
  }
  df1b2variable::pool = save;
}
