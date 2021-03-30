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

  ASSERT_EQ(laplace_approximation_calculator::saddlepointflag, 0);
  ASSERT_EQ(laplace_approximation_calculator::alternative_user_function_flag, 0);
  ASSERT_EQ(laplace_approximation_calculator::sparse_hessian_flag, 0);
  ASSERT_EQ(laplace_approximation_calculator::antiflag, 0);
  ASSERT_EQ(laplace_approximation_calculator::print_importance_sampling_weights_flag, 0);
  ASSERT_TRUE(laplace_approximation_calculator::variance_components_vector == nullptr);
  ASSERT_EQ(laplace_approximation_calculator::where_are_we_flag, 0);

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
    ASSERT_TRUE(lac.antiepsilon == nullptr);
    ASSERT_TRUE(lac.triplet_information == nullptr);
    ASSERT_TRUE(lac.compressed_triplet_information == nullptr);
    ASSERT_TRUE(lac.calling_set == nullptr);
    ASSERT_TRUE(lac.importance_sampling_values == nullptr);
    ASSERT_TRUE(lac.importance_sampling_weights == nullptr);
    ASSERT_TRUE(lac.num_local_re_array == nullptr);
    ASSERT_TRUE(lac.num_local_fixed_array == nullptr);
    ASSERT_TRUE(lac.separable_function_difference == nullptr);
    ASSERT_TRUE(lac.gh == nullptr);
    ASSERT_TRUE(lac.importance_sampling_components == nullptr);
    ASSERT_TRUE(lac.block_diagonal_hessian == nullptr);
    ASSERT_TRUE(lac.block_diagonal_ch == nullptr);
    ASSERT_TRUE(lac.block_diagonal_vch == nullptr);
    ASSERT_TRUE(lac.block_diagonal_Dux == nullptr);
    ASSERT_TRUE(lac.block_diagonal_re_list == nullptr);
    ASSERT_TRUE(lac.block_diagonal_fe_list == nullptr);
    ASSERT_TRUE(lac.block_diagonal_vhessianadjoint == nullptr);
    ASSERT_TRUE(lac.block_diagonal_vhessian == nullptr);
    ASSERT_TRUE(lac.bHess == nullptr);
    ASSERT_TRUE(lac.bHessadjoint == nullptr);
    ASSERT_TRUE(lac.sparse_triplet == nullptr);
    ASSERT_TRUE(lac.sparse_iterator == nullptr);
    ASSERT_TRUE(lac.sparse_triplet2 == nullptr);
    ASSERT_TRUE(lac.vsparse_triplet == nullptr);
    ASSERT_TRUE(lac.vsparse_triplet_adjoint == nullptr);
    ASSERT_TRUE(lac.sparse_symbolic == nullptr);
    ASSERT_TRUE(lac.sparse_symbolic2 == nullptr);
    ASSERT_TRUE(lac.grad_x_u == nullptr);
    ASSERT_TRUE(lac.grad_x == nullptr);
    ASSERT_TRUE(lac.Hess_components == nullptr);
    ASSERT_TRUE(lac.pHess_non_quadprior_part == nullptr);
    ASSERT_TRUE(lac.derindex == nullptr);
    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  ASSERT_EQ(laplace_approximation_calculator::saddlepointflag, 0);
  ASSERT_EQ(laplace_approximation_calculator::alternative_user_function_flag, 0);
  ASSERT_EQ(laplace_approximation_calculator::sparse_hessian_flag, 0);
  ASSERT_EQ(laplace_approximation_calculator::antiflag, 0);
  ASSERT_EQ(laplace_approximation_calculator::print_importance_sampling_weights_flag, 0);
  ASSERT_TRUE(laplace_approximation_calculator::variance_components_vector == nullptr);
  ASSERT_EQ(laplace_approximation_calculator::where_are_we_flag, 0);
}
TEST_F(test_laplace_approximation_calculator, default_constructor2)
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
    ASSERT_TRUE(lac.antiepsilon == nullptr);
    ASSERT_TRUE(lac.triplet_information == nullptr);
    ASSERT_TRUE(lac.compressed_triplet_information == nullptr);
    ASSERT_TRUE(lac.calling_set == nullptr);
    ASSERT_TRUE(lac.importance_sampling_values == nullptr);
    ASSERT_TRUE(lac.importance_sampling_weights == nullptr);
    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, default_constructor3)
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
    ASSERT_TRUE(lac.antiepsilon == nullptr);
    ASSERT_TRUE(lac.triplet_information == nullptr);
    ASSERT_TRUE(lac.compressed_triplet_information == nullptr);
    ASSERT_TRUE(lac.calling_set == nullptr);
    ASSERT_TRUE(lac.importance_sampling_values == nullptr);
    ASSERT_TRUE(lac.importance_sampling_weights == nullptr);
    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, deallocate_then_check_pool_size)
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

    ASSERT_TRUE(df1b2variable::pool != NULL);
    lac.check_pool_size();
    ASSERT_TRUE(df1b2variable::pool != NULL);
     
    delete pmin;
    pmin = nullptr;
  }
  df1b2variable::pool->deallocate();
  delete df1b2variable::pool;
  df1b2variable::pool = nullptr;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, check_sparse_matrix_structure)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  ASSERT_EQ(laplace_approximation_calculator::saddlepointflag, 0);
  ASSERT_EQ(laplace_approximation_calculator::alternative_user_function_flag, 0);
  ASSERT_EQ(laplace_approximation_calculator::sparse_hessian_flag, 0);
  ASSERT_EQ(laplace_approximation_calculator::antiflag, 0);
  ASSERT_EQ(laplace_approximation_calculator::print_importance_sampling_weights_flag, 0);
  ASSERT_TRUE(laplace_approximation_calculator::variance_components_vector == nullptr);
  ASSERT_EQ(laplace_approximation_calculator::where_are_we_flag, 0);

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

    lac.derindex = new imatrix(1, 1000);
    lac.check_sparse_matrix_structure();
    delete lac.derindex;
    lac.derindex = nullptr;

    delete pmin;
    pmin = nullptr;
  }

  df1b2variable::pool->deallocate();
  delete df1b2variable::pool;
  df1b2variable::pool = nullptr;
     
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
