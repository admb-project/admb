/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
Return d3_array with computed exponent for each element in m.
*/
d3_array mfexp(const d3_array& m)
{
  d3_array tmp;
  tmp.allocate(m);
  int min = tmp.slicemin();
  int max = tmp.slicemax();
  dmatrix* ptmpi = &tmp(min);
  const dmatrix* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = mfexp(*pmi);
    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
/**
Return d3_array with computed exponent for each element in m with bounds d.
*/
d3_array mfexp(const d3_array& m, const double d)
{
  d3_array tmp;
  tmp.allocate(m);
  int min = tmp.slicemin();
  int max = tmp.slicemax();
  dmatrix* ptmpi = &tmp(min);
  const dmatrix* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = mfexp(*pmi, d);
    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
