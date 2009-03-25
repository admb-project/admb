/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>
#include <stdlib.h>

  adstring_array& adstring_array::operator += (const adstring& s)
  {
    int tmp_min;
    int tmp_max;
    vector_shape * tmp_shape;
    if (!shape)
    {
      tmp_min=1;
      tmp_max=1;
    }
    else
    {
      tmp_min=shape->indexmin();
      tmp_max=shape->indexmax()+1;
      delete shape;
    }
    if (!(tmp_shape=new vector_shape(tmp_min,tmp_max)))
    {
      cerr << "Error allocating memory in adstring_array" << endl;
    }
    adstring ** tmp_ptr;
    if (!(tmp_ptr=new adstring* [tmp_max-tmp_min+1]))
    {
      cerr << "Error allocating memory in adstring_array +=" << endl;
    }
    tmp_ptr-=tmp_min;
    for (int i=tmp_min;i<=tmp_max-1;i++)
    {
      tmp_ptr[i]=new adstring(*(ptr[i]));
    }
    tmp_ptr[tmp_max]=new adstring();
    *tmp_ptr[tmp_max]=s;
    if (ptr)
    {
      for (int i=tmp_min;i<=tmp_max-1;i++)
      {
        delete ptr[i];
      }
      ptr+=tmp_min;
      delete [] ptr;
    }
    ptr=tmp_ptr;
    shape=tmp_shape;
    adstring_array * tmp = (adstring_array *) this->next;
    while (tmp != this)
    {
      tmp->shape = shape;
      tmp->ptr = ptr;
      tmp = (adstring_array *) tmp->next;
    }
    return *this;
  }

  adstring_array& adstring_array::append_distinct(const adstring& s)
  {
    int tmp_min;
    int tmp_max;
    vector_shape * tmp_shape;
    if (!shape)
    {
      tmp_min=1;
      tmp_max=1;
    }
    else
    {
      tmp_min=shape->indexmin();
      tmp_max=shape->indexmax()+1;
      delete shape;
    }
    if (!(tmp_shape=new vector_shape(tmp_min,tmp_max)))
    {
      cerr << "Error allocating memory in adstring_array" << endl;
    }
    adstring ** tmp_ptr;
    if (!(tmp_ptr=new adstring* [tmp_max-tmp_min+1]))
    {
      cerr << "Error allocating memory in adstring_array +=" << endl;
    }
    tmp_ptr-=tmp_min;
    for (int i=tmp_min;i<=tmp_max-1;i++)
    {
      tmp_ptr[i]=new adstring(*(ptr[i]));
    }
    tmp_ptr[tmp_max]=new adstring();
    *tmp_ptr[tmp_max]=s;
    if (ptr)
    {
      for (int i=tmp_min;i<=tmp_max-1;i++)
      {
        delete ptr[i];
      }
      ptr+=tmp_min;
      delete [] ptr;
    }
    ptr=tmp_ptr;
    shape=tmp_shape;
    adstring_array * tmp = (adstring_array *) this->next;
    while (tmp != this)
    {
      tmp->shape = shape;
      tmp->ptr = ptr;
      tmp = (adstring_array *) tmp->next;
    }
    return *this;
  }
