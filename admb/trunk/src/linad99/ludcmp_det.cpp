/*
 * $Id$
 *
 * Copyright (c) 2009-2011 ADMB Foundation
 */
/**
 * \file
 * This file contains the routines necessary to compute
 * the determinate of a matrix
 */

#include <fvar.hpp>

dvariable ln_det(const dvar_matrix & aa, const int &_sgn);
double ln_det(_CONST dmatrix & m1, BOR_CONST int &_sgn);


/** Determinaant of matrix.
    \param aa dvar_matrix containing a square matrix,\f$A\f$.
    \return \f$\det(A)\f$.
*/
dvariable det(const dvar_matrix & aa)
{
   int sign = 0;
   dvariable lndet = 0.0;
   dvariable determ = 0.0;
   dvar_matrix mat;
   mat = aa;

   lndet = ln_det(mat, sign);
   determ = exp(lndet);
   return determ;
}

/** Compute determinant of a constant matrix.
    \ingroup matop
    \param m1 A dmatrix, \f$M\f$, for which the determinant is computed.
    \return A double containing \f$|M|\f$.
*/
double det(_CONST dmatrix & m1)
{
   int sign = 0;
   double lndet = 0.0;
   double determ = 0.0;
   dmatrix mat;
   mat = m1;

   lndet = ln_det(mat, sign);
   determ = exp(lndet);
   return determ;
}
