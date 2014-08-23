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
  The VEC operator concatenates the columns of matrix M into a column vector.
  \param matrix M
 */
dvar_vector VEC(const dvar_matrix& _m)
  {
    dvar_matrix& m= (dvar_matrix&) _m;
    int i;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    int ii=0;
    ivector io(mmin-1,mmax);
    io(mmin-1)=0;
    for (i=mmin;i<=mmax;i++)
    {
      ii+=m(i).indexmax()-m(i).indexmin()+1;
      io(i)=ii;
    }
    dvar_vector tmp(1,ii);
    for (i=mmin;i<=mmax;i++)
    {
      tmp(io(i-1)+1,io(i)).shift(m(i).indexmin())=m(i);
    }
    return tmp;
  }

/**
  The MAT operator is the inverse of the VEC operator.
It takes the elements of vector v and sequentially fills in the columns of an n by m matrix.
  \param vector v
  \param integer n, the number of rows in the resulting matrix
  \param integer m, the umber of columns in the resulting matrix
 */
dvar_matrix MAT(const dvar_vector& v, int n, int m)
  {
    dvar_matrix tmp(1,n,1,m);
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    int ii=mmin;
    if ( mmax-mmin+1 != n*m)
    {
      cerr << " Vector and Matrix sizes don't match in function MAT" << endl;
      tmp.initialize();
      return tmp;
    }
    for (int i=1;i<=n;i++)
    {
      for (int j=1;j<=m;j++)
      {
        tmp(i,j)=v(ii++);
      }
    }
    return tmp;
  }
