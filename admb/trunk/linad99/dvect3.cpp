#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include <fvar.hpp>

  double norm(_CONST dvector& t1)
  {
    double tmp;
    tmp=t1*t1;
    if (tmp>0)
    {
      tmp=pow(tmp,.5);
    }
    return(tmp);
  }

  double norm2(_CONST dvector& t1)
  {
    double tmp;
    tmp=t1*t1;
    return(tmp);
  }

#undef HOME_VERSION
