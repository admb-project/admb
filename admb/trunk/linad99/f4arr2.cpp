#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

   dvar4_array operator / (_CONST d4_array& m,_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar4_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar4_array operator / (_CONST dvar4_array& m, CGNU_DOUBLE d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar4_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar4_array operator / (_CONST dvar4_array& m,_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar4_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   void dvar4_array::operator /=(_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
     RETURN_ARRAYS_DECREMENT();
   }  

   void dvar4_array::operator /=(_CONST double& d)
   {
     RETURN_ARRAYS_INCREMENT();
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
     RETURN_ARRAYS_DECREMENT();
   }  

#undef HOME_VERSION
