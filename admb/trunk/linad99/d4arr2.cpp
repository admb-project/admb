
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   void d4_array::operator /= (CGNU_DOUBLE d)
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
   }  

   d4_array operator / (_CONST d4_array& m, CGNU_DOUBLE d)
   {
     d4_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     return tmp;
   }  

   d4_array operator / ( CGNU_DOUBLE d,_CONST d4_array& m)
   {
     d4_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=d/m(i);
     }
     return tmp;
   }  

#undef HOME_VERSION
