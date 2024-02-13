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

/**
Check index i is in matrix row bounds [index_min, index_max]

\param i row index
*/
bool imatrix::is_valid_row(const int i) const
{
  const bool valid = index_min <= i && i <= index_max;
  if (!valid)
  {
    cerr << "Error: Used invalid i = " << i << " for imatrix rows bounded by ["
         << index_min << ", " << index_max << "].\n";
  }
  return valid;
}
#if !defined(OPT_LIB)
/**
Returns a reference to the ivector element at specified row i in imatrix.
Bounds checking is performed.

\param i row index
*/
ivector& imatrix::operator()(int i)
{
  if (!is_valid_row(i))
  {
    ad_exit(1);
  }

  return elem(i);
}
/**
Returns a const reference to the ivector element at specified row i in imatrix.
Bounds checking is performed.

\param i row index
*/
const ivector& imatrix::operator()(int i) const
{
  if (!is_valid_row(i))
  {
    ad_exit(1);
  }

  return elem(i);
}
#endif
