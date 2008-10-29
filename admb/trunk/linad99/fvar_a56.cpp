
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

  dvar_vector& dvar_vector::operator *= ( CGNU_DOUBLE x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)*=x;
    }
    return(*this);
  }

  dvar_vector& dvar_vector::operator *= ( _CONST prevariable& x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)*=x;
    }
    return(*this);
  }
#undef HOME_VERSION
