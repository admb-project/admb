#include <gtest/gtest.h>
#include <fvar.hpp>
#define XCONST const
#include <hs.h>

class test_hs_smatrix: public ::testing::Test {};

TEST_F(test_hs_smatrix, make_dmatrix)
{
  dmatrix m(1, 4, 1, 4);
  m.initialize();

  m(1, 3) = 5; 
  m(2, 2) = 2; 
  m(4, 1) = -62; 

  hs_smatrix make_hs_smatrix(const dmatrix & M);
  hs_smatrix sm = make_hs_smatrix(m);

  cout << sm.get_x() << endl;
  cout << sm.get_x().indexmin() << endl;
  cout << sm.get_x().indexmax() << endl;

  sm.print();
  sm.print_pattern();
  //sm.print_trans_zeros();

  dmatrix make_dmatrix(const hs_smatrix& M);
  dmatrix result = make_dmatrix(sm);

  ASSERT_DOUBLE_EQ(result(1, 1), 0);
  ASSERT_DOUBLE_EQ(result(1, 2), 0);
  ASSERT_DOUBLE_EQ(result(1, 3), m(1, 3));
  ASSERT_DOUBLE_EQ(result(1, 4), 0);
  ASSERT_DOUBLE_EQ(result(2, 1), 0);
  ASSERT_DOUBLE_EQ(result(2, 2), m(2, 2));
  ASSERT_DOUBLE_EQ(result(2, 3), 0);
  ASSERT_DOUBLE_EQ(result(2, 4), 0);
  ASSERT_DOUBLE_EQ(result(3, 1), 0);
  ASSERT_DOUBLE_EQ(result(3, 2), 0);
  ASSERT_DOUBLE_EQ(result(3, 3), 0);
  ASSERT_DOUBLE_EQ(result(3, 4), 0);
  ASSERT_DOUBLE_EQ(result(4, 1), m(4, 1));
  ASSERT_DOUBLE_EQ(result(4, 2), 0);
  ASSERT_DOUBLE_EQ(result(4, 3), 0);
  ASSERT_DOUBLE_EQ(result(4, 4), 0);
}
TEST_F(test_hs_smatrix, constructor_dcompressed_triplet)
{
  dcompressed_triplet data(1, 3, 4, 4);
  int n = data.get_n();
  int m = data.get_m();
  ASSERT_EQ(n, 4);
  ASSERT_EQ(m, 4);
  int indexmin = data.indexmin();
  int indexmax = data.indexmax();
  ASSERT_EQ(indexmin, 1);
  ASSERT_EQ(indexmax, 3);

  imatrix& coords = data.get_coords(); 
  coords.initialize();
  coords(1, 1) = 1;
  coords(2, 1) = 1;
  coords(1, 2) = 2;
  coords(2, 2) = 2;
  coords(1, 3) = 3;
  coords(2, 3) = 4;
  ASSERT_EQ(1, coords.rowmin());
  ASSERT_EQ(2, coords.rowmax());
  ASSERT_EQ(1, coords.colmin());
  ASSERT_EQ(3, coords.colmax());

  dvector& x = data.get_x(); 
  x.initialize();
  x(1) = 5;
  x(2) = -6;
  x(3) = 7;
  ASSERT_EQ(x.indexmin(), 1);
  ASSERT_EQ(x.indexmax(), 3);

  dmatrix result = make_dmatrix(data);

  ASSERT_DOUBLE_EQ(result(1, 1), x(1));
  ASSERT_DOUBLE_EQ(result(1, 2), 0);
  ASSERT_DOUBLE_EQ(result(1, 3), 0);
  ASSERT_DOUBLE_EQ(result(1, 4), 0);
  ASSERT_DOUBLE_EQ(result(2, 1), 0);
  ASSERT_DOUBLE_EQ(result(2, 2), x(2));
  ASSERT_DOUBLE_EQ(result(2, 3), 0);
  ASSERT_DOUBLE_EQ(result(2, 4), 0);
  ASSERT_DOUBLE_EQ(result(3, 1), 0);
  ASSERT_DOUBLE_EQ(result(3, 2), 0);
  ASSERT_DOUBLE_EQ(result(3, 3), 0);
  ASSERT_DOUBLE_EQ(result(3, 4), x(3));
  ASSERT_DOUBLE_EQ(result(4, 1), 0);
  ASSERT_DOUBLE_EQ(result(4, 2), 0);
  ASSERT_DOUBLE_EQ(result(4, 3), 0);
  ASSERT_DOUBLE_EQ(result(4, 4), 0);
}
TEST_F(test_hs_smatrix, DISABLED_make_dmatrix)
{
  dmatrix m(1, 4, 1, 4);
  m.initialize();

  m(1, 3) = 5; 
  m(2, 2) = 2; 
  m(4, 1) = -62; 

  hs_smatrix make_hs_smatrix(const dmatrix & M);
  hs_smatrix sm = make_hs_smatrix(m);

  cout << sm.get_x() << endl;
  cout << sm.get_x().indexmin() << endl;
  cout << sm.get_x().indexmax() << endl;

  sm.print();
  sm.print_pattern();
  //Error
  sm.print_trans_zeros();
}
