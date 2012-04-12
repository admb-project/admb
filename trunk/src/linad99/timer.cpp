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
#include <admodel.h>
#if (defined(linux) || defined(__linux__)) && !defined(__WIN32)
#include <sys/time.h>
#include <iostream>

/**
 * Description not yet available.
 * \param
 */
  adtimer::adtimer (void)
  {
    gettimeofday(&tv,0);
    
    tvold.tv_sec=tv.tv_sec;	       
    tvold.tv_usec=tv.tv_usec;	       

  }

/**
 * Description not yet available.
 * \param
 */
  double adtimer::get_elapsed_time_and_reset(void)
  {
    gettimeofday(&tv,0);
    //std::cout << tv.tv_sec << " " << tv.tv_usec << std::endl;
    int nsec=0; 
    int nusec=0; 
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
    tvold.tv_sec=tv.tv_sec;	       
    tvold.tv_usec=tv.tv_usec;	       
    return 1000.*nsec+nusec/1000.;
  }

/**
 * Description not yet available.
 * \param
 */
  double adtimer::get_elapsed_time(void)
  {
    int nsec=0; 
    int nusec=0; 
    gettimeofday(&tv,0);
    //std::cout << tv.tv_sec << " " << tv.tv_usec << std::endl;
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
    return 1000.*nsec+nusec/1000.;
  }

#else
#include <windows.h>

/**
 * Description not yet available.
 * \param
 */
  adtimer::adtimer (void)
  {
    t=GetCurrentTime(); 
    told=t;
  }

/**
 * Description not yet available.
 * \param
 */
  double adtimer::get_elapsed_time_and_reset(void)
  {
    t=GetCurrentTime(); 
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
    t=GetCurrentTime(); 
    //std::cout << tv.tv_sec << " " << tv.tv_usec << std::endl;
    double diff=t-told;
    return diff;
  }

#endif
