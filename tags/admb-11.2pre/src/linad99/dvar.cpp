/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
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
double sigmoid(const double v1)
 {
   return(atan(v1)/2.8);
 }
