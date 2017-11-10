#include <vector>
#include <gtest/gtest.h>
#include <thread>
#include <future>
#include <fvar.hpp>

class test_opt: public ::testing::Test {};

TEST_F(test_opt, carray_to_vector)
{
  double values[3];
  values[0] = 4.1;
  values[1] = 3.5;
  values[2] = 1.4;

  std::vector<double> v;
  v.assign(&values[0], &values[0] + 3);
  ASSERT_DOUBLE_EQ(values[0], *v.begin());
  ASSERT_DOUBLE_EQ(values[1], v[1]);
  ASSERT_DOUBLE_EQ(values[2], v[2]);
}
TEST_F(test_opt, dvector_to_vector)
{
  dvector values(1, 3);
  values[1] = 4.1;
  values[2] = 3.5;
  values[3] = 1.4;

  std::vector<double> v;
  v.assign(values.begin(), values.end());
  ASSERT_DOUBLE_EQ(values[1], *v.begin());
  ASSERT_DOUBLE_EQ(values[2], v[1]);
  ASSERT_DOUBLE_EQ(values[3], v[2]);
}
TEST_F(test_opt, dmatrix_times_dvector)
{
  dmatrix m(1, 3, 1, 3);
  m(1, 1) = 1;
  m(1, 2) = 2;
  m(1, 3) = 3;
  m(2, 1) = 4;
  m(2, 2) = 5;
  m(2, 3) = 6;
  m(3, 1) = 7;
  m(3, 2) = 8;
  m(3, 3) = 9;
  dvector v(1, 3);
  v(1) = 1;
  v(2) = 2;
  v(3) = 3;
  dvector results = m * v;
  ASSERT_DOUBLE_EQ(14, results(1));
  ASSERT_DOUBLE_EQ(32, results(2));
  ASSERT_DOUBLE_EQ(50, results(3));
}
TEST_F(test_opt, dmatrix_times_dvector_opt)
{
  dmatrix m(1, 3, 1, 3);
  m(1, 1) = 1;
  m(1, 2) = 2;
  m(1, 3) = 3;
  m(2, 1) = 4;
  m(2, 2) = 5;
  m(2, 3) = 6;
  m(3, 1) = 7;
  m(3, 2) = 8;
  m(3, 3) = 9;
  dvector v(1, 3);
  v(1) = 1;
  v(2) = 2;
  v(3) = 3;

  dvector results(1, 3);
  dvector* ptr_m = m.begin();
  double* ptr_r = results.begin();
  for (int i = 1; i <= 3; ++i)
  {
    double* ptr_mv = ptr_m->begin();
    double* ptr_v = v.begin();
    for (int j = 1; j <= 3; ++j)
    {
      *ptr_r += *ptr_mv * *ptr_v;
      ++ptr_mv;
      ++ptr_v;
    }
    ++ptr_r;
    ++ptr_m;
  }
  ASSERT_DOUBLE_EQ(14, results(1));
  ASSERT_DOUBLE_EQ(32, results(2));
  ASSERT_DOUBLE_EQ(50, results(3));
}
void myrange(const int imin, const int imax, dvector& v, dmatrix& m)
{
  dvector results(imin, imax);
  for (int i = imin; i <= imax; ++i)
  {
    int j = v.indexmin();
    double* pmi = &m(i)(j);
    double* pv = &v(j);
    double sum = *pmi * *pv;
    for (; j <= v.indexmax(); ++j)
    {
      sum += *(++pmi) * *(++pv);
    }
    results[i] = sum;
  }
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_async5)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::future<void>a(std::async(
    &myrange, 1, 2000, std::ref(v), std::ref(m)));
  std::future<void> b(std::async(
    &myrange, 2001, 4000, std::ref(v), std::ref(m)));
  std::future<void> c(std::async(
    &myrange, 4001, 6000, std::ref(v), std::ref(m)));
  std::future<void> d(std::async(
    &myrange, 6001, 8000, std::ref(v), std::ref(m)));
  std::future<void> e(std::async(
    &myrange, 8001, 10000, std::ref(v), std::ref(m)));
  a.get();
  b.get();
  c.get();
  d.get();
  e.get();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_sequential5)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  myrange(1, 2000, v, m);
  myrange(2001, 4000, v, m);
  myrange(4001, 6000, v, m);
  myrange(6001, 8000, v, m);
  myrange(8001, 10000, v, m);
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_threaded5)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::thread a(&myrange, 1, 2000, std::ref(v), std::ref(m));
  std::thread b(&myrange, 2001, 4000, std::ref(v), std::ref(m));
  std::thread c(&myrange, 4001, 6000, std::ref(v), std::ref(m));
  std::thread d(&myrange, 6001, 8000, std::ref(v), std::ref(m));
  std::thread e(&myrange, 8001, 10000, std::ref(v), std::ref(m));
  a.join();
  b.join();
  c.join();
  d.join();
  e.join();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_async2)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::future<void>a(std::async(&myrange,
    1, 5000, std::ref(v), std::ref(m)));
  std::future<void> b(std::async(&myrange,
    5001, 10000, std::ref(v), std::ref(m)));
  a.get();
  b.get();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_sequential2)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  myrange(1, 5000, v, m);
  myrange(5001, 10000, v, m);
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_threaded2)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::thread a(&myrange, 1, 5000, std::ref(v), std::ref(m));
  std::thread b(&myrange, 5001, 10000, std::ref(v), std::ref(m));
  a.join();
  b.join();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_async3)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::future<void>a(std::async(&myrange,
    1, 3333, std::ref(v), std::ref(m)));
  std::future<void> b(std::async(&myrange,
    3334, 6666, std::ref(v), std::ref(m)));
  std::future<void> c(std::async(&myrange,
    6667, 10000, std::ref(v), std::ref(m)));
  a.get();
  b.get();
  c.get();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_sequential3)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  myrange(1, 3333, v, m);
  myrange(3334, 6666, v, m);
  myrange(6666, 10000, v, m);
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_threaded3)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::thread a(&myrange, 1, 3333, std::ref(v), std::ref(m));
  std::thread b(&myrange, 3334, 6666, std::ref(v), std::ref(m));
  std::thread c(&myrange, 6667, 10000, std::ref(v), std::ref(m));
  a.join();
  b.join();
  c.join();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);
  dvector* ptr_m = m.begin();
  for (int i = 1; i <= size; ++i)
  {
    double* ptr_mv = ptr_m->begin();
    double* ptr_v = v.begin();
    double sum = *ptr_mv * *ptr_v;
    for (int j = 1; j <= size; ++j)
    {
      sum += *(++ptr_mv) * *(++ptr_v);
    }
    results[i] = sum;
    ++ptr_m;
  }
}
TEST_F(test_opt, dmatrix_times_dvector_large_array_core)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  results = m * v;
}
TEST_F(test_opt, vector_times_matrix)
{
  int size = 3;
  dmatrix m(1, size, 1, size);
  m(1, 1) = 1;
  m(1, 2) = 2;
  m(1, 3) = 3;
  m(2, 1) = 1;
  m(2, 2) = 2;
  m(2, 3) = 3;
  m(3, 1) = 1;
  m(3, 2) = 2;
  m(3, 3) = 3;

  dvector x(1, size);
  x(1) = 1;
  x(2) = 2;
  x(3) = 3;

  dvector tmp(1, size);
  tmp.initialize();

  for (int j = m.colmin(); j <= m.colmax(); ++j)
  {

    int i = x.indexmin();
    dvector column = extract_column(m, j);
    double* pm = (double*)&column(i);
    double* px = (double*)&x(i);
    double sum = *px * *pm;
    for (; i <= x.indexmax(); ++i)
    {
      sum += *(++px) * *(++pm);
    }

    tmp[j] = sum;
  }

  ASSERT_DOUBLE_EQ(6.0, tmp(1));
  ASSERT_DOUBLE_EQ(12.0, tmp(2));
  ASSERT_DOUBLE_EQ(18.0, tmp(3));
}
TEST_F(test_opt, vector_times_matrix_large_array)
{
  int size = 1000;
  dmatrix m(1, size, 1, size);
  m = 1;
  dvector x(1, size);
  x = 0.5;

  dvector tmp(1, size);
  tmp.initialize();

  for (int j = m.colmin(); j <= m.colmax(); ++j)
  {
    int i = x.indexmin();
    dvector column = extract_column(m, j);
    double* pm = (double*)&column(i);
    double* px = (double*)&x(i);
    double sum = *px * *pm;
    for (; i <= x.indexmax(); ++i)
    {
      sum += *(++px) * *(++pm);
    }

    tmp[j] = sum;
  }

  for (int i = 1; i <= size; ++i)
  {
    ASSERT_DOUBLE_EQ(0.5 * size, tmp(i));
  }
}
TEST_F(test_opt, vector_times_matrix_core)
{
  int size = 1000;
  dmatrix m(1, size, 1, size);
  m = 1;
  dvector x(1, size);
  x = 0.5;

  dvector tmp(1, size);
  tmp.initialize();

  tmp = x * m;

  for (int i = 1; i <= size; ++i)
  {
    ASSERT_DOUBLE_EQ(0.5 * size, tmp(i));
  }
}
dvector myrange2(const int imin, const int imax, dvector& v, dmatrix& m)
{
  dvector results(imin, imax);
  for (int i = imin; i <= imax; ++i)
  {
    int j = v.indexmin();
    double* pmi = &m(i)(j);
    double* pv = &v(j);
    double sum = *pmi * *pv;
    for (; j <= v.indexmax(); ++j)
    {
      sum += *(++pmi) * *(++pv);
    }
    results[i] = sum;
  }

  return results;
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_async_return_dvector2)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::future<dvector>a(std::async(&myrange2,
    1, 5000, std::ref(v), std::ref(m)));
  std::future<dvector> b(std::async(&myrange2,
    5001, 10000, std::ref(v), std::ref(m)));
  dvector dva = a.get();
  dvector dvb = b.get();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_async_return_dvector3)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::future<dvector>a(std::async(&myrange2,
    1, 3333, std::ref(v), std::ref(m)));
  std::future<dvector> b(std::async(&myrange2,
    3334, 6666, std::ref(v), std::ref(m)));
  std::future<dvector> c(std::async(&myrange2,
    6667, 10000, std::ref(v), std::ref(m)));
  dvector dva = a.get();
  dvector dvb = b.get();
  dvector dvc = c.get();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_async_return_dvector4)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::future<dvector>a(std::async(&myrange2,
    1, 2500, std::ref(v), std::ref(m)));
  std::future<dvector> b(std::async(&myrange2,
    2501, 5000, std::ref(v), std::ref(m)));
  std::future<dvector> c(std::async(&myrange2,
    5001, 7500, std::ref(v), std::ref(m)));
  std::future<dvector> d(std::async(&myrange2,
    7501, 10000, std::ref(v), std::ref(m)));
  dvector dva = a.get();
  dvector dvb = b.get();
  dvector dvc = c.get();
  dvector dvd = d.get();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_async_return_dvector5)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);

  std::future<dvector>a(std::async(&myrange2,
    1, 2000, std::ref(v), std::ref(m)));
  std::future<dvector> b(std::async(&myrange2,
    2001, 4000, std::ref(v), std::ref(m)));
  std::future<dvector> c(std::async(&myrange2,
    4001, 6000, std::ref(v), std::ref(m)));
  std::future<dvector> d(std::async(&myrange2,
    6001, 8000, std::ref(v), std::ref(m)));
  std::future<dvector> e(std::async(&myrange2,
    8001, 10000, std::ref(v), std::ref(m)));
  dvector dva = a.get();
  dvector dvb = b.get();
  dvector dvc = c.get();
  dvector dvd = d.get();
  dvector dve = e.get();
}
