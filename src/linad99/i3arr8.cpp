/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifndef OPT_LIB

/// Returns integer reference element from i3_array(i, j, k).
const int& i3_array::operator()(int i, int j, int k) const
{
  return elem(i)(j, k);
}
/// Returns vector reference element from i3_array(i, j).
const ivector& i3_array::operator()(int i, int j) const
{
  return elem(i)(j);
}
/// Returns matrix reference element from i3_array[i].
const imatrix& i3_array::operator[](int i) const
{
  return t[i];
}
/// Returns matrix reference element from i3_array(i).
const imatrix& i3_array::operator()(int i) const
{
  return t[i];
}
#endif

/**
Assign values from other to i3_array.
Note: Both matrices should have the same bounds.

\param other i3_array
*/
i3_array& i3_array::operator=(const i3_array& other)
{
  if (slicemin() != other.slicemin() || slicemax() != other.slicemax())
  {
    cerr << "Incompatible array bounds in "
         << "i3_array& i3_array::operator=(const i3_array&).\n";
     ad_exit(1);
  }
  // Check that both matrices don't point to the same object.
  if (t != other.t)
  {
    for (int i = slicemin(); i <= slicemax(); ++i)
    {
      elem(i) = other.elem(i);
    }
  }
  return *this;
}
/**
Assigns value to all elements of i3_array.

\param value integer
*/
i3_array& i3_array::operator=(int value)
{
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i) = value;
  }
  return *this;
}
