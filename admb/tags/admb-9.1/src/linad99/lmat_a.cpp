/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

 lmatrix::lmatrix(BOR_CONST lmatrix_position& pos)
 {
   int nrl=pos.row_min;
   int nrh=pos.row_max;
   ivector& ncl=(ivector&) pos.lb;
   ivector& nch=(ivector&) pos.ub;
   if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
     nrl !=nch.indexmin() || nrh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in lmatrix(int nrl,int nrh,BOR_CONST ivector& ncl,BOR_CONST ivector& nch)\n";
     ad_exit(1);
   }

   if ( (shape = new mat_shape(nrl,nrh,ncl[nrl],nch[nrl]))== 0)
   {
     cerr << " Error allocating memory in lmatrix contructor\n";
     ad_exit(21);
   }

   int rs=rowsize();
   if ( (m = new lvector [rs]) == 0)
   {
     cerr << " Error allocating memory in lmatrix contructor\n";
     ad_exit(21);
   }

   #ifdef DIAG
     cerr << "Created a lmatrix with adress "<< farptr_tolong(m)<<"\n";
   #endif

   m -= rowmin();

   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl[i],nch[i]);
   }
 }


