#include <gtest/gtest.h>
#include <df1b2fun.h>

class test_df1b2matrix: public ::testing::Test
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
TEST_F(test_df1b2matrix, default_constructor)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  {
    df1b2matrix m;
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 0);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 0);
    m.deallocate();
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 0);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2matrix, constructor_full_size)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  {
    df1b2matrix m(0, -1, 1, 2);
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 0);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 0);
    m.deallocate();
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 0);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2matrix, constructor_row_size)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  {
    df1b2matrix m(0, -1);
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 0);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 0);
    m.deallocate();
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 0);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2matrix, rowsize_constructor)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  {
    df1b2matrix m(1, 5);
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 5);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 5);
    m.initialize();
    m.deallocate();
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 0);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2matrix, size_constructor)
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
    df1b2matrix m(1, 2, 1, 3);
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 2);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 2);
    //m.initialize();
    m.deallocate();
    ASSERT_EQ(m.indexmin(), 1);
    ASSERT_EQ(m.indexmax(), 0);
    ASSERT_EQ(m.indexmin(), m.rowmin());
    ASSERT_EQ(m.indexmax(), m.rowmax());
    ASSERT_EQ(m.size(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2matrix, assigment_variable)
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

    double expected = 8.5;
    v.allocate();
    v = expected;

    ASSERT_TRUE(v.ptr != nullptr);
    ASSERT_DOUBLE_EQ(value(v), expected);

    df1b2matrix m(1, 2, 1, 2);

    m = v;

    ASSERT_EQ(expected, value(m(1, 1)));
    ASSERT_EQ(expected, value(m(1, 2)));
    ASSERT_EQ(expected, value(m(2, 1)));
    ASSERT_EQ(expected, value(m(2, 2)));

    v.deallocate();

    ASSERT_TRUE(v.ptr == nullptr);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
