/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

   dvar7_array operator / (_CONST d7_array& m,_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar7_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar7_array operator / (_CONST dvar7_array& m, CGNU_DOUBLE d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar7_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar7_array operator / (_CONST dvar7_array& m,_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar7_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   void dvar7_array::operator /=(_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
     RETURN_ARRAYS_DECREMENT();
   }  

   void dvar7_array::operator /=(_CONST double& d)
   {
     RETURN_ARRAYS_INCREMENT();
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
     RETURN_ARRAYS_DECREMENT();
   }  

dvariable sum(_CONST dvar7_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvariable tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

