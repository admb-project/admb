/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

// file fvar_fn.cpp
// math.h functions involving prevariables
#include "fvar.hpp"
#include <stdio.h>



 double sfabs( CGNU_DOUBLE v1)
 {
   #define cutoff 0.001
   #define cutoff2 0.000001
   double a = 2./cutoff;
   double b = 1./cutoff2;     

   double tmp,tmp1,t2;
   double return_value;
   tmp1=v1;
   tmp=::fabs(tmp1);
   if (tmp > cutoff)
   {
        return_value=tmp;
   }
   else
   {
     t2=tmp*tmp;

     if (tmp1 >=0)
     {
       return_value=t2*(a-b*tmp1);
     }
     else
     {
       return_value=t2*(a+b*tmp1);
     }
   }
   return(return_value);
 }



  dvector sfabs(_CONST dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=sfabs(t1.elem(i));
     }
     return(tmp);
  }

