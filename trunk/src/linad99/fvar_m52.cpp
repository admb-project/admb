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
dvar_vector solve_trans(const banded_lower_triangular_dvar_matrix& M,
  const dvector& y)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int bw=M.bandwidth();

  if (y.indexmin() !=mmin || y.indexmax() !=mmax)
  {
    cerr << "incompatible size in solve_trans" << endl;
    ad_exit(1);
  }
  dvar_vector x(mmin,mmax);
  int i,j;

  for (i=mmax;i>=mmin;i--)
  {
    dvariable sum=0.0;
    int jmax=admin(mmax,i+bw-1);
    for (j=i+1;j<=jmax;j++)
    {
      sum+=M(j,i)*x(j);
    }
    x(i)=(y(i)-sum)/M(i,i);
  }

  return x;
}
