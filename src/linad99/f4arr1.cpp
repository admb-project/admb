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
dvar4_array sqrt(const dvar4_array& m)
{
  dvar4_array tmp;
  tmp.allocate(m);
  int min = m.slicemin();
  int max = m.slicemax();
  dvar3_array* ptmpi = &tmp(min);
  const dvar3_array* pmi = &m(min);
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
dvar4_array exp(const dvar4_array& m)
{
  dvar4_array tmp;
  tmp.allocate(m);
  int min = m.slicemin();
  int max = m.slicemax();
  dvar3_array* ptmpi = &tmp(min);
  const dvar3_array* pmi = &m(min);
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
dvar4_array mfexp(const dvar4_array& m)
{
  dvar4_array tmp;
  tmp.allocate(m);
  int min = m.slicemin();
  int max = m.slicemax();
  dvar3_array* ptmpi = &tmp(min);
  const dvar3_array* pmi = &m(min);
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
dvar4_array log(const dvar4_array& m)
{
  dvar4_array tmp;
  tmp.allocate(m);
  int min = m.indexmin();
  int max = m.indexmax();
  dvar3_array* ptmpi = &tmp(min);
  const dvar3_array* pmi = &m(min);
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
dvariable sum(const dvar4_array& m)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();

  int min = m.indexmin();
  int max = m.indexmax();
  dvariable tmp = 0.0;
  const dvar3_array* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    tmp += sum(*pmi);
    ++pmi;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
