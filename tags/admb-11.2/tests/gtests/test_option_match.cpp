#include <gtest/gtest.h>

class test_option_match: public ::testing::Test {};

TEST_F(test_option_match, calls)
{
  //ASSERT_NE(0, strcmp(0, "-option"));

  int option_match(int argc, char *argv[], const char *option, const int& _nopt);

  int nopt = -1;
  ASSERT_EQ(-1, option_match(0, 0, 0, nopt));
  ASSERT_EQ(-1, option_match(0, 0, "-check", nopt));

  //Should not happen, but still need to check.
  ASSERT_EQ(-1, option_match(1, 0, "-check", nopt));

  int argc = 1;
  char* argv[] = { "./simple"};

  char* option = "-none";
  ASSERT_EQ(-1, option_match(argc, argv, option, nopt));
  ASSERT_EQ(0, nopt);

  int argc2 = 2;
  char* argv2[] = { "./simple", "-myoption" };
  char* myoption = "-myoption";
  ASSERT_EQ(1, option_match(argc2, argv2, myoption, nopt));
  ASSERT_EQ(0, nopt);

  int argc3 = 3;
  char* argv3[] = { "./simple", "\0", "-myoption" };
  char* option3 = "-myoption";
  ASSERT_EQ(2, option_match(argc3, argv3, option3, nopt));
  ASSERT_EQ(0, nopt);
}
