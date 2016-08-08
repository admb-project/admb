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
  for (int i = tmp.slicemin(); i <= tmp.slicemax(); ++i)
  {
    tmp(i) = mfexp(m(i));
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
  for (int i = tmp.slicemin(); i <= tmp.slicemax(); ++i)
  {
    tmp(i) = mfexp(m(i), d);
  }
  return tmp;
}
