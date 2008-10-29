
//#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

dvar6_array::dvar6_array() 
{
  allocate();
}

void dvar6_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}

#undef HOME_VERSION

