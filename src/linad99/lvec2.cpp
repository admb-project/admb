/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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

void f63hhh(void){int x=1;}

