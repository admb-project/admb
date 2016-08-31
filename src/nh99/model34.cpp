/**
Author: David Fournier

Copyright (c) 2008-2016 ADMB Foundation and
Regents of the University of California
*/
#if defined(_WIN32)
#include <windows.h>
#include <time.h>
#endif

#include <admodel.h>

/**
Delay runtime by seconds(sec).

\param sec seconds to delay
*/
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
