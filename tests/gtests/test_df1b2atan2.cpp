#include <gtest/gtest.h>
#include <df1b2fun.h>
#include <cmath>

class test_df1b2atan2 :public ::testing::Test
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

#ifdef DEBUG
TEST_F(test_df1b2atan2, should_fail_df1b2variable_null_constructor)
#else
TEST_F(test_df1b2atan2, DISABLED_should_fail_df1b2variable_null_constructor)
#endif
{
  df1b2variable::noallocate = 0;
  ASSERT_DEATH({df1b2variable y;}, "Assertion");
}
TEST_F(test_df1b2atan2, noallocate_df1b2variable_null_constructor)
{
  df1b2variable::noallocate = 1;
  df1b2variable y;
}
#ifdef DEBUG
TEST_F(test_df1b2atan2, noallocate_df1b2variable_null_constructor_allocate)
#else
TEST_F(test_df1b2atan2, DISABLED_noallocate_df1b2variable_null_constructor_allocate)
#endif
{
  df1b2variable::noallocate = 1;
  df1b2variable y;
  ASSERT_DEATH({ y.allocate(); }, "Assertion");
}
TEST_F(test_df1b2atan2, adpool_default_constructor)
{
  adpool pool;
  ASSERT_EQ(0, pool.head);
  ASSERT_EQ(0, pool.size);
}
TEST_F(test_df1b2atan2, adpool_default_constructor_grow)
{
  adpool pool;
  pool.set_size(808);
  pool.grow();

  const int overhead = 12 + sizeof(char*);
  const int chunk_size = 16 * 65000 - overhead;
  int expected_nelem = chunk_size / 808;
  ASSERT_EQ(expected_nelem, pool.nelem);
}
TEST_F(test_df1b2atan2, should_fail_adpool_alloc)
{
  adpool pool;
  pool.set_size(808);
  pool.alloc();
}
TEST_F(test_df1b2atan2, default_constructor_deallocate)
{
  df1b2variable::noallocate = 1;
  df1b2variable y;
  ASSERT_EQ(0, y.ptr);
  {
    adpool pool;
    df1b2variable::pool = &pool;
    pool.set_size(808);
    df1b2_gradlist::no_derivatives = 1;
    y.ptr = (double*)pool.alloc();

    ASSERT_EQ(0, y.ncopies);
    y.deallocate();
    ASSERT_EQ(0, y.ptr);
  }
  df1b2variable::pool = nullptr;
}
#ifdef _WIN32
TEST_F(test_df1b2atan2, DISABLED_default_constructor_initialize_int)
#else
TEST_F(test_df1b2atan2, default_constructor_initialize_int)
#endif
{
  df1b2variable::noallocate = 1;
  df1b2variable y;
  ASSERT_EQ(0, y.ptr);
  {
    adpool pool;
    df1b2variable::pool = &pool;
    pool.set_size(808);
    df1b2_gradlist::no_derivatives = 1;
    y.ptr = (double*)pool.alloc();

    y.initialize(808);
  }
  df1b2variable::pool = nullptr;
}
TEST_F(test_df1b2atan2, default_constructor_initialize)
{
  df1b2variable::noallocate = 1;
  df1b2variable y;
  ASSERT_EQ(0, y.ptr);
  {
    adpool pool;
    df1b2variable::pool = &pool;
    pool.set_size(808);
    pool.nvar = 808;
    df1b2_gradlist::no_derivatives = 1;
    y.ptr = (double*)pool.alloc();

    y.initialize();
  }
  df1b2variable::pool = nullptr;
}
TEST_F(test_df1b2atan2, default_constructor_allocate)
{
  df1b2variable::noallocate = 1;
  df1b2variable y;
  ASSERT_EQ(0, y.ptr);
  {
    adpool pool;
    df1b2variable::pool = &pool;
    pool.set_size(808);
    pool.nvar = 808;
    df1b2_gradlist::no_derivatives = 1;
    y.ptr = (double*)pool.alloc();

    y.allocate();
  }
  df1b2variable::pool = nullptr;
}
TEST_F(test_df1b2atan2, default_constructor_withallocate)
{
  {
    adpool pool;
    pool.set_size(808);
    pool.nvar = 808;
    df1b2variable::pool = &pool;
    df1b2_gradlist::no_derivatives = 1;
    df1b2variable::noallocate = 0;
    df1b2variable y;
  }
  df1b2variable::pool = nullptr;
}
TEST_F(test_df1b2atan2, df1b2_gradlist_default_constructor)
{
  int argc = 1;
  char* argv[] = {"./gtest-all"};
  ad_comm::argc = argc;
  ad_comm::argv = argv;

  int get_f1b2buffer_size(const char * s);

  int bs  = get_f1b2buffer_size("-l1");
  int nbs = get_f1b2buffer_size("-nl1");
  ASSERT_EQ(0, bs);
  ASSERT_EQ(0, nbs);
  int bs2 = get_f1b2buffer_size("-l2");
  int nbs2 = get_f1b2buffer_size("-nl2");
  ASSERT_EQ(0, bs2);
  ASSERT_EQ(0, nbs2);
  int bs3 = get_f1b2buffer_size("-l3");
  int nbs3 = get_f1b2buffer_size("-nl3");
  ASSERT_EQ(0, bs3);
  ASSERT_EQ(0, nbs3);

  df1b2_gradlist f1b2gradlist(4000000U,200000U,8000000U,400000U,2000000U,100000U,adstring("f1b2list1"));

  ad_comm::argc = 0;
  ad_comm::argv = 0;
}
TEST_F(test_df1b2atan2, no_derivatives_0)
{
  int argc = 1;
  char* argv[] = {"./gtest-all"};
  ad_comm::argc = argc;
  ad_comm::argv = argv;

  extern df1b2_gradlist* f1b2gradlist;
  {
    adpool pool;
    pool.set_size(808);
    pool.nvar = 808;
    df1b2variable::pool = &pool;
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable::noallocate = 0;

    df1b2_gradlist gradlist(4000000U,200000U,8000000U,400000U,2000000U,100000U,adstring("f1b2list1"));
    f1b2gradlist = &gradlist;;

    df1b2variable y;
  }
  f1b2gradlist = nullptr;
  df1b2variable::pool = nullptr;

  ad_comm::argc = 0;
  ad_comm::argv = 0;
}
TEST_F(test_df1b2atan2, atan2)
{
  int argc = 1;
  char* argv[] = {"./gtest-all"};
  ad_comm::argc = argc;
  ad_comm::argv = argv;

  extern df1b2_gradlist* f1b2gradlist;
  {
  adpool pool;
  pool.set_size(808);
  pool.nvar = 808;
  df1b2variable::pool = &pool;
  df1b2_gradlist::no_derivatives = 0;
  df1b2variable::noallocate = 0;

  df1b2_gradlist gradlist(4000000U,200000U,8000000U,400000U,2000000U,100000U,adstring("f1b2list1"));
  f1b2gradlist = &gradlist;;

  df1b2variable y(0.0);
  df1b2variable x(0.0);

  df1b2variable atan2(const df1b2variable& y, const df1b2variable& x);
  //df1b2variable v = atan2(y, x);
  //ASSERT_DOUBLE_EQ(std::atan2(0, 0), value(v));
  }
  f1b2gradlist = nullptr;
  df1b2variable::pool = nullptr;

  ad_comm::argc = 0;
  ad_comm::argv = 0;
}
