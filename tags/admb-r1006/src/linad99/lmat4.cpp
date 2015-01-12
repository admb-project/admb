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
#include "admb_messages.h"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
 lvector& lmatrix::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
   if (i < rowmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "lvector& lmatrix::operator[] (int i)", rowmin(), rowmax(), i);
   }
   if (i > rowsize() + rowmin() - 1)
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high", "lvector& lmatrix::operator[] (int i)", rowmin(), rowmax(), i);
   }
   #endif
   return m[i];
 }

#ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
 _CONST lvector& lmatrix::operator [] (int i) _CONST 
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in imatrix::operator[]"
	     << "value was" << i;
       ad_exit(21);
     }
     if (i>rowsize()+rowmin()-1)
     {
       cerr << "matrix bound exceeded -- row index too high in imatrix::operator[]"
	     << "value was" << i;
       ad_exit(22);
     }
   #endif
   return m[i];
 }
#endif
#endif
void AAsvs(void){/*int x=1;*/}
