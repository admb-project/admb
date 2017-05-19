/**
 * \file
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns dvar3_array where each element (i, j) is equal to d / m(i, j).

\param d numerator
\param m denominator for each element i and j.
*/
dvar3_array operator/(const prevariable& d, const dvar3_array& arr3)
{
  dvar3_array result;
  result.allocate(arr3);
  for (int i = result.slicemin(); i<= result.slicemax(); ++i)
  {
    result(i) = d / arr3(i);
  }
  return result;
}
/**
Returns dvar3_array where each element (i, j) is equal to d / m(i, j).

\param d numerator
\param m denominator for each element i and j.
*/
dvar3_array operator/(const prevariable& d, const d3_array& arr3)
{
  dvar3_array result;
  result.allocate(arr3);
  for (int i = result.slicemin(); i<= result.slicemax(); ++i)
  {
    result(i) = d / arr3(i);
  }
  return result;
}
/**
Returns dvar3_array where each element (i, j) is equal to d / m(i, j).

\param d double numerator
\param m denominator for each element i and j.
*/
dvar3_array operator/(const double d, const dvar3_array& arr3)
{
  dvar3_array result;
  result.allocate(arr3);
  for (int i = result.slicemin(); i<= result.slicemax(); ++i)
  {
    result(i) = d / arr3(i);
  }
  return result;
}
