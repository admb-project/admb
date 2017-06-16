/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"

/** \ingroup matop
Transpose of a matrix; constant objects.
\param m1 The matrix,\f$M\f$, to be transposed.
\return \f$M^T\f$
*/
dmatrix trans(const dmatrix& m1)
{
  dmatrix tmp(m1.colmin(), m1.colmax(), m1.rowmin(), m1.rowmax());

  for (int i = m1.rowmin(); i <= m1.rowmax(); ++i)
  {
    for (int j = m1.colmin(); j <= m1.colmax(); ++j)
    {
      tmp[j][i] = m1[i][j];
    }
  }
  return tmp;
}
/** \ingroup matop
Norm of a matrix; constant object.
\param m1 a matrix, \f$M\f$
\return \f$||M||\f$
*/
double norm(const dmatrix& m1)
{
  double tmp = 0;
  for (int i = m1.rowmin(); i <= m1.rowmax(); ++i)
  {
    tmp += norm2(m1.elem(i));
  }
  return sqrt(tmp);
}
/** \ingroup matop
Norm squared of a matrix; constant object.
\param m1 a matrix, \f$M\f$
\return \f$||M||^2\f$
*/
double norm2(const dmatrix& m1)
{
  double tmp = 0;
  for (int i = m1.rowmin(); i <= m1.rowmax(); ++i)
  {
    tmp += norm2(m1.elem(i));
  }
  return tmp;
}
/** \ingroup matop
Calls norm2.
\param m1 a matrix, \f$M\f$
\return norm2 of m1
*/
double sumsq(const dmatrix& m1) { return norm2(m1); }
