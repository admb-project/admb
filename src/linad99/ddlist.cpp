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

#include <stdlib.h>
#include "fvar.hpp"

//#define MAX_DLINKS 1000

dlink::dlink()
{
  di.x = 0;
  prev = nullptr;
}
dlink::~dlink()
{
}
dlink* dlink::previous()
{
  return prev;
}

__thread char* ddlist_space;
__thread char* ddlist_spacea;

/**
 * Description not yet available.
 * \param
 */
dlist::dlist(void)
{
  int on, nopt;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mdl",nopt))>-1)
  {
    if (nopt == 1)	    
    {	      
      gradient_structure::MAX_DLINKS=atoi(ad_comm::argv[on+1]);
    }
    else
    {
      cerr << "Wrong number of options to -mdl -- must be 1 you have " << nopt << endl;		
      ad_exit(1);
    }	
  }   

  last = nullptr;
  last_offset = 0;
  nlinks = 0;

  dlink_addresses = new dlink*[gradient_structure::MAX_DLINKS];
  for (int i = 0; i < gradient_structure::MAX_DLINKS; ++i)
  {
    dlink_addresses[i] = nullptr;
  }

  ddlist_space = (char*)malloc(2 * sizeof(double) * (gradient_structure::MAX_DLINKS + 1));
#if defined(__x86_64)
  intptr_t adjust=(8 - ((intptr_t)(ddlist_space))%8)%8;
#else
  int adjust=(8- ((int) (ddlist_space))%8)%8;
#endif
  ddlist_spacea=ddlist_space+adjust;
}

/**
 * Description not yet available.
 * \param
 */
dlink* dlist::create()
{
  dlink* tmp = (dlink*)(ddlist_spacea + 2 * sizeof(double) * nlinks);
  tmp->prev = nullptr;

  // keep track of the links so you can zero them out
  dlink_addresses[nlinks] = tmp;

  nlinks++;
  if (nlinks > (unsigned int)gradient_structure::MAX_DLINKS)
  {
    cerr << "Need to increase the maximum number of dlinks" << endl;
    ad_exit(1);
  }

  return tmp;
}
 
/**
 * Description not yet available.
 * \param
 */
dlink* dlist::last_remove()
{
  dlink* tmp = nullptr;
  if (last != nullptr)
  {
    tmp = last;
    last = last->prev;
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dlist::~dlist()
{
  ::free(ddlist_space);
  ddlist_space = nullptr;

  delete [] dlink_addresses;
  dlink_addresses = nullptr;
}

/**
 * Description not yet available.
 * \param
 */
unsigned int dlist::check_list()
{
  unsigned int count = 0;

  dlink* tmp_last = last;
  while (tmp_last != nullptr)
  {
    count+=1;
    if (count > nlinks)
    {
      cerr << "In check_list() number of links > number created\n";
      cerr << " The number created was "<< nlinks << endl;
      break;
    }

    tmp_last = tmp_last->prev;
  }
  cerr << "In check_list() number of free links is " << count << endl;

  return count;
}

/**
 * Description not yet available.
 * \param
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
