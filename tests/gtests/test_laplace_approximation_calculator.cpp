#include <gtest/gtest.h>
#include <admodel.h>
#include <df1b2fun.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

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
    for (int i=0;i<df1b2variable::adpool_counter;i++)
    {
      delete df1b2variable::adpool_vector[i];
      df1b2variable::adpool_vector[i]=0;
      df1b2variable::nvar_vector[i]=0;
    }
    df1b2variable::adpool_counter=0;
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
    ad_comm::no_ln_det_choleski_flag = 0;
    ad_comm::print_hess_and_exit_flag = 0;
    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 0;
    initial_params::varsptr.initialize();
    initial_df1b2params::num_initial_df1b2params = 0;
    for (int i = 0; i < 100; ++i)
    {
      quadratic_prior::ptr[i] = nullptr;
      df1b2quadratic_prior::ptr[i] = nullptr;
    }
    quadratic_prior::num_quadratic_prior = 0;
    df1b2quadratic_prior::num_quadratic_prior = 0;
    if (gradient_structure::ARR_LIST1)
    {
      delete gradient_structure::ARR_LIST1;
      gradient_structure::ARR_LIST1 = nullptr;
    }
    function_minimizer::first_hessian_flag = 0;
    ad_comm::argc = 0;
    ad_comm::argv = nullptr;
    laplace_approximation_calculator::antiflag = 0;
    df1b2variable::nvar = 0;
  }
};
class myfunction_minimizer: public function_minimizer
{
public:
  myfunction_minimizer(): function_minimizer() {}
  virtual ~myfunction_minimizer() {}

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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
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
    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);
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
    ASSERT_EQ(lac.init_switch, 1);
    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
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
}
TEST_F(test_laplace_approximation_calculator, default_constructor2)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
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
    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_TRUE(lac.antiepsilon == nullptr);
    ASSERT_TRUE(lac.triplet_information == nullptr);
    ASSERT_TRUE(lac.compressed_triplet_information == nullptr);
    ASSERT_TRUE(lac.calling_set == nullptr);
    ASSERT_TRUE(lac.importance_sampling_values == nullptr);
    ASSERT_TRUE(lac.importance_sampling_weights == nullptr);
    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, default_constructor3)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
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
    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_TRUE(lac.antiepsilon == nullptr);
    ASSERT_TRUE(lac.triplet_information == nullptr);
    ASSERT_TRUE(lac.compressed_triplet_information == nullptr);
    ASSERT_TRUE(lac.calling_set == nullptr);
    ASSERT_TRUE(lac.importance_sampling_values == nullptr);
    ASSERT_TRUE(lac.importance_sampling_weights == nullptr);
    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, allocated_pool_for_check_pool_size)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    adpool* expected_pool = df1b2variable::pool;
    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 0;
    int xsize = 1;
    int usize = 1;
    ivector minder(1, 1);
    minder(1) = 1;
    ivector maxder(1, 1);
    maxder(1) = 1;

    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(f1b2gradlist == NULL);
    ASSERT_EQ(df1b2variable::pool->nvar, 0);
    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(df1b2variable::pool->nvar, 1);
    ASSERT_TRUE(f1b2gradlist != NULL);

    ASSERT_TRUE(df1b2variable::pool != NULL);
    ASSERT_EQ(df1b2variable::pool->nvar, 1);
    ASSERT_EQ(lac.nvar, 1);
    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    lac.check_pool_size();
    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    ASSERT_TRUE(df1b2variable::pool != NULL);
    ASSERT_TRUE(df1b2variable::pool == expected_pool);

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, allocated_pool_for_check_pool_size_nvar)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    adpool* expected_pool = df1b2variable::pool;
    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 0;
    int xsize = 1;
    int usize = 1;
    ivector minder(1, 1);
    minder(1) = 1;
    ivector maxder(1, 1);
    maxder(1) = 1;

    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(f1b2gradlist == NULL);
    ASSERT_EQ(df1b2variable::pool->nvar, 0);
    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);
    lac.nvar = 2;
    ASSERT_EQ(lac.nvar, 2);
    ASSERT_EQ(df1b2variable::pool->nvar, 1);
    ASSERT_TRUE(f1b2gradlist != NULL);

    ASSERT_TRUE(df1b2variable::pool != NULL);
    ASSERT_EQ(df1b2variable::pool->nvar, 1);
    ASSERT_EQ(lac.nvar, 2);
    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    lac.check_pool_size();
    ASSERT_TRUE(df1b2variable::adpool_vector[0] == pool);
    pool = nullptr;
    ASSERT_EQ(df1b2variable::adpool_counter, 1);
    ASSERT_TRUE(df1b2variable::pool != NULL);
    ASSERT_TRUE(df1b2variable::pool != expected_pool);

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool != pool);
  df1b2variable::pool->deallocate();
  delete df1b2variable::pool;
  df1b2variable::pool = nullptr;

  ASSERT_TRUE(df1b2variable::adpool_vector[0] != nullptr);
  delete df1b2variable::adpool_vector[0];
  df1b2variable::adpool_vector[0] = nullptr;
  --df1b2variable::adpool_counter;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, allocated_pool_for_check_pool_size_move_to_next)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  df1b2variable::adpool_vector[0] = nullptr;

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    adpool* expected_pool = df1b2variable::pool;
    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 0;
    int xsize = 1;
    int usize = 1;
    ivector minder(1, 1);
    minder(1) = 1;
    ivector maxder(1, 1);
    maxder(1) = 1;

    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(f1b2gradlist == NULL);
    ASSERT_EQ(df1b2variable::pool->nvar, 0);
    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);
    lac.nvar = 2;
    ASSERT_EQ(lac.nvar, 2);
    ASSERT_EQ(df1b2variable::pool->nvar, 1);
    ASSERT_TRUE(f1b2gradlist != NULL);

    ASSERT_TRUE(df1b2variable::pool != NULL);
    ASSERT_EQ(df1b2variable::pool->nvar, 1);
    ASSERT_EQ(lac.nvar, 2);
    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    ++df1b2variable::adpool_counter;
    ASSERT_TRUE(df1b2variable::adpool_vector[0] == nullptr);
    df1b2variable::adpool_vector[0] = new adpool();
    df1b2variable::adpool_vector[0]->nvar = 2;
    adpool* pool2 = df1b2variable::adpool_vector[0];
    lac.check_pool_size();
    ASSERT_TRUE(df1b2variable::adpool_vector[0] == pool);
    pool = nullptr;
    ASSERT_EQ(df1b2variable::adpool_counter, 1);
    ASSERT_TRUE(df1b2variable::pool != NULL);
    ASSERT_TRUE(df1b2variable::pool == pool2);
    ASSERT_TRUE(df1b2variable::pool != expected_pool);

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool != pool);
  df1b2variable::pool->deallocate();
  delete df1b2variable::pool;
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  df1b2variable::pool = nullptr;

  ASSERT_TRUE(df1b2variable::adpool_vector[0] != nullptr);
  delete df1b2variable::adpool_vector[0];
  df1b2variable::adpool_vector[0] = nullptr;
  --df1b2variable::adpool_counter;
  ASSERT_EQ(df1b2variable::adpool_counter, 0);

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, unallocated_pool_for_check_pool_size)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
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

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.derindex = new imatrix(1, 1000);

    df1b2variable::pool = NULL;
    lac.check_pool_size();
    ASSERT_TRUE(df1b2variable::pool != NULL);
    ASSERT_TRUE(df1b2variable::pool != pool);

    delete lac.derindex;
    lac.derindex = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool != pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool->deallocate();
  delete df1b2variable::pool;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
#ifdef _WIN32
TEST_F(test_laplace_approximation_calculator, DISABLED_unallocated_pool_for_check_pool_size_2)
#else
TEST_F(test_laplace_approximation_calculator, unallocated_pool_for_check_pool_size_2)
#endif
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
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

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.derindex = new imatrix(1, 1000);

    df1b2variable::pool = NULL;
    lac.check_pool_size();
    ASSERT_TRUE(df1b2variable::pool != NULL);
    ASSERT_TRUE(df1b2variable::pool != pool);

    delete lac.derindex;
    lac.derindex = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool != pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool->deallocate();
  delete df1b2variable::pool;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);

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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.derindex = new imatrix(1, 1000);
    lac.check_sparse_matrix_structure();
    delete lac.derindex;
    lac.derindex = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, check_sparse_matrix_structure_derindex)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.derindex = new imatrix(1, 1000, 1, 2);
    *(lac.derindex) = 1;
    lac.num_separable_calls = 1;
    lac.check_sparse_matrix_structure();
    delete lac.derindex;
    lac.derindex = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
#ifdef _WIN32
TEST_F(test_laplace_approximation_calculator, DISABLED_get_uhat_lm_newton)
#else
TEST_F(test_laplace_approximation_calculator, get_uhat_lm_newton)
#endif
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 0;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 1);
    minder(1) = 1;
    ivector maxder(1, 1);
    maxder(1) = 1;

    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();
    ASSERT_EQ(initial_params::nvarcalc(), 0);

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    {
      ASSERT_EQ(initial_params::nvarcalc(), 0);
      param_init_vector number;
      ASSERT_EQ(initial_params::nvarcalc(), 0);
      ASSERT_TRUE(ad_comm::global_bparfile == nullptr);
      ASSERT_TRUE(ad_comm::global_parfile == nullptr);
      //ASSERT_TRUE(number.share_flags == nullptr);
      number.allocate(1, 1, 1, "number");
      //ASSERT_TRUE(number.share_flags == nullptr);
      ASSERT_DOUBLE_EQ(value(number(1)), 0);
      ivector ivsf(1, 1);
      index_type sf(ivsf);
      ASSERT_EQ(sf.dimension(), 1);
      ivector ivaf(1, 1);
      index_type af(ivaf);
      ASSERT_EQ(af.dimension(), 1);
      number.setshare(sf, af);
      //ASSERT_TRUE(number.share_flags != nullptr);

      ASSERT_EQ(lac.init_switch, 1);

      ASSERT_EQ(initial_params::num_initial_params, 1);
      //ASSERT_EQ(initial_params::varsptr.list.size(), 1);
      //ASSERT_TRUE(initial_params::varsptr[0] != &number);
      //ASSERT_TRUE(initial_params::varsptr[0]->share_flags != nullptr);
      //ASSERT_EQ(initial_params::varsptr[0]->shared_size_count(), 0);
      //ASSERT_EQ(initial_params::varsptr[0]->share_flags->get_current_phase(), number.current_phase);
      //(initial_params::varsptr[0])->get_share_flags()->get_maxshare() = 1;
      number.get_share_flags()->get_maxshare() = 1;
      //ASSERT_EQ(initial_params::varsptr[0]->share_flags->get_maxshare(), 1);
      ASSERT_EQ(initial_params::nvarcalc(), 1);
      dvector empty(1, 1);
      lac.get_uhat_lm_newton(empty, pmin);
    }

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, DISABLED_default_calculations_check_derivatives)
{
  ASSERT_EQ(quadratic_prior::num_quadratic_prior, 0);
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

  adpool* pool = new adpool(100);
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    ASSERT_EQ(quadratic_prior::num_quadratic_prior, 0);
    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 0;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 1);
    minder(1) = 1;
    ivector maxder(1, 1);
    maxder(1) = 1;

    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();
    ASSERT_EQ(initial_params::nvarcalc(), 0);

    ASSERT_TRUE(f1b2gradlist == NULL);
    pmin->lapprox = new laplace_approximation_calculator(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(pmin->lapprox->num_importance_samples, 0);
    ASSERT_TRUE(f1b2gradlist != NULL);

    re_objective_function_value::pobjfun = new re_objective_function_value();
    re_objective_function_value::pobjfun->allocate();

    {
      ASSERT_EQ(quadratic_prior::num_quadratic_prior, 0);
      ASSERT_EQ(initial_params::nvarcalc(), 0);
      param_init_vector number;
      ASSERT_EQ(initial_params::nvarcalc(), 0);
      ASSERT_TRUE(ad_comm::global_bparfile == nullptr);
      ASSERT_TRUE(ad_comm::global_parfile == nullptr);
      //ASSERT_TRUE(number.share_flags == nullptr);
      number.allocate(1, 1, 1, "number");
      //ASSERT_TRUE(number.share_flags == nullptr);
      ASSERT_DOUBLE_EQ(value(number(1)), 0);
      ivector ivsf(1, 1);
      index_type sf(ivsf);
      ASSERT_EQ(sf.dimension(), 1);
      ivector ivaf(1, 1);
      index_type af(ivaf);
      ASSERT_EQ(af.dimension(), 1);
      number.setshare(sf, af);
      //ASSERT_TRUE(number.share_flags != nullptr);

      ASSERT_EQ(pmin->lapprox->init_switch, 1);

      ASSERT_EQ(initial_params::num_initial_params, 1);
      //ASSERT_EQ(initial_params::varsptr.list.size(), 1);
      //ASSERT_TRUE(initial_params::varsptr[0] != &number);
      //ASSERT_TRUE(initial_params::varsptr[0]->share_flags != nullptr);
      ASSERT_EQ(initial_params::varsptr[0]->shared_size_count(), 0);
      //ASSERT_EQ(initial_params::varsptr[0]->share_flags->get_current_phase(), number.current_phase);
      //(initial_params::varsptr[0])->get_share_flags()->get_maxshare() = 1;
      number.get_share_flags()->get_maxshare() = 1;
      //ASSERT_EQ(initial_params::varsptr[0]->share_flags->get_maxshare(), 1);
      ASSERT_EQ(initial_params::nvarcalc(), 1);
      dvector x(1, 1);
      x = 1;
      double f = 0;

      ASSERT_EQ(pmin->lapprox->num_importance_samples, 0);
      ASSERT_EQ(quadratic_prior::num_quadratic_prior, 0);
      ASSERT_TRUE(pmin->lapprox != nullptr);
      dvector result = pmin->lapprox->default_calculations_check_derivatives(x, pmin, f);
    }

    re_objective_function_value::pobjfun->deallocate();
    delete re_objective_function_value::pobjfun;
    re_objective_function_value::pobjfun = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, generate_antithetical_rvs_noactive_parameters)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;
     ad_exit=&test_ad_exit;
    ASSERT_THROW(lac.generate_antithetical_rvs(), int);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, cleanup_laplace_stuff)
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
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator* l =
      new laplace_approximation_calculator(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    ASSERT_EQ(l->separable_call_level, 1);
    l->begin_separable_call_stuff();
    ASSERT_EQ(l->separable_call_level, 2);
    l->end_separable_call_stuff();
    ASSERT_EQ(l->separable_call_level, 1);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    df1b2variable::adpool_vector[df1b2variable::adpool_counter] = df1b2variable::pool;
    df1b2variable::nvar_vector[df1b2variable::adpool_counter] = 1;
    ++df1b2variable::adpool_counter;

    void cleanup_laplace_stuff(laplace_approximation_calculator* l);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);
    cleanup_laplace_stuff(l);
    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    ASSERT_TRUE(df1b2variable::adpool_vector[0] == nullptr);
    ASSERT_EQ(df1b2variable::nvar_vector[0], 0);

    //ASSERT_TRUE(l == nullptr);

    delete pmin;
    pmin = nullptr;
  }
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, get_fx_fu)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;
     ad_exit=&test_ad_exit;
    lac.get_fx_fu(pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, get_uhat_lm_newton2_error)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;
     ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_THROW(lac.get_uhat_lm_newton2(x, pmin), int);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, get_uhat_lm_newton2)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;


    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);

    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(lac.usize, 1);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);


    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;

    ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    lac.ubest.allocate(1, 1);
    lac.get_uhat_lm_newton2(x, pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, get_newton_raphson_info)
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

  initial_df1b2params::num_initial_df1b2params = 0;
  ASSERT_EQ(initial_df1b2params::num_initial_df1b2params, 0);
  initial_df1b2params::varsptr = new P_INITIAL_DF1B2PARAMS[10];
  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    void get_newton_raphson_info(int xs, int us,const init_df1b2vector _y, dmatrix& Hess,
    dvector& grad, df1b2_gradlist* f1b2gradlist, function_minimizer* pfmin);
    int xs = 0;
    int us = 0;
    init_df1b2vector y;
    y.allocate(1, 2);
    dmatrix Hess;
    dvector grad;
    ASSERT_EQ(initial_df1b2params::num_initial_df1b2params, 0);
    re_objective_function_value::pobjfun = new re_objective_function_value();
    re_objective_function_value::pobjfun->allocate();
    get_newton_raphson_info(xs, us, y, Hess, grad, f1b2gradlist, pmin);

    re_objective_function_value::pobjfun->deallocate();
    delete re_objective_function_value::pobjfun;
    re_objective_function_value::pobjfun = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;

  delete initial_df1b2params::varsptr;
  initial_df1b2params::varsptr = nullptr;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, build_up_nested_shape)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    re_objective_function_value::pobjfun = new re_objective_function_value();
    re_objective_function_value::pobjfun->allocate();
    lac.build_up_nested_shape();

    re_objective_function_value::pobjfun->deallocate();
    delete re_objective_function_value::pobjfun;
    re_objective_function_value::pobjfun = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, gauss_hermite_stuff)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    re_objective_function_value::pobjfun = new re_objective_function_value();
    re_objective_function_value::pobjfun->allocate();
    //lac.build_up_nested_shape();

    ivector itmp;
    gauss_hermite_stuff stuff(&lac, true, 0, itmp);

    re_objective_function_value::pobjfun->deallocate();
    delete re_objective_function_value::pobjfun;
    re_objective_function_value::pobjfun = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, gauss_hermite_stuff2)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    re_objective_function_value::pobjfun = new re_objective_function_value();
    re_objective_function_value::pobjfun->allocate();
    //lac.build_up_nested_shape();

    ivector itmp(1, 2);
    itmp(1) = 0;
    itmp(2) = 1;
    ad_exit=&test_ad_exit;
    ASSERT_THROW(gauss_hermite_stuff stuff(&lac, true, 2, itmp), int);

    re_objective_function_value::pobjfun->deallocate();
    delete re_objective_function_value::pobjfun;
    re_objective_function_value::pobjfun = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, build_up_nested_shape_2)
{
  ad_exit=&test_ad_exit;

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
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator* l =
      new laplace_approximation_calculator(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    l->nested_shape.allocate(1, 1, 1);
    l->nested_shape(1) = -1;
    l->nested_shape(1, 1) = -1;
    l->nested_shape(1, 1, 1) = -1;
    i4_array* ptr4 = l->nested_shape.get_ptr4();
    ptr4 = new i4_array(1, 1, 1, 1, 1, 1, 1, 1);
    ptr4->operator()(1, 1, 1, 1) = -1;
    l->nested_separable_calls_counter.allocate(1, 5);
    l->nested_separable_calls_counter(1) = 1;
    l->nested_separable_calls_counter(2) = 1;
    l->nested_separable_calls_counter(3) = 1;
    l->nested_separable_calls_counter(4) = 1;
    l->nested_separable_calls_counter(5) = 0;

    ASSERT_EQ(l->separable_call_level, 1);
    l->build_up_nested_shape();
    ASSERT_EQ(l->separable_call_level, 1);
    ASSERT_DOUBLE_EQ(l->nested_shape(1), 1);

    //l->nested_separable_calls_counter(2) = 1;
    //l->build_up_nested_shape();

    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    df1b2variable::adpool_vector[df1b2variable::adpool_counter] = df1b2variable::pool;
    df1b2variable::nvar_vector[df1b2variable::adpool_counter] = 1;
    ++df1b2variable::adpool_counter;

    void cleanup_laplace_stuff(laplace_approximation_calculator* l);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);
    cleanup_laplace_stuff(l);
    ASSERT_EQ(df1b2variable::adpool_counter, 0);
    ASSERT_TRUE(df1b2variable::adpool_vector[0] == nullptr);
    ASSERT_EQ(df1b2variable::nvar_vector[0], 0);

    //ASSERT_TRUE(l == nullptr);

    delete pmin;
    pmin = nullptr;
  }
  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
class ad_comm2: public ad_comm
{
public:
ad_comm2(): ad_comm() {}
ad_comm2(const int argc, const char *argv[]): ad_comm((int)argc, (char**)argv) {}
};
TEST_F(test_laplace_approximation_calculator, ndi)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    int argc = 3;
    const char* argv[] = { "./simple" , "-ndi", "5"};
    ad_comm2 adcomm(argc, argv);
    ASSERT_EQ(ad_comm::argc, 3);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);

    ASSERT_EQ(lac.derindex->rowmin(), 1);
    ASSERT_EQ(lac.derindex->rowmax(), 5);

    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(lac.usize, 1);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;

    ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    lac.ubest.allocate(1, 1);
    lac.get_uhat_lm_newton2(x, pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, ilmn)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    int argc = 3;
    const char* argv[] = { "./simple" , "-ilmn", "5"};
    ad_comm2 adcomm(argc, argv);
    ASSERT_EQ(ad_comm::argc, 3);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);

    ASSERT_EQ(lac.derindex->rowmin(), 1);
    ASSERT_EQ(lac.derindex->rowmax(), 20000);
    ASSERT_EQ(lac.inner_lmnsteps, 5);

    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(lac.usize, 1);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;

    ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    lac.ubest.allocate(1, 1);
    lac.get_uhat_lm_newton2(x, pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, ndb)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    int argc = 3;
    const char* argv[] = { "./simple" , "-ndb", "2"};
    ad_comm2 adcomm(argc, argv);
    ASSERT_EQ(ad_comm::argc, 3);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);

    ASSERT_EQ(lac.derindex->rowmin(), 1);
    ASSERT_EQ(lac.derindex->rowmax(), 20000);
    ASSERT_EQ(lac.inner_lmnsteps, 10);
    ASSERT_EQ(lac.num_der_blocks, 2);

    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(lac.usize, 1);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;

    ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    lac.ubest.allocate(1, 1);
    lac.get_uhat_lm_newton2(x, pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, nr)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    int argc = 3;
    const char* argv[] = { "./simple" , "-nr", "2"};
    ad_comm2 adcomm(argc, argv);
    ASSERT_EQ(ad_comm::argc, 3);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);

    ASSERT_EQ(lac.derindex->rowmin(), 1);
    ASSERT_EQ(lac.derindex->rowmax(), 20000);
    ASSERT_EQ(lac.inner_lmnsteps, 10);
    ASSERT_EQ(lac.num_nr_iters, 2);

    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(lac.usize, 1);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;

    ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    lac.ubest.allocate(1, 1);
    lac.get_uhat_lm_newton2(x, pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, nrcrit)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    int argc = 3;
    const char* argv[] = { "./simple" , "-nrcrit", "2"};
    ad_comm2 adcomm(argc, argv);
    ASSERT_EQ(ad_comm::argc, 3);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);

    ASSERT_EQ(lac.derindex->rowmin(), 1);
    ASSERT_EQ(lac.derindex->rowmax(), 20000);
    ASSERT_EQ(lac.inner_lmnsteps, 10);
    ASSERT_EQ(lac.nr_crit, 2);

    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(lac.usize, 1);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;

    ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    lac.ubest.allocate(1, 1);
    lac.get_uhat_lm_newton2(x, pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, use_gauss_hermite)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    int argc = 3;
    const char* argv[] = { "./simple" , "-gh", "2"};
    ad_comm2 adcomm(argc, argv);
    ASSERT_EQ(ad_comm::argc, 3);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);

    ASSERT_EQ(lac.derindex->rowmin(), 1);
    ASSERT_EQ(lac.derindex->rowmax(), 20000);
    ASSERT_EQ(lac.inner_lmnsteps, 10);
    ASSERT_EQ(lac.use_gauss_hermite, 2);

    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(lac.usize, 1);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;

    ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    lac.ubest.allocate(1, 1);
    lac.get_uhat_lm_newton2(x, pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, isfunnel_flag)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    int argc = 8;
    const char* argv[] = { "./simple" , "-isf", "2", "-anti", "-nrdbg", "-ddnr", "-nochol", "-phe"};
    ad_comm2 adcomm(argc, argv);
    ASSERT_EQ(ad_comm::argc, 8);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_EQ(df1b2variable::adpool_counter, 1);

    ASSERT_EQ(lac.derindex->rowmin(), 1);
    ASSERT_EQ(lac.derindex->rowmax(), 20000);
    ASSERT_EQ(lac.inner_lmnsteps, 10);
    ASSERT_EQ(lac.nfunnelblocks, 2);
    ASSERT_EQ(lac.isfunnel_flag, 1);
    ASSERT_EQ(lac.antiflag, 1);
    ASSERT_EQ(lac.nr_debug, 1);
    ASSERT_EQ(lac.dd_nr_flag, 1);
    ASSERT_EQ(ad_comm::no_ln_det_choleski_flag, 1);
    ASSERT_EQ(ad_comm::print_hess_and_exit_flag, 1);

    ASSERT_TRUE(f1b2gradlist != NULL);
    ASSERT_EQ(lac.usize, 1);

    lac.num_importance_samples = 1;
    ASSERT_EQ(lac.num_importance_samples, 1);

    lac.num_local_re_array = new ivector(1, 1);
    *(lac.num_local_re_array) = 1;
    lac.num_separable_calls = 1;

    ad_exit=&test_ad_exit;
    dvector x(1, 1);
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    lac.ubest.allocate(1, 1);
    lac.get_uhat_lm_newton2(x, pmin);
    delete lac.num_local_re_array;
    lac.num_local_re_array = nullptr;

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, icrit)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    {
      int argc = 2;
      const char* argv[] = { "./simple" , "-icrit"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 2);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.inner_crit, 1.e-3);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-icrit", "0"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.inner_crit, 1.e-3);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-icrit", "1.5"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.inner_crit, 1.5);
    }

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, num_importance_samples)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    {
      int argc = 2;
      const char* argv[] = { "./simple" , "-is"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 2);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_EQ(lac.num_importance_samples, 0);
      ASSERT_EQ(lac.rseed, 3456);
      ASSERT_EQ(ad_comm::argc, 2);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-is", "0"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_EQ(lac.num_importance_samples, 0);
      ASSERT_EQ(lac.rseed, 3456);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-is", "5"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_EQ(lac.num_importance_samples, 5);
      ASSERT_EQ(lac.rseed, 3456);
    }

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, iiprint2)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    {
      int argc = 2;
      const char* argv[] = { "./simple" , "-iiprint"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 2);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.inner_iprint, 0);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-iiprint", "0"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.inner_iprint, 0);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-iiprint", "5"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.inner_iprint, 5);
    }

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, isb)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    {
      int argc = 2;
      const char* argv[] = { "./simple" , "-isb"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 2);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_EQ(lac.num_importance_samples, 0);
      ASSERT_EQ(lac.rseed, 3456);
      ASSERT_EQ(ad_comm::argc, 2);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-isb", "0"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_EQ(lac.num_importance_samples, 0);
      ASSERT_EQ(lac.rseed, 3456);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-isb", "5"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_EQ(lac.num_importance_samples, 10);
      ASSERT_EQ(lac.rseed, 3456);
    }

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_laplace_approximation_calculator, iiprint)
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

  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    int minder = 1;
    int maxder = 1;
    ASSERT_TRUE(gradient_structure::get() == NULL);
    myfunction_minimizer* pmin = new myfunction_minimizer();
    ASSERT_TRUE(gradient_structure::get()->GRAD_STACK1 != NULL);
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_number number;
    number.allocate(1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    *(objective_function_value::pobjfun) = number;

    ASSERT_TRUE(f1b2gradlist == NULL);

    ASSERT_EQ(df1b2variable::adpool_counter, 0);

    {
      int argc = 2;
      const char* argv[] = { "./simple" , "-nrcrit"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 2);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.nr_crit, 1.e-11);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-nrcrit", "0"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.nr_crit, 1.e-11);
    }
    df1b2variable::adpool_counter=0;
    {
      int argc = 3;
      const char* argv[] = { "./simple" , "-nrcrit", "5"};
      ad_comm2 adcomm(argc, argv);
      ASSERT_EQ(ad_comm::argc, 3);
      laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
      ASSERT_EQ(df1b2variable::adpool_counter, 1);
      ASSERT_DOUBLE_EQ(lac.nr_crit, 5);
    }

    delete pmin;
    pmin = nullptr;

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;
  }
  ASSERT_EQ(df1b2variable::adpool_counter, 1);
  ASSERT_TRUE(df1b2variable::pool == df1b2variable::adpool_vector[0]);

  df1b2variable::adpool_vector[0] = nullptr;
  df1b2variable::adpool_counter = 0;

  pool->deallocate();
  delete pool;
  pool = nullptr;

  df1b2variable::pool = nullptr;
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
double ff(double arg, double arg2) { return 0; }
TEST_F(test_laplace_approximation_calculator, write_pass1)
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

  initial_df1b2params::num_initial_df1b2params = 0;
  ASSERT_EQ(initial_df1b2params::num_initial_df1b2params, 0);
  initial_df1b2params::varsptr = new P_INITIAL_DF1B2PARAMS[10];
  adpool* pool = new adpool();
  df1b2variable::pool = pool;
  ASSERT_EQ(df1b2variable::pool->nvar, 0);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    int xsize = 1;
    int usize = 1;
    ivector minder(1, 2);
    minder(1) = 1;
    minder(2) = 1;
    ivector maxder(1, 2);
    maxder(1) = 2;
    maxder(2) = 2;
    myfunction_minimizer* pmin = new myfunction_minimizer();
    objective_function_value::pobjfun = new objective_function_value();

    ASSERT_TRUE(f1b2gradlist == NULL);
    laplace_approximation_calculator lac(xsize, usize, minder, maxder, pmin);
    ASSERT_TRUE(f1b2gradlist != NULL);

    {
    df1b2variable px(2.1);
    df1b2variable py(2.2);
    df1b2variable pz(2.4);
    df1b2function2 pf(&ff,
                      &ff,
                      &ff,
                      &ff,
                      &ff,
                      &ff,
                      &ff,
                      &ff,
                      &ff,
                      &ff,
                      "try");

    f1b2gradlist->write_pass1(&px, &py, &pz, &pf);
    }

    delete objective_function_value::pobjfun;
    objective_function_value::pobjfun = nullptr;

    delete pmin;
    pmin = nullptr;
  }
  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;

  delete initial_df1b2params::varsptr;
  initial_df1b2params::varsptr = nullptr;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
