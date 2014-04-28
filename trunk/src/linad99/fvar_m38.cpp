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
  RETURN_ARRAYS_INCREMENT();
  int rmin=m.rowmin();
  int rmax=m.rowmax();

  ivector cmin(rmin,rmax);
  ivector cmax(rmin,rmax);

  int i;
  for (i=rmin;i<=rmax;i++)
  {
    cmin(i)=(m(i)).indexmin();
    cmax(i)=(m(i)).indexmax();
  }
  dvar_matrix tmp(rmin,rmax,cmin,cmax);

  for (i=rmin;i<=rmax;i++)
  {
    tmp(i)=x*m(i);
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const dvar_matrix& m, const double x)
{
  RETURN_ARRAYS_INCREMENT();
  int rmin=m.rowmin();
  int rmax=m.rowmax();

  ivector cmin(rmin,rmax);
  ivector cmax(rmin,rmax);

  int i;
  for (i=rmin;i<=rmax;i++)
  {
    cmin(i)=(m(i)).indexmin();
    cmax(i)=(m(i)).indexmax();
  }
  dvar_matrix tmp(rmin,rmax,cmin,cmax);

  for (i=rmin;i<=rmax;i++)
  {
    tmp(i)=x*m(i);
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const double x, const dvar_matrix& m)
{
  RETURN_ARRAYS_INCREMENT();
  int rmin=m.rowmin();
  int rmax=m.rowmax();

  ivector cmin(rmin,rmax);
  ivector cmax(rmin,rmax);

  int i;
  for (i=rmin;i<=rmax;i++)
  {
    cmin(i)=(m(i)).indexmin();
    cmax(i)=(m(i)).indexmax();
  }
  dvar_matrix tmp(rmin,rmax,cmin,cmax);

  for (i=rmin;i<=rmax;i++)
  {
    tmp(i)=x*m(i);
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
