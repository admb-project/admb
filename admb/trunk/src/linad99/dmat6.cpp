/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
#include "fvar.hpp"
#include "admb_messages.h"

  dvector column(_CONST dmatrix& m,int j)
  {
    return extract_column(m,j);
  }

  dvector row(_CONST dmatrix& m,int j)
  {
    return extract_row(m,j);
  }

  dvector extract_column(_CONST dmatrix& m,int j)
  {
    if (j < m.colmin() || j > m.colmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Invalid matrix column specified", "dvector extract_column(_CONST dmatrix& m,int j)", m.colmin(), m.colmax(), j);
    }  
    int mmin=m.rowmin();
    int mmax=m.rowmax();
    dvector tmp(mmin,mmax);

    for (int i=mmin; i<=mmax; i++)
    {
      tmp.elem(i)=m.elem(i,j);
    }
    return(tmp);
  }

  dvector extract_row(_CONST dmatrix& m,int i)
  {
    if (i < m.rowmin() || i > m.rowmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Invalid matrix row specified", "dvector extract_row(_CONST dmatrix& m,int i)", m.rowmin(), m.rowmax(), i);
    }  
    dvector tmp(m.colmin(),m.colmax());

    for (int j=m.colmin(); j<=m.colmax(); j++)
    {
      tmp.elem(j)=m.elem(i,j);
    }
    return(tmp);
  }
