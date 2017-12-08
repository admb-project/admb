/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <fvar.hpp>

/** \ingroup matop
Norm of a vector; constant objects.
\param t1 A vector, \f$v\f$.
\returns \f$||v|| = (v\times v)^{1/2} = (\sum_i v_i^2)^{1/2}\f$
*/
double norm(const dvector& t1)
{
  double tmp = t1 * t1;
  if (tmp > 0)
  {
    tmp = pow(tmp,.5);
  }
  return tmp;
}
/** \ingroup matop
Squared norm of a vector; constant objects.
Computes the sum of squares of its vector argument.
\param t1 A vector, \f$v\f$.
\returns \f$||v||^2 = v\times v = \sum_i v_i^2\f$
*/
double norm2(const dvector& t1)
{
  double tmp = t1 * t1;
  return tmp;
}
double sumsq(const dvector& t1) { return norm2(t1); }
