#include <gtest/gtest.h>

class test_option_match: public ::testing::Test {};

TEST_F(test_option_match, calls)
{
  //ASSERT_NE(0, strcmp(0, "-option"));

  int option_match(int argc, char *argv[], const char *option, int& _nopt);

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
TEST_F(test_option_match, check_null_indexes)
{
  int option_match(char* _s, const char* option);

  char* p = strtok(NULL, " ");
  ASSERT_TRUE(p == NULL);
  //Will produce segmentation fault:
  //ASSERT_NE(0, strcmp(p, " "));

  ASSERT_EQ(-1, option_match(NULL, "abc")); 
  ASSERT_EQ(1, option_match("abc def ghi jkl", "abc")); 
  ASSERT_EQ(2, option_match("abc def ghi jkl", "def")); 
  ASSERT_EQ(3, option_match("abc def ghi jkl", "ghi")); 
  ASSERT_EQ(4, option_match("abc def ghi jkl", "jkl")); 
  ASSERT_EQ(-1, option_match("abc def ghi jkl", "f g")); 
}
TEST_F(test_option_match, check_null_indexes_opt)
{
  int option_match(char* _s, const char* option, int& _nopt);

  int nopt = -1;
  ASSERT_EQ(-1, option_match(NULL, "abc", nopt)); 
  ASSERT_EQ(0, nopt);
  ASSERT_EQ(1, option_match("abc def ghi jkl", "abc", nopt)); 
  ASSERT_EQ(3, nopt);
  ASSERT_EQ(2, option_match("abc def ghi jkl", "def", nopt)); 
  ASSERT_EQ(2, nopt);
  ASSERT_EQ(3, option_match("abc def ghi jkl", "ghi", nopt)); 
  ASSERT_EQ(1, nopt);
  ASSERT_EQ(4, option_match("abc def ghi jkl", "jkl", nopt)); 
  ASSERT_EQ(0, nopt);
  ASSERT_EQ(-1, option_match("abc def ghi jkl", "f g", nopt)); 
  ASSERT_EQ(0, nopt);

  ASSERT_EQ(1, option_match("abc def ghi -jkl", "abc", nopt)); 
  ASSERT_EQ(3, nopt);
  ASSERT_EQ(2, option_match("abc def ghi -jkl", "def", nopt)); 
  ASSERT_EQ(2, nopt);
  ASSERT_EQ(3, option_match("abc def ghi -jkl", "ghi", nopt)); 
  ASSERT_EQ(1, nopt);

  ASSERT_EQ(1, option_match("-abc def ghi -jkl", "-abc", nopt)); 
  ASSERT_EQ(3, nopt);
  ASSERT_EQ(2, option_match("abc -def ghi -jkl", "-def", nopt)); 
  ASSERT_EQ(2, nopt);
  ASSERT_EQ(3, option_match("abc def -ghi -jkl", "-ghi", nopt)); 
  ASSERT_EQ(1, nopt);
}
