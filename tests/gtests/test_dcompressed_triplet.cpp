#include <gtest/gtest.h>
#include <admodel.h>
#define XCONST const
#include <hs.h>

void test_ad_exit(const int exit_code);

class test_dcompressed_triplet: public ::testing::Test { };

TEST_F(test_dcompressed_triplet, make_dmatrix)
{
  dcompressed_triplet data(1, 3, 3, 4);
  int n = data.get_n();
  int m = data.get_m();
  ASSERT_EQ(n, 3);
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

  dmatrix make_dmatrix(dcompressed_triplet& M);
  dmatrix result = make_dmatrix(data);

  ASSERT_DOUBLE_EQ(x(1), result(1, 1));
  ASSERT_DOUBLE_EQ(0, result(1, 2));
  ASSERT_DOUBLE_EQ(0, result(1, 3));
  ASSERT_DOUBLE_EQ(0, result(1, 4));

  ASSERT_DOUBLE_EQ(0, result(2, 1));
  ASSERT_DOUBLE_EQ(x(2), result(2, 2));
  ASSERT_DOUBLE_EQ(0, result(2, 3));
  ASSERT_DOUBLE_EQ(0, result(2, 4));

  ASSERT_DOUBLE_EQ(0, result(3, 1));
  ASSERT_DOUBLE_EQ(0, result(3, 2));
  ASSERT_DOUBLE_EQ(0, result(3, 3));
  ASSERT_DOUBLE_EQ(x(3), result(3, 4));
}
TEST_F(test_dcompressed_triplet, make_sdmatrix)
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

  dmatrix make_sdmatrix(dcompressed_triplet& M);
  dmatrix result = make_sdmatrix(data);

  ASSERT_DOUBLE_EQ(x(1), result(1, 1));
  ASSERT_DOUBLE_EQ(0, result(1, 2));
  ASSERT_DOUBLE_EQ(0, result(1, 3));
  ASSERT_DOUBLE_EQ(0, result(1, 4));

  ASSERT_DOUBLE_EQ(0, result(2, 1));
  ASSERT_DOUBLE_EQ(x(2), result(2, 2));
  ASSERT_DOUBLE_EQ(0, result(2, 3));
  ASSERT_DOUBLE_EQ(0, result(2, 4));

  ASSERT_DOUBLE_EQ(0, result(3, 1));
  ASSERT_DOUBLE_EQ(0, result(3, 2));
  ASSERT_DOUBLE_EQ(0, result(3, 3));
  ASSERT_DOUBLE_EQ(x(3), result(3, 4));

  ASSERT_DOUBLE_EQ(0, result(4, 1));
  ASSERT_DOUBLE_EQ(0, result(4, 2));
  ASSERT_DOUBLE_EQ(x(3), result(4, 3));
  ASSERT_DOUBLE_EQ(0, result(4, 4));
}
TEST_F(test_dcompressed_triplet, make_sdmatrix_m_n)
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

  dmatrix make_dmatrix(dcompressed_triplet& M,int n,int m);
  dmatrix result = make_dmatrix(data, 4, 4);
  ASSERT_EQ(result.rowmax(), 4);
  ASSERT_EQ(result.colmax(), 4);

  ASSERT_DOUBLE_EQ(x(1), result(1, 1));
  ASSERT_DOUBLE_EQ(0, result(1, 2));
  ASSERT_DOUBLE_EQ(0, result(1, 3));
  ASSERT_DOUBLE_EQ(0, result(1, 4));

  ASSERT_DOUBLE_EQ(0, result(2, 1));
  ASSERT_DOUBLE_EQ(x(2), result(2, 2));
  ASSERT_DOUBLE_EQ(0, result(2, 3));
  ASSERT_DOUBLE_EQ(0, result(2, 4));

  ASSERT_DOUBLE_EQ(0, result(3, 1));
  ASSERT_DOUBLE_EQ(0, result(3, 2));
  ASSERT_DOUBLE_EQ(0, result(3, 3));
  ASSERT_DOUBLE_EQ(x(3), result(3, 4));

  ASSERT_DOUBLE_EQ(0, result(4, 1));
  ASSERT_DOUBLE_EQ(0, result(4, 2));
  ASSERT_DOUBLE_EQ(x(3), result(4, 3));
  ASSERT_DOUBLE_EQ(0, result(4, 4));
}
TEST_F(test_dcompressed_triplet, deallocate)
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

  data.deallocate();
  n = data.get_n();
  m = data.get_m();
  ASSERT_EQ(n, -1);
  ASSERT_EQ(m, -1);
  indexmin = data.indexmin();
  indexmax = data.indexmax();
  ASSERT_EQ(indexmin, 1);
  ASSERT_EQ(indexmax, 3);

  imatrix& coords = data.get_coords(); 
  ASSERT_EQ(1, coords.rowmin());
  ASSERT_EQ(0, coords.rowmax());

  dvector& x = data.get_x(); 
  ASSERT_EQ(x.indexmin(), 1);
  ASSERT_EQ(x.indexmax(), 3);
}
