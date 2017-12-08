/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

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

\param value double
*/
dmatrix& dmatrix::operator=(const double value)
{
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i) = value;
  }
  return *this;
}
/**
Divide value to all elements in dmatrix.

\param value double
*/
dmatrix& dmatrix::operator/=(const double value)
{
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i) /= value;
  }
  return *this;
}
/**
Multiply value to all elements in dmatrix.

\param value double
*/
dmatrix& dmatrix::operator*=(const double value)
{
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i) *= value;
  }
  return *this;
}
