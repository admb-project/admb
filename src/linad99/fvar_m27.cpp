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
  int min = m.rowmin();
  int max = m.rowmax();
  ivector cmin(min, max);
  ivector cmax(min, max);
  int* pcmini = cmin.get_v() + min;
  int* pcmaxi = cmax.get_v() + min;
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *pcmini = pmi->indexmin();
    *pcmaxi = pmi->indexmax();

    ++pmi;
    ++pcmini;
    ++pcmaxi;
  }
  dvar_matrix tmp(min, max, cmin, cmax);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix use_shape(const dmatrix& m)
{
  int min = m.rowmin();
  int max = m.rowmax();
  ivector cmin(min, max);
  ivector cmax(min, max);

  int* pcmini = cmin.get_v() + min;
  int* pcmaxi = cmax.get_v() + min;
  const dvector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *pcmini = pmi->indexmin();
    *pcmaxi = pmi->indexmax();

    ++pmi;
    ++pcmini;
    ++pcmaxi;
  }
  dmatrix tmp(min, max, cmin, cmax);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix pow(const dvar_matrix& m, int e)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = pow(*pmi, e);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix pow(const dmatrix& m, const prevariable& e)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = pow(*pmi, e);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix pow(const dvar_matrix& m, const prevariable& e)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = pow(*pmi, e);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix pow(const dvar_matrix& m, const double e)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = pow(*pmi, e);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix tan(const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = tan(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix cos(const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = cos(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix sin(const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = sin(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix log(const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = log(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix sqrt(const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = sqrt(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix sqr(const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = sqr(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix exp(const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = exp(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_div(const dvar_matrix& m, const dvar_matrix& m2)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  const dvar_vector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = elem_div(*pmi, *pm2i);

    ++ptmpi;
    ++pmi;
    ++pm2i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_div(const dmatrix& m,const dvar_matrix& m2)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvector* pmi = &m(min);
  const dvar_vector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = elem_div(*pmi, *pm2i);

    ++ptmpi;
    ++pmi;
    ++pm2i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_div(const dvar_matrix& m, const dmatrix& m2)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  const dvector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = elem_div(*pmi, *pm2i);

    ++ptmpi;
    ++pmi;
    ++pm2i;
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
  int min = m.rowmin();
  int max = m.rowmax();
  dvar_matrix tmp(min, max);

  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  const dvar_vector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = elem_prod(*pmi, *pm2i);

    ++ptmpi;
    ++pmi;
    ++pm2i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_prod(const dmatrix& m, const dvar_matrix& m2)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvector* pmi = &m(min);
  const dvar_vector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = elem_prod(*pmi, *pm2i);

    ++ptmpi;
    ++pmi;
    ++pm2i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix elem_prod(const dvar_matrix& m, const dmatrix& m2)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  const dvector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = elem_prod(*pmi, *pm2i);

    ++ptmpi;
    ++pmi;
    ++pm2i;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const double x, const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = x + *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const prevariable& x, const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = x * *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const dvar_matrix& m, const double x)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pmi + x;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const dvariable& x, const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = x + *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const dvar_matrix& m, const dvariable& x)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pmi + x;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const dvar_matrix& m, const prevariable& x)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pmi * x;

    ++ptmpi;
    ++pmi;
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

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pmi - x;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const double x, const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = x - *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const dvar_matrix& m, const dvariable& x)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pmi - x;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const dvariable& x, const dvar_matrix& m)
{
  dvar_matrix tmp = use_shape(m);

  int min = m.rowmin();
  int max = m.rowmax();
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = x - *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
