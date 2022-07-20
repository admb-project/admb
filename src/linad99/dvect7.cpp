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
dvector log(const dvector& t1)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  const double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = log(*pt1i);

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector exp(const dvector& t1)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  const double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = exp(*pt1i);

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector fabs(const dvector& t1)
{
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvector tmp(min, max);

  double* ptmpi = tmp.get_v() + min;
  const double* pt1i = t1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = fabs(*pt1i);

    ++ptmpi;
    ++pt1i;
  }
  return tmp;
}

/**
Returns the maximum value of vector vec.
Note: vec is an allocated vector.

\param vec scalar vector
*/
double max(const dvector& vec)
{
  int indexmin = vec.indexmin();
  int indexmax = vec.indexmax();
  const double* pveci = vec.get_v() + indexmin;
  double maximum = *pveci;
  ++pveci;
  for (int i = indexmin + 1; i <= indexmax; ++i)
  {
    double value = *pveci;
    if (value > maximum) maximum = value;

    ++pveci;
  }
  return maximum;
}
/**
Returns the minimum value of vector vec.
Note: vec is an allocated vector.

\param vec scalar vector
 */
double min(const dvector& vec)
{
  int indexmin = vec.indexmin();
  int indexmax = vec.indexmax();
  const double* pveci = vec.get_v() + indexmin;
  double minimum = *pveci;
  ++pveci;
  for (int i = indexmin + 1; i <= indexmax; ++i)
  {
    double value = *pveci;
    if (value < minimum) minimum = value;

    ++pveci;
  }
  return minimum;
}
