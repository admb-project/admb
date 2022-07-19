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

  int min = result.slicemin();
  int max = result.slicemax();
  dvar_matrix* presulti = &result(min);
  const dvar_matrix* pvararr3i = &vararr3(min);
  for (int i = min; i <= max; ++i)
  {
    *presulti = square(*pvararr3i);

    ++presulti;
    ++pvararr3i;
  }
  return result;
}
