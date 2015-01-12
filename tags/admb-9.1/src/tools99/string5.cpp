/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>
#include <stdlib.h>

  adstring_array::adstring_array(_CONST adstring_array& sa) :
    clist(sa)
  {
    shape=sa.shape;
    ptr=sa.ptr;
  }

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
          }
        }
        ptr+=indexmin();
        delete [] ptr;
        delete shape;
        shape=NULL;
        ptr=NULL;
      }
    }
  }

  adstring_array::adstring_array(void)
  {
    shape=NULL;
    ptr=NULL;
  }

  adstring_array::adstring_array(int min,int max) 
  {
    allocate(min,max); 
  }

  void adstring_array::allocate(int min,int max) 
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

  adstring& adstring_array::operator [] (int i)
  {
    if (!shape)
    {
      cerr << "Error -- trying to acess unallocated adstring array"
        << endl;
      exit(1);
    }

    if (i<indexmin())
    {
      cerr << "Error index too low in adstring& operator [] (int i)" << endl;
      cerr << "value was " << i << " minimum valid index is "
        << indexmin() << endl;
      exit(1);
    }
    if (i>indexmax())
    {
      cerr << "Error index too high in adstring& operator [] (int i)" << endl;
      cerr << "value was " << i << " maximum valid index is "
        << indexmax() << endl;
      exit(1);
    }
    return *(ptr[i]);
  }

  adstring& adstring_array::operator () (int i)
  {
    if (!shape)
    {
      cerr << "Error -- trying to acess unallocated adstring array"
        << endl;
      exit(1);
    }
    if (i<indexmin())
    {
      cerr << "Error index too low in adstring& operator [] (int i)" << endl;
      cerr << "value was " << i << " minimum valid index is "
        << indexmin() << endl;
      exit(1);
    }
    if (i>indexmax())
    {
      cerr << "Error index too high in adstring& operator [] (int i)" << endl;
      cerr << "value was " << i << " maximum valid index is "
        << indexmax() << endl;
      exit(1);
    }
    return *(ptr[i]);
  }

#ifdef USE_CONST

  _CONST adstring& adstring_array::operator [] (int i) _CONST
  {
    if (!shape)
    {
      cerr << "Error -- trying to acess unallocated adstring array"
        << endl;
      exit(1);
    }

    if (i<indexmin())
    {
      cerr << "Error index too low in adstring& operator [] (int i)" << endl;
      cerr << "value was " << i << " minimum valid index is "
        << indexmin() << endl;
      exit(1);
    }
    if (i>indexmax())
    {
      cerr << "Error index too high in adstring& operator [] (int i)" << endl;
      cerr << "value was " << i << " maximum valid index is "
        << indexmax() << endl;
      exit(1);
    }
    return *(ptr[i]);
  }

  _CONST adstring& adstring_array::operator () (int i) _CONST
  {
    if (!shape)
    {
      cerr << "Error -- trying to acess unallocated adstring array"
        << endl;
      exit(1);
    }
    if (i<indexmin())
    {
      cerr << "Error index too low in adstring& operator [] (int i)" << endl;
      cerr << "value was " << i << " minimum valid index is "
        << indexmin() << endl;
      exit(1);
    }
    if (i>indexmax())
    {
      cerr << "Error index too high in adstring& operator [] (int i)" << endl;
      cerr << "value was " << i << " maximum valid index is "
        << indexmax() << endl;
      exit(1);
    }
    return *(ptr[i]);
  }
#endif
