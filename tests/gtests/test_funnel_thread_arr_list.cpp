#include <gtest/gtest.h>
#include <thread>
#include <fvar.hpp>

class test_funnel_thread_arr_list: public ::testing::Test {};

TEST_F(test_funnel_thread_arr_list, default)
{
  arr_list alist;

  ASSERT_TRUE(alist.get_last() == nullptr);
  ASSERT_EQ(alist.get_last_offset(), 0);
  ASSERT_EQ(alist.get_number_arr_links(), 0);
  ASSERT_EQ(alist.get_max_last_offset(), 0);
}
TEST_F(test_funnel_thread_arr_list, size)
{
  auto f = []()
  {
    arr_list alist(sizeof(double_and_int));
    ASSERT_EQ(alist.get_number_arr_links(), 0);
  };

  std::thread t1(f);
  std::thread t2(f);
  std::thread t3(f);
  t1.join();
  t2.join();
  t3.join();
}
TEST_F(test_funnel_thread_arr_list, arr_new_free1x)
{
  auto f = []()
  {
    arr_list alist(2 * sizeof(double_and_int));
    ASSERT_EQ(alist.get_number_arr_links(), 0);
    double_and_int* p2 = alist.arr_new(2);
    ASSERT_EQ(alist.get_number_arr_links(), 1);
    alist.arr_free(p2);
    ASSERT_EQ(alist.get_number_arr_links(), 0);
    p2 = nullptr;
  };

  std::thread t1(f);
  std::thread t2(f);
  std::thread t3(f);
  t1.join();
  t2.join();
  t3.join();
}
TEST_F(test_funnel_thread_arr_list, arr_new_free3x)
{
  std::srand(std::time(nullptr));
  auto f = []()
  {
    int random1 = std::rand() % 5 + 1;
    arr_list alist(6 * sizeof(double_and_int));
    ASSERT_EQ(alist.get_number_arr_links(), 0);
    std::this_thread::sleep_for (std::chrono::seconds(random1));
    double_and_int* p1 = alist.arr_new(2);
    double_and_int* p2 = alist.arr_new(2);
    double_and_int* p3 = alist.arr_new(2);
    std::this_thread::sleep_for (std::chrono::seconds(random1));
    ASSERT_EQ(alist.get_number_arr_links(), 3);
    alist.arr_free(p1);
    alist.arr_free(p2);
    alist.arr_free(p3);
    ASSERT_EQ(alist.get_number_arr_links(), 0);
    p1 = nullptr;
    p2 = nullptr;
    p3 = nullptr;
  };

  std::thread t1(f);
  std::thread t2(f);
  std::thread t3(f);
  t1.join();
  t2.join();
  t3.join();
}
