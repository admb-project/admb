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
ivector::ivector(void)
{
  allocate();
}
/**
Copy constructor
*/
ivector::ivector(const ivector& t)
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
Destructor
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
      if (v != NULL)
      {
        deallocate();
      }
#ifdef SAFE_ALL
      else
      {
         cerr << " Trying to delete NULL pointer in ~ivector\n";
         ad_exit(21);
      }
#endif
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
 * Description not yet available.
 * \param
 */
  void ivector::safe_deallocate()
  {
    if (shape)
    {
      if (shape->ncopies)
      {
        cerr << "trying to deallocate a dvector with copies" << endl;
        ad_exit(1);
      }
    }
    else
    {
      deallocate();
    }
  }

/**
 * Description not yet available.
 * \param
 */
 void ivector::deallocate()
 {
   if (shape)
   {
     v = (int*) (shape->trueptr);
     delete [] v;
     v=NULL;
     delete  shape;
   }
   else
   {
     //cerr << "Warning -- trying to deallocate an unitialized ivector" << endl;
   }
   shape=NULL;
 }


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
 ivector& ivector::operator = (int u)
 {
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     elem(i) = u;
   }
   return (*this);
 }

/**
Constructor
*/
ivector::ivector(unsigned int sz, long int* x )
{
  allocate(0,sz-1);

  for (unsigned int i=0; i<sz; i++)
  {
    cout << "Doing the assignment in constructor\n";
#ifdef OPT_LIB
    v[i] = x[i];
#else
    long int xi = x[i];
    assert(xi <= INT_MAX);
    v[i] = (int)xi;
#endif
  }
}

/**
Constructor
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
 * Description not yet available.
 * \param
 */
 ivector::ivector(int ncl,int nch)
 {
   allocate(ncl, nch);
 }

/**
 * Description not yet available.
 * \param
 */
 void ivector::allocate(int ncl,int nch)
 {
   int itemp=nch-ncl;
   if (itemp<0)
   {
     //cerr << "Error in ivector constructor max index must be >= minindex\n"
     //  << "minindex = " << ncl << " maxindex = " << nch <<endl;
     //ad_exit(1);
     allocate();
   }
   else
   {
     if ( (v = new int [itemp+1]) == 0 )
     {
       cerr << " Error trying to allocate memory for ivector\n";
       ad_exit(21);
     }

     if ( (shape=new vector_shapex(ncl,nch,v)) == NULL)
     {
       cerr << "Error trying to allocate memory for ivector\n";
       ad_exit(1);
     }

     index_min=ncl;
     index_max=nch;
     v -= indexmin();
     #ifdef SAFE_INITIALIZE
       for ( int i=indexmin(); i<=indexmax(); i++)
       {
         v[i]=0.;
       }
     #endif
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
 * Description not yet available.
 * \param
 */
void ivector::allocate(void)
{
  shape=NULL;
  index_min=1;
  index_max=-1;
  v = NULL;
}

/**
 * Description not yet available.
 * \param
 */
ivector::ivector(const preivector& pdv)
 {
   #ifdef DIAG
    // cout << "starting out in dvector contructor\n";
   #endif
   shape=pdv.p->shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
   else
   {
     cerr << "Taking a subvector  of an unallocated ivector"<<endl;
   }
   v = pdv.p->v;
   index_min=pdv.lb;
   index_max=pdv.ub;
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
