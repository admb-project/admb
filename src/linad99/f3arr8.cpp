/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns results in dvar3_array with elements in base raised to power exp.

\param base dvar3_array of base
*/
dvar3_array pow(const dvar3_array& base, int exp)
{
  dvar3_array results;
  results.allocate(base);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = pow(base(i), exp);
  }
  return results;
}
