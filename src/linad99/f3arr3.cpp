/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"

/**
Returns d3_array with scalar values of variable arr3 array.

\param arr3 
*/
d3_array value(const dvar3_array& arr3)
{
  d3_array result;
  result.allocate(arr3);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result[i] = value(arr3(i));
  }
  return result;
}
/**
Allocate d3_array with same dimensions as d3v.
\param d3v a dvar3_array
*/
void d3_array::allocate(const dvar3_array& d3v)
{
  int sl = d3v.slicemin();
  int sh = d3v.slicemax();
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
     cerr << " Error: d3_array unable to allocate memory in "
          << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
  }
  if ((t = new dmatrix[slicesize()]) == 0)
  {
    cerr << " Error: d3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate(d3v(i));
  }
}
