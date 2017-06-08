#include <gtest/gtest.h>
#include <fvar.hpp>
#include <cmath>

class test_ad_comm: public ::testing::Test {};

class ad_comm2: public ad_comm
{
public:
ad_comm2(): ad_comm() {}
ad_comm2(int argc, char *argv[]): ad_comm(argc, argv) {}
};

/*
TEST_F(test_ad_comm, defaultconstructor)
{
  ad_comm::argc = 0;
  ad_comm::argv = 0;
  ad_comm2 adcomm;
}
*/
TEST_F(test_ad_comm, constructor)
{
  int argc = 3;
  char* argv[] = { "./simple" , "-ind", "other.dat"};
  ad_comm2 adcomm(argc, argv);
}
TEST_F(test_ad_comm, timer)
{
  int argc = 2;
  char* argv[] = { "./simple" , "-timer" };
  ad_comm2 adcomm(argc, argv);
}
TEST_F(test_ad_comm, help)
{
  int argc = 2;
  char* argv[] = { "./simple" , "-help"};
  ASSERT_ANY_THROW({
    ad_comm2 adcomm(argc, argv);
  });
}
TEST_F(test_ad_comm, info)
{
  int argc = 2;
  char* argv[] = { "./simple" , "-info"};
  ASSERT_ANY_THROW({
    ad_comm2 adcomm(argc, argv);
  });
}
TEST_F(test_ad_comm, option_match_ind)
{
  int argc = 7;
  char* argv[] = {"./dogsbmDIC", "-ind", "dog4s.ctl", "-ainp", "dog4p.pin", "-nox", "-est"};
  int opt = option_match(argc, argv, "-ind");
  EXPECT_EQ(1, opt);
}
TEST_F(test_ad_comm, option_match_ind_option_with_unicode_char)
{
  int argc = 3;
  //the '-' is a unicode char
  char* argv[] = {"./dogsbmDIC", "–ind", "dog4s.ctl"};
  EXPECT_EQ('\xE2', argv[1][0]);
  EXPECT_EQ('\x80', argv[1][1]);
  EXPECT_EQ('\x93', argv[1][2]);
  int opt = option_match(argc, argv, "-ind");
  EXPECT_EQ(-1, opt);
}
