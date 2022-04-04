/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function to compute sigmoid.
*/

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
Returns computed sigmoid value at v1.

@param v1 value
@return computed sigmoid value
*/
double sigmoid(const double v1)
{
  return(atan(v1)/2.8);
}
