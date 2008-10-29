#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"


 struct dvec_ptr_ptr
 {
   void ** m;
 };

 dmatrix::dmatrix(BOR_CONST dvar_matrix_position& pos)
 {
   int nrl=pos.row_min;
   int nrh=pos.row_max;
   const ivector& ncl=pos.lb;
   const ivector& nch=pos.ub;
   #ifdef DIAG
     myheapcheck("Entering dmatrix(nrl,nrh,ncl,nch)" );
   #endif
   if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
     nrl !=nch.indexmin() || nrh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)\n";
     ad_exit(1);
   }
   index_min=nrl;
   index_max=nrh;

   int rs=rowsize();
   if ( (m = new dvector [rs]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }


   #ifdef DIAG
     cerr << "Created a dmatrix with adress "<< farptr_tolong(m)<<"\n";
   #endif

   m -= rowmin();

   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl[i],nch[i]);
     #ifdef DIAG
       cerr << "Created a dvector with address "<< farptr_tolong(*(m+i))<<"\n";
     #endif
   }
   #ifdef DIAG
     myheapcheck("Leaving dmatrix(nrl,nrh,ncl,nch)" );
   #endif
 }

 dmatrix::dmatrix(BOR_CONST dmatrix_position& pos)
 {
   int nrl=pos.row_min;
   int nrh=pos.row_max;
   const ivector& ncl=pos.lb;
   const ivector& nch=pos.ub;
   #ifdef DIAG
     myheapcheck("Entering dmatrix(nrl,nrh,ncl,nch)" );
   #endif
   if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
     nrl !=nch.indexmin() || nrh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)\n";
     ad_exit(1);
   }
   index_min=nrl;
   index_max=nrh;

   int rs=rowsize();
   if ( (m = new dvector [rs]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }

   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }

   #ifdef DIAG
     cerr << "Created a dmatrix with adress "<< farptr_tolong(m)<<"\n";
   #endif

   m -= rowmin();

   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl[i],nch[i]);
   }
   #ifdef DIAG
     myheapcheck("Leaving dmatrix(nrl,nrh,ncl,nch)" );
   #endif
 }

#undef HOME_VERSION
