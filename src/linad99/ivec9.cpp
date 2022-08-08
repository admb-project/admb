/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"

/**
Element wise add elements from other to ivector.

\param other ivector
*/
ivector& ivector::operator+=(const ivector& other)
{
  int min = indexmin();
  int max = indexmax();
#ifndef OPT_LIB
  if (min != other.indexmin() || max != other.indexmax())
  {
    cerr << " Incompatible vector indexes in "
         << "ivector::operator+=(const ivector&).\n";
    ad_exit(1);
  }
#endif
  int* pvi = v + min;
  int* potheri = other.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *pvi += *potheri;

    ++pvi;
    ++potheri;
  }
  return *this;
}
/**
Add value to each element of ivec.

\param value integer
*/
ivector& ivector::operator+=(int value)
{
  int min = indexmin();
  int max = indexmax();
  int* pvi = v + min;
  for (int i = min; i <= max; ++i)
  {
    *pvi += value;
    ++pvi;
  }
  return *this;
}
