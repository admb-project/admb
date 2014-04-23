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
#include "fvar.hpp"
#include "admb_messages.h"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdlib.h>

#ifndef OPT_LIB
/**
 * Description not yet available.
 * \param
 */
 AD_LONG_INT& lvector::operator[] (int i)
 {
     if (i>indexmax())
     {
       ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high",
       "AD_LONG_INT& lvector::operator() (int i)", indexmin(), indexmax(), i);
     }

     if (i<indexmin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low",
       "AD_LONG_INT& lvector::operator() (int i)", indexmin(), indexmax(), i);
     }
   return(*(v+i));
 }

/**
 * Description not yet available.
 * \param
 */
 AD_LONG_INT& lvector::operator() (int i)
 {
     if (i>indexmax())
     {
       ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high",
       "AD_LONG_INT& lvector::operator() (int i)", indexmin(), indexmax(), i);
     }
     if (i<indexmin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low",
       "AD_LONG_INT& lvector::operator() (int i)", indexmin(), indexmax(), i);
     }
   return(*(v+i));
 }
#endif
