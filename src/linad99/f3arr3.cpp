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

  int min = result.slicemin();
  int max = result.slicemax();

  dmatrix* presulti = &result(min);
  const dvar_matrix* parr3i = &arr3(min);
  for (int i = min; i <= max; ++i)
  {
    *presulti = value(*parr3i);

    ++presulti;
    ++parr3i;
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
  t -= sl;
  dmatrix* pti = t + sl;
  const dvar_matrix* pd3vi = &d3v(sl);
  for (int i = sl; i <= sh; ++i)
  {
    pti->allocate(*pd3vi);
    ++pti;
    ++pd3vi;
  }
}
