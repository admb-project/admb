/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>

#ifndef OPT_LIB
  #include <cassert>
#endif

adstring adstring::operator()(const size_t i, const size_t j)
{
#ifndef OPT_LIB
  assert(1 <= i && i <= shape->size());
  assert(i <= j);
  assert(j <= shape->size());
#endif

  adstring tmp(1, j - i + 1);
  for (size_t ii = i; ii <= j; ii++)
  {
    tmp(ii - i + 1) = (* this) (ii);
  }
  return tmp;
}

adstring adstring::operator()(const size_t i, const size_t j) const
{
#ifndef OPT_LIB
  assert(1 <= i && i <= shape->size());
  assert(i <= j);
  assert(j <= shape->size());
#endif

  adstring tmp(1, j - i + 1);
  for (size_t ii = i; ii <= j; ii++)
  {
    tmp(ii - i + 1) = (* this) (ii);
  }
  return tmp;
}

adstring& adstring::operator=(const adstring & t)
{
  if (s != t.s)
  {
    size_t sz = t.size();
    shape->size() = sz;
    delete [] ++s;
    s=new unsigned char[sz+1];
    s--;
    size_t size = t.size();
    for (size_t i = 1; i <= size; i++)
    {
      s[i] = t[i];
    }
    s[sz + 1] = '\0';
    adstring* tmp = (adstring*)this->next;
    while (tmp != this)
    {
      if (tmp)
      {
        tmp->shape = shape;
        tmp->s = s;
        tmp = (adstring*)tmp->next;
      }
    }
  }
  return (* this);
}

void adstring::realloc(const char* t)
{
  size_t sz = strlen(t);
  shape->size() = sz;
  ++s;
  delete [] s;
  s=new unsigned char[sz+1];
  strcpy((char*)(s),t);
  s--;
  adstring* tmp = (adstring*)this->next;
  while (tmp != this)
  {
    if (tmp)
    {
      tmp->shape = shape;
      tmp->s = s;
      tmp = (adstring *) tmp->next;
    }
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

unsigned char & adstring::operator()(const size_t i)
{
/*
  if (i < 1 || i > shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "unsigned char & adstring::operator()(int i)", 1, shape->size(), i);
  }
*/
  return ( ((unsigned char *)s)[i]);
}

const unsigned char& adstring::operator()(const size_t i) const
{
/*
  if (i < 1 || i > shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "unsigned char & adstring::operator()(int i) const", 1, shape->size(), i);
  }
*/
  return (s[i]);
}

unsigned char& adstring::operator[](const size_t i) const
{
/*
  if (i < 1 || i > shape->size())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
    "unsigned char & adstring::operator[](int i) const ", 1, shape->size(), i);
  }
*/
  return s[i];
}

/**
Return true if adstring is equal to other, otherwise false.

\param other compare string
*/
bool adstring::operator==(const adstring& other) const
{
  return !strcmp(*this, other);
}
/**
Return true if adstring is equal to other, otherwise false.

\param other compare string
*/
bool adstring::operator==(const adstring& other)
{
  return !strcmp(*this, other);
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
  size_t us = size();
  size_t vs = v.size ();
  size_t bs = buff_size();
  if (bs > us + vs)
  {
    for (size_t i = 1; i <= vs; i++)
    {
      s[i + us] = v(i);
    }
  }
  else
  {
    adstring tmp(1, us + vs);
    for (size_t i = 1; i <= us; i++)
    {
      tmp(i) = s[i];
    }
    for (size_t i = 1; i <= vs; i++)
    {
      tmp(i + us) = v(i);
    }
    * this = tmp;
  }
  return (* this);
}
/**
Returns reference to element at specified index i.

\param i index
*/
unsigned char& adstring::operator[](const size_t i)
{
  if (i < 1 || i > shape->size())
  {
    cerr << "Index out of bounds in adstring::operator[](const size_t)\n"
         << "Index value was " << i
         << " The size of this adstring is " << shape->size() << "\n";
    ad_exit(1);
  }
  return s[i];
}
/**
Returns the size of adstr.

\param adstr is a adstring.
*/
size_t length(const adstring& adstr)
{
  return adstr.size();
}
