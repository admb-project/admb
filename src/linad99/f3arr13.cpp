/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Assignment functions for dvar3_array for d3_array and double.
*/
#include <fvar.hpp>

#ifdef DEBUG
#include <cassert>
#endif

/**
Assign element values from scalar arr3 to dvar3_array.

\param arr3 d3_array
*/
dvar3_array& dvar3_array::operator=(const d3_array& arr3)
{
#ifdef DEBUG
  assert(allocated(arr3));
#endif
  int min = slicemin();
  int max = slicemax();
#ifndef OPT_LIB
  if (min != arr3.slicemin() || max != arr3.slicemax())
  {
     cerr << " Incompatible array bounds in "
          << "dvar3_array& dvar3_array::operator=(const d3_array&)\n";
     ad_exit(1);
  }
#endif
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i) = arr3.elem(i);
  }
  dvar_matrix* pti = t + min;
  const dmatrix* parr3i = &arr3(min);
  for (int i = min; i <= max; ++i)
  {
    *pti = *parr3i;
    ++pti;
    ++parr3i;
  }
  return *this;
}
/**
Assigns value to all elements of dvar3_array.

\param value double
*/
dvar3_array& dvar3_array::operator=(double value)
{
  int min = slicemin();
  int max = slicemax();
  dvar_matrix* pti = t + min;
  for (int i = min; i <= max; ++i)
  {
    *pti = value;
    ++pti;
  }
  return *this;
}
