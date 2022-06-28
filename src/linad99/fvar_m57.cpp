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

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator+(const dvariable& x, const dmatrix& m)
{
  int mmin = m.indexmin();
  int mmax = m.indexmax();
  dvar_matrix tmp(mmin, mmax);

  dvar_vector* ptmpi = &tmp(mmin);
  const dvector* pmi = &m(mmin);
  for (int i=mmin;i<=mmax;i++)
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
dvar_matrix operator-(const dvariable& x, const dmatrix& m)
{
  int mmin=m.indexmin();
  int mmax=m.indexmax();
  dvar_matrix tmp(mmin, mmax);

  dvar_vector* ptmpi = &tmp(mmin);
  const dvector* pmi = &m(mmin);
  for (int i=mmin;i<=mmax;i++)
  {
    *ptmpi = x - *pmi;

    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
