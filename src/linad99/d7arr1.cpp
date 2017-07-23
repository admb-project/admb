/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return result of dividing all darray elements by divisor.

\param divisor double
*/
d7_array operator/(const d7_array& darray, const double divisor)
{
  d7_array results;
  results.allocate(darray);
  for (int i = darray.indexmin(); i <= darray.indexmax(); ++i)
  {
    results(i) = darray(i) / divisor;
  }
  return results;
}
/**
Divide all elements of d7_array by divisor.

\param divisor double
*/
void d7_array::operator/=(const double divisor)
{
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) /= divisor;
  }
}
/**
Return total sum of darray. 

\param darray d7_array
*/
double sum(const d7_array& darray)
{
  double total = 0.0;
  for (int i = darray.indexmin(); i <= darray.indexmax(); ++i)
  {
    total += sum(darray.elem(i));
  }
  return total;
}
