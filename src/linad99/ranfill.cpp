/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB Foundation
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>


#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <math.h>

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define M1 = 714025
#else
constexpr int M1 = 714025;
#endif

#define IA1 1366
#define IC1 150889

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define RM1 (1.0f/M1)
#else
constexpr float RM1 = 1.0f / M1;
#endif

#define M3 134456
#define IA3 8121
#define IC3 28411

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define M2 243000
#else
constexpr int M2 = 243000;
#endif

#define IA2 4561
#define IC2 51349

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define RM2 (1.0f/M2)
#else
constexpr float RM2 = 1.0f / M2;
#endif

double auto_rand(long int& idum, int reset);
void reinitialize_auto_rand();
double randn(long int& n);

/**
 * Description not yet available.
 * \param
 */
void reinitialize_auto_rand()
{
  long int One = 1;
  auto_rand(One, -1);
}

/**
Random number generator.

\n\n The implementation of this algorithm was inspired by
"Numerical Recipes in C", 2nd edition,
Press, Teukolsky, Vetterling, Flannery, chapter 7
*/
double auto_rand(long int& idum, int reset)
{
  static long ix1,ix2,ix3;
  static float r[108];
  static int iff=0;

  if (reset < 0)
  {
    iff = 0;
    return .5;
  }

  if (idum < 0 || iff == 0)
  {
    iff=2;
    ix1=(IC1-(idum))%M1;
    ix1=ix1 % M1;


    ix1=(IA1*ix1+IC1);
    ix1=ix1 % M1;

    ix2=ix1 % M2;
    ix1=(IA1*ix1+IC1);
    ix1=ix1 % M1;
    ix3=ix1 % M3;
    for (int j=1;j<=107;j++)
    {
      ix2=(IA2*ix2+IC2) % M2;
      ix1=(IA1*ix1+IC1);
              ix1=ix1 % M1;

      long int iu = (long int)(ix2 * RM2);
      r[j]=(ix1+iu)*RM1;
    }
    idum =6;
  }

  ix3=(IA3*ix3+IC3) % M3;
  ix3=ix3 % M3;
  ix1=(IA1*ix1+IC1) % M1;
  ix1=ix1 % M1;
  ix2=(IA2*ix2+IC2) % M2;
  ix2=ix2 % M2;
  long j = 1 + ((107*ix3)/M3);
  if (j > 107 || j < 1) cerr << " Error in random number generator\n";
  double temp = r[j];
  r[j]=ix2*RM2;
  r[j]=(ix1+r[j]);
  r[j]=r[j]*RM1;
  return temp;
}

#undef IA1
#undef IC1
#undef IA2
#undef IC2
#undef M3
#undef IA3
#undef IC3

/**
Returns a random number.
\param n seed
*/
double randn(long int& n)
{
  long int nn=n;
  double x=auto_rand(nn,1);
  double y=auto_rand(nn,1);
  double u=sqrt(-2*log(x))*cos(2*PI*y);
  return(u);
}
/**
Fill vector with binary random numbers.  If random number is
less than p, vector element is set to 1, otherwise it is set to
0.
\param n seed
\param p value between 0 and 1
*/
void dvector::fill_randbi(long int& n, double p)
{
  if (p < 0.0 || p > 1.0)
  {
    cerr << "Error in dvar_vector::fill_randbi proportions of"
            " successes must lie between 0 and 1.\n";
    ad_exit(1);
  }
  long int nn = n;
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    if (auto_rand(nn, 1) <= p)
    {
      elem(i) = 1.0;
    }
    else
    {
      elem(i) = 0.0;
    }
  }
  reinitialize_auto_rand();
}
/**
Fill vector with random numbers.
\param n seed
*/
void dvector::fill_randu(long int& n)
{
  long int nn=n;
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) = auto_rand(nn, 1);
  }
  reinitialize_auto_rand();
}
/**
Fill random numbers into specified column j of matrix.
\param j specified column
\param n seed
*/
void dmatrix::colfill_randu(const int& j, long int& n)
{
  long int nn = n;
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
      elem(i, j) = auto_rand(nn, 1);
  }
  reinitialize_auto_rand();
}
/**
Fill random numbers into specified row i of matrix.
\param i specified row
\param n seed
*/
void dmatrix::rowfill_randu(const int& i, long int& n)
{
  long int nn = n;
  for (int j = colmin(); j <= colmax(); ++j)
  {
    elem(i, j) = auto_rand(nn, 1);
  }
  reinitialize_auto_rand();
}
/**
Fill vector with random numbers.
\param n seed
*/
void dvector::fill_randn(long int& n)
{
  long int nn = n;
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    (*this)(i) = randn(nn);
  }
  reinitialize_auto_rand();
}
/**
Fill matrix with random numbers.
\param n seed
*/
void dmatrix::fill_randn(long int& n)
{
  long int nn = n;
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).fill_randn_ni(nn);
    nn += 2;
  }
  reinitialize_auto_rand();
}
/**
Fill multi array with random numbers.
\param n seed
*/
void d3_array::fill_randn(long int& n)
{
  long int nn = n;
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i).fill_randn_ni(nn);
    nn += 2;
  }
  reinitialize_auto_rand();
}
/**
Fill multi array with random numbers.
\param n seed
*/
void d3_array::fill_randu(long int& n)
{
  long int nn = n;
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i).fill_randu_ni(nn);
    nn += 2;
  }
  reinitialize_auto_rand();
}
/**
Fill matrix with random numbers.
\param n seed
*/
void dmatrix::fill_randu(long int& n)
{
  long int nn = n;
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).fill_randu_ni(nn);
    nn += 2;
  }
  reinitialize_auto_rand();
}
/**
Fill random numbers into specified column j of matrix.
\param j specified column
\param n seed
*/
void dmatrix::colfill_randn(const int& j,long int& n)
{
  long int nn=n;
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i, j) = randn(nn);
  }
  reinitialize_auto_rand();
}
/**
Fill random numbers into specified row i of matrix.
\param i specified row
\param n seed
*/
void dmatrix::rowfill_randn(const int& i, long int& n)
{
  long int nn = n;
  for (int j = colmin(); j <= colmax(); ++j)
  {
    elem(i, j) = randn(nn);
  }
  reinitialize_auto_rand();
}
