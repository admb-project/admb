#include <gtest/gtest.h>
#include "df1b2fun.h"

class test_df1b2vector: public ::testing::Test {};

TEST_F(test_df1b2vector, constructor)
{
  adpool* save = df1b2variable::pool;

  extern df1b2_gradlist* f1b2gradlist;
  df1b2_gradlist* save2 = f1b2gradlist;
  {
    adpool a;
    const size_t n = 10;
    size_t size = sizeof(double) * df1b2variable::get_blocksize(n);
    a.set_size(size);
    df1b2variable::pool = &a;

    df1b2_gradlist gradlist(4000000U,200000U,8000000U,400000U,2000000U,100000U,adstring("f1b2list1"));
    f1b2gradlist = &gradlist;;

    df1b2vector v(1, 5);
  }
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
