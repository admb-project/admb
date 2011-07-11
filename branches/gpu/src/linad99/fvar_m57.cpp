/*
 * $Id: fvar_m57.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable 

#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator + (const dvariable& x,const dmatrix& m)
{
  int mmin=m.indexmin();
  int mmax=m.indexmax();
  dvar_matrix tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=x+m(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator - (const dvariable& x,const dmatrix& m)
{
  int mmin=m.indexmin();
  int mmax=m.indexmax();
  dvar_matrix tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=x-m(i);
  }
  return tmp;
}
