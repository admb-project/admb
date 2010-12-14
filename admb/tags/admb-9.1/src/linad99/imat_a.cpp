/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

 imatrix::imatrix(BOR_CONST imatrix_position& pos)
 {
   int nrl=pos.row_min;
   int nrh=pos.row_max;
   index_min=nrl;
   index_max=nrh;
   const ivector& ncl=pos.lb;
   const ivector& nch=pos.ub;
   if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
     nrl !=nch.indexmin() || nrh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in imatrix(int nrl,int nrh,BOR_CONST ivector& ncl,BOR_CONST ivector& nch)\n";
     ad_exit(1);
   }

   int rs=rowsize();

   if ( (m = new ivector [rs]) == 0)
   {
     cerr << " Error allocating memory in imatrix contructor\n";
     ad_exit(21);
   }

   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in imatrix contructor\n";
     ad_exit(21);
   }

   #ifdef DIAG
     cerr << "Created a imatrix with adress "<< farptr_tolong(m)<<"\n";
   #endif

   m -= rowmin();

   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl[i],nch[i]);
   }
 }


