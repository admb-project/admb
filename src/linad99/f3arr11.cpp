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
dvar3_array mfexp(const dvar3_array& m)
{
  dvar3_array tmp;
  tmp.allocate(m);
  int min = tmp.slicemin();
  int max = tmp.slicemax();
  dvar_matrix* ptmpi = &tmp(min);
  const dvar_matrix* pmi = &m(min);
  for (int i = min;i <= max; ++i)
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
dvar3_array mfexp(const dvar3_array& m, const double d)
{
  dvar3_array tmp;
  tmp.allocate(m);
  int min = tmp.slicemin();
  int max = tmp.slicemax();
  dvar_matrix* ptmpi = &tmp(min);
  const dvar_matrix* pmi = &m(min);
  for (int i = min;i <= max; ++i)
  {
    *ptmpi = mfexp(*pmi, d);
    ++ptmpi;
    ++pmi;
  }
  return tmp;
}
