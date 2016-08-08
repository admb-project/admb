#include <gtest/gtest.h>
#include <admodel.h>
#include <df1b2fun.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_data_number: public ::testing::Test
{
public:
  virtual ~test_data_number()
  {
  }
  virtual void TearDown()
  {
    f1b2gradlist = NULL;
    df1b2variable::pool = NULL;
  }
};

TEST_F(test_data_number, constructor)
{
  ad_exit=&test_ad_exit;

  data_number M;
  M = 4;
  double d = M;

  ASSERT_DOUBLE_EQ(d, 4);

  if (df1b2variable::pool)
  {
    delete df1b2variable::pool;
    df1b2variable::pool = NULL;
  }

  adpool a;
  const size_t n = 10;
  size_t size = sizeof(double) * df1b2variable::get_blocksize(n);
  a.set_size(size);
  df1b2variable::pool = &a;

  if (f1b2gradlist)
  {
    delete f1b2gradlist;
    f1b2gradlist = NULL;
  }
  df1b2_gradlist gradlist(4000000U,200000U,8000000U,400000U,2000000U,100000U,adstring("f1b2list1"));
  f1b2gradlist = &gradlist;;

  initial_df1b2params::varsptr = new P_INITIAL_DF1B2PARAMS[1];
  df1b2variable::noallocate = 1;
  df1b2_init_number number;
  initial_df1b2params::varsptr[0] = &number;

  df1b2variable v(d);

  if (initial_df1b2params::varsptr)
  {
    delete initial_df1b2params::varsptr;
    initial_df1b2params::varsptr = NULL;
  }
}
