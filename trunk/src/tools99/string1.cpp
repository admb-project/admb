/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>
#include "admb_messages.h"

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

adstring adstring::operator()(int i, int j)
{
  if (i < 1 || i > (int) shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("First index out of bounds",
    "adstring adstring::operator()(int i, int j)", 1, shape->size(), i);
  }
  if (i > j)
  {
    ADMB_ARRAY_BOUNDS_ERROR(
    "First index must be less than or equal to second index",
    "adstring adstring::operator()(int i, int j)", 1, shape->size(), j);
  }
  if (j > (int) shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Second index out of bounds",
    "adstring adstring::operator()(int i, int j)", 1, shape->size(), j);
  }
  adstring tmp(1, size_t(j - i + 1));
  for (int ii = i; ii <= j; ii++)
  {
    tmp(ii - i + 1) = (* this) (ii);
  }
  return (tmp);
}

adstring adstring::operator()(int i, int j) const
{
  if (i < 1 || i > (int) shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("First index out of bounds",
    "adstring adstring::operator()(int i, int j)", 1, shape->size(), i);
  }
  if (i > j)
  {
    ADMB_ARRAY_BOUNDS_ERROR(
    "First index must be less than or equal to second index",
    "adstring adstring::operator()(int i, int j)", 1, shape->size(), j);
  }
  if (j > (int) shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Second index out of bounds",
    "adstring adstring::operator()(int i, int j)", 1, shape->size(), j);
  }
  adstring tmp(1, size_t(j - i + 1));
  for (int ii = i; ii <= j; ii++)
  {
    tmp(ii - i + 1) = (* this) (ii);
  }
  return (tmp);
}

adstring& adstring::operator=(const adstring & t)
{
  if (s != t.s)
  {
    int sz = t.size ();
    shape->size() = t.size();
    delete [] ++s;
    s=new unsigned char[sz+1];
    s--;
    int size = t.size();
    for (int i = 1; i <= size; i++)
    {
      s[i] = t[i];
    }
    s[sz + 1] = '\0';
    adstring * tmp = (adstring *) this->next;
    while (tmp != this)
    {
      tmp->shape = shape;
      tmp->s = s;
      tmp = (adstring *) tmp->next;
    }
  }
  return (* this);
}

void adstring::realloc(const char* t)
{
  size_t sz = strlen(t);
#ifndef OPT_LIB
  assert(sz <= INT_MAX);
#endif
  shape->size() = (int)sz;
  delete [] ++s;
  s=new unsigned char[sz+1];
  strcpy((char*)(s),t);
  s--;
  adstring * tmp = (adstring *) this->next;
  while (tmp != this)
  {
    tmp->shape = shape;
    tmp->s = s;
    tmp = (adstring *) tmp->next;
  }
}

/**
Destructor
*/
adstring::~adstring()
{
  if (next==this)
  {
    deallocate();
  }
}

unsigned char & adstring::operator()(const int i)
{
  if (i < 1 || i > (int) shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "unsigned char & adstring::operator()(int i)", 1, shape->size(), i);
  }
  return ( ((unsigned char *)s)[i]);
}

const unsigned char& adstring::operator()(const int i) const
{
  if (i < 1 || i > (int) shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "unsigned char & adstring::operator()(int i) const", 1, shape->size(), i);
  }
  return (s[i]);
}

const unsigned char& adstring::operator[](const int i) const
{
  if (i < 1 || i > (int) shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "unsigned char & adstring::operator[](int i) const ", 1, shape->size(), i);
  }
  return (s[i]);
}

int adstring::operator==(const adstring& v) const
{
  int tmp = strcmp (* this, v);
  return (tmp == 0);
}

int adstring::operator==(const adstring& v)
{
  int tmp = strcmp (* this, v);
  return (tmp == 0);
}
/*
int adstring::operator!=(const adstring& v)
{
  int tmp = strcmp (* this, v);
  return (tmp != 0);
}
*/
adstring& adstring::operator+=(const adstring& v)
{
  int us = size ();
  int vs = v.size ();
  int bs = buff_size();
  if (bs > us + vs)
  {
    for (int i = 1; i <= vs; i++)
    {
      s[i + us] = v(i);
    }
  }
  else
  {
    adstring tmp(1, us + vs);
    int i;
    for (i = 1; i <= us; i++)
    {
      tmp(i) = s[i];
    }
    for (i = 1; i <= vs; i++)
    {
      tmp(i + us) = v(i);
    }
    * this = tmp;
  }
  return (* this);
}

unsigned char& adstring::operator[](const int i)
{
  if (i < 1 || i > (int) shape->size())
  {
    cerr << "Index out of bounds in adstring::operator () (const int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
  }
 // return (s[i]);
  return ( ((unsigned char *)s)[i]);
}

int length(const adstring& t)
{
  return (int(t.size()));
}
