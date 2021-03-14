#include <gtest/gtest.h>
#include <df1b2fun.h>

class test_df1b2variable: public ::testing::Test
{
public:
  virtual ~test_df1b2variable() {}
  virtual void TearDown()
  {
    f1b2gradlist = NULL;
    df1b2variable::pool = NULL;
  }
};

TEST_F(test_df1b2variable, default_constructor)
{
  if (df1b2variable::pool)
  {
    delete df1b2variable::pool;
    df1b2variable::pool = NULL;
  }
  ASSERT_TRUE(df1b2variable::pool == NULL);
  if (f1b2gradlist)
  {
    delete f1b2gradlist;
    f1b2gradlist = NULL;
  }
  ASSERT_TRUE(f1b2gradlist == NULL);

  if (initial_df1b2params::varsptr)
  {
    delete initial_df1b2params::varsptr;
    initial_df1b2params::varsptr = NULL;
  }
  ASSERT_TRUE(initial_df1b2params::varsptr == NULL);

  adpool a;
  const size_t n = 10;
  size_t size = sizeof(double) * df1b2variable::get_blocksize(n);
  a.set_size(size);
  df1b2variable::pool = &a;

  df1b2_gradlist gradlist(4000000U,200000U,8000000U,400000U,2000000U,100000U,adstring("f1b2list1"));
  f1b2gradlist = &gradlist;;

  initial_df1b2params::varsptr = new P_INITIAL_DF1B2PARAMS[1];

  df1b2variable::noallocate = 1;
  df1b2_init_number number;
  initial_df1b2params::varsptr[0] = &number;

  int ii = 0;
  dvector y(0, 1);
  (initial_df1b2params::varsptr[0])->set_value(y, ii);

  if (initial_df1b2params::varsptr)
  {
    delete initial_df1b2params::varsptr;
    initial_df1b2params::varsptr = NULL;
  }
}
/*
TEST_F(test_df1b2variable, default_constructor)
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

    df1b2variable::noallocate = 1;
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

    v.allocate();
    ASSERT_TRUE(v.ptr);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->nvar);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->ncopies);
    ASSERT_TRUE(((twointsandptr*)v.ptr)->ptr == &a);
    ASSERT_EQ(0, *v.ncopies);
    ASSERT_TRUE(v.u == (v.ptr + 2));
    ASSERT_TRUE(v.u_dot == (v.u + 1));
    int nvar = v.get_local_nvar();
    ASSERT_TRUE(v.u_bar == (v.u_dot + nvar));
    ASSERT_TRUE(v.u_dot_bar == (v.u_bar + nvar));
    ASSERT_TRUE(v.u_tilde == (v.u_dot_bar + nvar));
    ASSERT_TRUE(v.u_dot_tilde == (v.u_tilde + 1));
    ASSERT_TRUE(v.u_bar_tilde == (v.u_dot_tilde + nvar));
    ASSERT_TRUE(v.u_dot_bar_tilde == (v.u_bar_tilde + nvar));
    ASSERT_FALSE(0 == v.indindex);
  }
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
TEST_F(test_df1b2variable, default_constructor_noallocate_false)
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

    df1b2variable::noallocate = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->nvar);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->ncopies);
    ASSERT_TRUE(((twointsandptr*)v.ptr)->ptr == &a);

    ASSERT_EQ(0, *v.ncopies);
    ASSERT_TRUE(v.u == (v.ptr + 2));
    ASSERT_TRUE(v.u_dot == (v.u + 1));
    int nvar = v.get_local_nvar();
    ASSERT_TRUE(v.u_bar == (v.u_dot + nvar));
    ASSERT_TRUE(v.u_dot_bar == (v.u_bar + nvar));
    ASSERT_TRUE(v.u_tilde == (v.u_dot_bar + nvar));
    ASSERT_TRUE(v.u_dot_tilde == (v.u_tilde + 1));
    ASSERT_TRUE(v.u_bar_tilde == (v.u_dot_tilde + nvar));
    ASSERT_TRUE(v.u_dot_bar_tilde == (v.u_bar_tilde + nvar));
    ASSERT_FALSE(0 == v.indindex);
  }
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
TEST_F(test_df1b2variable, copy_constructor_null)
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

    df1b2variable::noallocate = 1;
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
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
TEST_F(test_df1b2variable, copy_constructor_noallocate_false)
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

    df1b2variable::noallocate = 0;
    df1b2variable v;

    ASSERT_TRUE(v.ptr);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->nvar);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->ncopies);
    ASSERT_TRUE(((twointsandptr*)v.ptr)->ptr == &a);
    ASSERT_EQ(0, *v.ncopies);
    ASSERT_TRUE(v.u == (v.ptr + 2));
    ASSERT_TRUE(v.u_dot == (v.u + 1));
    int nvar = v.get_local_nvar();
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
    ASSERT_TRUE(((twointsandptr*)copy.ptr)->ptr == &a);

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
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
TEST_F(test_df1b2variable, constructor_double)
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
  
    double expected = 6.5;
    df1b2variable v(expected);

    ASSERT_TRUE(v.ptr);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->nvar);
    ASSERT_EQ(0, ((twointsandptr*)v.ptr)->ncopies);
    ASSERT_TRUE(((twointsandptr*)v.ptr)->ptr == &a);
    ASSERT_EQ(0, *v.ncopies);
    ASSERT_DOUBLE_EQ(*v.u, expected);
    ASSERT_TRUE(v.u == (v.ptr + 2));
    ASSERT_TRUE(v.u_dot == (v.u + 1));
    int nvar = v.get_local_nvar();
    ASSERT_TRUE(v.u_bar == (v.u_dot + nvar));
    ASSERT_TRUE(v.u_dot_bar == (v.u_bar + nvar));
    ASSERT_TRUE(v.u_tilde == (v.u_dot_bar + nvar));
    ASSERT_TRUE(v.u_dot_tilde == (v.u_tilde + 1));
    ASSERT_TRUE(v.u_bar_tilde == (v.u_dot_tilde + nvar));
    ASSERT_TRUE(v.u_dot_bar_tilde == (v.u_bar_tilde + nvar));
    ASSERT_FALSE(0 == v.indindex);
  }
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
TEST_F(test_df1b2variable, df1b2vector)
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
  
    df1b2vector v;
    v.allocate(1, 2);
    //df1b2vector copy(v);
    //copy.deallocate();
  }
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
TEST_F(test_df1b2variable, df1b2vector2)
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
  
    df1b2vector v;
    v.allocate(1, 10);
    v.deallocate();
  }
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
TEST_F(test_df1b2variable, ncopies_is_one)
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
  
    df1b2variable v;
    v.allocate();
    df1b2variable copy(v);
    copy.deallocate();
  }
  df1b2variable::pool = save;
  f1b2gradlist = save2;
}
*/
