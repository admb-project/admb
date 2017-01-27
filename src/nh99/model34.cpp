/**
Author: David Fournier

Copyright (c) 2008-2016 ADMB Foundation and
Regents of the University of California
*/

#include <cmath>
#include <ctime>

#if defined(_WIN32)
  #include <windows.h>
#endif

/**
Delay runtime by seconds(sec).

\param sec seconds to delay

\return total seconds waited
*/
time_t _adwait(double sec)
{
  time_t total_wait = 0;

  const time_t max_seconds = 
    static_cast<long int>(ceil(sec));

  time_t current;
  time_t start;
  time(&start);

  do
  {
    time(&current);
    total_wait = current - start;
  }
  while(total_wait <= max_seconds);

  return total_wait;
}
void adwait(double sec)
{
  _adwait(sec);
}
