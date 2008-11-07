/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
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
