/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
  dvar_vector column(_CONST dvar_matrix& m,int j)
  {
    return extract_column(m,j);
  }

/**
 * Description not yet available.
 * \param
 */
  dvar_vector row(_CONST dvar_matrix& m,int j)
  {
    return extract_row(m,j);
  }

/**
 * Description not yet available.
 * \param
 */
  dvar_vector extract_column(_CONST dvar_matrix& m,int j)
  {
    if (j < m.colmin() || j > m.colmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Invalid matrix column specified", "dvar_vector extract_column(_CONST dvar_matrix& m,int j)", m.colmin(), m.colmax(), j);
    }  
    dvar_vector tmp(m.rowmin(),m.rowmax());

    for (int i=m.rowmin(); i<=m.rowmax(); i++)
    {
      tmp.elem(i)=m.elem(i,j);
    }
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  dvector column_value(_CONST dvar_matrix& m,int j)
  {
    if (j < m.colmin() || j > m.colmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Invalid matrix column specified", "dvector column_value(_CONST dvar_matrix& m,int j)", m.colmin(), m.colmax(), j);
    }  
    dvector tmp(m.rowmin(),m.rowmax());

    for (int i=m.rowmin(); i<=m.rowmax(); i++)
    {
      tmp.elem(i)=m.elem_value(i,j);
    }
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  dvar_vector extract_row(_CONST dvar_matrix& m,int i)
  {
    if (i < m.rowmin() || i > m.rowmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Invalid matrix row specified", "dvar_vector extract_row(_CONST dvar_matrix& m,int i)", m.rowmin(), m.rowmax(), i);
    }  
    dvar_vector tmp(m.colmin(),m.colmax());

    for (int j=m.colmin(); j<=m.colmax(); j++)
    {
      tmp.elem(j)=m.elem(i,j);
    }
    return(tmp);
  }
