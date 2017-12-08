/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns vector of signs from variables.
-1 for negative number and zero, 1 for positive.

\param variables dvar_vector
*/
ivector sgn(const dvar_vector& variables)
{
  int mmin = variables.indexmin();
  int mmax = variables.indexmax();
  ivector signs(mmin,mmax);
  for (int i = mmin; i <= mmax; ++i)
  {
    signs(i) = variables(i) > 0.0 ? 1 : -1;
  }
  return signs;
}
