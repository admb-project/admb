
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
  void dvector::initialize(void)
  {
    if (!(!(*this)))  // only initialize allocated objects
    {
      for (int i=indexmin();i<=indexmax();i++)
      {
        elem(i)=0.0;
      }
    }
  }
#undef HOME_VERSION
