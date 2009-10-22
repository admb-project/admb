/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
#endif

#include <math.h>

 void shape_check(_CONST dvector& v1,_CONST dvector& v2,char * function_name);

 dvector sin(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sin(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector cos(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=cos(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector tan(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=tan(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector sinh(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sinh(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector cosh(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=cosh(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector tanh(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=tanh(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector pow(_CONST dvector& v1, CGNU_DOUBLE x)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=pow(v1.elem(i),x);             // ***
   }
   return(tmp);
 }

 dvector pow(_CONST dvector& v1,int x)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=pow(v1.elem(i),x);             // ***
   }
   return(tmp);
 }


 dvector pow(_CONST dvector& v1,_CONST dvector& v2)              // ***
 {
   shape_check(v1,v2,"dvector pow(_CONST dvector& v1,_CONST dvector& v2)");

   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=pow(v1.elem(i),v2.elem(i));             // ***
   }
   return(tmp);
 }

 dvector pow( CGNU_DOUBLE x,_CONST dvector& v2)                 // ***
 {
   dvector tmp(v2.indexmin(),v2.indexmax());
   for (int i=v2.indexmin();i<=v2.indexmax();i++)
   {
     tmp.elem(i)=pow(x,v2.elem(i));             // ***
   }
   return(tmp);
 }

 dvector asin(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=asin(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector acos(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=acos(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector atan(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=atan(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector log10(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=log10(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector sqrt(_CONST dvector& v1)                            // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sqrt(v1.elem(i));             // ***
   }
   return(tmp);
 }

 dvector sqr(_CONST dvector& v1)                       // ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sqrt(v1.elem(i));             // ***
   }
   return(tmp);
 }


