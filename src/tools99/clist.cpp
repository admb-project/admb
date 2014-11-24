/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "clist.h"

clist* clist::prev()
{
  clist* tmp = this->next;
  while (tmp && tmp->next != this)
  {
    tmp = tmp->next;
  }
  return tmp;
}

int clist::length(const int& max)
{
  int num = 1;
  clist* tmp = this;
  while (tmp && tmp->next != this)
  {
    tmp = tmp->next;
    if (++num > max)
    {
      return -1;
    }
  }
  return num;
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
