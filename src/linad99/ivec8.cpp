/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifndef OPT_LIB
  #include <cassert>
#endif

/**
Returns results of adding each element of a to value.

ie results(i) = value + a(i)

\param value integer
\param aivector
*/
ivector operator+(int value, const ivector& a)
{
  int min = a.indexmin();
  int max = a.indexmax();
  ivector results(min, max);
  for (int i = min; i <= max; ++i)
  {
    results(i) = value + a(i);
  }
  return results;
}
/**
Returns results of subtracting each element of a from value.

ie results(i) = value - a(i)

\param value integer
\param a ivector
*/
ivector operator-(int value, const ivector& a)
{
  int min = a.indexmin();
  int max = a.indexmax();
  ivector results(min, max);
  for (int i = min; i <= max; ++i)
  {
    results(i) = value - a(i);
  }
  return results;
}
/**
Returns results of element wise adding for vectors a and b.
Note: a and b should have the same dimensions.

ie results(i) = a(i) + b(i)

\param a ivector
\param b ivector
*/
ivector operator+(const ivector& a, const ivector& b)
{
  int min = a.indexmin();
  int max = b.indexmax();
#ifndef OPT_LIB
  assert(min == b.indexmin() && max == b.indexmax()); 
#endif
  ivector results(min, max);
  for (int i = min; i <= max; ++i)
  {
    results(i) = a(i) + b(i);
  }
  return results;
}
/**
Returns results of element wise substracting for vectors a and b.
Note: a and b should have the same dimensions.

ie results(i) = a(i) - b(i)

\param a ivector
\param b ivector
*/
ivector operator-(const ivector& a, const ivector& b)
{
  int min = a.indexmin();
  int max = b.indexmax();
#ifndef OPT_LIB
  assert(min == b.indexmin() && max == b.indexmax()); 
#endif
  ivector results(min, max);
  for (int i = min; i <= max; ++i)
  {
    results(i) = a(i) - b(i);
  }
  return results;
}
/**
Returns results of adding value to each element of vector a.

ie results(i) = a(i) + value;

\param a ivector
\param value integer
*/
ivector operator+(const ivector& a, int value)
{
  int min = a.indexmin();
  int max = a.indexmax();
  ivector results(min, max);
  for (int i = min; i <= max; ++i)
  {
    results(i) = a(i) + value;
  }
  return results;
}
/**
Returns results of substrating value from each element of vector a.

ie results(i) = a(i) - value;

\param a ivector
\param value integer
*/
ivector operator-(const ivector& a, int value)
{
  int min = a.indexmin();
  int max = a.indexmax();
  ivector results(min, max);
  for (int i = min; i <= max; ++i)
  {
    results(i) = a(i) - value;
  }
  return results;
}
