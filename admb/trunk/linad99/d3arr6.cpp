#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   d3_array pow(_CONST d3_array& m,int e)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=pow(m(i),e);
     }
     return tmp;
   }  

#undef HOME_VERSION
