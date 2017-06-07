/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns results innn dvar3_array with elements in vararr3 raised to power exp.

\param m dvar3_array of base
*/
dvar3_array pow(const dvar3_array& m, int exp)
{
  dvar3_array result;
  result.allocate(m);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = pow(m(i), exp);
  }
  return result;
}
