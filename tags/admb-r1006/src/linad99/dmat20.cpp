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

// dmatrix mathematical functions
    dmatrix exp(_CONST dmatrix& m);
    dmatrix log(_CONST dmatrix& m);
    dmatrix sin(_CONST dmatrix& m);
    dmatrix cos(_CONST dmatrix& m);
    dmatrix tan(_CONST dmatrix& m);
    dmatrix pow(_CONST dmatrix& m, CGNU_DOUBLE e);
    dmatrix pow(_CONST dmatrix& m,int e);
// end of dvar_vector mathematical functions

/*  "template form for editor
dmatrix XXX(_CONST dmatrix& m)
{
  ivector cmin(m.rowmin(),m.rowmax());
  ivector cmax(m.rowmin(),m.rowmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    cmin(i)=m(i).indexmin();
    cmax(i)=m(i).indexmax();
  }
  dmatrix tmp(m.rowmin(),m.rowmax(),cmin,cmax);
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=XXX(m(i));
  }
  return tmp;
}

*/

/**
 * Description not yet available.
 * \param
 */
dmatrix pow(_CONST dmatrix& m,int e)
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
    tmp(i)=pow(m(i),e);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix pow(_CONST dmatrix& m, CGNU_DOUBLE e)
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
    tmp(i)=pow(m(i),e);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix tan(_CONST dmatrix& m)
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
    tmp(i)=tan(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix cos(_CONST dmatrix& m)
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
    tmp(i)=cos(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix sin(_CONST dmatrix& m)
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
    tmp(i)=sin(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix elem_prod(_CONST dmatrix& m,_CONST dmatrix& m2)
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
    tmp(i)=elem_prod(m(i),m2(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix log(_CONST dmatrix& m)
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
    tmp(i)=log(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix sqrt(_CONST dmatrix& m)
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
    tmp(i)=sqrt(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix sqr(_CONST dmatrix& m)
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
    tmp(i)=sqr(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix exp(_CONST dmatrix& m)
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
    tmp(i)=exp(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix elem_div(_CONST dmatrix& m,_CONST dmatrix& m2)
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
    tmp(i)=elem_div(m(i),m2(i));
  }
  return tmp;
}
