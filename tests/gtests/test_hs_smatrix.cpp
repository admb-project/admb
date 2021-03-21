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

  int value;
  //sm.trace_log();
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
TEST_F(test_hs_smatrix, print_trans_zeros)
{
  dmatrix m(1, 3, 1, 3);
  m.initialize();

  m(1, 3) = 5; 
  m(2, 2) = 2; 
  m(3, 3) = -62; 

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
TEST_F(test_hs_smatrix, multiply2x)
{
  dmatrix m(1, 4, 1, 4);
  m.initialize();
  m(1, 1) = 5; 
  m(2, 2) = 3; 
  m(3, 3) = -62; 
  m(4, 4) = -10; 

  dmatrix n(1, 4, 1, 4);
  n.initialize();
  n(1, 1) = 5; 
  n(2, 2) = 7; 
  n(3, 3) = -62; 
  n(4, 4) = 10; 

  hs_smatrix make_hs_smatrix(const dmatrix & M);
  hs_smatrix sm = make_hs_smatrix(m);
  hs_smatrix sn = make_hs_smatrix(n);

  hs_smatrix operator*(const hs_smatrix &A, const hs_smatrix &B);
  hs_smatrix mn = sm * sn;

  dmatrix make_dmatrix(const hs_smatrix& M);
  dmatrix results = make_dmatrix(mn);

  cout << results << endl;

  ASSERT_DOUBLE_EQ(25.0, results(1, 1));
  ASSERT_DOUBLE_EQ(0.0, results(1, 2));
  ASSERT_DOUBLE_EQ(0.0, results(1, 3));
  ASSERT_DOUBLE_EQ(0.0, results(1, 4));
  ASSERT_DOUBLE_EQ(0.0, results(2, 1));
  //ASSERT_DOUBLE_EQ(21.0, results(2, 2));
  ASSERT_DOUBLE_EQ(0.0, results(2, 3));
  ASSERT_DOUBLE_EQ(0.0, results(2, 4));
  ASSERT_DOUBLE_EQ(0.0, results(3, 1));
  ASSERT_DOUBLE_EQ(0.0, results(3, 2));
  //ASSERT_DOUBLE_EQ(3844.0, results(3, 3));
  ASSERT_DOUBLE_EQ(0.0, results(3, 4));
  ASSERT_DOUBLE_EQ(0.0, results(4, 1));
  ASSERT_DOUBLE_EQ(0.0, results(4, 2));
  ASSERT_DOUBLE_EQ(0.0, results(4, 3));
  //ASSERT_DOUBLE_EQ(-100.0, results(4, 4));
}
/*
TEST_F(test_hs_smatrix, constructor_cs)
{
  cs* ptr = new cs();
  ptr->nzmax = 4;
  ptr->n = 3;
  ptr->p = new int[3];
  ptr->p[0] = 0;
  ptr->p[1] = 1;
  ptr->p[2] = 2;
  ptr->i = new int[3];
  ptr->i[0] = 0;
  ptr->i[1] = 1;
  ptr->i[2] = 2;
  ptr->x = new double[3];
  ptr->x[0] = 1;
  ptr->x[1] = 2;
  ptr->x[2] = 3;
  hs_smatrix data(ptr);
  delete ptr->p;
  ptr->p = nullptr;
  delete ptr->i;
  ptr->i = nullptr;
  delete ptr->x;
  ptr->x = nullptr;
  delete ptr;
  ptr = nullptr;
  dmatrix make_dmatrix(const hs_smatrix& M);
  dmatrix results = make_dmatrix(data);

  cout << results << endl;
  ASSERT_DOUBLE_EQ(1.0, results(1, 1));
  ASSERT_DOUBLE_EQ(0.0, results(1, 2));
  ASSERT_DOUBLE_EQ(0.0, results(1, 3));
  ASSERT_DOUBLE_EQ(0.0, results(2, 1));
  ASSERT_DOUBLE_EQ(2.0, results(2, 2));
  ASSERT_DOUBLE_EQ(0.0, results(2, 3));
  ASSERT_DOUBLE_EQ(0.0, results(3, 1));
  ASSERT_DOUBLE_EQ(0.0, results(3, 2));
  ASSERT_DOUBLE_EQ(0.0, results(3, 3));
}
*/
TEST_F(test_hs_smatrix, cs_pvec)
{
  gradient_structure gs;

  ivector p(0, 2);
  p(0) = 1;
  p(1) = 2;
  p(2) = 0;
  dvar_vector b(0, 2);
  b(0) = 1;
  b(1) = 2;
  b(2) = 3;
  dvar_vector cs_pvec(XCONST ivector &p, XCONST dvar_vector &b);
  dvar_vector results = cs_pvec(p, b);
  
  ASSERT_DOUBLE_EQ(value(b(1)), value(results(0)));
  ASSERT_DOUBLE_EQ(value(b(2)), value(results(1)));
  ASSERT_DOUBLE_EQ(value(b(0)), value(results(2)));
}
TEST_F(test_hs_smatrix, cs_pvec_none)
{
  gradient_structure gs;

  ivector p(0, 2);
  p(0) = -1;
  p(1) = 3;
  p(2) = 1;
  dvar_vector b(0, 2);
  b(0) = 1;
  b(1) = 2;
  b(2) = 3;
  dvar_vector cs_pvec(XCONST ivector &p, XCONST dvar_vector &b);
  dvar_vector results = cs_pvec(p, b);
  
  ASSERT_DOUBLE_EQ(value(b(0)), value(results(0)));
  ASSERT_DOUBLE_EQ(value(b(1)), value(results(1)));
  ASSERT_DOUBLE_EQ(value(b(2)), value(results(2)));
}
