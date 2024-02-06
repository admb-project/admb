#include <gtest/gtest.h>

class test_option_match: public ::testing::Test {};


TEST_F(test_option_match, option_negative)
{
  int argc = 3;
  char* argv[] = { (char*)"./simple", (char*)"-option", (char*)"-1"};

  int nopt = 0;

  int option_match(int argc, char** argv, const char *option, int& _nopt);

  ASSERT_EQ(1, option_match(argc, static_cast<char**>(argv), "-option", nopt));
  ASSERT_EQ(0, nopt);
  ASSERT_EQ(-1, std::atoi(argv[2]));
}
TEST_F(test_option_match, calls)
{
  //ASSERT_NE(0, strcmp(0, "-option"));

  int option_match(int argc, char** argv, const char *option, int& _nopt);

  int nopt = -1;
  ASSERT_EQ(-1, option_match(0, 0, 0, nopt));
  ASSERT_EQ(-1, option_match(0, 0, "-check", nopt));

  //Should not happen, but still need to check.
  ASSERT_EQ(-1, option_match(1, 0, "-check", nopt));

  int argc = 1;
  char* argv[1] = { (char*)"./simple"};

  char* option = (char*)"-none";
  ASSERT_EQ(-1, option_match(argc, argv, option, nopt));
  ASSERT_EQ(0, nopt);

  int argc2 = 2;
  char* argv2[2] = { (char*)"./simple", (char*)"-myoption" };
  char* myoption = (char*)"-myoption";
  ASSERT_EQ(1, option_match(argc2, argv2, myoption, nopt));
  ASSERT_EQ(0, nopt);

  int argc3 = 3;
  char* argv3[3] = { (char*)"./simple", (char*)"\0", (char*)"-myoption" };
  char* option3 = (char*)"-myoption";
  ASSERT_EQ(2, option_match(argc3, argv3, option3, nopt));
  ASSERT_EQ(0, nopt);
}
#ifndef _MSC_VER
TEST_F(test_option_match, check_null_indexes)
{
  int option_match(char* _s, const char* option);

#if !defined(__GNUC__) && !defined(__WIN32)
  char* p = strtok(NULL, " ");
  ASSERT_TRUE(p == NULL);
#endif
  //Will produce segmentation fault:
  //ASSERT_NE(0, strcmp(p, " "));

  ASSERT_EQ(-1, option_match(NULL, "abc")); 
  ASSERT_EQ(1, option_match((char*)"abc def ghi jkl", "abc")); 
  ASSERT_EQ(2, option_match((char*)"abc def ghi jkl", "def")); 
  ASSERT_EQ(3, option_match((char*)"abc def ghi jkl", "ghi")); 
  ASSERT_EQ(4, option_match((char*)"abc def ghi jkl", "jkl")); 
  ASSERT_EQ(-1, option_match((char*)"abc def ghi jkl", "f g")); 
}
#endif
TEST_F(test_option_match, check_null_indexes_opt)
{
  int option_match(char* _s, const char* option, int& _nopt);

  int nopt = -1;
  ASSERT_EQ(-1, option_match(NULL, "abc", nopt)); 
  ASSERT_EQ(0, nopt);
  ASSERT_EQ(1, option_match((char*)"abc def ghi jkl", "abc", nopt)); 
  ASSERT_EQ(3, nopt);
  ASSERT_EQ(2, option_match((char*)"abc def ghi jkl", "def", nopt)); 
  ASSERT_EQ(2, nopt);
  ASSERT_EQ(3, option_match((char*)"abc def ghi jkl", "ghi", nopt)); 
  ASSERT_EQ(1, nopt);
  ASSERT_EQ(4, option_match((char*)"abc def ghi jkl", "jkl", nopt)); 
  ASSERT_EQ(0, nopt);
  ASSERT_EQ(-1, option_match((char*)"abc def ghi jkl", "f g", nopt)); 
  ASSERT_EQ(0, nopt);

  ASSERT_EQ(1, option_match((char*)"abc def ghi -jkl", "abc", nopt)); 
  ASSERT_EQ(3, nopt);
  ASSERT_EQ(2, option_match((char*)"abc def ghi -jkl", "def", nopt)); 
  ASSERT_EQ(2, nopt);
  ASSERT_EQ(3, option_match((char*)"abc def ghi -jkl", "ghi", nopt)); 
  ASSERT_EQ(1, nopt);

  ASSERT_EQ(1, option_match((char*)"-abc def ghi -jkl", "-abc", nopt)); 
  ASSERT_EQ(3, nopt);
  ASSERT_EQ(2, option_match((char*)"abc -def ghi -jkl", "-def", nopt)); 
  ASSERT_EQ(2, nopt);
  ASSERT_EQ(3, option_match((char*)"abc def -ghi -jkl", "-ghi", nopt)); 
  ASSERT_EQ(1, nopt);
}
