/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <stdlib.h>

#ifndef OPT_LIB
  #include <cassert>
#endif

/**
Default constructor
*/
adstring_array::adstring_array()
{
  shape=NULL;
  ptr=NULL;
}
/**
Copy constructor
*/
adstring_array::adstring_array(const adstring_array& sa): clist(sa)
{
  shape=sa.shape;
  ptr=sa.ptr;
}
adstring_array::adstring_array(int min,int max)
{
  allocate(min,max);
}
/**
Destructor
*/
adstring_array::~adstring_array()
{
  if (ptr)
  {
    if (next==this)
    {
      int min=indexmin();
      int max=indexmax();
      for(int i=min;i<=max;i++)
      {
        if (ptr[i])
        {
          delete ptr[i];
          ptr[i] = 0;
        }
      }
      ptr+=indexmin();

      delete [] ptr;
      ptr = 0;

      delete shape;
      shape = 0;
    }
  }
}

int adstring_array::size() const
  { return shape ? shape->indexmax() - shape->indexmin() + 1 : 0; }

int adstring_array::indexmin() const
  { return shape ? shape->indexmin() : 0;}

int adstring_array::indexmax() const
  { return shape ? shape->indexmax() : 0;}

/**
Allocate vector of adstring with range [min, max].

\param min lower index
\param max upper index
*/
void adstring_array::allocate(int min, int max)
{
  if (min > max)
  {
    cerr << " Error in adstring_array(int min,int max) --"
            " max must be >= min" << endl;
    exit(1);
  }
  shape = new vector_shape(min, max);
  if (!shape)
  {
    cerr << "Error allocating memory in adstring_array" << endl;
  }
  int size = max - min + 1;
  ptr =
    new adstring*[static_cast<unsigned int>(size < 0 ? 0 : size)];
  if (!ptr)
  {
    cerr << "Error allocating memory in adstring_array" << endl;
  }
  ptr-=indexmin();
  for (int i=min;i<=max;i++)
  {
    ptr[i]=new adstring;
  }
}
/**
Returns a reference to the element at specified index i. Bounds checking is performed.

\param i index
*/
adstring& adstring_array::operator[](int i)
{
  if (!shape)
  {
    cerr << "Error -- trying to acess unallocated adstring array" << endl;
    ad_exit(1);
  }

#ifndef OPT_LIB
  assert(indexmin() <= i && i <= indexmax());
#endif

  return *(ptr[i]);
}
/**
Returns a reference to the element at specified index i. Bounds checking is performed.

\param i index
*/
adstring& adstring_array::operator()(int i)
{
  if (!shape)
  {
    cerr << "Error -- trying to acess unallocated adstring array" << endl;
    ad_exit(1);
  }

#ifndef OPT_LIB
  assert(indexmin() <= i && i <= indexmax());
#endif

  return *(ptr[i]);
}
/**
Returns a reference to the element at specified index i. Bounds checking is performed.

\param i index
*/
const adstring& adstring_array::operator[](int i) const
{
  if (!shape)
  {
    cerr << "Error -- trying to acess unallocated adstring array" << endl;
    exit(1);
  }

#ifndef OPT_LIB
  assert(indexmin() <= i && i <= indexmax());
#endif

  return *(ptr[i]);
}
/**
Returns a reference to the element at specified index i. Bounds checking is performed.

\param i index
*/
const adstring& adstring_array::operator()(int i) const
{
  if (!shape)
  {
    cerr << "Error -- trying to acess unallocated adstring array" << endl;
    ad_exit(1);
  }

#ifndef OPT_LIB
  assert(indexmin() <= i && i <= indexmax());
#endif

  return *(ptr[i]);
}
