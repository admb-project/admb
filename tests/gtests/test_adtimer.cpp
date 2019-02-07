#include <gtest/gtest.h>
#include <fvar.hpp>

void ADSleep(unsigned int t);

class test_adtimer: public ::testing::Test {};

#ifndef __MINGW32__
TEST_F(test_adtimer, get_elapsed)
{
  adtimer t;

  double mls_t0 = t.get_elapsed_time();
  ADSleep(1);
  double mls_t1 = t.get_elapsed_time();
  ASSERT_LT(mls_t0, mls_t1);
  ADSleep(1);
  double mls_t2 = t.get_elapsed_time_and_reset();
  ASSERT_LT(mls_t1, mls_t2);
  double mls_t3 = t.get_elapsed_time_and_reset();
  ASSERT_LT(mls_t3, mls_t2);
}
#endif
TEST_F(test_adtimer, _adwait)
{
  long int _adwait(double sec);
  long int total_wait = _adwait(3.5);
  ASSERT_GT(total_wait, 4);
}
