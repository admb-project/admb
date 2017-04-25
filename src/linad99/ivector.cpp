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
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdlib.h>

#ifdef DIAG
long int _farptr_tolong(void* px);
long int farptr_tolong(void*);
#endif

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
Default constructor
*/
ivector::ivector()
{
  allocate();
}
/**
Copy constructor
*/
ivector::ivector(const ivector& t)
{
#ifdef DIAG
    cout << "Copy constructor called for ivector with address "
         << _farptr_tolong(t.v) <<"\n";
#endif

  index_min = t.index_min;
  index_max = t.index_max;

  shape=t.shape;
  if (shape)
  {
    (shape->ncopies)++;
    v = t.v;
  }
  else
  {
    v = NULL;
  }
}
/**
Default destructor. Invoked by the compiler. Only frees allocated memory
if all shallow copies in scope have been removed.
Produces an error if the double* member v is NULL.
*/
ivector::~ivector()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
#ifdef SAFE_ALL
  #ifdef DIAG
      myheapcheck(" Entering ~dvector");
  #endif
      if (v == NULL)
      {
        cerr << " Trying to delete NULL pointer in ~ivector\n";
        ad_exit(21);
      }
#endif
      deallocate();
    }
  }
}
/**
 * Description not yet available.
 * \param
 */
 void ivector::safe_allocate(int ncl,int nch)
 {
   if (allocated())
   {
     cerr << "trying to allocate an already allocated dvector " << endl;
     ad_exit(1);
   }
   else
   {
     allocate(ncl,nch);
   }
 }
/**
Called by destructor to deallocate memory for a ivector object.
Produces an error if the int* member is NULL.
*/
void ivector::deallocate()
{
  if (shape)
  {
    v = (int*)(shape->trueptr);

    if (v)
    {
      delete [] v;
      v = NULL;
    }

    delete shape;
    shape = NULL;
  }
}
/**
Safely deallocates memory by reporting if shallow copies are still in scope.
*/
void ivector::safe_deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      cerr << "trying to deallocate a ivector with copies" << endl;
      ad_exit(1);
    }
    deallocate();
  }
}

/**
 * Description not yet available.
 * \param
 */


/**
 * Description not yet available.
 * \param
 */
void ivector::shallow_copy(const ivector& t)
 {
   index_min=t.index_min;
   index_max=t.index_max;
   #ifdef DIAG
    cout << "Copy constructor called for ivector with address "
         << _farptr_tolong(t.v) <<"\n";
   #endif
   shape=t.shape;
   if (shape)
   {
     (shape->ncopies)++;
     v = t.v;
   }
 }

/**
 * Description not yet available.
 * \param
 */
ivector& ivector::operator=(const ivector& t)
 {
   // disconnect ivector  pointer  from old array
   if (::allocated(*this))
   {
     if (v != t.v)
     {
       if (indexmin() != t.indexmin() || indexmax() != t.indexmax())
       {
         cerr << " Array sizes do not match in ivector operator"
                 " =(const ivector&)" << endl;
         ad_exit(1);
       }

       for ( int i=indexmin(); i<=indexmax(); i++)
       {
         elem(i) = t.elem(i);
       }
     }
   }
   else
   {
     shallow_copy(t);
   }
   return (*this);
 }

/**
 * Description not yet available.
 * \param
 */
ivector& ivector::operator=(int u)
{
  for (int i = indexmin(); i <= indexmax(); i++)
  {
    elem(i) = u;
  }
  return (*this);
}

/**
Constructor
*/
ivector::ivector(unsigned int sz, long int* x)
{
#ifndef OPT_LIB
  assert(sz > 0 && sz <= INT_MAX);
  assert(x);
#endif
  allocate(0, (int)(sz - 1));

  if (v)
  {
    for (unsigned int i = 0; i < sz; i++)
    {
#ifdef OPT_LIB
      v[i] = (int)x[i];
#else
      long int xi = x[i];
      assert(xi <= INT_MAX);
      v[i] = static_cast<int>(xi);
#endif
    }
  }
}
/**
Construct ivector with same dimensions as u.
*/
ivector::ivector(const dvector& u)
{
  allocate(u);
  for (int i=indexmin();i<=indexmax();i++)
  {
#ifdef OPT_LIB
    elem(i) = int(u.elem(i));
#else
    double ui = u.elem(i);
    assert(ui <= INT_MAX);
    v[i] = (int)ui;
#endif
  }
}
/**
Allocate vector of integers with dimension
[ncl to nch].

\param ncl lower vector index
\param nch upper vector index
*/
ivector::ivector(int ncl, int nch)
{
  allocate(ncl, nch);
}
/**
Allocate vector of integers with dimension
[ncl to nch].

\param ncl lower vector index
\param nch upper vector index
*/
void ivector::allocate(int ncl,int nch)
{
  unsigned int ss =
    static_cast<unsigned int>(nch < ncl ? 0 : nch - ncl + 1);
  if (ss > 0)
  {
    if ((v = new int [ss]) == 0 )
    {
      cerr << " Error: i4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }
    if ((shape = new vector_shapex(ncl, nch, v)) == NULL)
    {
      cerr << " Error: i4_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
      ad_exit(1);
    }

    index_min=ncl;
    index_max=nch;

    v -= indexmin();

#ifdef SAFE_INITIALIZE
    for (int i = ncl; i <= nch; ++i)
    {
      v[i] = 0;
    }
#endif
  }
  else
  {
    allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
void ivector::allocate(const dvector& dv)
{
  allocate(dv.indexmin(),dv.indexmax());
}

/**
 * Description not yet available.
 * \param
 */
void ivector::allocate(const ivector& dv)
{
  allocate(dv.indexmin(),dv.indexmax());
}
/**
Does not allocate, but initializes class members.
*/
void ivector::allocate()
{
  shape = NULL;
  index_min = 1;
  index_max = -1;
  v = NULL;
}

/**
 * Description not yet available.
 * \param
 */
ivector::ivector(const preivector& pdv)
{
#if defined(SAFE_ALL)
  cout << "starting out in ivector constructor\n";
#endif

  shape=pdv.p->shape;
  if (shape)
  {
    (shape->ncopies)++;
  }
#if defined(SAFE_ALL)
  else
  {
    cerr << "Taking a subvector of an unallocated ivector" << endl;
  }
#endif
  v = pdv.p->v;
  index_min = pdv.lb;
  index_max = pdv.ub;
}

/**
 * Description not yet available.
 * \param
 */
  int norm2(const ivector& t1)
  {
    int tmp=0;;
   for (int i=t1.indexmin();i<=t1.indexmax();i++)
   {
     tmp+=t1(i)*t1(i);
   }
    return(tmp);
  }
  int sumsq(const ivector& t1) {return(norm2(t1));}

/**
 * Description not yet available.
 * \param
 */
  void clean(ivector& v,int level)
  {
    int mmax=v.indexmax();
    for (int i=level+1;i<=mmax;i++)
    {
      v(i)=0;
    }
  }
