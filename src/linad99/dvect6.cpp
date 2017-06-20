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
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
#endif

#include <math.h>

void shape_check(const dvector& v1, const dvector& v2,
  const char *function_name);

/**
Returns dvector with sine for each value of vec.

\param vec array of floating values
 */
dvector sin(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::sin(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with cosine for each value of vec.

\param vec array of floating values
 */
dvector cos(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::cos(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with tangent for each value of vec.

\param vec array of floating values
 */
dvector tan(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::tan(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with hyperbolic sine for each value of vec.

\param vec array of floating values
*/
dvector sinh(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::sinh(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with hyperbolic cosine for each value of vec.

\param vec array of floating values
*/
dvector cosh(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::cosh(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with hyperbolic tangent for each value of vec.

\param vec array of floating values
*/
dvector tanh(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::tanh(vec.elem(i));
  }
  return results;
}
/**
Returns a dvector with base raised to the power exponent for each element in
exponents.

\param base array of floating values
\param exponent a floating value
*/
dvector pow(const dvector& bases, const double exponent)
{
  dvector results(bases.indexmin(), bases.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::pow(bases.elem(i), exponent);
  }
  return results;
}
/**
Returns a dvector with base raised to the power exponent for each element in
exponents.

\param base array of floating values
\param exponent a integer
*/
dvector pow(const dvector& bases, int exponent)
{
  dvector results(bases.indexmin(), bases.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::pow(bases.elem(i), exponent);
  }
  return results;
}
/**
Returns a dvector with each element from bases is raised to the power
 exponent for each element in exponents.

\param base array of floating values
\param exponents array of floating values
*/
dvector pow(const dvector& bases, const dvector& exponents)
{
  shape_check(bases, exponents,
    "dvector pow(const dvector& bases ,constdvector& exponents)");

  dvector results(bases.indexmin(), bases.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::pow(bases.elem(i), exponents.elem(i));
  }
  return results;
}
/**
Returns a dvector with base raised to the power exponent for each element in
exponents.

\param base double
\param exponents array of floating points
*/
dvector pow(const double base, const dvector& exponents)// ***
{
  dvector results(exponents.indexmin(), exponents.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::pow(base, exponents.elem(i));
  }
  return results;
}
/**
Returns dvector with principal value of the arc sine of vec,
expressed in radians.

\param vec scalar vector
*/
dvector asin(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::asin(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with principal value of the arc cosine of vec,
expressed in radians.

\param vec scalar vector
*/
dvector acos(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::acos(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with principal value of the arc tangent of vec,
expressed in radians.

\param vec scalar vector
*/
dvector atan(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::atan(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with the common (base-10) logarithm of vec.

\param vec scalar vector
*/
dvector log10(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::log10(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with the square of each element in vec.

\param vec scalar vector
*/
dvector sqrt(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::sqrt(vec.elem(i));
  }
  return results;
}
/**
Returns dvector with the square of each element in vec.

\param vec scalar vector
*/
dvector sqr(const dvector& vec)
{
  dvector results(vec.indexmin(), vec.indexmax());
  for (int i = results.indexmin(); i <= results.indexmax(); ++i)
  {
    results.elem(i) = std::pow(vec.elem(i), 2);
  }
  return results;
}
