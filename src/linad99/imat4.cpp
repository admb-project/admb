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
#include "admb_messages.h"
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
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
     "ivector& imatrix::operator[] (int i)", rowmin(), rowmax(), i);
  }
  if (i > rowmax())
  {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
     "ivector& imatrix::operator[] (int i)", rowmin(), rowmax(), i);
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
            "imatrix::operator[]" << "value was" << i;
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
            "imatrix::operator[]" << "value was" << i;
    ad_exit(1);
  }
  return m[i];
}
#endif
