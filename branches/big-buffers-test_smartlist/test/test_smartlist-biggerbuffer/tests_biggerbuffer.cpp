#include <fstream>
#include <limits.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include <exception>
#include <cstdlib>
#include <algorithm>
using std::fstream;
#include <df1b2fun.h>

const int argc = 3;
const char *argv[3] = {"binomial", "-l1", "1000003"};

class tests_test_smartlist: public ::testing::Test
{
public:
  tests_test_smartlist() {}
  virtual ~tests_test_smartlist() {}
  virtual void SetUp() {}
  virtual void TearDown() {}
};

#define main main_binomial
#include "binomial.cpp"
#undef main

TEST(test_smartlist, main)
{
  main_binomial(argc, argv);
}
TEST(test_smartlist, atoi)
{
  std::ostringstream oss;
  oss << INT_MAX;
  int i = std::atoi(oss.str().c_str());
  EXPECT_EQ(INT_MAX, i);
}
TEST(test_smartlist, atoiwithlargeint)
{
  long long expected = INT_MAX;
  expected++;
  std::ostringstream oss;
  oss << expected;
  int i = std::atoi(oss.str().c_str());
  EXPECT_NE(expected, i);
}
TEST(test_smartlist, bigcppwrite)
{
  fstream fp;

  fp.open("test.txt", fstream::in | fstream::out | fstream::binary | fstream::trunc);

  long long nbytes = INT_MAX;
  nbytes++;

  char* buffer = new char[nbytes];

  ASSERT_NO_THROW(fp.write(buffer, nbytes));

  delete buffer;
  buffer = 0;

  fp.close();

  unlink("test.txt");
}
TEST(test_smartlist, bigcwrite)
{
  int fp = open("test.txt", O_RDWR | O_CREAT | O_TRUNC | O_BINARY, S_IREAD | S_IWRITE);

  long long expected = INT_MAX;
  expected++;

  char* buffer = new char[expected];
  long long got = write(fp, buffer, expected);
  EXPECT_NE(got, expected);

  delete buffer;
  buffer = 0;

  close(fp);

  unlink("test.txt");
}
TEST(test_smartlist, allocate)
{
  const size_t ndoubles = 20;
  const size_t nbytes = ndoubles * sizeof(double);
  test_smartlist lst;
  lst.allocate(nbytes, "list.txt");
  size_t size = nbytes;
  EXPECT_EQ(lst.bufsize, size);
  EXPECT_EQ(lst.bptr, lst.buffer);
  EXPECT_EQ(lst.true_buffend, lst.buffend + sizeof(double) - 1);
  EXPECT_EQ(lst.true_buffer + sizeof(double), lst.buffer);
  EXPECT_EQ(lst.doubleptr[0], 5678.9);
  EXPECT_EQ(lst.doubleptr[ndoubles + 1], 9876.5);
}
TEST(test_smartlist, memcpy)
{
  const size_t nbytes = 20;
  test_smartlist lst;
  lst.allocate(nbytes, "list.txt");
            
  char char5[] = "01234";
  memcpy(lst, char5, 5);
  EXPECT_EQ(lst.bptr, lst.buffer + 5);
  EXPECT_EQ(lst.buffer[0], '0');
  EXPECT_EQ(lst.buffer[1], '1');
  EXPECT_EQ(lst.buffer[2], '2');
  EXPECT_EQ(lst.buffer[3], '3');
  EXPECT_EQ(lst.buffer[4], '4');
}
TEST(test_smartlist, memcpy2)
{
  const size_t nbytes = 20;
  test_smartlist lst;
  lst.allocate(nbytes, "list.txt");
            
  char char5[] = "01234";
  memcpy(char5, lst, 5);
  EXPECT_EQ(lst.bptr, lst.buffer + 5);
  EXPECT_EQ(lst.buffer[0], '0');
  EXPECT_EQ(lst.buffer[1], '1');
  EXPECT_EQ(lst.buffer[2], '2');
  EXPECT_EQ(lst.buffer[3], '3');
  EXPECT_EQ(lst.buffer[4], '4');
}
TEST(test_smartlist, writeread)
{
  const size_t nbytes = 20;
  test_smartlist lst;
  lst.allocate(nbytes, "list.txt");
            
  char char5[] = "01234";
  memcpy(lst, char5, 5);
  EXPECT_EQ(lst.bptr, lst.buffer + 5);
  lst.write_buffer();
  EXPECT_EQ(lst.bptr, lst.buffer);
  lst.buffer[0] = 'x';
  lst.buffer[1] = 'x';
  lst.buffer[2] = 'x';
  lst.buffer[3] = 'x';
  lst.buffer[4] = 'x';
  EXPECT_EQ(lst.direction, 0);
  lst.set_backword();
  EXPECT_EQ(lst.direction, -1);
  lst.read_buffer();
  EXPECT_EQ(lst.recend, lst.buffer + 4);
  EXPECT_EQ(*(lst.buffer + 4), '4');
  EXPECT_EQ(lst.buffer[0], '0');
  EXPECT_EQ(lst.buffer[1], '1');
  EXPECT_EQ(lst.buffer[2], '2');
  EXPECT_EQ(lst.buffer[3], '3');
  EXPECT_EQ(lst.buffer[4], '4');
}
TEST(test_smartlist, rewind)
{
  const size_t nbytes = 20;
  test_smartlist lst;
  lst.allocate(nbytes, "list.txt");           
 
  char char5[] = "01234";
  memcpy(lst, char5, 5);
  EXPECT_EQ(lst.bptr, lst.buffer + 5);
  lst.write_buffer();
  EXPECT_EQ(lst.bptr, lst.buffer);
  lst.buffer[0] = 'x';
  lst.buffer[1] = 'x';
  lst.buffer[2] = 'x';
  lst.buffer[3] = 'x';
  lst.buffer[4] = 'x';
  char char5b[] = "56789";
  memcpy(lst, char5b, 5);
  EXPECT_EQ(lst.bptr, lst.buffer + 5);
  lst.write_buffer();
  EXPECT_EQ(lst.bptr, lst.buffer);
  lst.buffer[0] = 'x';
  lst.buffer[1] = 'x';
  lst.buffer[2] = 'x';
  lst.buffer[3] = 'x';
  lst.buffer[4] = 'x';
  EXPECT_EQ(lst.direction, 0);
  EXPECT_EQ(lst.written_flag, 1);
  lst.rewind();
  EXPECT_EQ(lst.buffer[0], '0');
  EXPECT_EQ(lst.buffer[1], '1');
  EXPECT_EQ(lst.buffer[2], '2');
  EXPECT_EQ(lst.buffer[3], '3');
  EXPECT_EQ(lst.buffer[4], '4');
}
TEST(test_smartlist, operator_plusequal)
{
  const size_t ndoubles = 20;
  const size_t nbytes = ndoubles * sizeof(double);
  test_smartlist lst;
  lst.allocate(nbytes, "list.txt");
  lst.initialize();
  EXPECT_EQ(lst.buffer, lst.bptr);
  
  ptrdiff_t ptrdiff = lst.buffend - lst.buffer;
  EXPECT_EQ(ptrdiff, lst.bufsize);
  size_t sizeofdouble = sizeof(double);
  int i = sizeofdouble;
  while (i <= ptrdiff)
  {
    lst += sizeofdouble;
    EXPECT_EQ(lst.buffer + i, lst.bptr);
    i += sizeofdouble;
  }
  EXPECT_EQ(lst.buffend, lst.bptr);
  
  lst += sizeofdouble;
  EXPECT_EQ(lst.buffer, lst.bptr);
}
TEST(test_smartlist, operator_minusequal)
{
  const size_t ndoubles = 20;
  const size_t nbytes = ndoubles * sizeof(double);
  test_smartlist lst;
  lst.allocate(nbytes, "list.txt");
  lst.initialize();
  EXPECT_EQ(lst.buffer, lst.bptr);
  
  ptrdiff_t ptrdiff = lst.buffend - lst.buffer;
  EXPECT_EQ(ptrdiff, lst.bufsize);
  size_t sizeofdouble = sizeof(double);
  int i = sizeofdouble;
  while (i <= ptrdiff)
  {
    lst += sizeofdouble;
    EXPECT_EQ(lst.buffer + i, lst.bptr);
    i += sizeofdouble;
  }
  EXPECT_EQ(lst.buffend, lst.bptr);
  
  i = ptrdiff;
  while(i > 0)
  {
    lst -= sizeofdouble;
    i -= sizeofdouble;
    EXPECT_EQ(lst.buffer + i, lst.bptr);
  }
  EXPECT_EQ(lst.buffer, lst.bptr);
}
TEST(test_smartlist, operator_check_buffer_size)
{
  const size_t nbytes = 20;
  test_smartlist lst;
  lst.allocate(nbytes, "list.txt");
  lst.initialize();
  EXPECT_EQ(lst.buffer, lst.bptr);
  EXPECT_EQ(lst.buffend - lst.bptr, nbytes);
  EXPECT_EQ(nbytes, lst.bufsize);
  try
  {
    //lst.check_buffer_size(lst.bufsize + 1);
    //FAIL();
  }
  catch(const int exit_code)
  {
    EXPECT_EQ(exit_code, 1);
  }
  catch(...)
  {
    FAIL();
  }  
}
TEST(test_smartlist, verybigwrite)
{
  test_smartlist lst;
  size_t nbytes = INT_MAX;
  ASSERT_NO_THROW(lst.allocate(nbytes, "list.txt"));
  
  EXPECT_EQ(lst.buffer, lst.bptr);
  EXPECT_EQ(nbytes, lst.buffend - lst.buffer);
  
  lst.initialize();
  
  std::fill(lst.bptr, lst.buffend, ' ');
  
  lst.bptr = lst.buffer + INT_MAX - 10;
  *(lst.bptr) = '\0';
  EXPECT_EQ(lst.bptr - lst.buffer, INT_MAX - 10);
  EXPECT_EQ(lst.buffend - lst.bptr, 10);
 
  //ASSERT_ANY_THROW(lst.write_buffer());
}
size_t get_f1b2buffer_size(const char * s);
TEST(tests_test_smarlist, get_f1b2buffer_size)
{  
  size_t size = get_f1b2buffer_size("-l1");
  EXPECT_EQ(size, 1000003);
}
extern "C"  
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}
using ::testing::InitGoogleTest;
int main(int argc, char** argv)
{
  InitGoogleTest(&argc, argv);
  ad_exit=&test_ad_exit;
  return RUN_ALL_TESTS();
}