/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
Return ivector filled with flags for 1 positive and -1 negative
for values in dvector v.
*/
ivector sgn(const dvector& v)
{
  int mmin = v.indexmin();
  int mmax = v.indexmax();
  ivector ret(mmin, mmax);
  for (int i = mmin; i <= mmax; ++i)
  {
    ret(i)= v(i) > 0 ? 1 : -1;
  }
  return ret;
}
