/*
 * $Id: lvec2.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdlib.h>

#ifndef OPT_LIB
#ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
 _CONST AD_LONG_INT& lvector::operator[] (int i) _CONST 
 {
   #ifdef SAFE_ARRAYS
     if (i>indexmax())
     {
       cerr << "array bound exceeded -- index too high in lvector::operator[]";
       ad_exit(1);
     }
     
     if (i<indexmin())
     {
       cerr << "array bound exceeded -- index too low in lvector::operator[]";
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }

/**
 * Description not yet available.
 * \param
 */
  _CONST AD_LONG_INT& lvector::operator() (int i) _CONST 
 {
   #ifdef SAFE_ARRAYS
     if (i>indexmax())
     {
       cerr << "array bound exceeded -- index too high in lvector::operator[]";
       ad_exit(1);
     }
     
     if (i<indexmin())
     {
       cerr << "array bound exceeded -- index too low in lvector::operator[]";
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }
#endif
#endif

void f63hhh(void){/*int x=1;*/}
