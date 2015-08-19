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
Check index i is in matrix row bounds [index_min, index_max]

\param i row index
*/
bool dmatrix::is_valid_row(const int i) const
{
  const bool valid = index_min <= i && i <= index_max;
  if (!valid)
  {
    cerr << "Error: Used invalid i = " << i << " for dmatrix rows bounded by ["
         << index_min << ", " << index_max << "].\n";
  }
  return valid;
}
#if !defined(OPT_LIB)
/**
Returns a reference to the dvector element at specified location (i) in dmatrix.
Bounds checking is performed.

\param i row index
*/
dvector& dmatrix::operator()(int i)
{
  //check that index i is in range
  assert((index_min <= i && i <= index_max) || is_valid_row(i));

  return *(m + i);
}
#endif

#if !defined(OPT_LIB) || defined(__INTEL_COMPILER)
/**
Returns a reference to the element at specified location (i, j) in dmatrix.
Bounds checking is performed.

\param i row index
\param j col index
*/
double& dmatrix::operator()(int i, int j)
{
  //check that index i is in range
  assert((index_min <= i && i <= index_max) || is_valid_row(i));

  dvector& dvi = elem(i);

  //check that index j is in range
  assert(dvi.is_valid_index(j));

  return *(dvi.v + j);
}
/**
Returns a const reference to the element at specified location (i, j) in dmatrix.
Bounds checking is performed.

\param i row index
\param j col index
*/
const double& dmatrix::operator()(int i, int j) const
{
  //check that index i is in range
  assert((index_min <= i && i <= index_max) || is_valid_row(i));

  const dvector& dvi = elem(i);
 
  //check that index j is in range
  assert(dvi.is_valid_index(j));

  return *(dvi.v + j);
}
#endif
