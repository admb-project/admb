/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */


// #define HOME_VERSION
// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable 

#include "fvar.hpp"

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
#undef HOME_VERSION
