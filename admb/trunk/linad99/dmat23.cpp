#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

 dmatrix outer_prod(_CONST dvector& v1,_CONST dvector& v2 )
 {
   dmatrix tmp(v1.indexmin(),v1.indexmax(), v2.indexmin(), v2.indexmax() );

   for (int i=v1.indexmin(); i<=v1.indexmax(); i++)
   {
     for (int j=v2.indexmin(); j<=v2.indexmax(); j++)
     {
       tmp.elem(i,j)=v1.elem(i)*v2.elem(j);
     }
   }
   return(tmp);
 }      


#undef HOME_VERSION
