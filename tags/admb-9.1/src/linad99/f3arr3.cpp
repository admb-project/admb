/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

 d3_array value(_CONST dvar3_array& ar)
 { 
   d3_array tmp;
   tmp.allocate(ar);
   for (int i=tmp.slicemin(); i<=tmp.slicemax(); i++)
   {
     tmp[i]=value(ar(i));
   }
   return tmp;
 }

 void d3_array::allocate(_CONST dvar3_array& d3v)
 {
   int sl=d3v.slicemin();
   int sh=d3v.slicemax();
   int nrl=d3v.rowmin();
   int nrh=d3v.rowmax();
   int ncl=d3v.colmin();
   int nch=d3v.colmax();
   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor\n";
   }
   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor\n";
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(d3v(i));
   }
 }


