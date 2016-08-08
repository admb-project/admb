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
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=m(i)/d;
  }
  return tmp;
}
/**
Divide each element of d3_array by d.
*/
void d3_array::operator/=(const double d)
{
  for (int i=slicemin();i<=slicemax();i++)
  {
    (*this)(i) /= d;
  }
}
