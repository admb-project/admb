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
// file fvar.cpp
// constructors, destructors and misc functions involving class dvariable 

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif


#include <stdio.h>
#ifndef __SUN__
#endif
#include <math.h>

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator / (_CONST dvar_matrix& m, CGNU_DOUBLE e)
{
  dvar_matrix tmp;
  tmp.allocate(m.indexmin(),m.indexmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)/e;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator / (_CONST dvar_matrix& m,_CONST prevariable& e)
{
  dvar_matrix tmp;
  tmp.allocate(m.indexmin(),m.indexmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)/e;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator / (_CONST dmatrix& m,_CONST prevariable& e)
{
  dvar_matrix tmp;
  tmp.allocate(m.indexmin(),m.indexmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(i)/e;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix symmetrize(_CONST dvar_matrix& m)
{
  if (m.rowmin() != m.colmin() || m.rowmax() != m.colmax() )
  {
    cerr << " Non square matrix passed to dmatrix symmetrize\n";
    ad_exit(1);
  }
  int rmin=m.rowmin();
  int rmax=m.rowmax();

  dvar_matrix s(rmin,rmax,rmin,rmax);


  for (int i=rmin;i<=rmax;i++)
  {
    s(i,i)=m(i,i);
    for (int j=rmin;j<i;j++)
    {
      s(i,j)=(m(i,j)+m(j,i))/2.;
      s(j,i)=s(i,j);
    }
  }

  return s;
}
