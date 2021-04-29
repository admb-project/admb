/**
\file

Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

#include <stdlib.h>
#ifndef OPT_LIB
  #include <cassert>
#endif

/**
Default constructor
*/
dlist::dlist(const unsigned int _size): size(_size)
{
  last = NULL;
  nlinks = 0;
  dlink_addresses = new dlink*[size];
  ddlist_space = (char*)malloc(size * sizeof(dlink));
  variables_save = new double[size];

#ifndef OPT_LIB
  //fails for insufficient memory to allocate space for dvariables save buffer
  assert(variables_save != NULL);
#endif

  //Initialize addresses to zero
  memset(dlink_addresses, 0, size * sizeof(dlink*));
}
/**
Destructor
*/
dlist::~dlist()
{
  if (dlink_addresses)
  {
    delete [] dlink_addresses;
    dlink_addresses = NULL;
  }
  if (ddlist_space)
  {
    ::free(ddlist_space);
    ddlist_space = NULL;
  }
  if (variables_save)
  {
    delete [] variables_save;
    variables_save = NULL;
  }
}
/**
Return new unlinked node.
*/
dlink* dlist::create()
{
#ifndef OPT_LIB
  //If fails, then need to increase the maximum number of dlinks.
  assert(nlinks < size);
#endif

  dlink* link = (dlink*)(&ddlist_space[sizeof(dlink) * nlinks]);

#ifndef OPT_LIB
  assert(link);
#endif

  //Do not add to list.
  link->prev = NULL;

  //Keep track of the links so you can zero them out (ie gradcalc).
  dlink_addresses[nlinks] = link;
  ++nlinks;

  return link;
}
/**
If list is not empty, pop and return last node.

\return 0 empty list.
*/
dlink* dlist::last_remove()
{
  dlink* link = last;
  if (link)
  {
    last = link->prev;
    link->prev = NULL;
  }
  return link;
}
/**
Append link to list.

\param link node
*/
dlink* dlist::append(dlink* link)
{
#ifndef OPT_LIB
  //Should fail if link is NULL.
  assert(link);
#endif

  link->prev = last;
  last = link;

  return last;
}
void dlist::initialize()
{
  dlink** dest = dlink_addresses;
  for (unsigned int i = 0; i < nlinks; ++i)
  {
    (*dest)->di.x = 0;
    ++dest;
  }
}
/**
Save variables to a buffer.
*/
void dlist::save_variables()
{
  dlink** src = dlink_addresses;
  double* dest = variables_save;
  for (unsigned int i = 0; i < nlinks; ++i)
  {
    *dest = (*src)->di.x;
    ++dest;
    ++src;
  }
}
/**
Restore variables from buffer.
*/
void dlist::restore_variables()
{
  dlink** dest = dlink_addresses;
  double* src = variables_save;
  for (unsigned int i = 0; i < nlinks; ++i)
  {
    (*dest)->di.x = *src;
    ++dest;
    ++src;
  }
}
/**
Get total addresses stored.
*/
size_t dlist::total_addresses() const
{
  size_t total = 0;
  for (unsigned int i = 0; i < size; ++i)
  {
    if (dlink_addresses[i] != 0)
    {
      total++;
    }
  }
  return total;
}
/**
Check link list integrity.
*/
void dlist::check_list(void)
{
  dlink* tmp_last=last;

  unsigned int count=0;
  while(tmp_last && count <=nlinks)
  {
    count+=1;
    if (count > nlinks)
    {
      cerr << "In check_list() number of links > number created\n";
      cerr << " The number created was "<< nlinks << endl;
    }

    dlink* tmp = tmp_last->prev;

//  cout << "last =" << _farptr_tolong(last) << "\n";
//  cout << "last->prev =" << _farptr_tolong(last->prev) << "\n";
//  cout << "deleted dlink with address" << _farptr_tolong(last) << "\n";

    tmp_last = tmp;
  }
  cerr << "In check_list() number of free links is " << count << endl;
}
