/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Member functions for class clist.
*/
#include "clist.h"
#include <new>

clist* clist::prev() const
{
  clist* t = this->next;
  while (t != this)
  {
    if (!t)
    {
      //unexpected
      throw std::bad_alloc();
    }
    else if (t->next == this)
    {
      return t;
    }
    else
    {
      t = t->next;
    }
  }
  return 0;
}

int clist::length(const int& max) const
{
  int num = 1;
  clist* t = this->next;
  while (num <= max)
  {
    if (!t)
    {
      //unexpected
      throw std::bad_alloc();
    }
    else if (t == this)
    {
      return num;
    }
    else
    {
      t = t->next;
    }
    ++num;
  }
  return -1;
}

/**
Copy constructor
*/
clist::clist(const clist& t)
{
  clist& tmp=*(clist *)(&t);
  next = t.next;
  tmp.next = this;
}

/**
Destructor
*/
clist::~clist()
{
  if (next == this)
  {
    next = 0;
  }
  else
  {
    prev()->next = next;
  }
}
