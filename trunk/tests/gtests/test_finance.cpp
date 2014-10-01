#include <gtest/gtest.h>
#include <df1b2fun.h>

class test_finance: public ::testing::Test {};

TEST_F(test_finance, hess_determinant)
{
  adpool* save = df1b2variable::pool;
  df1b2variable::pool = 0;
  {
    adpool pool;
    df1b2variable::pool = &pool;

    int argc = 1;
    char* argv[] = { (char*)"./finance" };

    int finance(int argc, char* argv[]);
    finance(argc, argv);

    extern double global_hess_determinant;
    ASSERT_DOUBLE_EQ(43.839847514172448, global_hess_determinant);

    df1b2variable::pool = 0;
  }
  df1b2variable::pool = save;
}
