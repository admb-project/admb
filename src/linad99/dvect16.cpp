/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Add values to dvector element-wise.

\param values dvector
*/
dvector& dvector::operator+=(const dvector& values)
{
  int min = indexmin();
  int max = indexmax();
#ifndef OPT_LIB
  if (min != values.indexmin() || max != values.indexmax())
  {
    cerr << " Incompatible array bounds in "
         << "dvector& operator+=(const dvector&)\n";
    ad_exit(1);
  }
#endif

  double* pvi = v + min;
  const double* pvaluesi = values.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *pvi += *pvaluesi;
    ++pvi;
    ++pvaluesi;
  }
  return *this;
}
/**
Subtract values from dvector element-wise.

\param values dvector
 */
dvector& dvector::operator-=(const dvector& values)
{
  int min = indexmin();
  int max = indexmax();
#ifndef OPT_LIB
  if (min != values.indexmin() || max != values.indexmax())
  {
    cerr << " Incompatible array bounds in "
         << "dvector& operator-=(const dvector&)\n";
    ad_exit(1);
  }
#endif
  double* pvi = v + min;
  const double* pvaluesi = values.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *pvi -= *pvaluesi;
    ++pvi;
    ++pvaluesi;
  }
  return *this;
}
/**
Add value to each element of dvector.

\param value double
*/
dvector& dvector::operator+=(const double value)
{
  int min = indexmin();
  int max = indexmax();
  double* pvi = v + min;
  for (int i = min; i <= max; ++i)
  {
    *pvi += value;
    ++pvi;
  }
  return *this;
}
/**
Subtract value to each element of dvector.

\param value double
*/
dvector& dvector::operator-=(const double value)
{
  int min = indexmin();
  int max = indexmax();
  double* pvi = v + min;
  for (int i = min; i <= max; ++i)
  {
    *pvi -= value;
    ++pvi;
  }
  return *this;
}
