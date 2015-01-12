/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"

  dvar_vector column(_CONST dvar_matrix& m,int j)
  {
    return extract_column(m,j);
  }

  dvar_vector row(_CONST dvar_matrix& m,int j)
  {
    return extract_row(m,j);
  }

  dvar_vector extract_column(_CONST dvar_matrix& m,int j)
  {
    if (j < m.colmin() || j > m.colmax())
    {
      cerr << " Invalid matrix column specified in "
        "dvar_vector extract_column(_CONST dvar_matrix& m,int j)\n value specified "
        "was " << j << " valid range is " << m.colmin() <<
        " to " << m.colmax() << "\n";
      ad_exit(1);
    }  
    dvar_vector tmp(m.rowmin(),m.rowmax());

    for (int i=m.rowmin(); i<=m.rowmax(); i++)
    {
      tmp.elem(i)=m.elem(i,j);
    }
    return(tmp);
  }
  dvector column_value(_CONST dvar_matrix& m,int j)
  {
    if (j < m.colmin() || j > m.colmax())
    {
      cerr << " Invalid matrix column specified in "
        "dvar_vector extract_column(_CONST dvar_matrix& m,int j)\n value specified "
        "was " << j << " valid range is " << m.colmin() <<
        " to " << m.colmax() << "\n";
      ad_exit(1);
    }  
    dvector tmp(m.rowmin(),m.rowmax());

    for (int i=m.rowmin(); i<=m.rowmax(); i++)
    {
      tmp.elem(i)=m.elem_value(i,j);
    }
    return(tmp);
  }


  dvar_vector extract_row(_CONST dvar_matrix& m,int i)
  {
    if (i < m.rowmin() || i > m.rowmax())
    {
      cerr << " Invalid matrix row specified in "
        "dvar_vector extract_row(_CONST dvar_matrix& m,int i)\n value specified "
        "was " << i << " valid range is " << m.rowmin() <<
        " to " << m.rowmax() << "\n";
      ad_exit(1);
    }  
    dvar_vector tmp(m.colmin(),m.colmax());

    for (int j=m.colmin(); j<=m.colmax(); j++)
    {
      tmp.elem(j)=m.elem(i,j);
    }
    return(tmp);
  }
