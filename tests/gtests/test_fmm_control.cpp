#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adstring.hpp>

class test_fmm_control: public ::testing::Test {};

/**
 * Tests for errors in "void adstring::to_lower(void)"
 */
TEST_F(test_fmm_control, constructor)
{
  fmm_control fc;
  EXPECT_EQ(0, fc.noprintx);
  EXPECT_EQ(0.0, fc.fringe);
  EXPECT_EQ(500, fc.maxfn);
  EXPECT_EQ(1, fc.iprint);
  EXPECT_EQ(0.0001, fc.crit);
  EXPECT_EQ(30, fc.imax);
  EXPECT_EQ(0, fc.dfn);
  EXPECT_EQ(0, fc.ifn);
  EXPECT_EQ(0, fc.iexit);
  EXPECT_EQ(0, fc.ialph);
  EXPECT_EQ(0, fc.ihflag);
  EXPECT_EQ(0, fc.ihang);
  EXPECT_EQ(1, fc.scroll_flag);
  EXPECT_EQ(0, fc.maxfn_flag);
  EXPECT_EQ(0, fc.quit_flag);
  EXPECT_EQ(.0000001, fc.min_improve);
  EXPECT_EQ(0, fc.ireturn);
  EXPECT_EQ(-1, fc.dcheck_flag);
  EXPECT_EQ(1, fc.use_control_c);
}
/**
 * Tests to make sure fringe value is copied.
 */
TEST_F(test_fmm_control, copy_constructor)
{
  fmm_control source;
  source.fringe = 1.0;
  fmm_control copy(source);
  EXPECT_EQ(1.0, copy.fringe);
}
TEST_F(test_fmm_control, constructor_ipars)
{
  lvector ipars(1, 5);
  ipars[1] = LONG_MAX;
  ipars[2] = LONG_MAX;
  ipars[3] = INT_MAX;
  ipars[4] = INT_MAX;
  ipars[5] = INT_MAX;
  fmm_control source(ipars);
  EXPECT_EQ(LONG_MAX, ipars[1]);
  EXPECT_EQ(LONG_MAX, ipars[2]);
  EXPECT_EQ(INT_MAX, ipars[3]);
  EXPECT_EQ(INT_MAX, ipars[4]);
  EXPECT_EQ(INT_MAX, ipars[5]);
}
