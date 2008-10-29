
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   d5_array operator / (_CONST d5_array& m, CGNU_DOUBLE d)
   {
     d5_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     return tmp;
   }  

   void d5_array::operator /= ( CGNU_DOUBLE d)
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
   }  

#undef HOME_VERSION
