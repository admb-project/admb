/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include "fvar.hpp"

AD_LONG_INT sum(_CONST lmatrix& m)
{
  AD_LONG_INT ssum=0;
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ssum+=sum(m(i));
  }
  return ssum;
}

AD_LONG_INT colsum(_CONST lmatrix& m,int col)
{ 
  if (col<m.colmin() || col>m.colmax())
  {
    cerr << "Row out of bounds in function"
            " colsum(_CONST imatrix& m,int col)" << endl;
    ad_exit(1);
  }
  AD_LONG_INT isum=0;
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    isum+=m(i,col);
  }
  return isum;
}


lvector column(_CONST lmatrix& m,int col)
{ 
  if (col<m.colmin() || col>m.colmax())
  {
    cerr << "Row out of bounds in function"
            " column(_CONST imatrix& m,int col)" << endl;
    ad_exit(1);
  }
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  lvector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=m(i,col);
  }
  return tmp;
}


