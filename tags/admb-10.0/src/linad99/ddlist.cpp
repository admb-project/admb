/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
extern char demo_capacity[];
extern char please_buy[];
extern char otter_address1[];
extern char otter_address2[];
extern char otter_address3[];
extern char otter_address4[];
extern char otter_address5[];


char * ddlist_space;
char * ddlist_spacea;

/**
 * Description not yet available.
 * \param
 */
dlist::dlist(void)
{
  int on,nopt;
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
  // cout << sizeof(double_and_int) << endl;
  // cerr << "dlist::dlist(void)\n";
  last = 0;
  last_offset = 0;
  nlinks = 0;
  dlink_addresses = new dlink *[gradient_structure::MAX_DLINKS];
  ddlist_space= (char *) malloc(2*sizeof(double)*
   (gradient_structure::MAX_DLINKS+1));
  //cout << (int) (ddlist_space) << endl;
  //cout << ((int) (ddlist_space))%8 << endl;
#if defined(__SUNPRO_CC) && defined(__x86_64)
  long adjust=(8 - ((long)(ddlist_space))%8)%8;
#else
  int adjust=(8- ((int) (ddlist_space))%8)%8;
#endif
  
  ddlist_spacea=ddlist_space+adjust;
  
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
#if defined(AD_DEMO)
    cout << demo_capacity << endl;
    cout << please_buy << endl;
    cout << otter_address1 << endl;
    cout << otter_address2 << endl;
    cout << otter_address3 << endl;
    cout << otter_address4 << endl;
    cout << otter_address5 << endl;
#endif
    ad_exit(1);
  }

  tmp->prev=0;
  // cout << "Made a dlink with address " << _farptr_tolong(tmp) <<"\n";
  return(tmp);
}
 
/**
 * Description not yet available.
 * \param
 */
dlink* dlist::last_remove()
{
  dlink * tmp;
  if (last)
  {
    tmp=last;
    last=last->prev;
    return(tmp);
  }
  else
  {
    return 0;
  }
}

/**
 * Description not yet available.
 * \param
 */
dlist::~dlist()
{
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
  ::free(ddlist_space);
  ddlist_space=NULL;
  delete [] dlink_addresses;
}

/**
 * Description not yet available.
 * \param
 */
void dlist::check_list(void)
{
  dlink * tmp;
  dlink * tmp_last=last;

  unsigned int count=0;
  while(tmp_last && count <=nlinks)
  {
    count+=1;
    if (count > nlinks)
    {
      cerr << "In check_list() number of links > number created\n";
      cerr << " The number created was "<< nlinks << endl;
    }

    tmp=tmp_last->prev;

//  cout << "last =" << _farptr_tolong(last) << "\n";
//  cout << "last->prev =" << _farptr_tolong(last->prev) << "\n";
//  cout << "deleted dlink with address" << _farptr_tolong(last) << "\n";

    tmp_last=tmp;
  }
  cerr << "In check_list() number of free links is " << count << endl;
}

/**
 * Description not yet available.
 * \param
 */
dlink * dlist::append(dlink * app)
{
  // cout << " In dlist::append\n";
  if (app ==0)
  {
    cerr << "NULL pointer passed to  dlist::append()\n";
    ad_exit(1);
  }

  dlink * tmp;

  tmp = last;

  last = app;

  last->prev = tmp;
  // cout << " In dlist::append  last = " << _farptr_tolong(last) <<"\n";

  return(last);
}    
