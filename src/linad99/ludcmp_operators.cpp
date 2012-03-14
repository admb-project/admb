/*
 * $Id$
 *
 * Copyright (c) 2009-2011 ADMB Foundation
 */
/**
 * \file
 * LU Decomposition operators.
 */
#include <ludcmp.hpp>
/**
 * Multiplication operator
 */
double operator *
   (const dvector_for_adjoint & v, const dvector_for_adjoint & w)
{
   double tmp = 0.0;
   int mmin = v.indexmin();
   int mmax = v.indexmax();
   for (int i = mmin; i <= mmax; i++)
   {
      tmp += v(i) * w(i);
   }
   return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector operator *(double x, const dvector_for_adjoint & w)
{
   int mmin = w.indexmin();
   int mmax = w.indexmax();
   dvector tmp(mmin, mmax);
   tmp.initialize();
   for (int i = mmin; i <= mmax; i++)
   {
      tmp(i) = x * w(i);
   }
   return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix get_dmatrix(cltudecomp & clu)
{
   int mmin = clu.indexmin();
   int mmax = clu.indexmax();
   dmatrix tmp(mmin, mmax, mmin, mmax);
   tmp.initialize();
   for (int i = mmin; i <= mmax; i++)
   {
      for (int j = mmin; j <= mmax; j++)
      {
	 tmp(i, j) = clu(i, j);
      }
   }
   return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix get_dmatrix(cltudecomp_for_adjoint & clu)
{
   int mmin = clu.indexmin();
   int mmax = clu.indexmax();
   dmatrix tmp(mmin, mmax, mmin, mmax);
   tmp.initialize();
   for (int i = mmin; i <= mmax; i++)
   {
      for (int j = mmin; j <= mmax; j++)
      {
	 tmp(i, j) = clu(i, j);
      }
   }
   return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix get_lower_matrix(cltudecomp_for_adjoint & clu)
{
   int mmin = clu.indexmin();
   int mmax = clu.indexmax();
   dmatrix tmp(mmin, mmax, mmin, mmax);
   tmp.initialize();
   for (int i = mmin; i <= mmax; i++)
   {
      tmp(i, i) = 1.0;
      for (int j = mmin; j < i; j++)
      {
	 tmp(i, j) = clu(i, j);
      }
   }
   return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix get_upper_matrix(cltudecomp_for_adjoint & clu)
{
   int mmin = clu.indexmin();
   int mmax = clu.indexmax();
   dmatrix tmp(mmin, mmax, mmin, mmax);
   tmp.initialize();
   for (int i = mmin; i <= mmax; i++)
   {
      for (int j = i; j <= mmax; j++)
      {
	 tmp(i, j) = clu(i, j);
      }
   }
   return tmp;
}
