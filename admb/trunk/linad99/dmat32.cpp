#define HOME_VERSION
#include "fvar.hpp"
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#if !defined(OPT_LIB)

#  ifdef USE_CONST
 _CONST dvector& dmatrix::operator() (int i)  _CONST
 {
#    ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dmatrix::operator()"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in dmatrix::operator()"
             << "value was" << i;
       ad_exit(22);
     }
#    endif
   return *(m+i);
 }

#  endif
#endif

#undef HOME_VERSION
