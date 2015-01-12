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
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdlib.h>

void denormalize_ptr(void * ptr, unsigned int byte_offset);

/**
 * Description not yet available.
 * \param
 */
 lvector::~lvector()
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       if ( v == NULL)
       {
         cerr << " Trying to delete NULL pointer in ~lvector\n";
         ad_exit(21);
       }
       v += indexmin();
       delete []v;
       v=NULL;
     
       delete  shape;
       shape = NULL;
     }
   }
   else
   {
     cerr << "Trying to delete an unallocated lvector" << endl;
   }
 }

/**
 * Description not yet available.
 * \param
 */
 lvector::lvector(_CONST lvector& t)
 {
   shape=t.shape;
   (shape->ncopies)++;
   v = t.v;
 }

/**
 * Description not yet available.
 * \param
 */
 lvector::lvector(void)
 {
   allocate();
 }

/**
 * Description not yet available.
 * \param
 */
 lvector::lvector(_CONST dvector& u)
 {
   if ( (shape=new vector_shape(u.indexmin(),u.indexmax()))==0 )
   {
     cerr << " Error trying to allocate memory for ivector\n";
   }
   v = new AD_LONG_INT [(size_t) u.size() ];
   if (v ==0)
   {
     cerr << " Error trying to allocate memory for ivector\n";
     ad_exit(21);
   }

   v -= indexmin();
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
   #if !defined(USE_DDOUBLE)
     v[i]= (AD_LONG_INT) u.elem(i);
   #else
     v[i]= int(u.elem(i));
   #endif
   }
 }

/**
 * Description not yet available.
 * \param
 */
 lvector& lvector::operator = (_CONST lvector& t)
 {
   if (v != t.v)
   {
     if (indexmin() != t.indexmin() || indexmax() != t.indexmax())
     {
       cerr << " Array sizes do not match in lvector operator =(_CONST lvector&)\n";
     }

     for ( int i=indexmin(); i<=indexmax(); i++)
     {
       elem(i) = t.elem(i);
     }
   }
   return (*this);
 }

/**
 * Description not yet available.
 * \param
 */
 lvector::lvector( unsigned int sz, AD_LONG_INT * x )
 {
   if ( (shape=new vector_shape(0,sz-1))==0 )
   {
     cerr << " Error trying to allocate memory for lvector\n";
   }
   if ( (v = new AD_LONG_INT [sz]) == NULL)
   {
     cerr << "Error trying to allocate memory for lvector\n";
     ad_exit(1);
   }

   for (unsigned int i=0; i<sz; i++)
   {
     cout << "Doing the assignment in constructor\n";
     v[i] = x[i];
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void lvector::allocate(const lvector& lv)
 {
   allocate(lv.indexmin(),lv.indexmax());
 }

/**
 * Description not yet available.
 * \param
 */
 void lvector::allocate(int ncl,int nch)
 {
   if ( (shape=new vector_shape(ncl,nch))==0 )
   {
     cerr << " Error trying to allocate memory for lvector\n";
   }
   v = new AD_LONG_INT [(size_t) (nch-ncl+1)];
   if (v ==0)
   {
     cerr << " Error trying to allocate memory for lvector\n";
     ad_exit(21);
   }

   v -= indexmin();
   #ifdef SAFE_ARRAYS
     for ( int i=indexmin(); i<=indexmax(); i++)
     {
       v[i]=0.;
     }
   #endif
 }

/**
 * Description not yet available.
 * \param
 */
 void lvector::allocate(void)
 {
   shape=NULL;
   v = NULL;
 }

/**
 * Description not yet available.
 * \param
 */
 lvector::lvector(int ncl,int nch)
 {
   allocate(ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 lvector::lvector(_CONST ivector& u)
 {
   if ( (shape=new vector_shape(u.indexmin(),u.indexmax()))==0 )
   {
     cerr << " Error trying to allocate memory for lvector\n";
   }
   v = new AD_LONG_INT [(size_t) (size()) ];
   if (v ==0)
   {
     cerr << " Error trying to allocate memory for lvector\n";
     ad_exit(21);
   }

   v -= indexmin();
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     elem(i)=u.elem(i);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void lvector::initialize(void)
 {
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     elem(i)=0;
   }
 }
