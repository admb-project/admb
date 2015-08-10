/**
\file

Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

#include <stdlib.h>
#if defined(__x86_64) || (defined(_MSC_VER) && defined(_M_X64))
  #include <stdint.h>
#endif
/**
\return previous node pointer.
*/
dlink* dlink::previous()
{
  return prev;
}

/**
Default constructor
*/
dlist::dlist()
{
  int on,nopt = 0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mdl",nopt))>-1)
  {
    if (nopt ==1)
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
  if (variables_save == NULL)
  {
    cerr << "insufficient memory to allocate space for dvariables"
         << " save buffer " << endl;
    ad_exit(1);
  }

  //Initialize addresses to zero
  memset(dlink_addresses, 0, sizeof(dlink*) * gradient_structure::MAX_DLINKS);
}
/**
Create unlinked new node.
*/
dlink* dlist::create()
{
  dlink* tmp= (dlink*)(ddlist_space+2*sizeof(double)*nlinks);
  // cout << "Made a dlink with address " << _farptr_tolong(tmp) <<"\n";

  if (!tmp)
  {
    cerr << "Error allocating dlink in dlist::create()\n";
    ad_exit(21);
  }
  else
  {
    // keep track of the links so you can zero them out
    dlink_addresses[nlinks]=tmp;
    nlinks+=1;

    if (nlinks > gradient_structure::MAX_DLINKS)
    {
      cerr << "Need to increase the maximum number of dlinks" << endl;
      ad_exit(1);
    }

    //do not add to list.
    tmp->prev=0;
  }

  return tmp;
}
/**
If list is not empty, pop and return last node.

\return 0 empty list.
*/
dlink* dlist::last_remove()
{
  if (last)
  {
    dlink* tmp = last;
    last = last->prev;
    return tmp;
  }
  return 0;
}
/**
Destructor
*/
dlist::~dlist()
{
/*
  dlink * tmp;
//   cout << "used the dlist destructor\n";
//   cout << "entered ~dlist   last =" << _farptr_tolong(last) << "\n";

  unsigned int count=0;

  while(last)
  {
    count+=1;
    tmp=last->prev;

//  cout << "last =" << _farptr_tolong(last) << "\n";
//  cout << "last->prev =" << _farptr_tolong(last->prev) << "\n";
//  cout << "deleted dlink with address" << _farptr_tolong(last) << "\n";

    //delete last;
    last=tmp;
  }
  if (count != nlinks)
  {
    cerr << "In ~dlist() number of links destroyed not equal to number created\n";
    cerr << " The number created was "<< nlinks << " The number destroyed was "
         << count << "\n";
    ad_exit(1);
  }
*/
  delete [] dlink_addresses;
  dlink_addresses = NULL;

  ::free(ddlist_space);
  ddlist_space = NULL;

  delete [] variables_save;
  variables_save = NULL;
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

/**
Append app to list.
\param app node
*/
dlink* dlist::append(dlink* app)
{
  if (!app)
  {
    cerr << "Error: NULL pointer passed to  dlist::append()\n";
    ad_exit(1);
  }
  else
  {
    app->prev = last;
    last = app;
  }

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
