#include <gtest/gtest.h>
#include <inttypes.h>
#include <climits>

class test_idea: public ::testing::Test {};

TEST_F(test_idea, if_literal_double)
{
  if (1.0e-10)
  {
  }
  else
  {
    FAIL();
  }
  if (1.0e+10)
  {
  }
  else
  {
    FAIL();
  }
  if (-1.0e-10)
  {
  }
  else
  {
    FAIL();
  }
  if (-1.0e+10)
  {
  }
  else
  {
    FAIL();
  }
  if (0.0)
  {
    FAIL();
  }
  else
  {
  }
}
TEST_F(test_idea, if_double)
{
  double d = 1.0e-10;
  if (d)
  {
  }
  else
  {
    FAIL();
  }
  d = 1.0e+10;
  if (d)
  {
  }
  else
  {
    FAIL();
  }
  d = -1.0e-10;
  if (d)
  {
  }
  else
  {
    FAIL();
  }
  d = -1.0e+10;
  if (d)
  {
  }
  else
  {
    FAIL();
  }
  d = 0.0;
  if (d)
  {
    FAIL();
  }
  else
  {
  }
}
TEST_F(test_idea, casting)
{
  long actual = long(-sizeof(off_t));
  long expected = -((long)sizeof(off_t));
  ASSERT_EQ(expected, actual);
}
TEST_F(test_idea, totalbytes)
{
  char s[10];
  char* _a = &s[0];
  char* _b = &s[9];

  uintptr_t a = (uintptr_t)_a;
  uintptr_t b = (uintptr_t)_b;
  ptrdiff_t actual = b - a;
  ASSERT_EQ(9, actual);

  char* _c = &s[3];
  char* _d = &s[7];
  uintptr_t c = (uintptr_t)_c;
  uintptr_t d = (uintptr_t)_d;
  ptrdiff_t actual2 = d - c;
  ASSERT_EQ(4, actual2);
}
TEST_F(test_idea, memcpy)
{
  char s[] = "12XX567YZ89\0";
  char* source = &s[7];
  char* destination = &s[2];
  size_t num = 2;
  memcpy(destination, source, num);
  ASSERT_EQ('1', s[0]);
  ASSERT_EQ('2', s[1]);
  ASSERT_EQ('Y', s[2]);
  ASSERT_EQ('Z', s[3]);
  ASSERT_EQ('5', s[4]);
  ASSERT_EQ('6', s[5]);
  ASSERT_EQ('7', s[6]);
  ASSERT_EQ('Y', s[7]);
  ASSERT_EQ('Z', s[8]);
  ASSERT_EQ('8', s[9]);
  ASSERT_EQ('9', s[10]);
  ASSERT_EQ('\0', s[11]);
}
TEST_F(test_idea, make_sub_directory)
{
  int make_sub_directory(const char* s);
  int ret = make_sub_directory("make_sub_directory");
  ASSERT_EQ(1, ret);
  ret = make_sub_directory("make_sub_directory");
  ASSERT_EQ(1, ret);
}
TEST_F(test_idea, multichar)
{
  ASSERT_FALSE(!(sizeof(char) == 1));
}
TEST_F(test_idea, multiple_int_double)
{
  int i = 5; 
  double d = 2.5; 
  ASSERT_DOUBLE_EQ(d * i, 12.5);
  ASSERT_DOUBLE_EQ(i * d, 12.5);
}
TEST_F(test_idea, parse_dll_options)
{
  char** parse_dll_options(char *pname, const int& _argc, char *s);

#ifdef _WIN32
  char* pname = "one two three four";
  char* pname_exe = "one two three four.exe";
#else
  char* pname = "one two three four";
#endif

  int argc = 4;
  char** ret = parse_dll_options(pname, argc, "one");
#ifdef _WIN32
  ASSERT_STREQ(pname_exe, ret[0]);
#else
  ASSERT_STREQ(pname, ret[0]);
#endif
  ASSERT_EQ(2, argc);
  free(ret);

  argc = 4;
  ret = parse_dll_options(pname, argc, "two");
#ifdef _WIN32
  ASSERT_STREQ(pname_exe, ret[0]);
#else
  ASSERT_STREQ(pname, ret[0]);
#endif
  ASSERT_EQ(2, argc);
  free(ret);

  argc = 4;
  ret = parse_dll_options(pname, argc, "three");
#ifdef _WIN32
  ASSERT_STREQ(pname_exe, ret[0]);
#else
  ASSERT_STREQ(pname, ret[0]);
#endif
  ASSERT_EQ(2, argc);
  free(ret);

  argc = 4;
  ret = parse_dll_options(pname, argc, "four");
#ifdef _WIN32
  ASSERT_STREQ(pname_exe, ret[0]);
#else
  ASSERT_STREQ(pname, ret[0]);
#endif
  ASSERT_EQ(2, argc);
  free(ret);
}
TEST_F(test_idea, parse_dll_options_same)
{
  char** parse_dll_options(char *pname, const int& _argc, char *s);

#ifdef _WIN32
  char* pname = "one two three four one two three four";
  char* pname_exe = "one two three four one two three four.exe";
#else
  char* pname = "one two three four one two three four";
#endif

  int argc = 8;
  char** ret = parse_dll_options(pname, argc, "one");
#ifdef _WIN32
  ASSERT_STREQ(pname_exe, ret[0]);
#else
  ASSERT_STREQ(pname, ret[0]);
#endif

  ASSERT_EQ(2, argc);
  free(ret);

  argc = 8;
  ret = parse_dll_options(pname, argc, "two");
#ifdef _WIN32
  ASSERT_STREQ(pname_exe, ret[0]);
#else
  ASSERT_STREQ(pname, ret[0]);
#endif
  ASSERT_EQ(2, argc);
  free(ret);

  argc = 8;
  ret = parse_dll_options(pname, argc, "three");
#ifdef _WIN32
  ASSERT_STREQ(pname_exe, ret[0]);
#else
  ASSERT_STREQ(pname, ret[0]);
#endif
  ASSERT_EQ(2, argc);
  free(ret);

  argc = 8;
  ret = parse_dll_options(pname, argc, "four");
#ifdef _WIN32
  ASSERT_STREQ(pname_exe, ret[0]);
#else
  ASSERT_STREQ(pname, ret[0]);
#endif
  ASSERT_EQ(2, argc);
  free(ret);
}
#ifdef _WIN32
TEST_F(test_idea, no_dll_options)
{
  char** no_dll_options(char *pname, const int& _nopt);
  const int nopt = 0;
  char* pname = (char*)"pname";
  char** ret = no_dll_options(pname, nopt);
  if (ret)
  {
    ASSERT_STREQ((char*)"pname.exe", ret[0]);
    delete [] ret;
    ret = 0;
  }
  else
  {
    FAIL();
  }
  ASSERT_EQ(nopt, 1);
}
TEST_F(test_idea, off_t)
{
  #if (defined(_FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64))
  ASSERT_EQ(64, sizeof(off_t) * CHAR_BIT);
  #else
  ASSERT_EQ(32, sizeof(off_t) * CHAR_BIT);
  #endif
}
#endif
