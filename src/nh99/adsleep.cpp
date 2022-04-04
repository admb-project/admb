/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function ADSleep
*/

#include <admodel.h>
#include <stdlib.h>

#if defined(_WIN32)
  #include <windows.h>
#endif

#ifndef _MSC_VER
  #include <unistd.h>
#endif

/**
 * Description not yet available.
 * \param
 */
void ADSleep(unsigned int t)
{
#if defined(_WIN32)
  Sleep(t);
#else
  sleep(t);
#endif
}
