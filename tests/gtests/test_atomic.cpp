#include <gtest/gtest.h>
#include <future>

class test_atomic: public ::testing::Test {};

TEST_F(test_atomic, default_constructor)
{
  std::atomic<int> counter(0);
  std::thread threads[10];

  for (int i = 0; i < 10; ++i)
  {
    threads[i] = std::thread([&counter](){ counter += 10; });
    std::cout << counter << std::endl;
  }
  std::cout << "out " << counter << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    threads[i].join();
  }

  ASSERT_EQ(counter, 100);
}
