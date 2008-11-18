/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
#include "fvar.hpp"

   d7_array operator / (_CONST d7_array& m, CGNU_DOUBLE d)
   {
     d7_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     return tmp;
   }  

   void d7_array::operator /= ( CGNU_DOUBLE d)
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
   }  

  double sum(_CONST d7_array& m)
  {
    RETURN_ARRAYS_INCREMENT();
    double tmp=0.;
    for (int i=m.indexmin();i<=m.indexmax();i++)
    {
      tmp+=sum(m.elem(i));
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
  }

#undef HOME_VERSION
