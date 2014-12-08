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
Return copy of jth column vector from matrix m.

/param m matrix
/param j column index to return
*/
dvector column(const dmatrix& m, int j)
{
  return extract_column(m,j);
}

/**
 * Description not yet available.
 * \param
 */
dvector row(const dmatrix& m, int j)
  {
    return extract_row(m,j);
  }

/**
Extract copy of jth column vector from matrix m.

/param m matrix
/param j column index to return
*/
dvector extract_column(const dmatrix& m, int j)
{
  if (j < m.colmin() || j > m.colmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Invalid matrix column specified",
      "dvector extract_column(const dmatrix& m,int j)",
      m.colmin(), m.colmax(), j);
  }
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  dvector tmp(mmin,mmax);

  for (int i=mmin; i<=mmax; i++)
  {
    tmp.elem(i)=m.elem(i,j);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector extract_row(const dmatrix& m, int i)
  {
    if (i < m.rowmin() || i > m.rowmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Invalid matrix row specified",
      "dvector extract_row(const dmatrix& m,int i)",
       m.rowmin(), m.rowmax(), i);
    }
    dvector tmp(m.colmin(),m.colmax());

    for (int j=m.colmin(); j<=m.colmax(); j++)
    {
      tmp.elem(j)=m.elem(i,j);
    }
    return(tmp);
  }
