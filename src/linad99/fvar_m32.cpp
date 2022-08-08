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

/**
 * Description not yet available.
 * \param
 */
dvar_matrix mfexp(const dvar_matrix& m)
{
  dvar_matrix tmp;

  int min = m.indexmin();
  int max = m.indexmax();
  tmp.allocate(min, max);
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = mfexp(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix mfexp(const dvar_matrix& m, const double d)
{
  dvar_matrix tmp;

  int min = m.indexmin();
  int max = m.indexmax();
  tmp.allocate(min, max);
  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = mfexp(*pmi, d);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
