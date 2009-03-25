/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#if defined(__SPDLL__)
#  if !defined(linux)
#    include <windows.h>
#  endif
#include <admodel.h>
#endif

#include <admodel.h>

#if defined (AD_DEMO)
#include <time.h>
double waste_time();

void adwait(double sec)
{
  time_t tt;
  time_t ttold;
  time(&ttold);
  do
  {
    time(&tt);
    if ( (tt-ttold) > sec ) break;
  }
  while(1);
}
#else
void adwait(double sec){;}
#endif

