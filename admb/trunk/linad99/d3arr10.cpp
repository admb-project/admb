#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

void d3_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}

d3_array::d3_array(void)
{
  allocate();
}
#undef HOME_VERSION

