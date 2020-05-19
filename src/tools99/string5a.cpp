/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Member functions append_distinct and operator+= for class adstring_array.
*/
#include <fvar.hpp>
#include <stdlib.h>

adstring_array& adstring_array::operator+=(const adstring& s)
{
  return append_distinct(s);
}

adstring_array& adstring_array::append_distinct(const adstring& s)
{
  int tmp_min = 1;
  int tmp_max = 1;
  if (shape)
  {
    tmp_min=shape->indexmin();
    tmp_max=shape->indexmax()+1;
    delete shape;
    shape = 0;
  }
  vector_shape* tmp_shape = new vector_shape(tmp_min,tmp_max);
  if (!tmp_shape)
  {
    cerr << "Error allocating memory in adstring_array" << endl;
  }
  int size = tmp_max - tmp_min + 1;
  adstring** tmp_ptr =
    new adstring*[static_cast<unsigned int>(size < 0 ? 0 : size)];
  if (!tmp_ptr)
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
      ptr[i] = 0;
    }
    ptr+=tmp_min;
    delete [] ptr;
    ptr = 0;
  }
  ptr=tmp_ptr;
  shape=tmp_shape;
  adstring_array* tmp = (adstring_array*)this->next;
  while (tmp != this)
  {
    if (tmp)
    {
      tmp->shape = shape;
      tmp->ptr = ptr;
      tmp = (adstring_array*)tmp->next;
    }
  }
  return *this;
}
