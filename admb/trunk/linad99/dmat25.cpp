/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


// file fvar.cpp
// constructors, destructors and misc functions involving class dvariable 

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif


#include <stdio.h>
#ifndef __SUN__
#endif
#include <math.h>

dmatrix operator / (_CONST dmatrix& m, CGNU_DOUBLE e)
{
  dmatrix tmp;
  tmp.allocate(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)/e;
  }
  return tmp;
}

dmatrix operator / ( CGNU_DOUBLE e,_CONST dmatrix& m)
{
  dmatrix tmp;
  tmp.allocate(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=e/m(i);
  }
  return tmp;
}

