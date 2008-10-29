
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
 double mean(_CONST dmatrix& m)
 {
   double tmp;
   tmp=sum(m)/size_count(m);
   return tmp;
 }
#undef HOME_VERSION
