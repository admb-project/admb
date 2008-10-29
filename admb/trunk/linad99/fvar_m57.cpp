

// #define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
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
