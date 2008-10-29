


#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   dvar_matrix cube(_CONST dvar_matrix& m)
   {
     dvar_matrix tmp;
     tmp.allocate(m);
     for (int i=tmp.rowmin();i<=tmp.rowmax();i++)
     {
       tmp(i)=cube(m(i));
     }
     return tmp;
   }  

   dvar3_array cube(_CONST dvar3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=cube(m(i));
     }
     return tmp;
   }  


#undef HOME_VERSION

