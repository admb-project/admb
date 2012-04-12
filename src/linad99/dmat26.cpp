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

/**
 * Description not yet available.
 * \param
 */
dmatrix mfexp(_CONST dmatrix& m)
{
  ivector cmin(m.rowmin(),m.rowmax());
  ivector cmax(m.rowmin(),m.rowmax());
  int i;
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    cmin(i)=m(i).indexmin();
    cmax(i)=m(i).indexmax();
  }
  dmatrix tmp(m.rowmin(),m.rowmax(),cmin,cmax);
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=mfexp(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix mfexp(_CONST dmatrix& m, CGNU_DOUBLE d)
{
  ivector cmin(m.rowmin(),m.rowmax());
  ivector cmax(m.rowmin(),m.rowmax());
  int i;
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    cmin(i)=m(i).indexmin();
    cmax(i)=m(i).indexmax();
  }
  dmatrix tmp(m.rowmin(),m.rowmax(),cmin,cmax);
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=mfexp(m(i),d);
  }
  return tmp;
}
