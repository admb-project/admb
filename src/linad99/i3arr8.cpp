/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

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
