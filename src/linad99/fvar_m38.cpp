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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const prevariable& x, const dmatrix& m)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();

  int rmin=m.rowmin();
  int rmax=m.rowmax();

  ivector cmin(rmin,rmax);
  ivector cmax(rmin,rmax);

  const dvector* pmi = &m(rmin);
  int* pcmini = cmin.get_v() + rmin;
  int* pcmaxi = cmax.get_v() + rmin;
  for (int i=rmin;i<=rmax;++i)
  {
    *pcmini = pmi->indexmin();
    *pcmaxi = pmi->indexmax();

    ++pcmini;
    ++pcmaxi;
    ++pmi;
  }

  dvar_matrix tmp(rmin,rmax,cmin,cmax);

  pmi = &m(rmin);
  for (int i=rmin;i<=rmax;++i)
  {
    tmp(i) = x * *pmi;

    ++pmi;
  }

  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const dvar_matrix& m, const double x)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();

  int rmin=m.rowmin();
  int rmax=m.rowmax();

  ivector cmin(rmin,rmax);
  ivector cmax(rmin,rmax);

  const dvar_vector* pmi = &m(rmin);
  int* pcmini = cmin.get_v() + rmin;
  int* pcmaxi = cmax.get_v() + rmin;
  for (int i=rmin;i<=rmax;++i)
  {
    *pcmini = pmi->indexmin();
    *pcmaxi = pmi->indexmax();

    ++pcmini;
    ++pcmaxi;
    ++pmi;
  }
  dvar_matrix tmp(rmin,rmax,cmin,cmax);

  pmi = &m(rmin);
  for (int i=rmin;i<=rmax;++i)
  {
    tmp(i) = x * *pmi;

    ++pmi;
  }

  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const double x, const dvar_matrix& m)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();
  int rmin=m.rowmin();
  int rmax=m.rowmax();

  ivector cmin(rmin,rmax);
  ivector cmax(rmin,rmax);

  const dvar_vector* pmi = &m(rmin);
  int* pcmini = cmin.get_v() + rmin;
  int* pcmaxi = cmax.get_v() + rmin;
  for (int i=rmin;i<=rmax;++i)
  {
    *pcmini = pmi->indexmin();
    *pcmaxi = pmi->indexmax();

    ++pcmini;
    ++pcmaxi;
    ++pmi;
  }

  dvar_matrix tmp(rmin,rmax,cmin,cmax);

  pmi = &m(rmin);
  for (int i=rmin;i<=rmax;++i)
  {
    tmp(i) = x * *pmi;

    ++pmi;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
