/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
\file
Contains ivector sum and pow functions.
*/
#include <fvar.hpp>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
Return integer sum of all the elements in ivector v.

\param v integer vector
*/
int sum(const ivector &v)
{
  int value = 0;
  for (int i = v.indexmin(); i <= v.indexmax(); i++)
  {
    value += v.elem(i);
  }
  return value;
}
/**
Returns integer vector with all the base elements in ivector v1 base raised 
to the power exponent x.

\param v1 base elements
\param x exponent
*/
ivector pow(const ivector& v1, int x)
{
  ivector tmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
#if defined(_MSC_VER) || defined(__SUNPRO_CC)
    double value = pow(double(v1.elem(i)),x);
#else
    double value = pow(v1.elem(i),x);
#endif

#ifndef OPT_LIB
    assert(value <= (double)INT_MAX);
#endif

    tmp.elem(i) = (int)value;
  }
  return tmp;
}
/**
Returns integer vector with base x raised with all the elements in exponent
ivector x.

\param x base
\param v1 exponent
*/
ivector pow(int x, const ivector& v1)
{
  ivector tmp(v1.indexmin(), v1.indexmax());
  for (int i = v1.indexmin(); i <= v1.indexmax(); i++)
  {
#if defined(_MSC_VER) || defined(__SUNPRO_CC)
    double value = pow(double(x), v1.elem(i));
#else
    double value = pow(x, v1.elem(i));
#endif

#ifndef OPT_LIB
    assert(value <= (double)INT_MAX);
#endif

    tmp.elem(i) = (int)value;
  }
  return tmp;
}
