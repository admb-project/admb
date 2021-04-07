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
    initial_params::varsptr.initialize();
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
TEST_F(test_laplace_approximation_calculator, DISABLED_check_sparse_matrix_structure)
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
TEST_F(test_laplace_approximation_calculator, DISABLED_check_sparse_matrix_structure_derindex)
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
      ASSERT_EQ(initial_params::varsptr[0]->shared_size_count(), 0);
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
      ASSERT_EQ(initial_params::varsptr[0]->shared_size_count(), 0);
      //ASSERT_EQ(initial_params::varsptr[0]->share_flags->get_current_phase(), number.current_phase);
      //(initial_params::varsptr[0])->get_share_flags()->get_maxshare() = 1;
      number.get_share_flags()->get_maxshare() = 1;
      //ASSERT_EQ(initial_params::varsptr[0]->share_flags->get_maxshare(), 1);
      ASSERT_EQ(initial_params::nvarcalc(), 1);
      dvector x(1, 1);
      double f = 0;
      dvector result = lac.default_calculations_check_derivatives(x, pmin, f);
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