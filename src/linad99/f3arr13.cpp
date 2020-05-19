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
  if (slicemin() != arr3.slicemin() || slicemax() != arr3.slicemax())
  {
     cerr << " Incompatible array bounds in "
          << "dvar3_array& dvar3_array::operator=(const d3_array&)\n";
     ad_exit(1);
  }
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i) = arr3.elem(i);
  }
  return *this;
}
/**
Assigns value to all elements of dvar3_array.

\param value double
*/
dvar3_array& dvar3_array::operator=(double value)
{
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i) = value;
  }
  return *this;
}
