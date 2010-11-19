/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
#include "fvar.hpp"
#include "admb_messages.h"

#if !defined(OPT_LIB)
 dvector& dmatrix::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i < rowmin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "dvector& dmatrix::operator[] (int i)", rowmin(), rowmax(), i);
     }
     if (i > rowsize()+rowmin()-1)
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high", "dvector& dmatrix::operator[] (int i)", rowmin(), rowmax(), i);
     }
   #endif
   return *(m+i);
 }

#ifdef USE_CONST
 _CONST dvector& dmatrix::operator[] (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dmatrix::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowsize()+rowmin()-1)
     {
       cerr << "matrix bound exceeded -- row index too high in dmatrix::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return *(m+i);
 }
#endif
#endif
