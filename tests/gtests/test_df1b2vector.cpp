#include <gtest/gtest.h>
#include "df1b2fun.h"

void test_ad_exit(const int exit_code);

extern df1b2_gradlist* f1b2gradlist;

class test_df1b2vector: public ::testing::Test
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
    df1b2variable::noallocate = 1;
    df1b2_gradlist::no_derivatives = 1;
  }
};

TEST_F(test_df1b2vector, default_constructor)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  {
    df1b2vector v;
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
    v.allocate();
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
    v.deallocate();
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2vector, check_shape_empty_v12)
{
  ad_exit=&test_ad_exit;
  df1b2vector empty;
  dvector v(1, 2);

  ASSERT_THROW(check_shape(empty, v, " empty-v12"),int);
  ASSERT_THROW(check_shape(v, empty, " v12-empty"),int);
}
TEST_F(test_df1b2vector, check_shape_empty_df1b2vector12)
{
  ad_exit=&test_ad_exit;

  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    df1b2variable::noallocate = 1;
    df1b2vector empty;
    df1b2vector v;
    v.allocate(1, 2);
    ASSERT_THROW(check_shape(empty, v, " empty-df1b2vector12"),int);
    ASSERT_THROW(check_shape(v, empty, " df1b2vector12-empty"),int);
  }
}
TEST_F(test_df1b2vector, check_shape_empty_df1b2matrix)
{
  ad_exit=&test_ad_exit;

  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    df1b2variable::noallocate = 1;
    df1b2vector v;
    v.allocate(1, 2);
    df1b2matrix m(3, 4);

    void check_shape(const df1b2vector & _x,const df1b2matrix & _y,const char * s);
    ASSERT_THROW(check_shape(v, m, " df1b2vector-df1b2matrix"),int);
  }
}
TEST_F(test_df1b2vector, assigment_dvector)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    df1b2variable::noallocate = 0;
    df1b2vector v;
    ASSERT_TRUE(v.getv() == nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
    df1b2_gradlist::no_derivatives = 1;
    v.allocate(1, 10);
    v.initialize();
    ASSERT_TRUE(v.getv() != nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 10);

    dvector values(1, 10);
    values(1) = 1;
    values(2) = 2;
    values(3) = 3;
    
    v = values;

    ASSERT_DOUBLE_EQ(value(v(1)), values(1));
    ASSERT_DOUBLE_EQ(value(v(2)), values(2));
    ASSERT_DOUBLE_EQ(value(v(3)), values(3));

    v.deallocate();

    ASSERT_TRUE(v.getv() == nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2vector, assigment)
{
  ASSERT_TRUE(df1b2variable::pool == NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
  const size_t n = 10;
  size_t s = sizeof(double) * df1b2variable::get_blocksize(n);
  df1b2variable::pool = new adpool();
  df1b2variable::pool->set_size(s);
  {
    df1b2variable::noallocate = 0;
    df1b2vector v;
    ASSERT_TRUE(v.getv() == nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
    df1b2_gradlist::no_derivatives = 1;
    v.allocate(1, 10);
    v.initialize();
    ASSERT_TRUE(v.getv() != nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 10);

    dvector values(1, 10);
    values(1) = 1;
    values(2) = 2;
    values(3) = 3;
    
    v = values;

    df1b2vector x;
    x.allocate(1, 10);
    x.initialize();

    x = v;

    ASSERT_DOUBLE_EQ(value(x(1)), values(1));
    ASSERT_DOUBLE_EQ(value(x(2)), values(2));
    ASSERT_DOUBLE_EQ(value(x(3)), values(3));

    v.deallocate();

    ASSERT_TRUE(v.getv() == nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2vector, _df1b2vector)
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

    df1b2vector v;
    v.allocate(1, 2);
    df1b2vector copy(v);
    ASSERT_TRUE(v.getv() == copy.getv());
    copy.deallocate();
    v.deallocate();
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist == NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2vector, df1b2vector_allocate_deallocate)
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

    df1b2vector v;
    ASSERT_TRUE(v.getv() == nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
    v.allocate(1, 10);

    ASSERT_TRUE(v.getv() != nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 10);

    v.initialize();

    dvector values(1, 10);
    values.initialize();
 
    v = values;

    v.deallocate();
    ASSERT_TRUE(v.getv() == nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
TEST_F(test_df1b2vector, assignment_df1b2variable)
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

    df1b2vector v;
    ASSERT_TRUE(v.getv() == nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
    v.allocate(1, 10);

    ASSERT_TRUE(v.getv() != nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 10);

    v.initialize();

    df1b2variable variable;

    double expected = 8.5;
    variable.allocate();
    variable = expected;

    v = variable;
    ASSERT_EQ(expected, value(v(1)));
    ASSERT_EQ(expected, value(v(2)));
    ASSERT_EQ(expected, value(v(3)));
    ASSERT_EQ(expected, value(v(4)));
    ASSERT_EQ(expected, value(v(5)));
    ASSERT_EQ(expected, value(v(6)));
    ASSERT_EQ(expected, value(v(7)));
    ASSERT_EQ(expected, value(v(8)));
    ASSERT_EQ(expected, value(v(9)));
    ASSERT_EQ(expected, value(v(10)));

    v.deallocate();
    ASSERT_TRUE(v.getv() == nullptr);
    ASSERT_EQ(v.indexmin(), 1);
    ASSERT_EQ(v.indexmax(), 0);
  }
  ASSERT_TRUE(df1b2variable::pool != NULL);
  ASSERT_TRUE(f1b2gradlist != NULL);
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);
}
