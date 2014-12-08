/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
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

// dvar_matrix mathematical functions
dvar_matrix exp(const dvar_matrix& m);
dvar_matrix log(const dvar_matrix& m);
dvar_matrix sin(const dvar_matrix& m);
dvar_matrix cos(const dvar_matrix& m);
dvar_matrix tan(const dvar_matrix& m);
dvar_matrix pow(const dvar_matrix& m, const double e);
dvar_matrix pow(const dvar_matrix& m, const prevariable& e);
dvar_matrix pow(const dmatrix& m, const prevariable& e);
dvar_matrix pow(const dvar_matrix& m, int e);
dvar_matrix elem_prod(const dvar_matrix& m, const dvar_matrix& m2);
dvar_matrix elem_prod(const dvar_matrix& m, const dmatrix& m2);
dvar_matrix elem_prod(const dmatrix& m, const dvar_matrix& m2);
dvar_matrix elem_div(const dvar_matrix& m, const dvar_matrix& m2);
dvar_matrix elem_div(const dvar_matrix& m, const dmatrix& m2);
dvar_matrix elem_div(const dmatrix& m, const dvar_matrix& m2);
// end of dvar_vector mathematical functions

/*  "template form for editor
dvar_matrix XXX(const dvar_matrix& m)
{
  ivector cmin(m.rowmin(),m.rowmax());
  ivector cmax(m.rowmin(),m.rowmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    cmin(i)=m(i).indexmin();
    cmax(i)=m(i).indexmax();
  }
  dvar_matrix tmp(m.rowmin(),m.rowmax(),cmin,cmax);
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
dvar_matrix use_shape(const dvar_matrix& m)
{
  ivector cmin(m.rowmin(),m.rowmax());
  ivector cmax(m.rowmin(),m.rowmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    cmin(i)=m(i).indexmin();
    cmax(i)=m(i).indexmax();
  }
  dvar_matrix tmp(m.rowmin(),m.rowmax(),cmin,cmax);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix use_shape(const dmatrix& m)
{
  ivector cmin(m.rowmin(),m.rowmax());
  ivector cmax(m.rowmin(),m.rowmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    cmin(i)=m(i).indexmin();
    cmax(i)=m(i).indexmax();
  }
  dmatrix tmp(m.rowmin(),m.rowmax(),cmin,cmax);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix pow(const dvar_matrix& m, int e)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=pow(m(i),e);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix pow(const dmatrix& m, const prevariable& e)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=pow(m(i),e);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix pow(const dvar_matrix& m, const prevariable& e)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=pow(m(i),e);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix pow(const dvar_matrix& m, const double e)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=pow(m(i),e);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix tan(const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=tan(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix cos(const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=cos(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix sin(const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=sin(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix log(const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=log(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix sqrt(const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=sqrt(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix sqr(const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=sqr(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix exp(const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=exp(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_div(const dvar_matrix& m, const dvar_matrix& m2)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=elem_div(m(i),m2(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_div(const dmatrix& m,const dvar_matrix& m2)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=elem_div(m(i),m2(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_div(const dvar_matrix& m, const dmatrix& m2)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=elem_div(m(i),m2(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_prod(const dvar_matrix& m, const dvar_matrix& m2)
{
  //dvar_matrix tmp=use_shape(m);
  dvar_matrix tmp(m.indexmin(),m.indexmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=elem_prod(m(i),m2(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_prod(const dmatrix& m, const dvar_matrix& m2)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=elem_prod(m(i),m2(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_prod(const dvar_matrix& m, const dmatrix& m2)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=elem_prod(m(i),m2(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const double x, const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=x+m(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const prevariable& x, const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=x*m(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const dvar_matrix& m, const double x)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)+x;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const dvariable& x, const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=x+m(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const dvar_matrix& m, const dvariable& x)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)+x;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const dvar_matrix& m, const prevariable& x)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)*x;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const dvar_matrix& m, const double x)
{
  dvar_matrix tmp=use_shape(m);
  double t=-x;
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)+t;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const double x, const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=x-m(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const dvar_matrix& m, const dvariable& x)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)-x;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const dvariable& x, const dvar_matrix& m)
{
  dvar_matrix tmp=use_shape(m);
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=x-m(i);
  }
  return tmp;
}
