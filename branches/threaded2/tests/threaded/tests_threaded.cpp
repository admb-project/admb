#include <gtest/gtest.h>

class tests_threaded: public ::testing::Test 
{
protected:
  tests_threaded() {
  }
  virtual ~tests_threaded() {
  }
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

TEST(tests_threaded, main3)
{
  int main3();
  main3();
}

/*
TEST(tests_threaded, main4)
{
  int main4();
  main4();
}
*/

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
