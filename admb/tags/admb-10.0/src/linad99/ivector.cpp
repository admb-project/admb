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
long int _farptr_tolong(void * px);
long int farptr_tolong(void *);

/**
 * Description not yet available.
 * \param
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
       if ( v == NULL)
       {
         cerr << " Trying to delete NULL pointer in ~ivector\n";
         ad_exit(21);
       }
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
     //cerr << "Warning -- trying to deallocate an unitialized ivector"
//	   << endl;
   }
   shape=NULL;
 }

/**
 * Description not yet available.
 * \param
 */
 ivector::ivector(_CONST ivector& t)
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
 void ivector::shallow_copy(_CONST ivector& t)
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
 ivector& ivector::operator = (_CONST ivector& t)
 {
   // disconnect ivector  pointer  from old array
   if (::allocated(*this))
   {
     if (v != t.v)
     {
       if (indexmin() != t.indexmin() || indexmax() != t.indexmax())
       {
         cerr << " Array sizes do not match in ivector operator"
                 " =(_CONST ivector&)" << endl;
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
 * Description not yet available.
 * \param
 */
 ivector::ivector( unsigned int sz, long int * x )
 {
   allocate(0,sz-1);

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
 ivector::ivector(_CONST dvector& u)
 {
   allocate(u);
   for (int i=indexmin();i<=indexmax();i++)
   {
     elem(i)=int(u.elem(i));
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
 ivector::ivector(void)
 {
   allocate();
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
void ivector::allocate(_CONST dvector& dv)
{
  allocate(dv.indexmin(),dv.indexmax());
}

/**
 * Description not yet available.
 * \param
 */
void ivector::allocate(_CONST ivector& dv)
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
 ivector::ivector(_CONST preivector& pdv)
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
  int  norm2(const ivector& t1)
  {
    int tmp=0;;
   for (int i=t1.indexmin();i<=t1.indexmax();i++)
   {
     tmp+=t1(i)*t1(i);
   }
    return(tmp);
  }

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
