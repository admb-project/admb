/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
/// file ddlist.cpp
#include "fvar.hpp"

#ifdef __ZTC__
   #include <iostream.hpp>
#endif

#ifdef __TURBOC__
   #pragma hdrstop
   #include <iostream.h>
#endif

#include <stdlib.h>
//#define MAX_DLINKS 1000
dlink * dlink::previous(){return prev;}

//////////////////////////////
// global list names
//dlist * GRAD_LIST;
//extern dlist * GRAD_LIST; //js
/////////////////////////////

char* ddlist_space;
char* ddlist_spacea;

/**
Default constructor
*/
dlist::dlist(void)
{
  int on,nopt = 0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mdl",nopt))>-1)
  {
    if (nopt ==1)
    {
      gradient_structure::MAX_DLINKS=atoi(ad_comm::argv[on+1]);
    }
    else
    {
      cerr << "Wrong number of options to -mdl -- must be 1"
        " you have " << nopt << endl;		
      ad_exit(1);
    }	
  }
  last = 0;
  last_offset = 0;
  nlinks = 0;
  dlink_addresses = new dlink*[gradient_structure::MAX_DLINKS];
  ddlist_space = (char*)malloc(2 * sizeof(double) * (gradient_structure::MAX_DLINKS + 1));
  //cout << (int) (ddlist_space) << endl;
  //cout << ((int) (ddlist_space))%8 << endl;
#if defined(__x86_64)
  intptr_t adjust=(8 - ((intptr_t)(ddlist_space))%8)%8;
#else
  int adjust=(8- ((int) (ddlist_space))%8)%8;
#endif

  ddlist_spacea=ddlist_space+adjust;

  memset(dlink_addresses, 0, sizeof(dlink*) * gradient_structure::MAX_DLINKS);
}

/**
 * Description not yet available.
 * \param
 */
dlink * dlist::create()
{

  dlink * tmp= (dlink*)(ddlist_spacea+2*sizeof(double)*nlinks);
  /*
  if ( (tmp = new dlink) ==0)
  {
    cerr << "Error allocating dlink in dlist::create()\n";
    ad_exit(21);
  }
 */

  dlink_addresses[nlinks]=tmp;   // keep track of the links so you can
                                 // zero them out
  nlinks+=1;

  if (nlinks > (unsigned int)gradient_structure::MAX_DLINKS)
  {
    cerr << "Need to increase the maximum number of dlinks" << endl;
    ad_exit(1);
  }

  tmp->prev=0;
  // cout << "Made a dlink with address " << _farptr_tolong(tmp) <<"\n";
  return(tmp);
}

/**
If last node in list exist, remove it and return it.
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
  ::free(ddlist_space);
  ddlist_space=NULL;

  delete [] dlink_addresses;
  dlink_addresses = 0;
}
/**
Get total addresses stored.
*/
size_t dlist::total_addresses() const
{
  size_t total = 0;
  for (int i = 0; i < gradient_structure::MAX_DLINKS; ++i)
  {
    if (dlink_addresses[i] != 0)
    {
      total++;
    }
  }
  return total;
}
/**
 * Description not yet available.
 * \param
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
  if (app == 0)
  {
    cerr << "NULL pointer passed to  dlist::append()\n";
    ad_exit(1);
  }

  dlink* tmp = last;
  last = app;
  last->prev = tmp;

  return last;
}
