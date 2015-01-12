/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>
#include <stdlib.h>


#if defined(__BORLANDC__) || defined(__MSVC32__) || defined(__MINGW32__)
#  if !defined(__linux__)
#   include <windows.h>
#  endif
#endif

void ADSleep(int t)
{
#if !defined(linux) && !defined(__CYGWIN__) && !defined(__linux__)	
  Sleep(t);
#else 
#  if defined(__MINGW32__)
     Sleep(t);
#  else
     sleep(t);
#  endif  
#endif  
}
