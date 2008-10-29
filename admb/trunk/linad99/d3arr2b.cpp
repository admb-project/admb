
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   d3_array operator / (_CONST d3_array& m, CGNU_DOUBLE d)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m(i)/d;
     }
     return tmp;
   }  

   void d3_array::operator /= ( CGNU_DOUBLE d)
   {
     for (int i=slicemin();i<=slicemax();i++)
     {
       (*this)(i)/=d;
     }
   }  

#undef HOME_VERSION
