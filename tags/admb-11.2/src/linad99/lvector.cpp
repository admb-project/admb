/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdlib.h>
#include "fvar.hpp"
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
Default constructor
*/
lvector::lvector(void)
{
  allocate();
}
/**
Copy constructor
*/
lvector::lvector(const lvector& t)
{
  shape=t.shape;
  (shape->ncopies)++;
  v = t.v;
}
/**
Destructor
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
      if (v)
      {
        v += indexmin();
        delete [] v;
        v = NULL;
      }
      delete shape;
      shape = NULL;
    }
  }
}
/**
 * Description not yet available.
 * \param
 */
lvector::lvector(const dvector& u)
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
   for (int i=indexmin(); i<=indexmax(); i++)
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
lvector& lvector::operator=(const lvector& t)
 {
   if (v != t.v)
   {
     if (indexmin() != t.indexmin() || indexmax() != t.indexmax())
     {
       cerr <<
         " Array sizes do not match in lvector operator =(const lvector&)\n";
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
#ifndef OPT_LIB
  assert(sz > 0 && sz - 1 <= INT_MAX);
#endif
  if ((shape=new vector_shape(0, (int)(sz - 1))) == 0)
  {
    cerr << " Error trying to allocate memory for lvector\n";
  }
  if ( (v = new AD_LONG_INT [sz]) == NULL)
  {
    cerr << "Error trying to allocate memory for lvector\n";
    ad_exit(1);
  }

  for (unsigned int i = 0; i < sz; i++)
  {
    //cout << "Doing the assignment in constructor\n";
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
Allocate vector of AD_LONG_INT.

\param ncl lower index
\param nch high index
*/
void lvector::allocate(int ncl, int nch)
{
  if ((shape = new vector_shape(ncl,nch)) == 0)
  {
     cerr << " Error trying to allocate memory for lvector\n";
  }
  v = new AD_LONG_INT[(size_t)(nch-ncl+1)];
  if (v == 0)
  {
    cerr << " Error trying to allocate memory for lvector\n";
    ad_exit(21);
  }
  v -= indexmin();
#ifndef OPT_LIB
  initialize();
#endif
}
/**
Does not really allocate, but empties the array.
*/
void lvector::allocate(void)
{
  shape = NULL;
  v = NULL;
}
/**
Constructor to allocate vector of AD_LONG_INT.

\param ncl lower index
\param nch high index
*/
lvector::lvector(int ncl, int nch)
{
  allocate(ncl, nch);
}
/**
 * Description not yet available.
 * \param
 */
lvector::lvector(const ivector& u)
 {
   if ((shape=new vector_shape(u.indexmin(),u.indexmax()))==0 )
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
Intialize vector values to zero.
*/
void lvector::initialize(void)
{
  //for (int i = indexmin(); i <= indexmax(); i++) { elem(i) = 0; }
#ifndef OPT_LIB
  assert(size() > 0);
#endif
  memset((void*)(v + indexmin()), 0,
    sizeof(AD_LONG_INT) * (unsigned int)size());
}
