/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/** Square of a number; constant object.
\ingroup misc
\param m Nu,ber to be squared.
\return \f$m^2\f$
*/
   double square( CGNU_DOUBLE m)
   {
     return m*m;
   }

/** Square of a number; constant vector object.
\ingroup misc
\param m vector of numbers to be squared.
\return vector of the same length ad #x containing \f$m_i^2\f$
*/
   dvector square(_CONST dvector& m)
   {
     dvector tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }  

/** Square of a number; constant matrix object.
\ingroup misc
\param m matrix of numbers to be squared.
\return A matrix of the same rank as #m containing \f$m_{ij}^2\f$
*/
   dmatrix square(_CONST dmatrix& m)
   {
     dmatrix tmp;
     tmp.allocate(m);
     for (int i=tmp.rowmin();i<=tmp.rowmax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }  

/** Square of a number; constant 3 dimensionsal array.
\ingroup misc
\param m d3_array of numbers to be squared.
\return A d3_array of the same shape as #m containing \f$m_{ijk}^2\f$
*/
   d3_array square(_CONST d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=square(m(i));
     }
     return tmp;
   }
