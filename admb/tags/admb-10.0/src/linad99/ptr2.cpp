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
#include "fvar.hpp"
#ifdef __ZTC__
#include <iostream.hpp>
#endif

#ifdef __TURBOC__
#pragma hdrstop
#pragma options -h-
#include <iostream.h>
#endif
#include <stdlib.h>

int aabbbcd(void)
{
  return 1;
}

#ifdef DOS386

#if defined( __NDPX__) || defined(__SUN__)
  void * _farptr_fromlong(long int i)
#else
  void * _farptr_fromlong(unsigned long int i)
#endif
{
  return( (void *) i);
}

/**
 * Description not yet available.
 * \param
 */
long int _farptr_tolong(void * ptr)
{
  return( (long int) ptr);
}

/**
 * Description not yet available.
 * \param
 */
void * _farptr_norm(void * ptr)
{
  return(ptr);
}
#endif
