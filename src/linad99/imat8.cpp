/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
  ivector colsum(_CONST imatrix&v)
  {
    int cmin=v.colmin();
    int cmax=v.colmax();
    int rmin=v.rowmin();
    int rmax=v.rowmax();

    ivector tmp(cmin,cmax);
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

/**
 * Description not yet available.
 * \param
 */
  ivector rowsum(_CONST imatrix&v)
  {
    int rmin=v.rowmin();
    int rmax=v.rowmax();

    ivector tmp(rmin,rmax);
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
  void imatrix::fill_seqadd(int i2,int j)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    int ii=i2;
    for (int i=mmin;i<=mmax;i++)
    {
      if (allocated((*this)(i)))
      {
        (*this)(i).fill_seqadd(ii,j);
        int jmax=(*this)(i).indexmax();
        ii=(*this)(i,jmax)+j;
      }
    }
  }
