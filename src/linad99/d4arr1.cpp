/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"

/**
Returns results in a d4_array with the computed square roots of the elements in
arr4.

\param arr4 d4_array
*/
d4_array sqrt(const d4_array& arr4)
{
  d4_array results;
  results.allocate(arr4);
  for (int i = results.hslicemin(); i <= results.hslicemax(); ++i)
  {
    results(i) = sqrt(arr4(i));
  }
  return results;
}
/**
Returns results in a d4_array with the computed exponential of the elements in
arr4.

\param arr4 d4_array
*/
d4_array exp(const d4_array& arr4)
{
  d4_array results;
  results.allocate(arr4);
  for (int i = results.hslicemin(); i <= results.hslicemax(); ++i)
  {
    results(i) = exp(arr4(i));
  }
  return results;
}
/**
Returns results in a d4_array with the computed exponential of the elements in
arr4.

\param arr4 d4_array
*/
d4_array mfexp(const d4_array& arr4)
{
  d4_array results;
  results.allocate(arr4);
  for (int i = results.hslicemin(); i <= results.hslicemax(); ++i)
  {
    results(i) = mfexp(arr4(i));
  }
  return results;
}
/**
Returns results in a d4_array with the computed log of the elements in
arr4.

\param arr4 d4_array
*/
d4_array log(const d4_array& arr4)
{
  d4_array results;
  results.allocate(arr4);
  for (int i = results.hslicemin(); i <= results.hslicemax(); ++i)
  {
    results(i) = log(arr4(i));
  }
  return results;
}
