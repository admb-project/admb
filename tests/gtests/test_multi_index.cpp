#include <gtest/gtest.h>
#include <fvar.hpp>

class test_multi_index: public ::testing::Test {};

TEST_F(test_multi_index, constructor)
{
  multi_index m(1, 3, 4);
  cout << m.get_offset() << endl;
}
