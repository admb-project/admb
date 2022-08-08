/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"
#include <cmath>

#ifdef __TURBOC__
  #pragma hdrstop
#endif

void shape_check(const dvector& v1, const dvector& v2,
  const char *function_name);

/**
Returns dvector with sine for each value of vec.

\param vec array of floating values
 */
dvector sin(const dvector& vec)
{
  int min = vec.indexmin();
  int max = vec.indexmax();
  dvector results(min, max);
  double* presultsi = results.get_v() + min;
  double* pveci = vec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = std::sin(*pveci);

    ++presultsi;
    ++pveci;
  }
  return results;
}
/**
Returns dvector with cosine for each value of vec.

\param vec array of floating values
 */
dvector cos(const dvector& vec)
{
  int min = vec.indexmin();
  int max = vec.indexmax();
  dvector results(min, max);
  double* presultsi = results.get_v() + min;
  double* pveci = vec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = std::cos(*pveci);

    ++presultsi;
    ++pveci;
  }
  return results;
}
/**
Returns dvector with tangent for each value of vec.

\param vec array of floating values
 */
dvector tan(const dvector& vec)
{
  int min = vec.indexmin();
  int max = vec.indexmax();
  dvector results(min, max);
  double* presultsi = results.get_v() + min;
  double* pveci = vec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = std::tan(*pveci);

    ++presultsi;
    ++pveci;
  }
  return results;
}
/**
Returns dvector with hyperbolic sine for each value of vec.

\param vec array of floating values
*/
dvector sinh(const dvector& vec)
{
  int min = vec.indexmin();
  int max = vec.indexmax();
  dvector results(min, max);
  double* presultsi = results.get_v() + min;
  double* pveci = vec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = std::sinh(*pveci);

    ++presultsi;
    ++pveci;
  }
  return results;
}
/**
Returns dvector with hyperbolic cosine for each value of vec.

\param vec array of floating values
*/
dvector cosh(const dvector& vec)
{
  int min = vec.indexmin();
  int max = vec.indexmax();
  dvector results(min, max);
  double* presultsi = results.get_v() + min;
  double* pveci = vec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = std::cosh(*pveci);

    ++presultsi;
    ++pveci;
  }
  return results;
}
/**
Returns dvector with hyperbolic tangent for each value of vec.

\param vec array of floating values
*/
dvector tanh(const dvector& vec)
{
  int min = vec.indexmin();
  int max = vec.indexmax();
  dvector results(min, max);
  double* presultsi = results.get_v() + min;
  double* pveci = vec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = std::tanh(*pveci);

    ++presultsi;
    ++pveci;
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
  int min = bases.indexmin();
  int max = bases.indexmax();
  dvector results(min, max);
  double* presultsi = results.get_v() + min;
  double* pbasesi = bases.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = std::pow(*pbasesi, exponent);

    ++presultsi;
    ++pbasesi;
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
  int min = bases.indexmin();
  int max = bases.indexmax();
  dvector results(min, max);
  double* presultsi = results.get_v() + min;
  double* pbasesi = bases.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *presultsi = std::pow(*pbasesi, exponent);

    ++presultsi;
    ++pbasesi;
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
    double x = vec.elem(i);
    results.elem(i) = x * x;
  }
  return results;
}
