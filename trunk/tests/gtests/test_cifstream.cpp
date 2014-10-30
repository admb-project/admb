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
