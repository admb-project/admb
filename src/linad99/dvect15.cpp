/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#ifdef DEBUG
  #include <cassert>
  #include <climits>
#endif

/**
Concatenates dvector elements in a with b and return results.

\param a scalar vector
\param b scalar vector
*/
dvector operator&(const dvector& a, const dvector& b)
{
#ifdef DEBUG
  assert(a.size() + b.size() <= INT_MAX);
#endif
  dvector results(1, static_cast<int>(a.size() + b.size()));
  int max = a.indexmax();
  for (int i = a.indexmin(); i <= max; ++i)
  {
    results(i) = a(i);
  }
  int index = max;
  max = b.indexmax();
  for (int i = b.indexmin(); i <= max; ++i)
  {
    results(++index) = b(i);
  }
  return results;
}
/**
Concatenates variable vector elements in a with b and return results.

\param a variable vector
\param b variable vector
*/
dvar_vector operator&(const dvar_vector& a, const dvar_vector& b)
{
#ifdef DEBUG
  assert(a.size() + b.size() <= INT_MAX);
#endif

  dvar_vector results(1, static_cast<int>(a.size() + b.size()));
  int max = a.indexmax();
  for (int i = a.indexmin(); i <= max; ++i)
  {
    results(i) = a(i);
  }
  int index = max;
  max = b.indexmax();
  for (int i = a.indexmin(); i <= max; ++i)
  {
    results(++index) = b(i);
  }
  return results;
}
