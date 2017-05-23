/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns d5_array with all elements arr5 divided by d.

\param arr5  numerator
\param d denominator
*/
d5_array operator/(const d5_array& arr5, const double d)
{
  d5_array results;
  results.allocate(arr5);
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results(i) = arr5(i) / d;
  }
  return results;
}
/**
Divides all elements of d5_array by d.

\param d denominator
*/
void d5_array::operator/=(const double d)
{
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    (*this)(i) /= d;
  }
}
