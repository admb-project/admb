#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"


dmatrix operator * (const d3_array & t,const dvector& v)
{
  int mmin=t.indexmin();
  int mmax=t.indexmax();
  dmatrix tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=t(i)*v;
  }
  return tmp;
}

#undef HOME_VERSION

