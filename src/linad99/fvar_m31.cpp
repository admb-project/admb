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
dvar_matrix operator/(const double e, const dvar_matrix& m)
{
  dvar_matrix tmp;
  int min = m.indexmin();
  int max = m.indexmax();
  tmp.allocate(min, max);

  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = e / *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator/(const prevariable& e, const dvar_matrix& m)
{
  dvar_matrix tmp;

  int min = m.indexmin();
  int max = m.indexmax();
  tmp.allocate(min, max);

  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = e / *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator/(const prevariable& e, const dmatrix& m)
{
  dvar_matrix tmp;

  int min = m.indexmin();
  int max = m.indexmax();
  tmp.allocate(min, max);

  dvar_vector* ptmpi = &tmp(min);
  const dvector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = e / *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
