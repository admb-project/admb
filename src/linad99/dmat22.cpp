/**
 * \file
 *
 * Constructors, destructors and misc functions involving class dvariable
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <stdio.h>
#include <math.h>
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

/**
Assign value x to all elements in dmatrix.
*/
dmatrix& dmatrix::operator=(const double x)
{
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i) = x;
  }
  return *this;
}
/**
Divide value x to all elements in dmatrix.
*/
dmatrix& dmatrix::operator/=(const double x)
{
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i) /= x;
  }
  return *this;
}
/**
Multiply value x to all elements in dmatrix.
*/
dmatrix& dmatrix::operator*=(const double x)
{
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i) *= x;
  }
  return *this;
}
