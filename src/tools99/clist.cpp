/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "clist.h"
#include <cassert>

/**
Copy constructor
*/
clist::clist(const clist& t):
  next(t.next)
{
  clist& tmp = *(clist*)(&t);
  tmp.next = this;
}
/**
Destructor
*/
clist::~clist()
{
  if (next == this)
  {
    next = NULL;
  }
  else
  {
    prev()->next = next;
  }
}
/**
Returns previous pointer to itself.
If single node, returns itself.
*/
clist* clist::prev()
{
  clist* t = this;
  while (t->next != this)
  {
#ifndef OPT_LIB
    assert(t->next);
#endif
    t = t->next;
  }
  return t;
}
/**
Returns number of pointers in circular list.
*/
int clist::length(const int& max)
{
  int num = 1;
  clist* t = this;
  while (t->next != this)
  {
#ifndef OPT_LIB
    assert(t->next);
#endif

    if (num >= max)
    {
      return -1;
    }
    ++num;

    t = t->next;
  }
  return num;
}
