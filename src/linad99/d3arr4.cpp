/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

/** \file
Code for computing square of various constant objects.
*/
#include "fvar.hpp"

/**Return square of value; constant object.
\ingroup misc
\param value to be squared.
\return \f$value^2\f$
*/
double square(const double value)
{
  return value * value;
}
/**
Return dvector results of squaring elements in a values;
constant vector object.

\ingroup misc
\param values of constant object to be squared.
\return vector of the same length as #values containing \f$values_i^2\f$
*/
dvector square(const dvector& values)
{
  dvector results;
  results.allocate(values);
  for (int i = values.indexmin(); i <= values.indexmax(); ++i)
  {
    results(i) = square(values(i));
  }
  return results;
}
/**
Return dvector results of squaring elements in a values;
constant vector object.

\ingroup misc
\param values of constant object to be squared.
\return vector of the same length as #values containing \f$values_i^2\f$
*/
ivector square(const ivector& values)
{
  ivector results;
  results.allocate(values);
  for (int i = values.indexmin(); i <= values.indexmax(); ++i)
  {
    results(i) = values(i) * values(i);
  }
  return results;
}
/** Square of a elements in a matrix; constant matrix object.
\ingroup misc
\param m matrix of numbers to be squared.
\return A matrix of the same rank as #a containing \f$a_{ij}^2\f$
*/
dmatrix square(const dmatrix& a)
{
  dmatrix results;
  results.allocate(a);
  for (int i = results.rowmin(); i <= results.rowmax(); ++i)
  {
    results(i) = square(a(i));
  }
  return results;
}
/** Square of elements in a 3-dimensional array; constant 3-dimensionsal array.
\ingroup misc
\param m d3_array of numbers to be squared.
\return A d3_array of the same shape as #a containing \f$a_{ijk}^2\f$
*/
d3_array square(const d3_array& a)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = square(a(i));
  }
  return results;
}
