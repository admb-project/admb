/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

  dvector extract_diagonal(_CONST dmatrix& m)
  {
    if ( (m.rowmin()!=m.colmin()) || (m.rowmax()!=m.colmax()))
    {
      cerr << "Error in extract_diagonal function -- input matrix not square"
       <<endl;
      ad_exit(1);
    }
    dvector tmp(m.rowmin(),m.rowmax());

    for (int i=m.rowmin(); i<=m.rowmax(); i++)
    {
      tmp.elem(i)=m.elem(i,i);
    }
    return(tmp);
  }

