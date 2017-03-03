/*
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#include "fvar.hpp"

/**
Returns a dvector containing the differences of an x(i) and  x(i + 1) for i = 1 to x.indexmax() - 1.

\param x input.
*/
dvector first_difference(const dvector& x)
 {
   if (x.size()<=1)
   {
     cerr << "Error -- vector size too small"
             " in first_difference(const dvector&)" << endl;
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
