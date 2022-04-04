#include <gtest/gtest.h>
#include <df1b2fun.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_funnel_init_df1b2variable: public ::testing::Test
{
public:
  virtual ~test_funnel_init_df1b2variable() {}
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
    extern df1b2_gradlist* f1b2gradlist;
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

TEST_F(test_funnel_init_df1b2variable, default_constructor)
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

    funnel_init_df1b2variable v;
    ASSERT_EQ(v.type, 0);
    ASSERT_TRUE(v.pointer == nullptr);
    //ASSERT_DOUBLE_EQ(v.xu, 0);
    ASSERT_EQ(v.ind_index, -1);
    ASSERT_EQ(v.nvar_calc(), 1);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_funnel_init_df1b2variable, preallocate)
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

    double expected = 6.5;
    df1b2variable x(expected);

    funnel_init_df1b2variable v;
    v.preallocate(x);

    ASSERT_EQ(v.type, 0);
    ASSERT_TRUE(v.pointer == nullptr);
    ASSERT_DOUBLE_EQ(v.xu, *(x.get_u()));
    ASSERT_EQ(v.ind_index, x.get_ind_index());
    ASSERT_EQ(v.nvar_calc(), 1);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_funnel_init_df1b2variable, copy_constructor)
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

    double expected = 6.5;
    df1b2variable x(expected);

    funnel_init_df1b2variable v;
    v.preallocate(x);

    funnel_init_df1b2variable y(v);

    void check_pool_depths(void);
    check_pool_depths();

    //ASSERT_EQ(v.type, y.type);
    //ASSERT_TRUE(v.pointer == y.pointer);
    //ASSERT_DOUBLE_EQ(v.xu, y.xu);
    //ASSERT_EQ(v.ind_index, y.ind_index);
    ASSERT_EQ(v.nvar_calc(), y.nvar_calc());
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_funnel_init_df1b2variable, delete_from_list_adexit)
{
  ad_exit=&test_ad_exit;

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

    double expected = 6.5;
    df1b2variable x(expected);

    funnel_init_df1b2variable v;
    v.preallocate(x);

    funnel_init_df1b2variable y(v);

    void check_pool_depths(void);
    check_pool_depths();

    ASSERT_ANY_THROW({
      y.delete_from_list();
    });
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
