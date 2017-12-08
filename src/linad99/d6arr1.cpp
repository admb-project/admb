/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return results of all elements of darray divided by divisor.

\param darray d6_array
\param divisor double
*/
d6_array operator/(const d6_array& darray, const double divisor)
{
  d6_array results;
  results.allocate(darray);
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = darray.elem(i) / divisor;
  }
  return results;
}
/**
Divides all elements of d6_array by divisor.

\param divisor double
*/
void d6_array::operator/=(const double divisor)
{
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) /= divisor;
  }
}
