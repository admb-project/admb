#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
// file fvar_fn.cpp
// math.h functions involving prevariables
#include "fvar.hpp"


#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
   #include <iomanip.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
   #include <iomanip.hpp>
#endif

#include <stdio.h>
#include <math.h>

 double sigmoid( CGNU_DOUBLE v1)
 {
   return(atan(v1)/2.8);
 }
#undef HOME_VERSION
