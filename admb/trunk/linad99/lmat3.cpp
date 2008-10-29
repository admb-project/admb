
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

 void lmatrix::initialize (void)
 {
   for (int i=rowmin();i<=rowmax();i++)
   {
     (*this)(i).initialize();
   }
 }
#undef HOME_VERSION
