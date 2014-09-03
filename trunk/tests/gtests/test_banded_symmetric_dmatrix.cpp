#include <gtest/gtest.h>
#include <sstream>
#include <fvar.hpp>

class test_banded_symmetric_dmatrix: public ::testing::Test {};

TEST_F(test_banded_symmetric_dmatrix, constructor)
{
  banded_symmetric_dmatrix m;
}
TEST_F(test_banded_symmetric_dmatrix, ostream)
{
  banded_symmetric_dmatrix m(0, 3, 5);
  m.initialize();

  std::ostringstream oss;

  oss << m;

  ASSERT_EQ("0 0 0 0 \n0 0 0 0 \n0 0 0 0 \n0 0 0 0 \n", oss.str());
}
