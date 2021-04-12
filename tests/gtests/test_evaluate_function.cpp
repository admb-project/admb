#include <gtest/gtest.h>
#include <admodel.h>
#include <df1b2fun.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_evaluate_function: public ::testing::Test
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

TEST_F(test_evaluate_function, case1)
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

  myfunction_minimizer* pfmin = new myfunction_minimizer();
  objective_function_value::pobjfun = new objective_function_value();
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_vector number;
    ASSERT_EQ(initial_params::nvarcalc(), 0);
    number.allocate(1, 1, 1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    ASSERT_TRUE(f1b2gradlist == NULL);

    double evaluate_function(double& fval,const dvector& x, function_minimizer* pfmin);
    double fval = 0;
    dvector x(1, 1);
    ASSERT_EQ(initial_params::nvarcalc(), 1);
    double result = evaluate_function(fval, x, pfmin);
    ASSERT_DOUBLE_EQ(result, 0.0);
  }

  delete pfmin;
  pfmin = nullptr;

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;

  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_evaluate_function, case2)
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

  myfunction_minimizer* pfmin = new myfunction_minimizer();
  objective_function_value::pobjfun = new objective_function_value();
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_vector number;
    ASSERT_EQ(initial_params::nvarcalc(), 0);
    number.allocate(1, 1, 1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    ASSERT_TRUE(f1b2gradlist == NULL);

    double evaluate_function(double& fval,const dvector& x,const dvector& g, function_minimizer* pfmin);
    double fval = 0;
    dvector x(1, 1);
    dvector g(1, 1);
    ASSERT_EQ(initial_params::nvarcalc(), 1);
    double result = evaluate_function(fval, x, g, pfmin);
    ASSERT_DOUBLE_EQ(result, 0.0);
  }

  delete pfmin;
  pfmin = nullptr;

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;

  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_evaluate_function, case3)
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

  myfunction_minimizer* pfmin = new myfunction_minimizer();
  objective_function_value::pobjfun = new objective_function_value();
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_vector number;
    ASSERT_EQ(initial_params::nvarcalc(), 0);
    number.allocate(1, 1, 1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    ASSERT_TRUE(f1b2gradlist == NULL);

    double evaluate_function_quiet(const dvector& x, function_minimizer* pfmin);
    dvector x(1, 1);
    ASSERT_EQ(initial_params::nvarcalc(), 1);
    double result = evaluate_function_quiet(x, pfmin);
    ASSERT_DOUBLE_EQ(result, 0.0);
  }

  delete pfmin;
  pfmin = nullptr;

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;

  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_evaluate_function, case4)
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

  myfunction_minimizer* pfmin = new myfunction_minimizer();
  objective_function_value::pobjfun = new objective_function_value();
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_vector a;
    param_init_vector b;
    ASSERT_EQ(initial_params::nvarcalc(), 0);
    a.allocate(1, 1, 1, "a");
    b.allocate(1, 1, 1, "b");
    ASSERT_EQ(initial_params::nvarcalc(), 2);

    ASSERT_TRUE(f1b2gradlist == NULL);

    void evaluate_function_gradient(double& f,const dvector& x, function_minimizer* pfmin, dvector& xadjoint, dvector& uadjoint);
    double f = 0.0;
    dvector x(1, 2);
    dvector xadjoint(1, 1);
    dvector uadjoint(1, 1);
    ASSERT_EQ(initial_params::nvarcalc(), 2);
    evaluate_function_gradient(f, x, pfmin, xadjoint, uadjoint);
  }

  delete pfmin;
  pfmin = nullptr;

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;

  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_evaluate_function, case5)
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

  myfunction_minimizer* pfmin = new myfunction_minimizer();
  objective_function_value::pobjfun = new objective_function_value();
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    ASSERT_EQ(initial_params::nvarcalc(), 0);
    param_init_vector number;
    ASSERT_EQ(initial_params::nvarcalc(), 0);
    number.allocate(1, 1, 1, "number");
    ASSERT_EQ(initial_params::nvarcalc(), 1);

    ASSERT_TRUE(f1b2gradlist == NULL);

    double evaluate_function_no_derivatives(const dvector& x, function_minimizer* pfmin);
    dvector x(1, 1);
    ASSERT_EQ(initial_params::nvarcalc(), 1);
    double result = evaluate_function_no_derivatives(x, pfmin);
    ASSERT_DOUBLE_EQ(result, 0.0);
  }

  delete pfmin;
  pfmin = nullptr;

  delete objective_function_value::pobjfun;
  objective_function_value::pobjfun = nullptr;

  ASSERT_TRUE(df1b2variable::pool == pool);
  pool->deallocate();
  delete pool;
  pool = nullptr;
  df1b2variable::pool = nullptr;

  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
