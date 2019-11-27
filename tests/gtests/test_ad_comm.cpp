#include <gtest/gtest.h>
#include <fvar.hpp>
#include <cmath>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_ad_comm: public ::testing::Test {};

class ad_comm2: public ad_comm
{
public:
ad_comm2(): ad_comm() {}
ad_comm2(int argc, char *argv[]): ad_comm(argc, argv) {}
};

TEST_F(test_ad_comm, defaultconstructor)
{
  ad_comm::argc = 0;
  ad_comm::argv = 0;
  ad_comm::adprogram_name = "test_ad_comm";
  ad_comm2 adcomm;
}
TEST_F(test_ad_comm, constructor)
{
  int argc = 3;
  char* argv[] = { "./simple" , "-ind", "other.dat"};
  ad_comm2 adcomm(argc, argv);
  ad_comm::argc = 0;
  ad_comm::argv = nullptr;
}
TEST_F(test_ad_comm, timer)
{
  int argc = 2;
  char* argv[] = { "./simple" , "-timer" };
  ad_comm2 adcomm(argc, argv);
  ad_comm::argc = 0;
  ad_comm::argv = nullptr;
}
TEST_F(test_ad_comm, help)
{
  int argc = 2;
  char* argv[] = { "./simple" , "-help"};
  ASSERT_ANY_THROW({
    ad_comm2 adcomm(argc, argv);
  });
  ad_comm::argc = 0;
  ad_comm::argv = nullptr;
}
TEST_F(test_ad_comm, info)
{
  int argc = 2;
  char* argv[] = { "./simple" , "-info"};
  ASSERT_ANY_THROW({
    ad_comm2 adcomm(argc, argv);
  });
  ad_comm::argc = 0;
  ad_comm::argv = nullptr;
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
TEST_F(test_ad_comm, change_pinfile_name_error)
{
  ad_exit=&test_ad_exit;

  ASSERT_TRUE(ad_comm::global_parfile == NULL);

  streampos off;
  ASSERT_ANY_THROW({
    off = ad_comm::change_pinfile_name("filedoesnotexist.txt2", off);
  });
#if defined(_MSC_VER) && (_MSC_VER >= 1910)
  ASSERT_TRUE(off == 0);
#endif

  ASSERT_TRUE(ad_comm::global_parfile == NULL);
}
TEST_F(test_ad_comm, change_pinfile_name)
{
  ad_exit=&test_ad_exit;

  ofstream ofs("pinfiledoesexist.pin");
  ofs << "#empty";
  ofs.close();

  ASSERT_TRUE(ad_comm::global_parfile == NULL);

  streampos off;
  off = ad_comm::change_pinfile_name("pinfiledoesexist.pin", off);
#if defined(_MSC_VER) && (_MSC_VER >= 1910)
  ASSERT_TRUE(off == 0);
#endif

  ASSERT_TRUE(ad_comm::global_parfile != NULL);

  ASSERT_ANY_THROW({
    off = ad_comm::change_pinfile_name("filedoesnotexist.txt2", off);
  });
  ASSERT_TRUE(off == 0);

  ASSERT_TRUE(ad_comm::global_parfile == NULL);
}
TEST_F(test_ad_comm, change_datafile_name)
{
  ad_exit=&test_ad_exit;

  ofstream ofs("datafiledoesexist.dat");
  ofs << "#empty";
  ofs.close();

  ASSERT_TRUE(ad_comm::global_datafile == NULL);

  streampos off;
  off = ad_comm::change_datafile_name("datafiledoesexist.dat", off);
#if defined(_MSC_VER) && (_MSC_VER >= 1910)
  ASSERT_TRUE(off == 0);
#endif

  ASSERT_TRUE(ad_comm::global_datafile != NULL);

  ASSERT_ANY_THROW({
    off = ad_comm::change_datafile_name("filedoesnotexist.txt2", off);
  });
  ASSERT_TRUE(off == 0);

  ASSERT_TRUE(ad_comm::global_datafile == NULL);
}
