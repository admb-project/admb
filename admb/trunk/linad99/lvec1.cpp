
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
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
 AD_LONG_INT& lvector::operator[] (int i)
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

 AD_LONG_INT& lvector::operator() (int i)
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
void xyw8(void){int x=1;}

#undef HOME_VERSION
