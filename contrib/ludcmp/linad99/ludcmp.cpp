/*
 * $Id$
 *
 * Copyright (c) 2009-2012 ADMB Foundation
 */
/**
 * \file
 * This file contains the routines necessary to compute
 * the LU decomposition of a matrix
 */

#include <ludcmp.hpp>

dmatrix ludecomp_for_adjoint(const dmatrix & M, const cltudecomp & dfclu);
cltudecomp ludecomp_pivot(const dmatrix & M);
dmatrix ludecomp_pivot_for_adjoint(const dmatrix & M,
				   const cltudecomp & dfclu,
				   const ivector & index2);

/**
 * LU Decomposition of a Matrix
 * \param M \f$M\f$ a square matrix to decompose
 * \return a cltudecomp object containg the
 * upper and lower parts of the decomposed matrix
 */
cltudecomp ludecomp(const dmatrix & M)
{
   int mmin = M.indexmin();
   int mmax = M.indexmax();
   cltudecomp clu(mmin, mmax);

   // get upper and lower parts of LU
   dmatrix & alpha = clu.get_L();
   dmatrix & gamma = clu.get_U();	// gamma is the transpose of beta
   // copy M into alpha and gamma
   for (int i = mmin; i <= mmax; i++)
   {
      for (int j = mmin; j <= mmax; j++)
      {
	 clu(i, j) = M(i, j);
      }
   }
   for (int j = mmin; j <= mmax; j++)
   {
      int i = 0;
      for (i = mmin + 1; i < j; i++)
      {
	 // using subvector here
	 clu(i, j) -= alpha(i) (mmin, i - 1) * gamma(j) (mmin, i - 1);
      }
      for (i = j; i <= mmax; i++)
      {
	 // using subvector here
	 if (j > 1)
	 {
	    clu(i, j) -= alpha(i) (mmin, j - 1) * gamma(j) (mmin, j - 1);
	 }
      }
      if (j != mmax)
      {
	 double z = 1.0 / gamma(j, j);
	 for (i = j + 1; i <= mmax; i++)
	 {
	    alpha(i, j) *= z;
	 }
      }
   }
   return clu;
}

/**
 * Adjoint code for the ludecomp
 * \param _M
 * \param _dfclu
 */
dmatrix ludecomp_for_adjoint(const dmatrix & _M, const cltudecomp & _dfclu)
{
   ADUNCONST(dmatrix, M)
   ADUNCONST(cltudecomp, dfclu)
   int mmin = M.indexmin();
   int mmax = M.indexmax();
   cltudecomp_for_adjoint clu(mmin, mmax, 3, 2);

   // get upper and lower parts of LU
   dmatrix_for_adjoint & alpha = clu.get_L();
   dmatrix_for_adjoint & gamma = clu.get_U();	// gamma is the transpose of beta
   dmatrix & dfalpha = dfclu.get_L();
   dmatrix & dfgamma = dfclu.get_U();
   // copy M into alpha and gamma
   // OUTER LOOP1
   int i = 0;
   int j = 0;
   for (i = mmin; i <= mmax; i++)
   {
      for (int j = mmin; j <= mmax; j++)
      {
	 clu(i, j) = M(i, j);
      }
   }
   // OUTER LOOP2
   for (j = mmin; j <= mmax; j++)
   {
      int i = 0;
      // INNER LOOP 2 1
      for (i = mmin + 1; i < j; i++)
      {
	 // using subvector here
	 //clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
	 double tmp =
	    clu(i, j) - alpha(i) (mmin, i - 1) * gamma(j) (mmin, i - 1);
	 clu.increment(i, j);
	 clu(i, j) = tmp;
      }
      // INNER LOOP 2 2
      for (i = j; i <= mmax; i++)
      {
	 // using subvector here
	 if (j > 1)
	 {
	    //clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
	    double tmp =
	       clu(i, j) - alpha(i) (mmin, j - 1) * gamma(j) (mmin, j - 1);
	    clu.increment(i, j);
	    clu(i, j) = tmp;
	 }
      }
      // INNER LOOP 2 3
      if (j != mmax)
      {
	 double z = 1.0 / gamma(j, j);
	 for (i = j + 1; i <= mmax; i++)
	 {
	    double tmp = alpha(i, j);
	    clu.increment(i, j);
	    alpha(i, j) = tmp * z;
	 }
      }
   }

   // OUTER LOOP2
   //for (int j=mmin;j<=mmax;j++)
   for (j = mmax; j >= mmin; j--)
   {
      int i = 0;
      // INNER LOOP 2 3
      if (j != mmax)
      {
	 // need to keep this line for  z
	 double z = 1.0 / gamma(j, j);
	 //for (i=j+1;i<=mmax;i++)
	 double dftmp = 0.0;
	 double dfz = 0.0;
	 for (i = mmax; i >= j + 1; i--)
	 {
	    // need to keep this line for tmp 
	    clu.decrement(i, j);
	    double tmp = alpha(i, j);
	    //alpha(i,j)=tmp*z;
	    dftmp += dfalpha(i, j) * z;
	    dfz += dfalpha(i, j) * tmp;
	    dfalpha(i, j) = 0.0;
	    //double tmp=alpha(i,j);
	    dfalpha(i, j) = dftmp;
	    dftmp = 0.0;
	 }
	 //double z= 1.0/gamma(j,j);
	 dfgamma(j, j) -= dfz / square(gamma(j, j));
	 dfz = 0.0;

      }
      // INNER LOOP 2 2
      //for (i=j;i<=mmax;i++)
      double dftmp = 0.0;
      for (i = mmax; i >= j; i--)
      {
	 // using subvector here
	 if (j > 1)
	 {
	    //clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
	    //double tmp=clu(i,j)-alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
	    //clu.increment(i,j);
	    //clu(i,j)=tmp;
	    clu.decrement(i, j);
	    dftmp = dfclu(i, j);
	    dfclu(i, j) = 0.0;
	    dfclu(i, j) = dftmp;
	    dfalpha(i) (mmin, j - 1) -= dftmp * gamma(j) (mmin, j - 1);
	    dfgamma(j) (mmin, j - 1) -= dftmp * alpha(i) (mmin, j - 1);
	    dftmp = 0.0;
	 }
      }
      // INNER LOOP 2 1
      //for (i=mmin+1;i<j;i++)
      for (i = j - 1; i >= mmin + 1; i--)
      {
	 // using subvector here
	 //clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
	 //double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
	 //clu.increment(i,j);
	 //clu(i,j)=tmp;
	 clu.decrement(i, j);
	 dftmp = dfclu(i, j);
	 dfclu(i, j) = 0.0;
	 //double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
	 dfclu(i, j) = dftmp;
	 dfalpha(i) (mmin, i - 1) -= dftmp * gamma(j) (mmin, i - 1);
	 dfgamma(j) (mmin, i - 1) -= dftmp * alpha(i) (mmin, i - 1);
	 dftmp = 0.0;
      }
   }
   // OUTER LOOP1
   dmatrix dfM(mmin, mmax, mmin, mmax);
   for (i = mmin; i <= mmax; i++)
   {
      for (int j = mmin; j <= mmax; j++)
      {
	 //clu(i,j)=M(i,j);
	 dfM(i, j) = dfclu(i, j);
      }
   }
   return dfM;
}


/**
 * LU decomp with partial pivoting 
 * \param M \f$M\f$ a constant square matrix to decompose
 * \return a cltudecomp object containg the
 * upper and lower parts of the decomposed matrix
 * as well as an index that keeps track of the
 * pivots.
 */
cltudecomp ludecomp_pivot(const dmatrix & M)
{
   int i = 0;
   int j = 0;
   int k = 0;
   int mmin = M.indexmin();
   int mmax = M.indexmax();
   int imax = mmax - 1;
   cltudecomp clu(mmin, mmax);
   dvector scale(mmin, mmax);
   scale.initialize();

   // get terms for implicit scaling
   for (i = mmin; i <= mmax; i++)
   {
      double tmp = 1.0 / max(fabs(M(i)));
      if (tmp == 0.0)
      {
	 cerr << "Error -- trying to take LU decomp of a singular matrix"
	    << endl;
	 // use ad_exit() so that debugger can trace this
	 ad_exit(1);
      }
      scale(i) = 1.0 / max(fabs(M(i)));
   }
   // get upper and lower parts of LU
   dmatrix & alpha = clu.get_L();
   dmatrix & gamma = clu.get_U();	// gamma is the transpose of beta
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
      int i;
      for (i = mmin + 1; i < j; i++)
      {
	 // using subvector here
	 clu(i, j) -= alpha(i) (mmin, i - 1) * gamma(j) (mmin, i - 1);
      }
      double maxterm = 0.0;

      for (i = j; i <= mmax; i++)
      {
	 // using subvector here
	 if (j > 1)
	 {
	    clu(i, j) -= alpha(i) (mmin, j - 1) * gamma(j) (mmin, j - 1);
	 }
	 double tmp = scale(i) * fabs(clu(i, j));
      cout << "";
	 if (tmp > maxterm)
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
	    double tmp = clu(imax, k);
	    clu(imax, k) = clu(j, k);
	    clu(j, k) = tmp;
	 }
	 scale(imax) = scale(j);
	 int itmp = index2(imax);
	 index2(imax) = index2(j);
	 index2(j) = itmp;
	 sign = -sign;
      }
      index(j) = imax;

      if (clu(j, j) == 0.0)
	 clu(j, j) = eps;
      if (j != mmax)
      {
	 double z = 1.0 / gamma(j, j);
	 for (i = j + 1; i <= mmax; i++)
	 {
	    alpha(i, j) *= z;
	 }
      }
   }
   return clu;
}

/**
 * LU decomp with partial pivoting 
 * \param M \f$M\f$ a variable square matrix to decompose
 * \return a cltudecomp object containg the
 * upper and lower parts of the decomposed matrix
 * as well as an index that keeps track of the
 * pivots.
 *
 * This one does not save to the stack automatically. The
 * solve function makes call to savetostack to do this.
 */
cltudecomp xludecomp_pivot_for_expm_solve(const dvar_matrix& M, const ivector& _index2)
{
   ivector& index2 = (ivector&) _index2;
   int i = 0;
   int j = 0;
   int k = 0;
   int mmin = M.indexmin();
   int mmax = M.indexmax();
   //int imax = mmin - 1;
   int imax = mmax - 1;
   cltudecomp clu(mmin, mmax);
   dvector scale(mmin, mmax);
   scale.initialize();

   // get terms for implicit scaling
   for (i = mmin; i <= mmax; i++)
   {
      double tmp = 1.0 / value(max(fabs(M(i))));
      if (tmp == 0.0)
      {
	 cerr << "Error -- trying to take LU decomp of a singular matrix"
	    << endl;
	 // use ad_exit() so that debugger can trace this
	 ad_exit(1);
      }
      scale(i) = 1.0 / value(max(fabs(M(i))));
   }

   // get upper and lower parts of LU
   dmatrix & alpha = clu.get_L();
   dmatrix & gamma = clu.get_U();	// gamma is the transpose of beta
   ivector & index = clu.get_index();
   index2 = clu.get_index2();
   int sign = clu.get_sign();
   // copy M into alpha and gamma
   for (i = mmin; i <= mmax; i++)
   {
      for (int j = mmin; j <= mmax; j++)
      {
	 clu(i, j) = value(M(i, j));
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
      double maxterm = 0.0;
      for (i = j; i <= mmax; i++)
      {
	 // using subvector here
	 if (j > 1)
	 {
	    clu(i, j) -= alpha(i) (mmin, j - 1) * gamma(j) (mmin, j - 1);
	 }
	 double tmp = scale(i) * fabs(clu(i, j));
	 if (tmp > maxterm)
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
	    double tmp = clu(imax, k);
	    clu(imax, k) = clu(j, k);
	    clu(j, k) = tmp;
	 }
	 scale(imax) = scale(j);
	 int itmp = index2(imax);
	 index2(imax) = index2(j);
	 index2(j) = itmp;
	 sign = -sign;
      }
      index(j) = imax;
      if (clu(j, j) == 0.0)
	 clu(j, j) = eps;
      if (j != mmax)
      {
	 double z = 1.0 / gamma(j, j);
	 for (i = j + 1; i <= mmax; i++)
	 {
	    alpha(i, j) *= z;
	 }
      }
   }


   return clu;

}


/**
 * LU decomp with partial pivoting 
 * \param M \f$M\f$ a variable square matrix to decompose
 * \return a cltudecomp object containg the
 * upper and lower parts of the decomposed matrix
 * as well as an index that keeps track of the
 * pivots.
 */
cltudecomp xludecomp_pivot(const dvar_matrix & M)
{
   int i = 0;
   int j = 0;
   int k = 0;
   int mmin = M.indexmin();
   int mmax = M.indexmax();
   //int imax = mmin - 1;
   int imax = mmax - 1;
   cltudecomp clu(mmin, mmax);
   dvector scale(mmin, mmax);
   scale.initialize();

   // get terms for implicit scaling
   for (i = mmin; i <= mmax; i++)
   {
      double tmp = 1.0 / value(max(fabs(M(i))));
      if (tmp == 0.0)
      {
	 cerr << "Error -- trying to take LU decomp of a singular matrix"
	    << endl;
	 // use ad_exit() so that debugger can trace this
	 ad_exit(1);
      }
      scale(i) = 1.0 / value(max(fabs(M(i))));
   }

   // get upper and lower parts of LU
   dmatrix & alpha = clu.get_L();
   dmatrix & gamma = clu.get_U();	// gamma is the transpose of beta
   ivector & index = clu.get_index();
   ivector & index2 = clu.get_index2();
   int sign = clu.get_sign();
   // copy M into alpha and gamma
   for (i = mmin; i <= mmax; i++)
   {
      for (int j = mmin; j <= mmax; j++)
      {
	 clu(i, j) = value(M(i, j));
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
      double maxterm = 0.0;
      for (i = j; i <= mmax; i++)
      {
	 // using subvector here
	 if (j > 1)
	 {
	    clu(i, j) -= alpha(i) (mmin, j - 1) * gamma(j) (mmin, j - 1);
	 }
	 double tmp = scale(i) * fabs(clu(i, j));
	 if (tmp > maxterm)
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
	    double tmp = clu(imax, k);
	    clu(imax, k) = clu(j, k);
	    clu(j, k) = tmp;
	 }
	 scale(imax) = scale(j);
	 int itmp = index2(imax);
	 index2(imax) = index2(j);
	 index2(j) = itmp;
	 sign = -sign;
      }
      index(j) = imax;
      if (clu(j, j) == 0.0)
	 clu(j, j) = eps;
      if (j != mmax)
      {
	 double z = 1.0 / gamma(j, j);
	 for (i = j + 1; i <= mmax; i++)
	 {
	    alpha(i, j) *= z;
	 }
      }
   }

   save_identifier_string("OZ1");
   M.save_dvar_matrix_value();
   M.save_dvar_matrix_position();
   save_identifier_string("OZ2");
   index2.save_ivector_value();
   index2.save_ivector_position();
   save_identifier_string("OZ");
   return clu;
}

  // *************************************************************8
  // *************************************************************8
  //split  ludecomp_pivot_for_adjoint into two parts
  // *************************************************************8
  // *************************************************************8

/**
 * Adjoint code number 1 for the ludecomp with pivoting.
 */
void cltudecomp_for_adjoint::ludecomp_pivot_for_adjoint_1(void)
{
   int i = 0;
   int j = 0;
   verify_identifier_string("OZ");
   ivector_position vpos = restore_ivector_position();
   ivector tmpindx2 = restore_ivector_value(vpos);
   verify_identifier_string("OZ2");
   if (pMpos)
   {
      delete pMpos;
      pMpos = 0;
   }
   pMpos = new dvar_matrix_position(restore_dvar_matrix_position());
   dmatrix M = restore_dvar_matrix_value(*pMpos);
   verify_identifier_string("OZ1");

   int mmin = M.indexmin();
   int mmax = M.indexmax();
   cltudecomp_for_adjoint & clu = *this;
   clu.allocate(mmin, mmax, 3, 2);

   indx2 = tmpindx2;


   // get upper and lower parts of LU
   dmatrix_for_adjoint & alpha = get_L();
   dmatrix_for_adjoint & gamma = get_U();	// gamma is the transpose of beta
   // copy M into alpha and gamma
   // OUTER LOOP1
   for (i = mmin; i <= mmax; i++)
   {
      int i1 = indx2(i);
      for (int j = mmin; j <= mmax; j++)
      {
	 clu(i, j) = M(i1, j);
      }
   }
//    // OUTER LOOP2
   for (j = mmin; j <= mmax; j++)
   {
      int i;
      // INNER LOOP 2 1
      for (i = mmin + 1; i < j; i++)
      {
	 // using subvector here
	 //clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
	 double tmp =
	    clu(i, j) - alpha(i) (mmin, i - 1) * gamma(j) (mmin, i - 1);
	 clu.increment(i, j);
	 clu(i, j) = tmp;
      }
      // INNER LOOP 2 2
      for (i = j; i <= mmax; i++)
      {
	 // using subvector here
	 if (j > 1)
	 {
	    //clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
	    double tmp =
	       clu(i, j) - alpha(i) (mmin, j - 1) * gamma(j) (mmin, j - 1);
	    clu.increment(i, j);
	    clu(i, j) = tmp;
	 }
      }
      // INNER LOOP 2 3
      if (j != mmax)
      {
	 double z = 1.0 / gamma(j, j);
	 for (i = j + 1; i <= mmax; i++)
	 {
	    double tmp = alpha(i, j);
	    clu.increment(i, j);
	    alpha(i, j) = tmp * z;
	 }
      }
   }

}

/**
 * Ajoint code number 2 for the ludecomp with pivoting.
 */
void cltudecomp_for_adjoint::ludecomp_pivot_for_adjoint_2(void)
{
   int i = 0;
   int j = 0;
   int mmin = indexmin();
   int mmax = indexmax();
   cltudecomp_for_adjoint & clu = *this;

   // get upper and lower parts of LU
   dmatrix_for_adjoint & alpha = clu.get_L();
   dmatrix_for_adjoint & gamma = clu.get_U();	// gamma is the transpose of beta
   dmatrix & dfalpha = dfclu.get_L();
   dmatrix & dfgamma = dfclu.get_U();

   for (j = mmax; j >= mmin; j--)
   {
      // INNER LOOP 2 3
      if (j != mmax)
      {
	 // need to keep this line for  z
	 double z = 1.0 / gamma(j, j);
	 //for (i=j+1;i<=mmax;i++)
	 double dftmp = 0.0;
	 double dfz = 0.0;
	 for (i = mmax; i >= j + 1; i--)
	 {
	    // need to keep this line for tmp 
	    clu.decrement(i, j);
	    double tmp = alpha(i, j);
	    //alpha(i,j)=tmp*z;
	    dftmp += dfalpha(i, j) * z;
	    dfz += dfalpha(i, j) * tmp;
	    dfalpha(i, j) = 0.0;
	    //double tmp=alpha(i,j);
	    dfalpha(i, j) = dftmp;
	    dftmp = 0.0;
	 }
	 //double z= 1.0/gamma(j,j);
	 dfgamma(j, j) -= dfz / square(gamma(j, j));
	 dfz = 0.0;

      }
      // INNER LOOP 2 2
      //for (i=j;i<=mmax;i++)
      double dftmp = 0.0;
      for (i = mmax; i >= j; i--)
      {
	 // using subvector here
	 if (j > 1)
	 {
	    //clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
	    //double tmp=clu(i,j)-alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
	    //clu.increment(i,j);
	    //clu(i,j)=tmp;
	    clu.decrement(i, j);
	    dftmp = dfclu(i, j);
	    dfclu(i, j) = 0.0;
	    dfclu(i, j) = dftmp;
	    dfalpha(i) (mmin, j - 1) -= dftmp * gamma(j) (mmin, j - 1);
	    dfgamma(j) (mmin, j - 1) -= dftmp * alpha(i) (mmin, j - 1);
	    dftmp = 0.0;
	 }
      }
      // INNER LOOP 2 1
      //for (i=mmin+1;i<j;i++)
      for (i = j - 1; i >= mmin + 1; i--)
      {
	 // using subvector here
	 //clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
	 //double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
	 //clu.increment(i,j);
	 //clu(i,j)=tmp;
	 clu.decrement(i, j);
	 dftmp = dfclu(i, j);
	 dfclu(i, j) = 0.0;
	 //double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
	 dfclu(i, j) = dftmp;
	 dfalpha(i) (mmin, i - 1) -= dftmp * gamma(j) (mmin, i - 1);
	 dfgamma(j) (mmin, i - 1) -= dftmp * alpha(i) (mmin, i - 1);
	 dftmp = 0.0;
      }
   }
   // OUTER LOOP1
   dmatrix dfM(mmin, mmax, mmin, mmax);
   dfM.initialize();
   for (i = mmin; i <= mmax; i++)
   {
      int i1 = indx2(i);
      for (int j = mmin; j <= mmax; j++)
      {
	 // clu(i,j)=M(i1,j);
	 dfM(i1, j) = dfclu(i, j);
      }
   }
   dfM.save_dmatrix_derivatives(*pMpos);
}
