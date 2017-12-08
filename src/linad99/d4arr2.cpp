/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Divides all elements of d4_array by d.

\param d double
*/
void d4_array::operator/=(double d)
{
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    (*this)(i) /= d;
  }
}
/**
Returns d4_array with all elements arr4 divided by d.

\param d double
*/
d4_array operator/(const d4_array& arr4, double d)
{
  d4_array results;
  results.allocate(arr4);
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results(i) = arr4(i) / d;
  }
  return results;
}
/**
Returns d4_array with all elements equal to d divided by elements in arr4.

\param arr4 d4_array
*/
d4_array operator/(double d, const d4_array& arr4)
{
  d4_array results;
  results.allocate(arr4);
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    for (int j = results(i).indexmin(); j <= results(i).indexmax(); ++j)
    {
      results(i, j) = d / arr4(i, j);
    }
  }
  return results;
}
