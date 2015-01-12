/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */




#include "fvar.hpp"


dvariable colsum(_CONST dvar_matrix& m,int col)
{ 
  if (col<m.rowmin() || col>m.rowmax())
  {
    cerr << "Row out of bounds in function"
            " colsum(_CONST imatrix& m,int col)" << endl;
    ad_exit(1);
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

