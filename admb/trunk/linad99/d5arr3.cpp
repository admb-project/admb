
//#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
//#include <d4arr.hpp>


 d5_array::d5_array() 
 {
   allocate();
 }

void d5_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }

#undef HOME_VERSION

