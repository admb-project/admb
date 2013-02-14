#include <iostream>
#include <thread>
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

void call_from_thread(int tid) 
{
  std::cout << __FILE__ << ':' << __LINE__ << ' ' << tid << std::endl;
}

/*
TEST(tests_threaded, example)
{
  static const int num_threads = 10;
  std::thread t[num_threads];
  for (int i = 0; i < num_threads; ++i) 
  {
    t[i] = std::thread(call_from_thread, i);
  }
  for (int i = 0; i < num_threads; ++i) 
  {
    t[i].join();
  }
}
*/

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
