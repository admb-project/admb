

#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
 dvariable mean(_CONST dvar_matrix& m)
 {
   dvariable tmp;
   tmp=sum(m)/double(size_count(m));
   return tmp;
 }
#undef HOME_VERSION
