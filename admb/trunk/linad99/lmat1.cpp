
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

#if !defined(OPT_LIB)
 lvector& lmatrix::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in lmatrix::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowsize()+rowmin()-1)
     {
       cerr << "matrix bound exceeded -- row index too high in lmatrix::operator[]"
            << "value was" << i;
       ad_exit(22);
     }
   #endif
   return m[i];
 }


#ifdef USE_CONST
 _CONST lvector& lmatrix::operator() (int i) _CONST 
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in lmatrix::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowsize()+rowmin()-1)
     {
       cerr << "matrix bound exceeded -- row index too high in lmatrix::operator[]"
            << "value was" << i;
       ad_exit(22);
     }
   #endif
   return m[i];
 }
#endif
#endif

#undef HOME_VERSION
