/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable 

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

dvar_matrix mfexp(_CONST dvar_matrix& m)
{
  dvar_matrix tmp;
  tmp.allocate(m.indexmin(),m.indexmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=mfexp(m(i));
  }
  return tmp;
}

dvar_matrix mfexp(_CONST dvar_matrix& m, CGNU_DOUBLE d)
{
  dvar_matrix tmp;
  tmp.allocate(m.indexmin(),m.indexmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=mfexp(m(i),d);
  }
  return tmp;
}


