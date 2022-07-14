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
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

/**
 * Description not yet available.
 * \param
 */
dmatrix value(const dvar_matrix& m)
{
  int nrl = m.rowmin();
  int nrh = m.rowmax();
  ivector ncl(nrl, nrh);
  ivector nch(nrl, nrh);
  int* pncli = ncl.get_v() + nrl;
  int* pnchi = nch.get_v() + nrl;
  const dvar_vector* pmi = &m(nrl);
  for (int i = nrl; i <= nrh; ++i)
  {
    *pncli = pmi->indexmin();
    *pnchi = pmi->indexmax();

    ++pncli;
    ++pnchi;
    ++pmi;
  }
  dmatrix tmp(nrl, nrh, ncl, nch);
  pmi = &m(nrl);

  dvector* ptmpi = &tmp(nrl);
  for (int i = nrl; i <= nrh; ++i)
  {
    *ptmpi = value(*pmi);

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
