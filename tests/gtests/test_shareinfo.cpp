#include <gtest/gtest.h>
#include <fvar.hpp>
#include <admodel.h>

class test_shareinfo: public ::testing::Test {};

TEST_F(test_shareinfo, constructor_set_bmap)
{
  index_type sf(1);
  index_type af(1);
  shareinfo info(sf, af);
  ASSERT_EQ(info.get_current_phase(), -1);
  ASSERT_EQ(info.get_dimension(), 0);
  ASSERT_EQ(info.get_bmap().indexmin(), 1);
  ASSERT_EQ(info.get_bmap().indexmax(), 0);

  i3_array bmap(1, 5);
  
  info.set_bmap(bmap);
  ASSERT_EQ(info.get_bmap().indexmin(), 1);
  ASSERT_EQ(info.get_bmap().indexmax(), 5);

  i3_array bmap2(2, 8);
  info.reset_bmap(bmap2);
  ASSERT_EQ(info.get_bmap().indexmin(), 2);
  ASSERT_EQ(info.get_bmap().indexmax(), 8);
}
