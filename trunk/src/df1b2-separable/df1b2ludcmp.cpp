/*
 * $Id$
 *
 * Copyright (c) 2010-2011 ADMB Foundation
 */
/**
 * \file
 * This file contains the routines necessary to compute
 * the LU decomposition of a matrix with random effects.
 */
  #include <df1b2ludcmp.hpp>

/**
 * LU decomp with partial pivoting 
 * \param M \f$M\f$ a constant square matrix to decompose
 * \return a cltudecomp object containg the
 * upper and lower parts of the decomposed matrix
 * as well as an index that keeps track of the
 * pivots.
 */
  df1b2ludecomp ludecomp_pivot(const df1b2matrix & M)
  {
     int i = 0;
     int j = 0;
     int k = 0;
     int mmin = M.indexmin();
     int mmax = M.indexmax();
     int imax = mmax - 1;
     df1b2ludecomp clu(mmin, mmax);
     df1b2vector scale(mmin, mmax);
  
     // get terms for implicit scaling
     for (i = mmin; i <= mmax; i++)
     {
        df1b2variable tmp = 0.0;
        tmp = 1.0 / max(fabs(M(i)));
        if (value(tmp) == 0.0)
        {
  	 cerr << "Error -- trying to take LU decomp of a singular matrix"
  	    << endl;
  	 // use ad_exit() so that debugger can trace this
  	 ad_exit(1);
        }
        scale(i) = 0.0;
        scale(i) = 1.0 / max(fabs(M(i)));
     }
     // get upper and lower parts of LU
     df1b2matrix & alpha = clu.get_L();
     df1b2matrix & gamma = clu.get_U();	// gamma is the transpose of beta
     ivector & index = clu.get_index();
     ivector & index2 = clu.get_index2();
     int sign = clu.get_sign();
     // copy M into alpha and gamma
     for (i = mmin; i <= mmax; i++)
     {
        for (int j = mmin; j <= mmax; j++)
        {
  	 clu(i, j) = M(i, j);
        }
     }
     for (j = mmin; j <= mmax; j++)
     {
        int i = 0;
        for (i = mmin + 1; i < j; i++)
        {
  	 // using subvector here
  	 clu(i, j) -= alpha(i) (mmin, i - 1) * gamma(j) (mmin, i - 1);
        }
        df1b2variable maxterm = 0.0;

        for (i = j; i <= mmax; i++)
        {
  	 // using subvector here
  	 if (j > 1)
  	 {
  	    clu(i, j) -= alpha(i) (mmin, j - 1) * gamma(j) (mmin, j - 1);
  	 }
         df1b2variable tmp = 0.0;
  	 tmp = scale(i) * fabs(clu(i, j));

  	 if (value(tmp) > value(maxterm))
  	 {
  	    maxterm = tmp;
  	    imax = i;
  	 }
        }

        if (j != imax)
        {
  	 // have to do this element-wise
  	 for (k = mmin; k <= mmax; k++)
  	 {
  	    df1b2variable tmp = 0.0;
            tmp = clu(imax, k);
  	    clu(imax, k) = clu(j,k);
  	    clu(j, k) = tmp;
  	 }

  	 scale(imax) = scale(j);
  	 int itmp = index2(imax);
  	 index2(imax) = index2(j);
  	 index2(j) = itmp;
  	 sign = -sign;
        }
        index(j) = imax;

        if (value(clu(j, j)) == 0.0)
  	  clu(j, j) = 1.e-25;
        if (j != mmax)
        {
         df1b2variable z = 0.0;
  	 z = 1.0 / gamma(j, j);
  	 for (i = j + 1; i <= mmax; i++)
  	 {
  	    alpha(i, j) *= z;
  	 }
        }
     }
     return clu;
  }
  //end ludcmp pivoting

/** Solve a linear system using LU decomposition.
    \param aa A df1b2matrix \f$A\f$. 
    \param z A df1b2vector containing the RHS, \f$B\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A df1b2vector containing solution vector \f$X\f$.
*/
df1b2vector solve(const df1b2matrix& aa,const df1b2vector& z)
{
   int n = aa.colsize();
   int lb = aa.colmin();
   int ub = aa.colmax();
   if (lb != aa.rowmin() || ub != aa.colmax())
   {
      cerr << "Error matrix not square in solve(df1b2matrix)" << endl;
      ad_exit(1);
   }
   
   df1b2vector x(lb, ub);
   x.initialize();

   if (ub == lb)
   {
      x(lb) = z(lb) / aa(lb, lb);
      return (x);
   }

   df1b2matrix MC(lb,ub,lb,ub);
   MC=aa;
   df1b2ludecomp dcmp = ludecomp_pivot(MC);
   ivector index2 = dcmp.get_index2();
   df1b2matrix & gamma = dcmp.get_U();
   df1b2matrix & alpha = dcmp.get_L();

   //check if invertable
   df1b2variable det = 1.0;
   for (int i = lb; i <= ub; i++)
   {
      det *= dcmp(i, i);
   }
   if (value(det) == 0.0)
   {
      cerr <<
	 "Error in matrix inverse -- matrix singular in solve(df1b2matrix)\n";
      ad_exit(1);
   }

   //Solve L*y=b with forward-substitution (before solving Ux=y)
   df1b2vector y(lb, ub);
   y.initialize();

   for (int i = lb; i <= ub; i++)
   {
      df1b2variable tmp = 0.0;
      for (int j = lb; j < i; j++)
      {
	 tmp += alpha(i, j) * y(j);
      }
      y(i) = z(index2(i)) - tmp;
   }

   //Now solve U*x=y with back substitution
   for (int i = ub; i >= lb; i--)
   {
      df1b2variable tmp = 0.0;
      for (int j = ub; j > i; j--)
      {
	 tmp += gamma(j, i) * x(j);
      }
      x(i) = (y(i) - tmp) / gamma(i, i);
   }

   return x;
}

/** Solve a linear system using LU decomposition.
    \param aa A df1b2matrix \f$A\f$. 
    \param z A dvector containing the RHS, \f$B\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A df1b2vector containing solution vector \f$X\f$.
*/
df1b2vector solve(const df1b2matrix& aa,const dvector& z)
{
  df1b2vector zz(z.indexmin(),z.indexmax());
  zz.initialize();
  /*for(int i=z.indexmin();i<=z.indexmax();i++)
  {
    zz(i) = 0.0;
    zz(i) = z(i);
  }*/
  zz = z;
  return solve(aa,zz);
}

/** Compute log determinant of a df1b2matrix.
    \param m1 A df1b2matrix, \f$M\f$, for which the determinant is computed.
    \return A df1b2matrix containing \f$|\log(M)|\f$.
*/
df1b2variable ln_det(const df1b2matrix & m1)
{
   int mmin = m1.indexmin();
   int mmax = m1.indexmax();

   df1b2matrix M(mmin,mmax,mmin,mmax);
   M = m1;
   df1b2ludecomp clu1 = ludecomp_pivot(M);

   int sign = clu1.get_sign();
   ivector index2 = clu1.get_index2();
   df1b2variable lndet = 0.0;
   df1b2matrix & gamma = clu1.get_U();
   df1b2matrix & alpha = clu1.get_L();

   // only need to save the diagonal of gamma
   for (int i = mmin; i <= mmax; i++)
   {
      if (value(gamma(i, i)) < 0.0)
      {
	 sign = -sign;
	 lndet += log(-gamma(i, i));
      } else
      {
	 lndet += log(gamma(i, i));
      }
   }
   return lndet;
}

/** Solve a linear system using LU decomposition.
    \param aa A df1b2matrix \f$A\f$. 
    \param z A dvector containing the RHS, \f$B\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A df1b2vector containing solution vector \f$X\f$.

    On return ln_unsigned_det will contain \f$|\log(A)|\f$.
*/
df1b2vector solve(const df1b2matrix & aa, const df1b2vector & z,
      df1b2variable & ln_unsigned_det,
      const df1b2variable & _sign)
{
   ADUNCONST(df1b2variable, sign)
   sign = 0.0;
   df1b2variable lndet = ln_det(aa);
   ln_unsigned_det = lndet;
   //df1b2variable sign = 0.0;
   //_sign = sign;

   df1b2vector sol = solve(aa, z);
   return sol;
}
