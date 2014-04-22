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

/**
 * Description not yet available.
 * \param
 */
dvariable colsum(const dvar_matrix& m, int col)
{
  if (col < m.rowmin() || col > m.rowmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Row out of bounds",
    "dvariable colsum(const dvar_matrix& m, int col)",
    m.rowmin(), m.rowmax(), col);
  }
  dvariable isum=0.0;
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    isum+=m(i,col);
  }
  return isum;
}
