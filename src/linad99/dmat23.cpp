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

/**
 * Description not yet available.
 * \param
 */
dmatrix outer_prod(const dvector& v1, const dvector& v2)
{
  int imin = v1.indexmin();
  int imax = v1.indexmax();
  int jmin = v2.indexmin();
  int jmax = v2.indexmax();

  dmatrix tmp(imin, imax, jmin, jmax);

  dvector* ptmpi = &tmp(imin);
  double* pv1i = v1.get_v() + imin;
  for (int i = imin; i <= imax; ++i)
  {
    double* ptmpij = ptmpi->get_v() + jmin;
    double* pv2j = v2.get_v() + jmin;
    for (int j = jmin; j <= jmax; ++j)
    {
      *ptmpij = *pv1i * *pv2j;

      ++ptmpij;
      ++pv2j;
    }

    ++ptmpi;
    ++pv1i;
  }
  return tmp;
}
