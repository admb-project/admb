
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   double square( CGNU_DOUBLE m)
   {
     return m*m;
   }

   dvector square(_CONST dvector& m)
   {
     dvector tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }  

   dmatrix square(_CONST dmatrix& m)
   {
     dmatrix tmp;
     tmp.allocate(m);
     for (int i=tmp.rowmin();i<=tmp.rowmax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }  

   d3_array square(_CONST d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }  


#undef HOME_VERSION
