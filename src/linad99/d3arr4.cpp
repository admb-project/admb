/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/** \file
    Code for computing square of various constant objects.

 */
#include "fvar.hpp"

/** Square of a number; constant object.
\ingroup misc
\param m Number to be squared.
\return \f$m^2\f$
*/
double square(const double m)
{
  return m * m;
}

/** Square of elements in a vector; constant vector object.
\ingroup misc
\param m Vector of constant object to be squared.
\return vector of the same length as #m containing \f$m_i^2\f$
*/
dvector square(const dvector& m)
   {
     dvector tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }

ivector square(const ivector& v)
{
  ivector tmp;
  tmp.allocate(v);
  for (int i = tmp.indexmin(); i <= tmp.indexmax(); i++)
  {
       tmp(i) = v(i) * v(i);
  }
  return tmp;
}

/** Square of a elements in a matrix; constant matrix object.
\ingroup misc
\param m matrix of numbers to be squared.
\return A matrix of the same rank as #m containing \f$m_{ij}^2\f$
*/
dmatrix square(const dmatrix& m)
   {
     dmatrix tmp;
     tmp.allocate(m);
     for (int i=tmp.rowmin();i<=tmp.rowmax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }

/** Square of elements in a 3-dimensional array; constant 3-dimensionsal array.
\ingroup misc
\param m d3_array of numbers to be squared.
\return A d3_array of the same shape as #m containing \f$m_{ijk}^2\f$
*/
d3_array square(const d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }
