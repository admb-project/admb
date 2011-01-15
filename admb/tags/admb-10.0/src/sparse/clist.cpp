/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include "clist.h"

#ifdef HERE
  #undef HERE
#endif
#define HERE cout << "reached line " << __LINE__ << " in " << __FILE__ << endl;
clist * clist::prev(void)
{
  clist * tmp = this->next;
  while (tmp->next != this) tmp = tmp->next;
  return (tmp);
}
 
int  clist::length(const int & max)
{
  int num = 1;
  clist * tmp = this;
  while (tmp->next != this)
  {
    tmp = tmp->next;
    if (++num > max)
    {
      return (-1);
    }
  }
  return (num);
}

clist::clist(const clist & t)
{
  clist& tmp=*(clist *)(&t); 
  next = t.next;
  tmp.next = this;
}
 
 
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
 
