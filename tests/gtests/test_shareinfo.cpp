#include <gtest/gtest.h>
#include <fvar.hpp>
#include <admodel.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

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
TEST_F(test_shareinfo, get_inv_matrix_shared_same)
{
  index_type sf(1);
  index_type af(1);
  shareinfo info(sf, af);
  info.get_current_phase() = 0;
  info.get_inv_matrix_shared(0);
}
TEST_F(test_shareinfo, get_inv_matrix_shared_01)
{
  ad_exit=&test_ad_exit;

  index_type sf(1);
  index_type af(1);
  shareinfo info(sf, af);
  info.get_current_phase() = 0;
  ASSERT_THROW(info.get_inv_matrix_shared(1), int);
}
