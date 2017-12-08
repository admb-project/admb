/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns d3_array with square root values from arr3.
\param arr3 input values
 */
d3_array sqrt(const d3_array& arr3)
{
  d3_array results;
  results.allocate(arr3);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = sqrt(arr3(i));
  }
  return results;
}
/**
Returns d3_array with square values from arr3.
\param arr3 input values
*/
d3_array sqr(const d3_array& arr3)
{
  d3_array results;
  results.allocate(arr3);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = sqr(arr3(i));
  }
  return results;
}
