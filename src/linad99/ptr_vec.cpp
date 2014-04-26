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

long int _farptr_tolong(void * px);
long int farptr_tolong(void *);

/**
 * Description not yet available.
 * \param
 */
struct void_ptr
{
  void * t;
};

/**
Destructor
*/
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
    if (v == NULL)
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
/**
Copy constructor
*/
ptr_vector::ptr_vector(const ptr_vector& t)
{
#ifdef DIAG
    cout << "Copy constructor called for ivector with address "
         << _farptr_tolong(t.v) <<"\n";
#endif
  shape=t.shape;
  (shape->ncopies)++;
  v = t.v;
}
/**
Copy values from _t to this. _t and this indexes should be the same.

\param _t values to copy
 */
ptr_vector& ptr_vector::operator=(const ptr_vector& _t)
{
  ADUNCONST(ptr_vector,t)
  // disconnect ivector  pointer  from old array
  if (v != t.v)
  {
    if (indexmin() != t.indexmin() || indexmax() != t.indexmax())
    {
      cerr << " Array sizes do not match in "
      "ptr_vector operator =(const ivector&)\n";
    }
    for ( int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i) = t.elem(i);
    }
  }
  return *this;
}
/**
Allocate array [ncl,...,nch].

\param ncl lower index
\param nch higher index
*/
ptr_vector::ptr_vector(int ncl,int nch)
{
  allocate(ncl,nch);
}
/**
Default constructor
*/
ptr_vector::ptr_vector()
{
  shape=NULL;
  v=NULL;
}
/**
Allocate array [ncl,...,nch].

ncl should be less than nch.

\param ncl lower index
\param nch higher index
*/
void ptr_vector::allocate(int ncl,int nch)
{
  if ((shape = new vector_shape(ncl,nch)) == 0)
  {
    cerr << " Error trying to allocate memory for ivector\n";
  }
  v = (void**) new void_ptr [(size_t) (nch-ncl+1)];
#ifdef DIAG
  cout << "Created a ivector with address " << _farptr_tolong(v) <<"\n";
#endif
  if (v == 0)
  {
    cerr << " Error trying to allocate memory for ptr_vector\n";
    ad_exit(21);
  }
  v -= indexmin();
#ifndef OPT_LIB
  this->initialize();
#endif
}
/**
Initialize elements in pointer array to null.
*/
void ptr_vector::initialize(void)
{
  for (int i = indexmin(); i <= indexmax(); i++)
  {
    v[i] = NULL;
  }
}
/**
 * Description not yet available.
 * \param
 */
void*& ptr_vector::operator[] (int i)
{
  if (i > indexmax())
  {
    cerr << "array bound exceeded -- index too high in ivector::operator[]";
    ad_exit(1);
  }
  if (i < indexmin())
  {
    cerr << "array bound exceeded -- index too low in ivector::operator[]";
    ad_exit(1);
  }
  return (*(v+i));
}

/**
 * Description not yet available.
 * \param
 */
void*& ptr_vector::operator()(int i)
{
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
  return(*(v+i));
}
/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _s, const ptr_vector& _v)
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
