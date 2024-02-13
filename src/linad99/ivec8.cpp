/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifdef DEBUG
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
  int* pai = a.get_v() + min;
  int* presultsi = results.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = value + *pai;

    ++pai;
    ++presultsi;
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
  int* pai = a.get_v() + min;
  int* presultsi = results.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = value - *pai;

    ++pai;
    ++presultsi;
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
#ifdef DEBUG
  assert(min == b.indexmin() && max == b.indexmax()); 
#endif
  ivector results(min, max);
  int* presultsi = results.get_v() + min;
  int* pai = a.get_v() + min;
  int* pbi = b.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = *pai + *pbi;
    ++presultsi;
    ++pai;
    ++pbi;
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
#ifdef DEBUG
  assert(min == b.indexmin() && max == b.indexmax()); 
#endif
  ivector results(min, max);
  int* pai = a.get_v() + min;
  int* pbi = b.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    results(i) = *pai - *pbi;
    ++pai;
    ++pbi;
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
  int* pai = a.get_v() + min;
  int* presultsi = results.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = *pai + value;
    ++pai;
    ++presultsi;
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
  int* pai = a.get_v() + min;
  int* presultsi = results.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = *pai - value;
    ++pai;
    ++presultsi;
  }
  return results;
}
