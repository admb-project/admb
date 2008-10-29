
//#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
//#include <d5arr.hpp>

 d7_array::d7_array() 
 {
   allocate();
 }

void d7_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }

#undef HOME_VERSION

