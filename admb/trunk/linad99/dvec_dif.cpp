/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"

 dvector first_difference(_CONST dvector& x)
 {
   if (x.size()<=1)
   {
     cerr << "Error -- vector size too small"
             " in first_difference(_CONST dvector&)" << endl;
     ad_exit(1);
   }
   int mmin=x.indexmin();
   int mmax=x.indexmax()-1;
   dvector tmp(mmin,mmax);
   for (int i=mmin; i<=mmax; i++)
   {
     tmp.elem(i)=x.elem(i+1)-x.elem(i);
   }
   return(tmp);
 }
