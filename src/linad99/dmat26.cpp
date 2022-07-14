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
dmatrix mfexp(const dmatrix& m)
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

    ++pcmini;
    ++pcmaxi;
    ++pmi;
  }

  dmatrix tmp(min, max, cmin, cmax);
  dvector* ptmpi = &tmp(min);
  pmi = &m(min);
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
dmatrix mfexp(const dmatrix& m, const double d)
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

    ++pcmini;
    ++pcmaxi;
    ++pmi;
  }

  dmatrix tmp(min, max, cmin, cmax);
  dvector* ptmpi = &tmp(min);
  pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = mfexp(*pmi, d);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
