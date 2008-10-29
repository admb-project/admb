
//#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
#include <d4arr.hpp>

dvar4_array::dvar4_array() 
{
  allocate();
}

void dvar4_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}
#undef HOME_VERSION

