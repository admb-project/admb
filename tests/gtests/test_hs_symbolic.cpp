#include <gtest/gtest.h>
#include <fvar.hpp>
#define XCONST const
#include <hs.h>

class test_hs_symbolic: public ::testing::Test {};

TEST_F(test_hs_symbolic, default_constructor)
{
  hs_symbolic data;
}
TEST_F(test_hs_symbolic, constructor_dvar_compressed_triplet)
{
  gradient_structure gs;
  dvar_compressed_triplet data(1, 3, 3, 3);
  int n = data.get_n();
  int m = data.get_m();
  ASSERT_EQ(n, 3);
  ASSERT_EQ(m, 3);
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
  coords(2, 3) = 3;
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

  hs_symbolic symbolic(data, 0);
}
