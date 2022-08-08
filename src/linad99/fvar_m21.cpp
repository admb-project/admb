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
dvar_matrix operator-(const dvar_matrix& m1, const dmatrix& m2 )
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();

#ifndef OPT_LIB
  if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
  {
    cerr << " Incompatible array bounds in "
     "dvar_matrix operator+(const dvar_matrix& x, const dmatrix& m)\n";
    ad_exit(21);
  }
#endif

  int min = m1.rowmin();
  int max = m1.rowmax();
  dvar_matrix tmp;
  tmp.allocate(min, max);

  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pm1i = &m1(min);
  const dvector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pm1i - *pm2i;

    ++ptmpi;
    ++pm1i;
    ++pm2i;
  }

  gs->RETURN_ARRAYS_DECREMENT();

  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const dvar_matrix& m1, const dvar_matrix& m2)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();

#ifndef OPT_LIB
  if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
  {
     cerr << " Incompatible array bounds in "
     "dvar_matrix operator+(const dvar_matrix& x, const dvar_matrix& m)\n";
     ad_exit(21);
  }
#endif

  int min = m1.rowmin();
  int max = m1.rowmax();
  dvar_matrix tmp;
  tmp.allocate(min, max);

  dvar_vector* ptmpi = &tmp(min);
  const dvar_vector* pm1i = &m1(min);
  const dvar_vector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pm1i - *pm2i;

    ++ptmpi;
    ++pm1i;
    ++pm2i;
  }

  gs->RETURN_ARRAYS_DECREMENT();

  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator-(const dmatrix& m1, const dvar_matrix& m2)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();

#ifndef OPT_LIB
  if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
  {
     cerr << " Incompatible array bounds in "
     "dvar_matrix operator+(const dmatrix& x, const dvar_matrix& m)\n";
     ad_exit(21);
  }
#endif

  int min = m1.rowmin();
  int max = m1.rowmax();
  dvar_matrix tmp;
  tmp.allocate(min, max);

  dvar_vector* ptmpi = &tmp(min);
  const dvector* pm1i = &m1(min);
  const dvar_vector* pm2i = &m2(min);
  for (int i = min; i <= max; ++i)
  {
    *ptmpi = *pm1i - *pm2i;

    ++ptmpi;
    ++pm1i;
    ++pm2i;
  }

  gs->RETURN_ARRAYS_DECREMENT();

  return tmp;
}
