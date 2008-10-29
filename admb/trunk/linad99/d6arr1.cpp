#define HOME_VERSION
//COPYRIGHT (c) 1997 OTTER RESEARCH LTD
#include "fvar.hpp"

   d6_array operator / (_CONST d6_array& m, CGNU_DOUBLE d)
   {
     d6_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     return tmp;
   }  

   void d6_array::operator /= ( CGNU_DOUBLE d)
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
   }  

#undef HOME_VERSION
