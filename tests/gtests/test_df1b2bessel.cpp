#include <gtest/gtest.h>
#include <df1b2fun.h>

extern df1b2_gradlist* f1b2gradlist;

class test_df1b2bessel: public ::testing::Test
{
public:
  virtual ~test_df1b2bessel() {}
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

TEST_F(test_df1b2bessel, bessj0)
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
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr != nullptr);

    v.allocate();
    v = 8.0;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), 8.0);

    df1b2variable bessj0(df1b2variable);
    df1b2variable result = bessj0(v);

    double bessj0(double);
    double expected = bessj0(value(v));

    ASSERT_EQ(expected, value(result));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2bessel, bessy0)
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
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr != nullptr);

    v.allocate();
    v = 8.0;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), 8.0);

    df1b2variable bessy0(df1b2variable);
    df1b2variable result = bessy0(v);

    double bessy0(double);
    double expected = bessy0(value(v));

    ASSERT_DOUBLE_EQ(expected, value(result));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2bessel, bessj1)
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
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr != nullptr);

    v.allocate();
    v = 8.0;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), 8.0);

    df1b2variable bessj1(df1b2variable);
    df1b2variable result = bessj1(v);

    double bessj1(double);
    double expected = bessj1(value(v));

    ASSERT_DOUBLE_EQ(expected, value(result));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2bessel, bessy1)
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
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr != nullptr);

    v.allocate();
    v = 8.0;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), 8.0);

    df1b2variable bessy1(df1b2variable);
    df1b2variable result = bessy1(v);

    double bessy1(double);
    double expected = bessy1(value(v));

    ASSERT_DOUBLE_EQ(expected, value(result));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2bessel, bessi1)
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
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr != nullptr);

    v.allocate();
    v = 8.0;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), 8.0);

    df1b2variable bessi1(df1b2variable);
    df1b2variable result = bessi1(v);

    double bessi1(double);
    double expected = bessi1(value(v));

    ASSERT_EQ(expected, value(result));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2bessel, bessk1)
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
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr != nullptr);

    v.allocate();
    v = 8.0;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), 8.0);

    df1b2variable bessk1(df1b2variable);
    df1b2variable result = bessk1(v);

    double bessk1(double);
    double expected = bessk1(value(v));

    ASSERT_EQ(expected, value(result));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2bessel, bessi0)
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
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr != nullptr);

    v.allocate();
    v = 8.0;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), 8.0);

    df1b2variable bessi0(df1b2variable);
    df1b2variable result = bessi0(v);

    double bessi0(double);
    double expected = bessi0(value(v));

    ASSERT_EQ(expected, value(result));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2bessel, bessk0)
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
    df1b2_gradlist::no_derivatives = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr != nullptr);

    v.allocate();
    v = 8.0;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), 8.0);

    df1b2variable bessk0(df1b2variable);
    df1b2variable result = bessk0(v);

    double bessk0(double);
    double expected = bessk0(value(v));

    ASSERT_EQ(expected, value(result));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
