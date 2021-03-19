#include <gtest/gtest.h>
#include <admodel.h>
#define XCONST const
#include <hs.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar_compressed_triplet: public ::testing::Test { };

TEST_F(test_dvar_compressed_triplet, default_constructor)
{
  gradient_structure gs;
  dvar_compressed_triplet data(1, 3, 3, 4);
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

  dvar_vector& x = data.get_x(); 
  x.initialize();
  x(1) = 5;
  x(2) = -6;
  x(3) = 7;
  ASSERT_EQ(x.indexmin(), 1);
  ASSERT_EQ(x.indexmax(), 3);

  dvar_matrix make_dvar_matrix(dvar_compressed_triplet& M);
  dvar_matrix result = make_dvar_matrix(data);

  ASSERT_DOUBLE_EQ(value(x(1)), value(result(1, 1)));
  ASSERT_DOUBLE_EQ(0, value(result(1, 2)));
  ASSERT_DOUBLE_EQ(0, value(result(1, 3)));
  ASSERT_DOUBLE_EQ(0, value(result(1, 4)));

  ASSERT_DOUBLE_EQ(0, value(result(2, 1)));
  ASSERT_DOUBLE_EQ(value(x(2)), value(result(2, 2)));
  ASSERT_DOUBLE_EQ(0, value(result(2, 3)));
  ASSERT_DOUBLE_EQ(0, value(result(2, 4)));

  ASSERT_DOUBLE_EQ(0, value(result(3, 1)));
  ASSERT_DOUBLE_EQ(0, value(result(3, 2)));
  ASSERT_DOUBLE_EQ(0, value(result(3, 3)));
  ASSERT_DOUBLE_EQ(value(x(3)), value(result(3, 4)));
}
