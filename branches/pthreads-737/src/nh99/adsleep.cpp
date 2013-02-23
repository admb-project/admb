/*
 * $Id: adsleep.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>
#include <stdlib.h>


#if defined(__BORLANDC__) || defined(__MSVC32__) || defined(__MINGW32__)
#  if !defined(__linux__)
#   include <windows.h>
#  endif
#endif

/**
 * Description not yet available.
 * \param
 */
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
