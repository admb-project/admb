/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
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

/**
 * Description not yet available.
 * \param
 */
 void shape_check(_CONST dvector& v1,_CONST dvector& v2, const char * function_name)
 {
   if (v1.indexmin() != v2.indexmin() || v1.indexmax() != v2.indexmax())
   {
     cerr << " Vector sizes do no match in" << function_name << "\n";
     ad_exit(1);
   }
 }
