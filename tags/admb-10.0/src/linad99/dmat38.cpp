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

#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#if defined (__WAT32__)
  #include <iostream.h>
  #include <strstrea.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include "ludcmp.hpp"

cltudecomp ludecomp_pivot(const dmatrix & M);

/** Solve a linear system using LU decomposition.
    \param aa A constant matrix. \f$A\f$. 
    \param z A matrix containing the RHS, \f$B\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A matrix containing solution \f$X\f$.
*/
dmatrix solve(const dmatrix & aa, const dmatrix & zz)
{
   int n = aa.colsize();
   int lb = aa.colmin();
   int ub = aa.colmax();
   if (lb != aa.rowmin() || ub != aa.colmax())
   {
      cerr << "Error matrix not square in"
           << "solve(const dmatrix & aa, const dmatrix & z)" << endl;
      ad_exit(1);
   }
   dmatrix bb(lb, ub, lb, ub);
   bb = aa;
   cltudecomp dcmp;
   dcmp = ludecomp_pivot(bb);
   ivector index2 = dcmp.get_index2();

   //check if invertable
   int i;
   double det = 1.0;
   for (i = lb; i <= ub; i++)
   {
      det *= dcmp(i, i);
   }
   if (det == 0.0)
   {
      cerr <<
	 "Error in matrix inverse -- matrix singular in solve(dmatrix)\n";
      ad_exit(1);
   }

   //for each column of X and B solve A*x_i = b_i
   dmatrix xx(lb,ub,lb,ub);
   for(int k=lb;k<=ub;k++)
   {
     dvector z = column(zz,k);

     //Solve L*y=b with forward-substitution (before solving Ux=y)
     dvector y(lb, ub);
     for (i = lb; i <= ub; i++)
     {
        double tmp = 0.0;
        for (int j = lb; j < i; j++)
        {
	   tmp += dcmp(i, j) * y(j);
        }
        y(i) = z(index2(i)) - tmp;
     }

     //Now solve U*x=y with back substitution
     dvector x(lb, ub);
     for (i = ub; i >= lb; i--)
     {
        double tmp = 0.0;
        for (int j = ub; j > i; j--)
        {
	   tmp += dcmp(i, j) * x(j);
        }
        x(i) = (y(i) - tmp) / dcmp(i, i);
     }

     xx.colfill(k,x);
   }

   return xx;
}

/**
 * Description not yet available.
 * \param
 */
double ln_det_choleski(
  const banded_symmetric_dmatrix& MM, const int& _ierr)
{
  banded_lower_triangular_dmatrix tmp=choleski_decomp(MM,_ierr);
  
  int mmin=tmp.indexmin();
  int mmax=tmp.indexmax();
  double ld=0.0;
  for (int i=mmin;i<=mmax;i++)
  {
    ld+=log(tmp(i,i));
  }
  return 2.0*ld;
}

/**
 * Description not yet available.
 * \param
 */
double norm(const banded_symmetric_dmatrix& B)
{
  return sqrt(norm2(B));
}

/**
 * Description not yet available.
 * \param
 */
double norm2(const banded_symmetric_dmatrix& B)
{
  double nm=0.0;
  for (int i=1;i<=B.bw-1;i++)
  {
    nm+=norm2(B.d(i));
  }
  nm*=2;
  nm+=norm2(B.d(0));
  return nm;
}
