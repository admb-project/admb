
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

void dmatrix::allocate(void)  //default constructor
{
  index_min=1;
  index_max=0;
  m=NULL;
  shape=NULL;
} 

dmatrix::dmatrix()  //default constructor 
{
  allocate();
} 
#undef HOME_VERSION
