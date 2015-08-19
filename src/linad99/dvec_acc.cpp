/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#include <cassert>


/**
Check index i is in dvector bounds [index_min, index_max]

\param i row index
*/
bool dvector::is_valid_index(const int i) const
{
  bool valid = index_min <= i && i <= index_max;
  if (!valid)
  {
#if defined(USE_EXCEPTIONS)
    throw vector_range_exception(i, index_min, index_max);
#else
    cerr << "Error: Used invalid i = " << i << " for dvector bounded by ["
         << index_min << ", " << index_max << "].\n";
#endif
  }
  return valid;
}
#if !defined(OPT_LIB)
/**
Returns a reference to the element at index __i__ in the array.

\param __i__ index
*/
double& dvector::operator[](int i)
{
  assert((index_min <= i && i <= index_max) || is_valid_index(i));

  return *(v + i);
}
/**
Returns a reference to the element at index __i__ in the array.

\param __i__ index
*/
double& dvector::operator()(int i)
{
  assert((index_min <= i && i <= index_max) || is_valid_index(i));

  return *(v + i);
}
/**
Returns a reference to the element at index __i__ in the array.

\param __i__ index
*/
const double& dvector::operator[](int i) const
{
  assert((index_min <= i && i <= index_max) || is_valid_index(i));

  return *(v + i);
}
/**
Returns a reference to the element at index __i__ in the array.

\param __i__ index
*/
const double& dvector::operator()(int i) const
{
  assert((index_min <= i && i <= index_max) || is_valid_index(i));

  return *(v + i);
}
#endif
