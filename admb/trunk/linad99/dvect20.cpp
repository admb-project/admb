


#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"




  dvector& dvector::operator /= ( CGNU_DOUBLE x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)/=x;
    }
    return(*this);
  }

  dvector& dvector::operator *= ( CGNU_DOUBLE x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)*=x;
    }
    return(*this);
  }
#undef HOME_VERSION
