#include <gtest/gtest.h>
#include "df1b2fun.h"

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
