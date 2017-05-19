/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns dvar_matrix where each element (i, j) is equal to varmat(i, j)^3.

\param varmat dvar_matrix input
*/
dvar_matrix cube(const dvar_matrix& varmat)
{
  dvar_matrix result;
  result.allocate(varmat);
  for (int i = result.rowmin(); i <= result.rowmax(); ++i)
  {
    result(i) = cube(varmat(i));
  }
  return result;
}
/**
Returns dvar3_array where each element (i, j, k) is equal to varmat(i, j, k)^3.

\param varmat dvar3_array input
*/
dvar3_array cube(const dvar3_array& vararr3)
{
  dvar3_array result;
  result.allocate(vararr3);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = cube(vararr3(i));
  }
  return result;
}
