
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

 dmatrix identity_matrix(int min,int max)
 {
   dmatrix tmp(min,max,min,max);
   #ifndef SAFE_INITIALIZE
     tmp.initialize();
   #endif

   for (int i=min; i<=max; i++)
   {
     tmp.elem(i,i)=1;
   }
   return(tmp);
 }      

#undef HOME_VERSION
