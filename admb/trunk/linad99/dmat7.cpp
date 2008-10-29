
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

void dmatrix::initialize(void)
{
  if (!(!(*this)))  // only initialize allocated objects
  {
    for (int i=rowmin();i<=rowmax();i++)
    {
      elem(i).initialize();
    }
  }
} 


#undef HOME_VERSION
