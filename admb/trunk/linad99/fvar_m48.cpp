#define HOME_VERSION
//#undef OPT_LIB
#include "fvar.hpp"
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD

#if !defined(OPT_LIB)

#ifdef USE_CONST
 _CONST dvar_vector& dvar_matrix::operator() (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dvar_matrix::operator()"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in dvar_matrix::operator()"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return (m[i]);
 }
#endif
#endif
#undef HOME_VERSION


