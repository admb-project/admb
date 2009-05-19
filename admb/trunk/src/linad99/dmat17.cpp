/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

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

