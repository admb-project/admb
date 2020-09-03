#include <gtest/gtest.h>
#include <fvar.hpp>
#include <future>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_thread_funnel: public ::testing::Test {};

TEST_F(test_thread_funnel, grad_stack1)
{
  auto start = std::chrono::high_resolution_clock::now();

  grad_stack* grad_stack1 = new grad_stack(10000, 10);

  delete grad_stack1;
  grad_stack1 = nullptr;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time (resource allocation): " << elapsed.count() <<  endl;
}
TEST_F(test_thread_funnel, grad_stack4)
{
  auto start = std::chrono::high_resolution_clock::now();

  grad_stack* grad_stack1 = new grad_stack(10000, 10);
  grad_stack* grad_stack2 = new grad_stack(10000, 10);
  grad_stack* grad_stack3 = new grad_stack(10000, 10);
  grad_stack* grad_stack4 = new grad_stack(10000, 10);

  delete grad_stack1;
  grad_stack1 = nullptr;
  delete grad_stack2;
  grad_stack2 = nullptr;
  delete grad_stack3;
  grad_stack3 = nullptr;
  delete grad_stack4;
  grad_stack4 = nullptr;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time (resource allocation): " << elapsed.count() <<  endl;
}
