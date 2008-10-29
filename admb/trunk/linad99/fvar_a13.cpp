
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

#include <stdlib.h>
#if defined(__TURBOC__) && !defined(__linux__)
   #include <alloc.h>
#endif


 dvar_vector::dvar_vector(int ncl,int nch,kkludge_object kg)
 {
   va=NULL;
   allocate(ncl,nch);

   #ifdef DIAG
     cout << " Allocating dvar_vector with ptr_address\n  "
         << &va << "  pointing at  " << (va+indexmin()) << "\n";
   #endif
 }
#undef HOME_VERSION
