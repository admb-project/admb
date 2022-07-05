/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
dvector operator*(const dvector& t1, const double x)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pt1i * x;

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector operator/(const double x, const dvector& t1)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = x / *pt1i;

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector operator/(const dvector& t1, const double x)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pt1i / x;

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector operator+(const double x, const dvector& t1)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = x + *pt1i;

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector operator+(const dvector& t1, const double x)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pt1i + x;

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector operator-(const double x, const dvector& t1)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = x - *pt1i;

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector operator-(const dvector& t1, const double x)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pt1i - x;

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}
