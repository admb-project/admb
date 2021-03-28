#include <gtest/gtest.h>
#include <admodel.h>
#include <df1b2fun.h>

class test_laplace_approximation_calculator: public ::testing::Test
{
public:
  virtual void SetUp()
  {
    TearDown();
  }
  virtual void TearDown()
  {
    if (df1b2variable::pool)
    {
      delete df1b2variable::pool;
      df1b2variable::pool = NULL;
    }
    if (f1b2gradlist)
    {
      delete f1b2gradlist;
      f1b2gradlist = NULL;
    }
    if (initial_df1b2params::varsptr)
    {
      delete initial_df1b2params::varsptr;
      initial_df1b2params::varsptr = NULL;
    }
    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 0;
  }
};
class myfunction_minimizer: public function_minimizer
{
public:
  void userfunction() {}
};

TEST_F(test_laplace_approximation_calculator, default_constructor)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  df1b2variable::pool = new adpool();
  {
    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 0;
    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
