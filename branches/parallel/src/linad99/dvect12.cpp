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
  double sum(_CONST dvector&v)
  {
    double tmp=0;
    for (int i=v.indexmin(); i<=v.indexmax(); i++)
    {
      tmp+=v.elem(i);
    }
    return tmp;
  }

/**
 * Description not yet available.
 * \param
 */
  dvector colsum(_CONST dmatrix&v)
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

/**
 * Description not yet available.
 * \param
 */
  dvector rowsum(_CONST dmatrix&v)
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
double sum(_CONST dmatrix& m)
{
  double tmp=0.;
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  return tmp;
}
