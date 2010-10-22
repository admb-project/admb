/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
#include "fvar.hpp"
#include "admb_messages.h"

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
  if (col < m.colmin() || col > m.colmax())
  {
    //JCA: Should be Column out of bounds
    ADMB_ARRAY_BOUNDS_ERROR("Row out of bounds", "int colsum(_CONST imatrix& m,int col)", m.colmin(), m.colmax(), col);
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
  if (col < m.colmin() || col > m.colmax())
  {
    //JCA: Should be Column out of bounds
    ADMB_ARRAY_BOUNDS_ERROR("Row out of bounds", "int colsum(_CONST imatrix& m,int col)", m.colmin(), m.colmax(), col);
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
