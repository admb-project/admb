/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif


 lmatrix::lmatrix(int nrl, int nrh, int ncl, int nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

 void lmatrix::allocate(int nrl,int nrh,int ncl,int nch)
 {
   if ( (shape = new mat_shape(nrl,nrh,ncl,nch))== 0)
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

   m -= rowmin();
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl,nch);
   }
 }

 void lmatrix::allocate(int nrl,int nrh,const ivector& ncl,const ivector& nch)
 {
   if ( (shape = new mat_shape(nrl,nrh,ncl(ncl.indexmin()),
					       nch(nch.indexmin()) ))== 0)
   {
     cerr << " Error allocating memory in lmatrix contructor\n";
     ad_exit(21);
   }
   if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
     nrl !=nch.indexmin() || nrh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)\n";
     ad_exit(1);
   }
   int rs=rowsize();
   if ( (m = new lvector [rs]) == 0)
   {
     cerr << " Error allocating memory in lmatrix contructor\n";
     ad_exit(21);
   }
   m -= rowmin();
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl(i),nch(i));
   }
 }

 void lmatrix::allocate(int nrl, int nrh, int ncl, const ivector& nch)
 {
   if (nrl !=nch.indexmin() || nrh !=nch.indexmax())
   {
     cerr << "Incompatible array bounds in lmatrix::allocate(int nrl,int nrh,int ncl,_CONST ivector& nch)\n";
     ad_exit(1);
   }
   if ( (shape = new mat_shape(nrl,nrh,ncl,nch(nch.indexmin())))== 0)
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
   m -= rowmin();
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(ncl,nch(i));
   }
 }


 lmatrix::lmatrix(_CONST lmatrix& m2)
 {
   if (m2.shape)
   {
     shape=m2.shape;
     (shape->ncopies)++;
     m = m2.m;
   }
   else
   {
     shape=NULL;
     m=NULL;
   }
 }

 lmatrix::lmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

 lmatrix::lmatrix(int nrl,int nrh,int ncl,_CONST ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

 lmatrix::lmatrix(void)
 {
   shape = NULL;
   m=NULL;
 }

 lmatrix::~lmatrix()
 {
   deallocate();
 }

 void lmatrix::deallocate()
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       int offset = rowmin();   
       m += rowmin();
       delete [] m;
       m=NULL;
       delete shape;
       shape=NULL;
     }
   }
   else
   {
     //cerr << "Warning -- trying to deallocate an unallocated lmatrix"<<endl;
   }
 }

