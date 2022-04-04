#include <gtest/gtest.h>
#include <fstream>
#include <fvar.hpp>
#include <admodel.h>

class test_utils: public ::testing::Test {};

TEST_F(test_utils, ranfill)
{
  double auto_rand(long int& idum, int reset);

  long idum = 5;

  double value = auto_rand(idum, -1);
  ASSERT_DOUBLE_EQ(value, 0.5);

  double value2 = auto_rand(idum, 1);
  ASSERT_DOUBLE_EQ(value2, 0.6659108996391296);

  void reinitialize_auto_rand();
  reinitialize_auto_rand();
}
TEST_F(test_utils, check_datafile_pointer)
{
  void check_datafile_pointer(void* p);

  ASSERT_THROW(check_datafile_pointer(NULL),int);
}
TEST_F(test_utils, variance)
{
  dvector data(1, 5);
  data(1) = 600;
  data(2) = 470;
  data(3) = 170;
  data(4) = 430;
  data(5) = 300;

  ASSERT_DOUBLE_EQ(21704, var(data));
}
TEST_F(test_utils, std_dev)
{
  dvector data(1, 5);
  data(1) = 600;
  data(2) = 470;
  data(3) = 170;
  data(4) = 430;
  data(5) = 300;

  ASSERT_DOUBLE_EQ(std::sqrt(21704), std_dev(data));
}
TEST_F(test_utils, dvector_times_dmatrix)
{
  dvector vec(1, 3);
  vec(1) = 1;
  vec(2) = 2;
  vec(3) = 3;
  dmatrix mat(1, 3, 1, 2);
  mat(1, 1) = 1;
  mat(1, 2) = 1;
  mat(2, 1) = 2;
  mat(2, 2) = 2;
  mat(3, 1) = 3;
  mat(3, 2) = 3;

  dvector ret = vec * mat;

  ASSERT_EQ(1, ret.indexmin());
  ASSERT_EQ(2, ret.indexmax());
  ASSERT_DOUBLE_EQ(14, ret(1));
  ASSERT_DOUBLE_EQ(14, ret(2));
}
TEST_F(test_utils, dvector_times_dmatrix_error)
{
  dvector vec(1, 3);
  dmatrix mat(2, 3, 1, 2);

  ASSERT_ANY_THROW({
    vec * mat;
  });
}
TEST_F(test_utils, dvector_times_dmatrix_error2)
{
  dvector vec(1, 3);
  dmatrix mat(1, 4, 1, 2);

  ASSERT_ANY_THROW({
    vec * mat;
  });
}
TEST_F(test_utils, dmatrix_times_dvector)
{
  dmatrix mat(1, 3, 1, 2);
  mat(1, 1) = 1;
  mat(1, 2) = 2;
  mat(2, 1) = 1;
  mat(2, 2) = 2;
  mat(3, 1) = 1;
  mat(3, 2) = 2;
  dvector vec(1, 2);
  vec(1) = 1;
  vec(2) = 2;

  dvector ret = mat * vec;

  ASSERT_EQ(1, ret.indexmin());
  ASSERT_EQ(3, ret.indexmax());
  ASSERT_DOUBLE_EQ(5, ret(1));
  ASSERT_DOUBLE_EQ(5, ret(2));
  ASSERT_DOUBLE_EQ(5, ret(3));
}
TEST_F(test_utils, dmatrix_times_dvector_error)
{
  dmatrix mat(1, 3, 1, 2);
  dvector vec(1, 3);

  ASSERT_ANY_THROW({
    mat * vec;
  });
}
TEST_F(test_utils, dmatrix_times_dvector_error2)
{
  dmatrix mat(1, 3, 2, 2);
  dvector vec(1, 2);

  ASSERT_ANY_THROW({
    mat * vec;
  });
}
TEST_F(test_utils, dmatrix_times_dmatrix)
{
  dmatrix mat(1, 2, 1, 2);
  mat(1, 1) = 1;
  mat(1, 2) = 2;
  mat(2, 1) = 1;
  mat(2, 2) = 2;
  dmatrix mat2(1, 2, 1, 2);
  mat2(1, 1) = 1;
  mat2(1, 2) = 2;
  mat2(2, 1) = 1;
  mat2(2, 2) = 2;

  dmatrix ret = mat * mat2;

  ASSERT_EQ(1, ret.rowmin());
  ASSERT_EQ(2, ret.rowmax());
  ASSERT_EQ(1, ret(1).indexmin());
  ASSERT_EQ(2, ret(1).indexmax());
  ASSERT_EQ(1, ret(2).indexmin());
  ASSERT_EQ(2, ret(2).indexmax());

  ASSERT_DOUBLE_EQ(3, ret(1, 1));
  ASSERT_DOUBLE_EQ(6, ret(1, 2));
  ASSERT_DOUBLE_EQ(3, ret(2, 1));
  ASSERT_DOUBLE_EQ(6, ret(2, 2));
}
TEST_F(test_utils, dmatrix_times_dmatrix_error)
{
  dmatrix A(1, 3, 1, 2);
  dmatrix B(1, 3, 1, 3);

  ASSERT_ANY_THROW({
    A * B;
  });
}
TEST_F(test_utils, dmatrix_times_dmatrix_error2)
{
  dmatrix A(1, 3, 2, 3);
  dmatrix B(1, 3, 1, 3);

  ASSERT_ANY_THROW({
    A * B;
  });
}
TEST_F(test_utils, allocated_arr6)
{
  d6_array arr6;

  ASSERT_EQ(0, allocated(arr6));

  arr6.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  ASSERT_EQ(1, allocated(arr6));
}
TEST_F(test_utils, allocated_varr6)
{
  gradient_structure gs;

  dvar6_array arr6;

  ASSERT_EQ(0, allocated(arr6));

  arr6.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  ASSERT_EQ(1, allocated(arr6));
}
TEST_F(test_utils, allocated_arr7)
{
  d7_array arr7;

  ASSERT_EQ(0, allocated(arr7));

  arr7.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  ASSERT_EQ(1, allocated(arr7));
}
TEST_F(test_utils, allocated_varr7)
{
  gradient_structure gs;

  dvar7_array arr7;

  ASSERT_EQ(0, allocated(arr7));

  arr7.allocate(1, 2, 1, 2, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2);

  ASSERT_EQ(1, allocated(arr7));
}
TEST_F(test_utils, is_defined_m_pi)
{
#ifndef M_PI
  FAIL();
#endif
  ASSERT_DOUBLE_EQ(PI, 3.14159265358979323846);
  ASSERT_DOUBLE_EQ(M_PI, 3.14159265358979323846);
}
TEST_F(test_utils, which_library)
{
#ifdef OPT_LIB
  ASSERT_EQ('o', which_library());
#else
  ASSERT_EQ('s', which_library());
#endif
}
TEST_F(test_utils, singval_decomp_empty)
{
  ad_exit=&test_ad_exit;

  dmatrix empty;
  ASSERT_ANY_THROW({
    singval_decomp(empty);
  });
}
TEST_F(test_utils, fcomp1)
{
  double fcomp1(dvector x, dvector d, int samplesize, int n, dvector& g, dmatrix& M);

  int samplesize = 2;
  int n = 1;
  dvector x(1, (samplesize - 1) * n);
  x = 10;
  dvector d(1, samplesize);
  d = 10;
  dvector g(1, (samplesize - 1) * n);
  dmatrix M(1, samplesize, 1, n);
  M = 5;
  double f = fcomp1(x, d, samplesize, n, g, M);
  ASSERT_DOUBLE_EQ(g(1), 46.051701859880922);
  ASSERT_DOUBLE_EQ(f, 789.21885044586338);
}
TEST_F(test_utils, read_hessian_matrix_and_scale1)
{
  void read_hessian_matrix_and_scale1(int nvar, const dmatrix& _SS, double rbp, int mcmc2_flag);

  uostream ofs("admodel.hes");

  int nvar = 2;
  ofs << nvar;

  dmatrix SS(1, nvar, 1, nvar);
  SS(1, 1) = 1;
  SS(1, 2) = 2;
  SS(2, 1) = 3;
  SS(2, 2) = 4;

  ofs << SS;

  ofs.close();

  read_hessian_matrix_and_scale1(nvar, SS, 1, 0);
}
TEST_F(test_utils, read_hessian_matrix_and_scale)
{
  ad_exit=&test_ad_exit;

  void read_hessian_matrix_and_scale(int nvar, const dmatrix& _SS, const dvector& pen_vector);

  uostream ofs("admodel.hes");

  int nvar = 2;
  ofs << nvar;

  dmatrix SS(1, nvar, 1, nvar);
  SS(1, 1) = 1;
  SS(1, 2) = 2;
  SS(2, 1) = 3;
  SS(2, 2) = 4;

  ofs << SS;

  ofs.close();

  std::ofstream ofs2("admodel.bvs");
  ofs2 << "1 1" << std::endl;
  ofs2.close();

  ad_comm::adprogram_name = "admodel";
  dvector pen_vector;
  ASSERT_ANY_THROW({
    read_hessian_matrix_and_scale(nvar, SS, pen_vector);
  });
}
TEST_F(test_utils, read_hessian_matrix_and_scale_zero)
{
  void read_hessian_matrix_and_scale(int nvar, const dmatrix& _SS, const dvector& pen_vector);

  uostream ofs("admodel.hes");

  int nvar = 2;
  ofs << nvar;

  dmatrix SS(1, nvar, 1, nvar);
  SS(1, 1) = 1;
  SS(1, 2) = -2;
  SS(2, 1) = 3;
  SS(2, 2) = 4;

  ofs << SS;

  ofs.close();

  std::ofstream ofs2("admodel.bvs");
  ofs2 << "0 0" << std::endl;
  ofs2.close();

  ad_comm::adprogram_name = "admodel";
  dvector pen_vector;
  read_hessian_matrix_and_scale(nvar, SS, pen_vector);
 
  ASSERT_DOUBLE_EQ(SS(1, 1), 0.4);
  ASSERT_DOUBLE_EQ(SS(1, 2), 0.2);
  ASSERT_DOUBLE_EQ(SS(2, 1), -0.3);
  ASSERT_DOUBLE_EQ(SS(2, 2), 0.1);
}
TEST_F(test_utils, log_likelihood_mixture)
{
  double log_likelihood_mixture(const double& x);

  double x = 0;

  double result = log_likelihood_mixture(x);

  ASSERT_DOUBLE_EQ(std::log(0.379+0.01254), result);
}
TEST_F(test_utils, log_likelihood_mixture_02)
{
  double log_likelihood_mixture_02(const double& x);

  double x = 0;

  double result = log_likelihood_mixture_02(x);

  ASSERT_DOUBLE_EQ(std::log(0.391+0.004502), result);
}
TEST_F(test_utils, ln_normal_tail_left)
{
  double ln_normal_tail_left(const double& x);

  double x = -2;

  double result = ln_normal_tail_left(x);

  ASSERT_DOUBLE_EQ(-3.7820288432464331, result);
}
TEST_F(test_utils, ln_normal_tail_right_zero)
{
  ad_exit=&test_ad_exit;

  double ln_normal_tail_right(const double& x);

  double x = 0;

  ASSERT_ANY_THROW({
    ln_normal_tail_right(x);
  });
}
TEST_F(test_utils, ln_normal_tail_leftt_zero)
{
  ad_exit=&test_ad_exit;

  double ln_normal_tail_left(const double& x);

  double x = 0;

  ASSERT_ANY_THROW({
    ln_normal_tail_left(x);
  });
}
TEST_F(test_utils, ln_normal_tail)
{
  ad_exit=&test_ad_exit;

  double ln_normal_tail(const double& x);

  double x = 0;

  ASSERT_ANY_THROW({
    ln_normal_tail(x);
  });
}
TEST_F(test_utils, inv_cumd_mixture_02)
{
  double inv_cumd_mixture_02(const double& zz);

  double zz = 0.5;
  ASSERT_DOUBLE_EQ(inv_cumd_mixture_02(zz), 0);

  zz = 0.001;
  ASSERT_DOUBLE_EQ(inv_cumd_mixture_02(zz), -8.9289930215071145);

  zz = 0.03;
  ASSERT_DOUBLE_EQ(inv_cumd_mixture_02(zz), -1.9634901490889378);
}
TEST_F(test_utils, inv_cumd_mixture)
{
  double inv_cumd_mixture(const double& zz);

  double zz = 0.5;
  ASSERT_DOUBLE_EQ(inv_cumd_mixture(zz), 0);

  zz = 0.001;
  ASSERT_DOUBLE_EQ(inv_cumd_mixture(zz), -22.478280885941615);

  zz = 0.03;
  ASSERT_DOUBLE_EQ(inv_cumd_mixture(zz), -2.0329110115658309);
}
TEST_F(test_utils, inv_cumd_norm_ln)
{
  double inv_cumd_norm_ln(const double& x);

  double x = 0;
  ASSERT_DOUBLE_EQ(inv_cumd_norm_ln(x), 0);

  x = -0.5;
  ASSERT_DOUBLE_EQ(inv_cumd_norm_ln(x), 0.26986516776287539);

  x = -0.1;
  ASSERT_DOUBLE_EQ(inv_cumd_norm_ln(x), 1.3098127659105443);
}
TEST_F(test_utils, cumd_mixture)
{
  double cumd_mixture(const double& x);

  double x = 0;
  ASSERT_DOUBLE_EQ(cumd_mixture(x), 0.50000000050027404);
}
TEST_F(test_utils, cumd_mixture_02)
{
  double cumd_mixture_02(const double& x);

  double x = 0;
  ASSERT_DOUBLE_EQ(cumd_mixture_02(x), 0.50000000051607218);
}
