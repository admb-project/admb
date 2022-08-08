/**
Author: David Fournier

Copyright (c) 2008-2012 Regents of the University of California
*/

#include "fvar.hpp"

/**
Divide each element of m by d.

\return Allocated d3_array with results of division.
*/
d3_array operator/(const d3_array& m, const double d)
{
  d3_array tmp;
  tmp.allocate(m);
  int min = tmp.slicemin();
  int max = tmp.slicemax();
  dmatrix* ptmpi = &tmp(min);
  const dmatrix* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pmi / d;
    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
/**
Divide each element of d3_array by d.
*/
void d3_array::operator/=(const double d)
{
  int min = slicemin();
  int max = slicemax();
  dmatrix* pti = t + min;
  for (int i = min; i <= max; ++i)
  {
    *pti /= d;
    ++pti;
  }
}
