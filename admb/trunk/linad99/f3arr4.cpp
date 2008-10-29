
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   dvar3_array operator - ( CGNU_DOUBLE d,_CONST dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d-m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvariable mean(_CONST dvar3_array& m)
   {
     dvariable tmp;
     tmp=sum(m)/double(size_count(m));
     return tmp;
   }
#undef HOME_VERSION
