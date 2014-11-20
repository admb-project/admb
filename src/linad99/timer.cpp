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
#include <admodel.h>
#if !defined(_WIN32)
#include <sys/time.h>
#include <iostream>

/**
Default constructor
*/
adtimer::adtimer (void)
{
  gettimeofday(&tv,0);

  tvold.tv_sec=tv.tv_sec;
  tvold.tv_usec=tv.tv_usec;
}

/**
Returns elapsed time in milliseconds of timer object and then 
resets the timer to current time.
*/
double adtimer::get_elapsed_time_and_reset(void)
{
  long int nsec=0;
  long int nusec=0;
  gettimeofday(&tv,0);
  if ( tv.tv_usec< tvold.tv_usec)
  {
    nsec=tv.tv_sec-tvold.tv_sec-1;
    nusec=tv.tv_usec-tvold.tv_usec+1000000;
  }
  else
  {
    nsec=tv.tv_sec-tvold.tv_sec;
    nusec=tv.tv_usec-tvold.tv_usec;
  }

  //reset
  tvold.tv_sec=tv.tv_sec;
  tvold.tv_usec=tv.tv_usec;

  return 1000.0 * (double)nsec + 0.001 * (double)nusec;
}

/**
Returns the elapsed time in milliseconds from the timer object.
*/
double adtimer::get_elapsed_time(void)
{
  long int nsec=0;
  long int nusec=0;
  gettimeofday(&tv,0);
  if ( tv.tv_usec< tvold.tv_usec)
  {
    nsec=tv.tv_sec-tvold.tv_sec-1;
    nusec=tv.tv_usec-tvold.tv_usec+1000000;
  }
  else
  {
    nsec=tv.tv_sec-tvold.tv_sec;
    nusec=tv.tv_usec-tvold.tv_usec;
  }
  return 1000.0 * (double)nsec + 0.001 * (double)nusec;
}

#else
#include <windows.h>

/**
 * Description not yet available.
 * \param
 */
  adtimer::adtimer (void)
  {
#ifdef _WIN64
    t=GetTickCount64();
#else
    t=GetCurrentTime();
#endif
    told=t;
  }

/**
 * Description not yet available.
 * \param
 */
  double adtimer::get_elapsed_time_and_reset(void)
  {
#ifdef _WIN64
    t=GetTickCount64();
#else
    t=GetCurrentTime();
#endif
    //std::cout << tv.tv_sec << " " << tv.tv_usec << std::endl;
    double diff=t-told;
    told=t;
    return diff;
  }

/**
 * Description not yet available.
 * \param
 */
  double adtimer::get_elapsed_time(void)
  {
#ifdef _WIN64
    t=GetTickCount64();
#else
    t=GetCurrentTime();
#endif
    //std::cout << tv.tv_sec << " " << tv.tv_usec << std::endl;
    double diff=t-told;
    return diff;
  }
#endif
