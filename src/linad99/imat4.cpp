/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
#endif

#ifndef OPT_LIB

/**
Returns a reference to the row of the matrix at a specified index i.
Bounds checking is performed.

\param i index
*/
ivector& imatrix::operator[](int i)
{
  if (i < rowmin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
            "imatrix::operator[i] value was \"" << i << "\".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
            "imatrix::operator[i] value was \"" << i << "\".\n";
    ad_exit(1);
  }
  return m[i];
}
/**
Returns a constant reference to the row of the matrix at a specified index i.
Bounds checking is performed.

\param i index
*/
const ivector& imatrix::operator[](int i) const
{
  if (i < rowmin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
            "imatrix::operator[i] value was \"" << i << "\".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
            "imatrix::operator[i] value was \"" << i << "\".\n";
    ad_exit(1);
  }
  return m[i];
}
#endif
