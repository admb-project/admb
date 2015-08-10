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
dlist::dlist()
{
  int on,nopt = 0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mdl",nopt))>-1)
  {
    if (nopt == 1)
    {
      int i = atoi(ad_comm::argv[on+1]);
      if (i > 0)
        gradient_structure::MAX_DLINKS = (unsigned int)i;
    }
    else
    {
      cerr << "Wrong number of options to -mdl -- must be 1"
        " you have " << nopt << endl;
      ad_exit(1);
    }
  }
  last = 0;
  nlinks = 0;
  dlink_addresses = new dlink*[gradient_structure::MAX_DLINKS];
  const size_t size = 2 * sizeof(double) * (gradient_structure::MAX_DLINKS + 1);
  ddlist_space = (char*)malloc(size * sizeof(char));

  variables_save = new double[gradient_structure::MAX_DLINKS];

#ifndef OPT_LIB
  //fails for insufficient memory to allocate space for dvariables save buffer
  assert(variables_save != NULL);
#endif

  //Initialize addresses to zero
  memset(dlink_addresses, 0, sizeof(dlink*) * gradient_structure::MAX_DLINKS);
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
Create unlinked new node.
*/
dlink* dlist::create()
{
  dlink* link = (dlink*)(ddlist_space+2*sizeof(double)*nlinks);
#ifndef OPT_LIB
  assert(link);
#endif

  //do not add to list.
  link->prev=0;

#ifndef OPT_LIB
  //If fails, then need to increase the maximum number of dlinks.
  assert(nlinks <= gradient_structure::MAX_DLINKS);
#endif

  // keep track of the links so you can zero them out
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
  for (unsigned int i = 0; i < nlinks; ++i)
  {
    *(double*)dlink_addresses[i] = 0;
  }
}
/**
Save variables to a buffer.
*/
void dlist::save_variables()
{
  for (unsigned int i = 0; i < nlinks; ++i)
  {
    variables_save[i] = *(double*)(dlink_addresses[i]);
  }
}
/**
Restore variables from buffer.
*/
void dlist::restore_variables()
{
  for (unsigned int i = 0; i < nlinks; ++i)
  {
    *(double*)(dlink_addresses[i]) = variables_save[i];
  }
}
/**
Get total addresses stored.
*/
size_t dlist::total_addresses() const
{
  size_t total = 0;
  for (unsigned int i = 0; i < gradient_structure::MAX_DLINKS; ++i)
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
