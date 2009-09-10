/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"

int sum(_CONST imatrix& m)
{
  int ssum=0;
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ssum+=sum(m(i));
  }
  return ssum;
}

int colsum(_CONST imatrix& m,int col)
{ 
  if (col<m.colmin() || col>m.colmax())
  {
    cerr << "Row out of bounds in function"
            " colsum(_CONST imatrix& m,int col)" << endl;
    ad_exit(1);
  }
  int isum=0;
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    isum+=m(i,col);
  }
  return isum;
}


ivector column(_CONST imatrix& m,int col)
{ 
  if (col<m.colmin() || col>m.colmax())
  {
    cerr << "Row out of bounds in function"
            " column(_CONST imatrix& m,int col)" << endl;
    ad_exit(1);
  }
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  ivector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=m(i,col);
  }
  return tmp;
}


