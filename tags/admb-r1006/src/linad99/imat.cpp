/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

/**
 * Description not yet available.
 * \param
 */
void imatrix::rowshift(int min )
{
  m = m + rowmin() - min;
  index_max+=min-index_min;
  index_min=min;
}

/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(int nrl,int nrh)
 {
   allocate(nrl,nrh);
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix imatrix::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     imatrix tmp(nrl,nrh);
     for (int i=nrl; i<=nrh; i++)
     {
       tmp[i].shallow_copy((*this)(i));
     }
     return tmp;
   }
   else
   {
     return *this;
   }
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(int nrl, int nrh, int ncl, int nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(const ad_integer& nrl,const ad_integer& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(int nrl,int nrh,BOR_CONST ivector& iv)
 {
   allocate(nrl,nrh,iv);
 }

/**
 * Description not yet available.
 * \param
 */
 void imatrix::allocate(int nrl,int nrh,BOR_CONST ivector& iv)
 {
   if (nrl>nrh)
   {
     allocate();
   }
   else
   { 
     index_min=nrl;
     index_max=nrh;
     
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
  
     m -= rowmin();
     for (int i=rowmin(); i<=rowmax(); i++)
     {
       m[i].index_min=iv.index_min;
       m[i].index_max=iv.index_max;
       m[i].shape=iv.shape;
       if (m[i].shape)
       {
         (m[i].shape->ncopies)++;
         m[i].v = iv.v;
       }
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void imatrix::allocate(int nrl,int nrh,int ncl,int nch)
 {
   if (nrl>nrh)
   {
     allocate();
   }
   else
   { 
     index_min=nrl;
     index_max=nrh;
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
  
     m -= rowmin();
     for (int i=rowmin(); i<=rowmax(); i++)
     {
       m[i].allocate(ncl,nch);
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void imatrix::allocate(void)  //default constructor
 {
   index_min=0;
   index_max=-1;
   m=NULL;
   shape=NULL;
 }

/**
 * Description not yet available.
 * \param
 */
 void imatrix::allocate(int nrl,int nrh,const ivector& ncl,const ivector& nch)
 {
   if (nrl>nrh)
   {
     allocate();
   }
   else
   { 
     index_min=nrl;
     index_max=nrh;
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
     if (nrl !=ncl.indexmin() || nrh !=ncl.indexmax() ||
       nrl !=nch.indexmin() || nrh !=nch.indexmax())
     {
       cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)\n";
       ad_exit(1);
     }
     m -= rowmin();
     for (int i=rowmin(); i<=rowmax(); i++)
     {
       m[i].allocate(ncl(i),nch(i));
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void imatrix::allocate(int nrl, int nrh, int ncl, const ivector& nch)
 {
   if (nrl>nrh)
   {
     allocate();
   }
   else
   { 
     index_min=nrl;
     index_max=nrh;
     int rs=rowsize();
     if ( (m = new ivector [rs]) == 0)
     {
       cerr << " Error allocating memory in imatrix contructor\n";
       ad_exit(21);
     }
     if (nrl !=nch.indexmin() || nrh !=nch.indexmax())
     {
       cerr << "Incompatible array bounds in imatrix::allocate(int nrl,int nrh,int ncl,_CONST ivector& nch)\n";
       ad_exit(1);
     }
     if ( (shape = new mat_shapex(m))== 0)
     {
       cerr << " Error allocating memory in imatrix contructor\n";
       ad_exit(21);
     }
     m -= rowmin();
     for (int i=rowmin(); i<=rowmax(); i++)
     {
       m[i].allocate(ncl,nch(i));
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(_CONST imatrix& m2)
 {
   index_min=m2.index_min;
   index_max=m2.index_max;
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

/**
 * Description not yet available.
 * \param
 */
 void imatrix::shallow_copy(_CONST imatrix& m2)
 {
   index_min=m2.index_min;
   index_max=m2.index_max;
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

/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(int nrl,int nrh,int ncl,_CONST ivector& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix::imatrix(void)
 {
   allocate();
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix::~imatrix()
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
 void imatrix::deallocate()
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       m= (ivector*) (shape->get_pointer());
       delete [] m;
       m=NULL;
       delete shape;
       shape=NULL;
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void imatrix::allocate(int nrl,int nrh)
 {
   if (nrl>nrh)
     allocate();
   else
   {
     index_min=nrl;
     index_max=nrh;
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
     m -= indexmin();
   }
 }
