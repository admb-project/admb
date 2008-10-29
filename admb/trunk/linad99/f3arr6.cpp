

#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   dvar3_array square(_CONST dvar3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }  

#undef HOME_VERSION

