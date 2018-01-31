#include <future>
#include <gtest/gtest.h>
#include <fvar.hpp>

class test_async: public ::testing::Test {};

TEST_F(test_async, sample)
{
  std::future<int> result(std::async([](int m, int n) { return m + n;} , 2, 4));

  ASSERT_EQ(result.get(), 6);
}
TEST_F(test_async, sum)
{
  double value = 0.63;
  dmatrix matrix(1, 50, 1, 200);
  for (int i = 1; i <= 50; ++i)
  {
    for (int j = 1; j <= 200; ++j)
    {
      matrix(i, j) = value;
      value += i + j;
    }
  }

  auto start = std::chrono::steady_clock::now();
  double expected = sum(matrix);
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

  auto start2 = std::chrono::steady_clock::now();
  std::vector<std::future<double>> sums;
  for (int i = 1; i <= 50; ++i)
  {
    sums.push_back(
      std::async([](const dvector& v) { return sum(v); }, matrix(i))
    );
  }

  double total = 0;
  for (auto& result: sums)
  {
    total += result.get();
  }

  auto end2 = std::chrono::steady_clock::now();
  auto diff2 = end2 - start2;
  std::cout << std::chrono::duration <double, std::milli> (diff2).count() << " ms" << std::endl;

  ASSERT_DOUBLE_EQ(total, expected);
}
TEST_F(test_async, sum2)
{
  double value = 0.63;
  dmatrix matrix(1, 50, 1, 200);
  for (int i = 1; i <= 50; ++i)
  {
    for (int j = 1; j <= 200; ++j)
    {
      matrix(i, j) = value;
      value += i + j;
    }
  }

  auto start = std::chrono::steady_clock::now();
  double expected = sum(matrix);
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

  auto start2 = std::chrono::steady_clock::now();
  std::future<double> lower =
    std::async(std::launch::async, [](const dmatrix& m, int begin, int end)
    {
      double total = 0;
      for (int i = begin; i <= end; ++i)
      {
        total += sum(m.elem(i));
      }
      return total;
    }, std::cref(matrix), 1, 25);
  std::future<double> upper =
    std::async(std::launch::async, [](const dmatrix& m, int begin, int end)
    {
      double total = 0;
      for (int i = begin; i <= end; ++i)
      {
        total += sum(m.elem(i));
      }
      return total;
    }, std::cref(matrix), 26, 50);

  double total = lower.get() + upper.get();

  auto end2 = std::chrono::steady_clock::now();
  auto diff2 = end2 - start2;
  std::cout << std::chrono::duration <double, std::milli> (diff2).count() << " ms" << std::endl;

  ASSERT_DOUBLE_EQ(total, expected);
}
TEST_F(test_async, sum3)
{
  double value = 0.63;
  dmatrix matrix(1, 50, 1, 200);
  for (int i = 1; i <= 50; ++i)
  {
    for (int j = 1; j <= 200; ++j)
    {
      matrix(i, j) = value;
      value += i + j;
    }
  }

  auto start = std::chrono::steady_clock::now();
  double expected = sum(matrix);
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

  auto start2 = std::chrono::steady_clock::now();
  std::future<double> lower =
    std::async(std::launch::async, [](const dmatrix& m)
    {
      double total = 0;
      for (int i = 1; i <= 25; ++i)
      {
        total += sum(m.elem(i));
      }
      return total;
    }, std::cref(matrix));

  double total = 0;
  for (int i = 26; i <= 50; ++i)
  {
    total += sum(matrix.elem(i));
  }
  total += lower.get();

  auto end2 = std::chrono::steady_clock::now();
  auto diff2 = end2 - start2;
  std::cout << std::chrono::duration <double, std::milli> (diff2).count() << " ms" << std::endl;

  ASSERT_DOUBLE_EQ(total, expected);
}
TEST_F(test_async, sum4)
{
  double value = 0.63;
  dmatrix matrix(1, 50, 1, 200);
  for (int i = 1; i <= 50; ++i)
  {
    for (int j = 1; j <= 200; ++j)
    {
      matrix(i, j) = value;
      value += i + j;
    }
  }

  auto start = std::chrono::steady_clock::now();
  double expected = sum(matrix);
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

  auto start2 = std::chrono::steady_clock::now();
  std::future<double> lower =
    std::async(std::launch::deferred, [](const dmatrix& m)
    {
      double total = 0;
      for (int i = 1; i <= 25; ++i)
      {
        total += sum(m.elem(i));
      }
      return total;
    }, std::cref(matrix));

  std::future<double> upper =
    std::async(std::launch::deferred, [](const dmatrix& m)
    {
      double total = 0;
      for (int i = 26; i <= 50; ++i)
      {
        total += sum(m.elem(i));
      }
      return total;
    }, std::cref(matrix));


  double total = lower.get() + upper.get();

  auto end2 = std::chrono::steady_clock::now();
  auto diff2 = end2 - start2;
  std::cout << std::chrono::duration <double, std::milli> (diff2).count() << " ms" << std::endl;

  ASSERT_DOUBLE_EQ(total, expected);
}
