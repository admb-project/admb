//MY Signature
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
