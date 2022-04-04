/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2012 Regents of the University of California

@brief Math functions for dmatrix to compute cos, exp, log, pow, sin, sqr, sqrt, tan, elem_div and elem_prod.
*/

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
dmatrix exp(const dmatrix& m);
dmatrix log(const dmatrix& m);
dmatrix sin(const dmatrix& m);
dmatrix cos(const dmatrix& m);
dmatrix tan(const dmatrix& m);
dmatrix pow(const dmatrix& m, const double e);
dmatrix pow(const dmatrix& m,int e);
// end of dvar_vector mathematical functions

/*  "template form for editor
dmatrix XXX(const dmatrix& m)
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
Returns dmatrix with pow of each element in m raised to the exponent e.
\param m dmatrix
\param e integer exponent
*/
dmatrix pow(const dmatrix& m,int e)
{
  ivector cmin(m.rowmin(), m.rowmax());
  ivector cmax(m.rowmin(), m.rowmax());
  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
    cmin(i) = m(i).indexmin();
    cmax(i) = m(i).indexmax();
  }
  dmatrix tmp(m.rowmin(), m.rowmax(), cmin, cmax);
  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
    tmp(i) = pow(m(i), e);
  }
  return tmp;
}
/*
Returns dmatrix with pow of each element in m raised to the exponent e.
\param m dmatrix
\param e floating point exponent
*/
dmatrix pow(const dmatrix& m, const double e)
{
  ivector cmin(m.rowmin(), m.rowmax());
  ivector cmax(m.rowmin(), m.rowmax());
  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
    cmin(i) = m(i).indexmin();
    cmax(i) = m(i).indexmax();
  }
  dmatrix tmp(m.rowmin(), m.rowmax(), cmin, cmax);
  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
    tmp(i) = pow(m(i), e);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix tan(const dmatrix& m)
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
dmatrix cos(const dmatrix& m)
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
dmatrix sin(const dmatrix& m)
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
dmatrix elem_prod(const dmatrix& m, const dmatrix& m2)
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
dmatrix log(const dmatrix& m)
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
Returns dmatrix with each of element in m is square rooted.
\param m dmatrix
*/
dmatrix sqrt(const dmatrix& m)
{
  ivector cmin(m.rowmin(), m.rowmax());
  ivector cmax(m.rowmin(), m.rowmax());
  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
    cmin(i) = m(i).indexmin();
    cmax(i) = m(i).indexmax();
  }
  dmatrix tmp(m.rowmin(),m.rowmax(),cmin,cmax);
  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
    tmp(i) = sqrt(m(i));
  }
  return tmp;
}
/**
Returns dmatrix with each of element in m is squared.
\param m dmatrix
*/
dmatrix sqr(const dmatrix& m)
{
  ivector cmin(m.rowmin(), m.rowmax());
  ivector cmax(m.rowmin(), m.rowmax());
  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
    cmin(i) = m(i).indexmin();
    cmax(i) = m(i).indexmax();
  }
  dmatrix tmp(m.rowmin(), m.rowmax(), cmin, cmax);
  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
    tmp(i) = sqr(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix exp(const dmatrix& m)
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
dmatrix elem_div(const dmatrix& m, const dmatrix& m2)
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
