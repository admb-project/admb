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

#if !defined(OPT_LIB)
/**
 * Description not yet available.
 * \param
 */
lvector& lmatrix::operator()(int i)
{
  if (i < rowmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
    "lvector& lmatrix::operator() (int i)", rowmin(), rowmax(), i);
  }
  if (i > rowmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
    "lvector& lmatrix::operator() (int i)", rowmin(), rowmax(), i);
  }
  return m[i];
}

/**
 * Description not yet available.
 * \param
 */
const lvector& lmatrix::operator()(int i) const
{
  if (i < rowmin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
    "lmatrix::operator[]" << "value was" << i;
    ad_exit(21);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
    "lmatrix::operator[]" << "value was" << i;
    ad_exit(22);
  }
  return m[i];
}
#endif
