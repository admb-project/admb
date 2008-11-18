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

 dvar_vector  operator * (_CONST dvector& x,_CONST dvar_matrix& m)
 {
   RETURN_ARRAYS_INCREMENT();
   if (x.indexmin() != m.rowmin() || x.indexmax() != m.rowmax())
   {
     cerr << " Incompatible array bounds in dvar_vector  operator * (_CONST dvector& x,_CONST dvar_matrix& m)\n";
     ad_exit(21);
   }
   dvar_vector tmp(m.colmin(),m.colmax());
   dvariable sum;

   for (int j=m.colmin(); j<=m.colmax(); j++)
   {
     sum=0.0;
     for (int i=x.indexmin(); i<=x.indexmax(); i++)
     {
       sum+=x.elem(i)*m.elem(i,j);
     }
     tmp[j]=sum;
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }      


#undef HOME_VERSION
