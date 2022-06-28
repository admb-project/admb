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
dvar_matrix& dvar_matrix::operator+=(const dvar_matrix& m1)
{
  int min = rowmin();
  int max = rowmax();

#ifndef OPT_LIB
  if (min != m1.rowmin() || max != m1.rowmax())
  {
     cerr << " Incompatible array bounds in "
     "dvar_matrix& operator += (const dvar_vector&)\n";
     ad_exit(21);
  }
#endif

  dvar_vector* pmi = m + min;
  const dvar_vector* pm1i = &m1(min);
  for (int i = min; i <= max; ++i)
  {
     *pmi += *pm1i;

     ++pmi;
     ++pm1i;
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& dvar_matrix::operator+=(const dmatrix& m1)
{
  int min = rowmin();
  int max = rowmax();

#ifndef OPT_LIB
  if (min != m1.rowmin() || max != m1.rowmax())
  {
     cerr << " Incompatible array bounds in "
     "dvar_matrix& operator+=(const dvar_vector&)\n";
     ad_exit(21);
  }
#endif

  dvar_vector* pmi = m + min;
  const dvector* pm1i = &m1(min);
  for (int i = min; i <= max; ++i)
  {
     *pmi += *pm1i;

     ++pmi;
     ++pm1i;
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& dvar_matrix::operator-=(const dvar_matrix& m1)
{
  int min = rowmin();
  int max = rowmax();

#ifndef OPT_LIB
  if (min != m1.rowmin() || max != m1.rowmax())
  {
     cerr << " Incompatible array bounds in "
     "dvar_matrix& operator -= (const dvar_vector&)\n";
     ad_exit(21);
  }
#endif

  dvar_vector* pmi = m + min;
  const dvar_vector* pm1i = &m1(min);
  for (int i = min; i <= max; ++i)
  {
     *pmi -= *pm1i;

     ++pmi;
     ++pm1i;
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& dvar_matrix::operator-=(const dmatrix& m1)
{
  int min = rowmin();
  int max = rowmax();

#ifndef OPT_LIB
  if (min != m1.rowmin() || max != m1.rowmax())
  {
     cerr << " Incompatible array bounds in "
     "dvar_matrix& operator-=(const dvar_vector&)\n";
     ad_exit(21);
  }
#endif

  dvar_vector* pmi = m + min;
  const dvector* pm1i = &m1(min);
  for (int i = min; i <= max; ++i)
  {
     *pmi -= *pm1i;

     ++pmi;
     ++pm1i;
  }
  return *this;
}
