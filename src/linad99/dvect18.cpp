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
Determine if the lower and upper bounds of two evctors match in a specified
function.
\param v1 a data vector
\param v2 a data vector
\param function_nam a pointer to the name of the function in question.
*/
void shape_check(const dvector& v1, const dvector& v2,
  const char *function_name)
{
  if (v1.indexmin() != v2.indexmin() || v1.indexmax() != v2.indexmax())
  {
    cerr << " Vector sizes do no match in" << function_name << "\n";
    ad_exit(1);
  }
}
