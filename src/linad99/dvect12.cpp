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
double sum(const dvector &v)
  {
    double tmp=0;
    for (int i=v.indexmin(); i<=v.indexmax(); i++)
    {
      tmp+=v.elem(i);
    }
    return tmp;
  }

/** \ingroup matop
  Sum of the elements in each row of a matrix; constant object.
  \param v Reference to a matrix.
  \return A dvector, \f$s\f$, of length equal to the number of columns 
   in the matrix.
   \f$s_j=\sum_i v_{ij}\f$
 */
dvector colsum(const dmatrix &v)
  {
    int cmin=v.colmin();
    int cmax=v.colmax();
    int rmin=v.rowmin();
    int rmax=v.rowmax();

   // cout << "In colsum" << endl;
    dvector tmp(cmin,cmax);
    tmp.initialize();
    for (int j=cmin; j<=cmax; j++)
    {
      for (int i=rmin; i<=rmax; i++)
      {
        tmp(j)+=v(i,j);
      }
    }
    return tmp;
  }

/** \ingroup matop
  Sum of the elements in each column of a matrix; constant object.
  \param v Reference to a matrix.
  \return A dvector, \f$s\f$, of length equal to the number of rows 
   in the matrix.
   \f$s_i=\sum_j v_{ij}\f$
 */
dvector rowsum(const dmatrix &v)
  {
    //int cmin=v.colmin();
    //int cmax=v.colmax();
    int rmin=v.rowmin();
    int rmax=v.rowmax();

    dvector tmp(rmin,rmax);
    for (int i=rmin; i<=rmax; i++)
    {
      tmp(i)=sum(v(i));
    }
    return tmp;
  }

/**
 * Description not yet available.
 * \param
 */
double sum(const dmatrix& m)
{
  double tmp=0.;
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  return tmp;
}
