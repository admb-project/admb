/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"

/**
Returns dvar3_array with squared values from each element in vararr3.

\param vararr3 values to square
*/
dvar3_array square(const dvar3_array& vararr3)
{
  dvar3_array result;
  result.allocate(vararr3);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = square(vararr3(i));
  }
  return result;
}
