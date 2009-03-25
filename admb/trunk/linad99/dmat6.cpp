/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"

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
      cerr << " Invalid matrix column specified in "
        "dvector extract_column(_CONST dmatrix& m,int j)\n value specified "
        "was " << j << " valid range is " << m.colmin() <<
        " to " << m.colmax() << "\n";
      ad_exit(1);
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
      cerr << " Invalid matrix row specified in "
        "dvector extract_row(_CONST dmatrix& m,int i)\n value specified "
        "was " << i << " valid range is " << m.rowmin() <<
        " to " << m.rowmax() << "\n";
      ad_exit(1);
    }  
    dvector tmp(m.colmin(),m.colmax());

    for (int j=m.colmin(); j<=m.colmax(); j++)
    {
      tmp.elem(j)=m.elem(i,j);
    }
    return(tmp);
  }
