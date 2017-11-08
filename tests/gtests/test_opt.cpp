#include <vector>
#include <gtest/gtest.h>
#include <thread>
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
  results.initialize();
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
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs_threaded)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);
  results.initialize();

  int imin = m.rowmin();
  int imax = m.rowmax();
  int imid = (m.rowmax() - m.rowmin()) / 2;

  auto range = [&results](const int imin, const int imax, const dvector& v, const dmatrix& m)
  {
    dvector* ptr_m = m.begin() + (imin - 1);
    double* ptr_r = results.begin() + (imin - 1);
    for (int i = imin; i <= imax; ++i)
    {
      double* ptr_mv = ptr_m->begin();
      double* ptr_v = v.begin();
      double sum = 0.0;
      for (int j = v.indexmin(); j <= v.indexmax(); ++j)
      {
        sum += *ptr_mv * *ptr_v;
        ++ptr_mv;
        ++ptr_v;
      }
      *ptr_r = sum;
      ++ptr_r;
      ++ptr_m;
    }
  };

  std::thread lower(range, imin, imid, v, m);
  std::thread upper(range, imid + 1, imax, v, m);

  lower.join();
  upper.join();
}
TEST_F(test_opt, dmatrix_times_dvector_large_ptrs)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);
  results.initialize();
  dvector* ptr_m = m.begin();
  double* ptr_r = results.begin();
  for (int i = 1; i <= size; ++i)
  {
    double* ptr_mv = ptr_m->begin();
    double* ptr_v = v.begin();
    for (int j = 1; j <= size; ++j)
    {
      *ptr_r += *ptr_mv * *ptr_v;
      ++ptr_mv;
      ++ptr_v;
    }
    ++ptr_r;
    ++ptr_m;
  }
}
TEST_F(test_opt, dmatrix_times_dvector_large_array)
{
  int size = 10000;
  dmatrix m(1, size, 1, size);
  dvector v(1, size);

  dvector results(1, size);
  results.initialize();

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
