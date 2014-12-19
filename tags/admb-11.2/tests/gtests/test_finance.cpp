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
    ASSERT_NEAR(43.839847514172448, global_hess_determinant, 1e-6);

    extern double global_projected_hess_determinant;
    ASSERT_NEAR(28.314961861611934, global_projected_hess_determinant, 1e-6);

    extern double global_projected_hess_determinant_xscale;
    ASSERT_NEAR(42.13010376845299, global_projected_hess_determinant_xscale, 1e-6);

    extern double global_ln_det_proj_jac;
    ASSERT_NEAR(-0.00036865112372874741, global_ln_det_proj_jac, 1e-6);

    df1b2variable::pool = 0;
  }
  df1b2variable::pool = save;
}
