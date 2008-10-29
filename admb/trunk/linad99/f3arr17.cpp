#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

 dvar3_array::dvar3_array(void)
 {
   allocate();
 }

 void dvar3_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }

#undef HOME_VERSION

