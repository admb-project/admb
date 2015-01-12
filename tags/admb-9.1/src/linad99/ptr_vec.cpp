/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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

struct void_ptr
{
  void * t;
};

 ptr_vector::~ptr_vector()
 {
   #ifdef DIAG
     cout << "deleting an ivector with address " << _farptr_tolong(v)
          <<" and ncopies = " << *ncopies <<"\n";
   #endif
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
     v += indexmin();
     delete [] v;
     v=NULL;
     #ifdef DIAG
       cout << "Really deleting an ivector with address "
            << _farptr_tolong(v) <<"\n";
     #endif

     delete  shape;
     shape = NULL;
   }
 }

 ptr_vector::ptr_vector(BOR_CONST ptr_vector& t)
 {
   #ifdef DIAG
    cout << "Copy constructor called for ivector with address "
         << _farptr_tolong(t.v) <<"\n";
   #endif
   shape=t.shape;
   (shape->ncopies)++;
   v = t.v;
 }

 ptr_vector& ptr_vector::operator = (BOR_CONST ptr_vector& _t)
 {
   ADUNCONST(ptr_vector,t)
   // disconnect ivector  pointer  from old array
   if (v != t.v)
   {
     if (indexmin() != t.indexmin() || indexmax() != t.indexmax())
     {
       cerr << " Array sizes do not match in ptr_vector operator =(_CONST ivector&)\n";
     }

     for ( int i=indexmin(); i<=indexmax(); i++)
     {
       elem(i) = t.elem(i);
     }
   }
   return (*this);
 }

 ptr_vector::ptr_vector(int ncl,int nch)
 {
   allocate(ncl,nch);
 }

 ptr_vector::ptr_vector()
 {
   shape=NULL;
   v=NULL;
 }

 void ptr_vector::allocate(int ncl,int nch)
 {
   if ( (shape=new vector_shape(ncl,nch))==0 )
   {
     cerr << " Error trying to allocate memory for ivector\n";
   }
   v = (void**) new void_ptr [(size_t) (nch-ncl+1)];
   #ifdef DIAG
     cout << "Created a ivector with address " << _farptr_tolong(v) <<"\n";
   #endif
   if (v ==0)
   {
     cerr << " Error trying to allocate memory for ivector\n";
     ad_exit(21);
   }

   v -= indexmin();
   #ifdef SAFE_ARRAYS
     this->initialize();
   #endif
 }

 void ptr_vector::initialize(void)
 {
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     v[i]=NULL;
   }
 }

 void*& ptr_vector::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i>indexmax())
     {
       cerr << "array bound exceeded -- index too high in ivector::operator[]";
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "array bound exceeded -- index too low in ivector::operator[]";
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }

 void*& ptr_vector::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i>indexmax())
     {
       cerr << "array bound exceeded -- index too high in ivector::operator[]";
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "array bound exceeded -- index too low in ivector::operator[]";
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }

 ostream& operator << (BOR_CONST ostream& _s,BOR_CONST ptr_vector& _v)
 {
   ADUNCONST(ptr_vector,v)
   ostream & s = (ostream&) _s;
   for (int i=v.indexmin();i<=v.indexmax();i++)
   {
     s << v.elem(i) << " ";
   }
   s << endl;
   return s;
 } 



