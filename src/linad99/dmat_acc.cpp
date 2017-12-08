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

#if !defined(OPT_LIB)
/**
Returns reference to row vector at position i.
\param i position
*/
dvector& dmatrix::operator[](int i)
{
  if (i < rowmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
    "dvector& dmatrix::operator[] (int i)", rowmin(), rowmax(), i);
  }
  if (i > rowmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
    "dvector& dmatrix::operator[] (int i)", rowmin(), rowmax(), i);
  }
  return *(m + i);
}
/**
Returns reference to row vector at position i.
\param i position
*/
const dvector& dmatrix::operator[](int i) const
{
  if (i < rowmin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
    "dmatrix::operator[]" << "value was" << i;
    ad_exit(21);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
    "dmatrix::operator[]" << "value was" << i;
    ad_exit(22);
  }
  return *(m + i);
}
#endif
