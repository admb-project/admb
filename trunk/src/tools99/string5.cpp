/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <stdlib.h>
#include "admb_messages.h"

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
  { return shape->indexmax()-shape->indexmin() + 1; }
int adstring_array::indexmin() const { return shape->indexmin();}
int adstring_array::indexmax() const { return shape->indexmax();}

void adstring_array::allocate(int min, int max)
  {
    if (min > max)
    {
      cerr << " Error in adstring_array(int min,int max) --"
              " max must be >= min" << endl;
      exit(1);
    }
    if (!(shape=new vector_shape(min,max)))
    {
      cerr << "Error allocating memory in adstring_array" << endl;
    }
    if (!(ptr=new adstring* [max-min+1]))
    {
      cerr << "Error allocating memory in adstring_array" << endl;
    }
    ptr-=indexmin();
    for (int i=min;i<=max;i++)
    {
      ptr[i]=new adstring;
    }
  }

adstring& adstring_array::operator[](int i)
  {
    if (!shape)
    {
      cerr << "Error -- trying to acess unallocated adstring array"
        << endl;
      exit(1);
    }

    if (i<indexmin())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Error index too low", "adstring& adstring_array::operator [] (int i)", indexmin(), indexmax(), i);
    }
    if (i>indexmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Error index too high", "adstring& adstring_array::operator [] (int i)", indexmin(), indexmax(), i);
    }
    return *(ptr[i]);
  }

adstring& adstring_array::operator()(int i)
  {
    if (!shape)
    {
      cerr << "Error -- trying to acess unallocated adstring array"
        << endl;
      exit(1);
    }
    if (i<indexmin())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Error index too low", "adstring& adstring_array::operator () (int i)", indexmin(), indexmax(), i);
    }
    if (i>indexmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Error index too high", "adstring& adstring_array::operator () (int i)", indexmin(), indexmax(), i);
    }
    return *(ptr[i]);
  }

const adstring& adstring_array::operator[](int i) const
  {
    if (!shape)
    {
      cerr << "Error -- trying to acess unallocated adstring array"
        << endl;
      exit(1);
    }

    if (i<indexmin())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Error index too low", "adstring& adstring_array::operator [] (int i) const ", indexmin(), indexmax(), i);
    }
    if (i>indexmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Error index too high", "adstring& adstring_array::operator [] (int i) const ", indexmin(), indexmax(), i);
    }
    return *(ptr[i]);
  }

const adstring& adstring_array::operator()(int i) const
  {
    if (!shape)
    {
      cerr << "Error -- trying to acess unallocated adstring array"
        << endl;
      exit(1);
    }
    if (i<indexmin())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Error index too low", "adstring& adstring_array::operator () (int i) const", indexmin(), indexmax(), i);
    }
    if (i>indexmax())
    {
      ADMB_ARRAY_BOUNDS_ERROR("Error index too high", "adstring& adstring_array::operator () (int i) const", indexmin(), indexmax(), i);
    }
    return *(ptr[i]);
  }
