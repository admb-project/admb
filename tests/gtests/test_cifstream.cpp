//MY Signature
//Another line for testing
#include <gtest/gtest.h>
#include <cifstrem.h>

class test_cifstream: public ::testing::Test {};

TEST_F(test_cifstream, signature)
{
  cifstream cifs("test_cifstream.cpp");
  ASSERT_STREQ("//MY Signature", cifs.signature());
}
TEST_F(test_cifstream, get_file_name)
{
  cifstream cifs("test_cifstream.cpp");
  ASSERT_STREQ("test_cifstream.cpp", cifs.get_file_name());
}
TEST_F(test_cifstream, getline)
{
  cifstream cifs("test_cifstream.cpp");
  char line[20];
  cifs.getline(line, 20, '\n');
  ASSERT_STREQ("//MY Signature", line);
}
TEST_F(test_cifstream, call_signature_twice)
{
  cifstream cifs("test_cifstream.cpp");
  char* signature = cifs.signature();
  ASSERT_STREQ("//MY Signature", signature);
  char* signature2 = cifs.signature();
  ASSERT_STREQ("//MY Signature", signature2);
}
TEST_F(test_cifstream, big_signature)
{
  cifstream cifs("big_signature.txt");
  char* bigsignature = cifs.signature();
  ASSERT_STREQ(
    "01234567890123456789012345678901234567890123456789012345678901234567890123456789",
    bigsignature);
  char line[5];
  cifs.getline(line, 5, '\n');
  ASSERT_STREQ("END", line);
}
TEST_F(test_cifstream, double)
{
  cifstream cifs("test_cifstream_getfield.txt");
  double d;
  cifs >> d;
  ASSERT_DOUBLE_EQ(2.5, d);
  cifs >> d;
  ASSERT_DOUBLE_EQ(7.8, d);
  cifs.close();
}
TEST_F(test_cifstream, get_non_blank_line)
{
  int get_non_blank_line(const ifstream& _infile, char*& line,
     const int& line_length);

  int MAX_LINE_LENGTH = 10000;
  cifstream cifs("test_cifstream_get_non_blank_line.txt");
  char* signature = cifs.signature();
  ASSERT_STREQ("get_non_blank_line", signature);
  char* line = new char[MAX_LINE_LENGTH];

  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 3);
  ASSERT_STREQ("ONE", line);
  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 3);
  ASSERT_STREQ("TWO", line);
  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 5);
  ASSERT_STREQ("THREE", line);
  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 4);
  ASSERT_STREQ("FOUR", line);

  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 0);

  cifs.close();
}
