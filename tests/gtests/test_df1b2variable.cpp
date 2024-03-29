#include <gtest/gtest.h>
#include <df1b2fun.h>

class test_df1b2variable: public ::testing::Test
{
public:
  virtual ~test_df1b2variable() {}
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
    if (gradient_structure::get())
      if (gradient_structure::get()->ARR_LIST1)
      {
        delete gradient_structure::get()->ARR_LIST1;
        gradient_structure::get()->ARR_LIST1 = nullptr;
      }
    function_minimizer::first_hessian_flag = 0;
    ad_comm::argc = 0;
    ad_comm::argv = nullptr;
    laplace_approximation_calculator::antiflag = 0;
    df1b2variable::nvar = 0;
  }
};

TEST_F(test_df1b2variable, default_constructor_noallocate)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;
    df1b2variable v;

    ASSERT_EQ(NULL, v.ptr);
    ASSERT_EQ(NULL, v.ncopies);
    ASSERT_EQ(NULL, v.u);
    ASSERT_EQ(NULL, v.u_dot);
    ASSERT_EQ(NULL, v.u_bar);
    ASSERT_EQ(NULL, v.u_dot_bar);
    ASSERT_EQ(NULL, v.u_tilde);
    ASSERT_EQ(NULL, v.u_dot_tilde);
    ASSERT_EQ(NULL, v.u_bar_tilde);
    ASSERT_EQ(NULL, v.u_dot_bar_tilde);
    ASSERT_EQ(0, v.indindex);
  }
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2variable, default_constructor_allocate_deallocate)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    df1b2variable v;
    ASSERT_TRUE(v.ptr == nullptr);

    v.allocate();
    v.deallocate();
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}

//df1b2variable& df1b2variable::operator = (const df3_two_variable& v)

TEST_F(test_df1b2variable, default_constructor2)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    //df1b2_gradlist gradlist(4000000U,200000U,8000000U,400000U,2000000U,100000U,adstring("f1b2list1"));
    //f1b2gradlist = &gradlist;

    initial_df1b2params::varsptr = new P_INITIAL_DF1B2PARAMS[1];

    df1b2_init_number number;
    initial_df1b2params::varsptr[0] = &number;

    int ii = 0;
    dvector y(0, 1);
    (initial_df1b2params::varsptr[0])->set_value(y, ii);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr != NULL);
}
TEST_F(test_df1b2variable, copy_constructor_empty)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    df1b2variable empty;
    df1b2variable v(empty);

    ASSERT_EQ(NULL, v.ptr);
    ASSERT_EQ(NULL, v.ncopies);
    ASSERT_EQ(NULL, v.u);
    ASSERT_EQ(NULL, v.u_dot);
    ASSERT_EQ(NULL, v.u_bar);
    ASSERT_EQ(NULL, v.u_dot_bar);
    ASSERT_EQ(NULL, v.u_tilde);
    ASSERT_EQ(NULL, v.u_dot_tilde);
    ASSERT_EQ(NULL, v.u_bar_tilde);
    ASSERT_EQ(NULL, v.u_dot_bar_tilde);
    ASSERT_EQ(0, v.indindex);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2variable, copy_constructor_noallocate_nonempty)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    f1b2gradlist = new df1b2_gradlist(4000000U,200000U,8000000U,400000U,2000000U,100000U,adstring("f1b2list1"));

    df1b2variable::noallocate = 0;
    df1b2_gradlist::no_derivatives = 1;

    df1b2variable v;

    ASSERT_TRUE(v.ptr);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->nvar);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->ncopies);
    ASSERT_TRUE(((twointsandptr*)v.ptr)->ptr == df1b2variable::pool);
    ASSERT_EQ(0, *v.ncopies);
    ASSERT_TRUE(v.u == (v.ptr + 2));
    ASSERT_TRUE(v.u_dot == (v.u + 1));
    int nvar = df1b2variable::nvar;
    ASSERT_EQ(nvar, 0);
    ASSERT_TRUE(v.u_bar == (v.u_dot + nvar));
    ASSERT_TRUE(v.u_dot_bar == (v.u_bar + nvar));
    ASSERT_TRUE(v.u_tilde == (v.u_dot_bar + nvar));
    ASSERT_TRUE(v.u_dot_tilde == (v.u_tilde + 1));
    ASSERT_TRUE(v.u_bar_tilde == (v.u_dot_tilde + nvar));
    ASSERT_TRUE(v.u_dot_bar_tilde == (v.u_bar_tilde + nvar));
    ASSERT_FALSE(0 == v.indindex);

    df1b2variable copy(v);
    ASSERT_TRUE(v.ptr);
    ASSERT_EQ(0, ((twointsandptr*)copy.ptr)->nvar);
    ASSERT_EQ(1, ((twointsandptr*)copy.ptr)->ncopies);
    ASSERT_TRUE(((twointsandptr*)copy.ptr)->ptr == df1b2variable::pool);

    ASSERT_EQ(1, *copy.ncopies);
    ASSERT_TRUE(v.u == copy.u);
    ASSERT_TRUE(v.u_dot == copy.u_dot);
    ASSERT_TRUE(v.u_bar == copy.u_bar);
    ASSERT_TRUE(v.u_dot_bar == copy.u_dot_bar);
    ASSERT_TRUE(v.u_tilde == copy.u_tilde);
    ASSERT_TRUE(v.u_dot_tilde == copy.u_dot_tilde);
    ASSERT_TRUE(v.u_bar_tilde == copy.u_bar_tilde);
    ASSERT_TRUE(v.u_dot_bar_tilde == copy.u_dot_bar_tilde);
    ASSERT_TRUE(v.indindex != copy.indindex);
    ASSERT_TRUE(0 == copy.indindex);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2variable, constructor_double)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;

    double expected = 6.5;
    df1b2variable v(expected);

    ASSERT_TRUE(v.ptr);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->nvar);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->ncopies);
    ASSERT_TRUE(((twointsandptr*)v.ptr)->ptr == df1b2variable::pool);
    ASSERT_EQ(0, *v.ncopies);
    ASSERT_DOUBLE_EQ(*v.u, expected);
    ASSERT_TRUE(v.u == (v.ptr + 2));
    ASSERT_TRUE(v.u_dot == (v.u + 1));
    int nvar = df1b2variable::nvar;
    ASSERT_EQ(nvar, 0);
    ASSERT_TRUE(v.u_bar == (v.u_dot + nvar));
    ASSERT_TRUE(v.u_dot_bar == (v.u_bar + nvar));
    ASSERT_TRUE(v.u_tilde == (v.u_dot_bar + nvar));
    ASSERT_TRUE(v.u_dot_tilde == (v.u_tilde + 1));
    ASSERT_TRUE(v.u_bar_tilde == (v.u_dot_tilde + nvar));
    ASSERT_TRUE(v.u_dot_bar_tilde == (v.u_bar_tilde + nvar));
    ASSERT_FALSE(0 == v.indindex);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
