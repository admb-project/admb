



#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

  ivector sgn(_CONST dvector& v)
  {
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    ivector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      if(v(i)>0.0) 
        tmp(i)=1;
      else
        tmp(i)=-1;
    }
    return tmp;
  }

#undef HOME_VERSION
