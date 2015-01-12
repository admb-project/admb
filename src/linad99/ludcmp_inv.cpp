/*
 * $Id$
 *
 * Copyright (c) 2009-2011 ADMB Foundation
 */
/**
 * \file
 * This file contains the routines necessary to compute
 * the inverse of a matrix
 */

#define HOME_VERSION
#include <fvar.hpp>
#include <ludcmp.hpp>

#ifdef __TURBOC__
#pragma hdrstop
#include <iostream.h>
#endif

#ifdef __ZTC__
#include <iostream.hpp>
#endif

#define TINY 1.0e-20;
cltudecomp ludecomp(const dmatrix & M);
void dfinvpret(void);

/**
 * The minimum of an integer.
 * \param a
 * \param b
 */
int min(int a, int b)
{
   if (a > b)
      return b;
   return a;
}


/** Inverse of a constant matrix by LU decomposition.
    \ingroup matop
    \param aa A dmatrix, \f$M\f$, for which the inverse is to be computed.
    \return A dmatrix containing \f$M^{-1}\f$.
*/
dmatrix inv(_CONST dmatrix & aa)
{
   int imax = 0;
   int n = 0;
   n = aa.colsize();
   int lb = aa.colmin();
   int ub = aa.colmax();
   dmatrix vc(lb, ub, lb, ub);
   vc.initialize();
   if (n == 1)
   {
      if (aa(lb, lb) == 0.0)
      {
	 cerr <<
	    "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
	 ad_exit(1);
      } else
      {
	 vc(lb, lb) = 1.0 / aa(lb, lb);
	 return vc;
      }
   } else if (n == 2)
   {
      double det = aa(lb, lb) * aa(ub, ub) - aa(lb, ub) * aa(ub, lb);
      if (det == 0.0)
      {
	 cerr <<
	    "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
	 ad_exit(1);
      } else
      {
	 double detinv = 1.0 / det;
	 vc(lb, lb) = aa(ub, ub) * detinv;
	 vc(ub, ub) = aa(lb, lb) * detinv;
	 vc(lb, ub) = -aa(lb, ub) * detinv;
	 vc(ub, lb) = -aa(ub, lb) * detinv;
	 return vc;
      }
   }

   cltudecomp bb(lb, ub);
   bb = ludecomp(aa);

   dmatrix alpha = bb.get_L();
   dmatrix beta = bb.get_U();

   //check if invertable
   double det = 1.0;
   for (int i = lb; i <= ub; i++)
   {
      det *= beta(i, i);
   }
   if (det == 0.0)
   {
      cerr <<
	 "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
      ad_exit(1);
   }
   // Find inverse of L
   for (int i = lb + 1; i <= ub; i++)
   {
      alpha(i, 1) = -alpha(i, 1);
   }
   for (int k = lb + 1; k < ub; k++)
   {
      for (int j = lb; j < k; j++)
      {
	 for (int i = k + 1; i <= ub; i++)
	 {
	    alpha(i, j) -= alpha(k, j) * alpha(i, k);
	 }
      }
      for (int i = k + 1; i <= ub; i++)
      {
	 alpha(i, k) = -alpha(i, k);
      }
   }

   //Put L^-1 in Matrix to multiply with U^-1
   dmatrix Low(lb, ub, lb, ub);
   Low.initialize();
   for (int i = lb + 1; i <= ub; i++)
   {
      for (int j = lb; j < i; j++)
      {
	 Low(i, j) = alpha(i, j);
      }
   }
   for (int i = lb; i <= ub; i++)
   {
      Low(i, i) = 1.0;
   }
   for (int i = lb; i <= ub - 1; i++)
   {
      for (int j = lb + i; j <= ub; j++)
      {
	 Low(i, j) = 0.0;
      }
   }

   // Find inverse of U
   for (int i = lb + 1; i <= ub; i++)
   {
      for (int j = lb; j < i; j++)
      {
	 beta(i, j) = beta(i, j) / beta(i, i);
      }
   }
   for (int i = lb; i <= ub; i++)
   {
      beta(i, i) = 1 / beta(i, i);
   }
   for (int i = lb + 1; i <= ub; i++)
   {
      beta(i, 1) = -beta(i, 1) * beta(1, 1);
   }
   for (int k = lb + 1; k < ub; k++)
   {
      for (int j = lb; j < k; j++)
      {
	 for (int i = k + 1; i <= ub; i++)
	 {
	    beta(i, j) -= beta(k, j) * beta(i, k);
	 }
      }
      for (int i = k + 1; i <= ub; i++)
      {
	 beta(i, k) = -beta(i, k) * beta(k, k);
      }
   }

   //Put U^-1 in Matrix to multiply with U^-1
   dmatrix Up(lb, ub, lb, ub);
   Up.initialize();
   for (int i = lb; i <= ub; i++)
   {
      for (int j = lb; j <= i; j++)
      {
	 Up(i, j) = beta(i, j);
      }
   }
   for (int i = lb; i <= ub - 1; i++)
   {
      for (int j = lb + i; j <= ub; j++)
      {
	 Up(i, j) = 0.0;
      }
   }
   Up = trans(Up);

   //compute inverese by U^-1*L^-1
   vc = Up * Low;
   return vc;
}

/** Inverse of a varaiable matrix.    
    \param aa dvar_matrix conaining matrix to be inverted,\f$A\f$.
    \return dvar_matrix containing \f$A^{-1}\f$.
*/
dvar_matrix inv(_CONST dvar_matrix & aa)
{
   int i = 0;
   int imax = 0;
   int j = 0;
   int k = 0;
   int n = 0;
   n = aa.colsize();
   int lb = aa.colmin();
   int ub = aa.colmax();
   dvar_matrix vc(lb, ub, lb, ub);
   if (n == 1)
   {
      if (aa(lb, lb) == 0.0)
      {
	 cerr <<
	    "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
	 ad_exit(1);
      } else
      {
	 vc(lb, lb) = 1.0 / aa(lb, lb);
	 return vc;
      }
   } else if (n == 2)
   {
      dvariable det = aa(lb, lb) * aa(ub, ub) - aa(lb, ub) * aa(ub, lb);
      if (det == 0.0)
      {
	 cerr <<
	    "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
	 ad_exit(1);
      } else
      {
	 dvariable detinv = 1.0 / det;
	 vc(lb, lb) = aa(ub, ub) * detinv;
	 vc(ub, ub) = aa(lb, lb) * detinv;
	 vc(lb, ub) = -aa(lb, ub) * detinv;
	 vc(ub, lb) = -aa(ub, lb) * detinv;
	 return vc;
      }
   }

   ivector indx(lb, ub);
   indx.initialize();
   int One = 1;
   indx.fill_seqadd(lb, One);
   double d = 0.0;
   double w1 = 0.0;
   double ssum = 0.0;
   double temp = 0.0;
   dvar_matrix_position dmp(aa, 0);
   //dmatrix bb=value(aa);
   cltudecomp bb(lb, ub);
   //bb=value(aa);   // bad because it creates an extra copy of aa
   bb.assign_value(aa);
   dvector vv(lb, ub);
   vv.initialize();

   d = 1.0;
   for (int i = lb; i <= ub; i++)
   {
      w1 = 0.0;
      for (int j = lb; j <= ub; j++)
      {
	 temp = fabs(bb.elem(i, j));
	 if (temp > w1)
	 {
	    w1 = temp;
	 }
      }
      if (w1 == 0.0)
      {
	 cerr <<
	    "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
	 ad_exit(1);
      }
      vv[i] = 1.0 / w1;
   }

   dmatrix alpha = bb.get_L();
   dmatrix beta = bb.get_U();
   double v1 = 0.0;
   for (int j = lb; j <= ub; j++)
   {
      for (int i = lb; i < j; i++)
      {
	 ssum = bb.elem(i, j);

	 if (lb < i)
	 {
	    ssum -= alpha(i) (lb, i - 1) * beta(j) (lb, i - 1);
	 }

	 bb.elem(i, j) = ssum;
      }
      w1 = 0.0;
      for (int i = j; i <= ub; i++)
      {
	 ssum = bb.elem(i, j);
	 if (lb < j)
	 {
	    ssum -= alpha(i) (lb, j - 1) * beta(j) (lb, j - 1);
	 }
	 bb.elem(i, j) = ssum;
	 v1 = vv[i] * fabs(ssum);
	 if (v1 >= w1)
	 {
	    w1 = v1;
	    imax = i;
	 }
      }
      if (j != imax)
      {
	 for (int k = lb; k <= ub; k++)
	 {
	    v1 = bb.elem(imax, k);
	    bb.elem(imax, k) = bb.elem(j, k);
	    bb.elem(j, k) = v1;
	 }
	 d = -1. * d;
	 vv[imax] = vv[j];

	 //if (j<ub)
	 {
	    int itemp = indx.elem(imax);
	    indx.elem(imax) = indx.elem(j);
	    indx.elem(j) = itemp;
	 }
	 //cout << "indx= " <<indx<<endl;
      }

      if (bb.elem(j, j) == 0.0)
      {
	 bb.elem(j, j) = TINY;
      }

      if (j != n)
      {
	 double binv = 1.0 / bb.elem(j, j);
	 for (int i = j + 1; i <= ub; i++)
	 {
	    bb.elem(i, j) *= binv;
	 }
      }
   }

   dvector y(lb, ub);
   dvector x(lb, ub);
   y.initialize();
   x.initialize();

   cltudecomp & b = bb;
   ivector indxinv(lb, ub);
   indxinv.initialize();
   for (int i = lb; i <= ub; i++)
   {
      indxinv(indx.elem(i)) = i;
   }
   for (int ii = lb; ii <= ub; ii++)
   {
      y.initialize();
      y(indxinv(ii)) = 1.;
      for (int i = indxinv(ii); i <= ub; i++)
      {
	 // ssum=y(ii,i);
	 if (i == indxinv(ii))
	 {
	    ssum = 1.;
	 } else
	 {
	    ssum = 0.;
	 }
	 if (indxinv(ii) < i)
	 {
	    ssum -= alpha(i) (indxinv(ii), i - 1) * y(indxinv(ii), i - 1);
	 }
	 y.elem(i) = ssum;
      }
      for (int i = ub; i >= lb; i--)
      {
	 ssum = y.elem(i);
	 for (int j = i + 1; j <= ub; j++)
	 {
	    ssum -= beta(j, i) * x.elem(j);
	 }
	 x.elem(i) = ssum / b.elem(i, i);
      }
      y.save_dvector_value();
      x.save_dvector_value();
      nograd_assign_column(vc, x, ii);
   }

   dmatrix bb1(lb, ub, lb, ub);
   bb1.initialize();
   for (int i = lb; i <= ub; i++)
   {
      for (int j = lb; j <= ub; j++)
      {
	 bb1(i, j) = bb(i, j);
      }
   }
   save_identifier_string("P5");
   x.save_dvector_position();
   y.save_dvector_position();
   indx.save_ivector_value();
   indx.save_ivector_position();
   aa.save_dvar_matrix_position();
   vc.save_dvar_matrix_position();
   bb1.save_dmatrix_value();
   bb1.save_dmatrix_position();
   save_identifier_string("P1");
   gradient_structure::GRAD_STACK1->set_gradient_stack(dfinvpret);
   return vc;
}

/** Adjoint code for dvar_matrix inv(_CONST dvar_matrix& aa).
*/
void dfinvpret(void)
{
   verify_identifier_string("P1");
   dmatrix_position bpos = restore_dmatrix_position();
   dmatrix b = restore_dmatrix_value(bpos);
   dvar_matrix_position v_pos = restore_dvar_matrix_position();
   dvar_matrix_position a_pos = restore_dvar_matrix_position();
   ivector_position indx_pos = restore_ivector_position();
   ivector indx = restore_ivector_value(indx_pos);
   dvector_position y_pos = restore_dvector_position();
   dvector_position x_pos = restore_dvector_position();
   verify_identifier_string("P5");
   int lb = b.colmin();
   int ub = b.colmax();
   dmatrix dfb(lb, ub, lb, ub);
   ivector indxinv(lb, ub);
   for (int i = lb; i <= ub; i++)
   {
      indxinv(indx.elem(i)) = i;
   }

   double dfssum = 0.;
   dvector dfy(lb, ub);
#ifndef SAFE_INITIALIZE
   dfb.initialize();
   dfy.initialize();
#endif
   for (int ii = ub; ii >= lb; ii--)
   {
      //x.save_dvector_value();
      dvector x = restore_dvector_value(x_pos);
      //y.save_dvector_value();
      dvector y = restore_dvector_value(y_pos);
      dvector dfx = restore_dvar_matrix_derivative_column(v_pos, ii);
      for (int i = lb; i <= ub; i++)
      {
	 // x.elem(i)=ssum/b.elem(i,i);
	 dfssum += dfx.elem(i) / b.elem(i, i);
	 dfb.elem(i, i) -= dfx.elem(i) * x.elem(i) / b.elem(i, i);
	 dfx.elem(i) = 0.;
	 for (int j = ub; j >= i + 1; j--)
	 {
	    // ssum -=b.elem(i,j)*x.elem(j);
	    dfb.elem(i, j) -= dfssum * x.elem(j);
	    dfx.elem(j) -= dfssum * b.elem(i, j);
	 }
	 // ssum=y.elem(i);
	 dfy.elem(i) += dfssum;
	 dfssum = 0.;
      }

      //for (i=ub;i>=lb;i--)
      int i2;
      for (i2 = ub; i2 >= indxinv(ii); i2--)
      {
	 // y.elem(i)=ssum;
	 dfssum += dfy.elem(i2);
	 dfy.elem(i2) = 0.;
	 // for (int j=i-1;j>=lb;j--)
	 for (int j = i2 - 1; j >= indxinv(ii); j--)
	 {
	    // ssum-=b.elem(i,j)*y.elem(j);
	    dfb.elem(i2, j) -= dfssum * y.elem(j);
	    dfy.elem(j) -= dfssum * b.elem(i2, j);
	 }
	 //ssum=y.elem(i);
	 dfy.elem(i2) = dfssum;
	 dfssum = 0.;
      }
      //x.initialize()
      //y.initialize()
      dfx.initialize();
      dfy.initialize();
   }

   for (int j = ub; j >= lb; j--)
   {
      for (int i = ub; i >= lb; i--)
      {
	 if (i <= j)
	 {
	    // b.elem(i,j)=ssum;
	    dfssum += dfb.elem(i, j);
	    dfb.elem(i, j) = 0.;
	 } else
	 {
	    // b.elem(i,j)=ssum/b.elem(j,j);
	    dfssum += dfb.elem(i, j) / b.elem(j, j);
	    dfb.elem(j, j) -= dfb.elem(i, j) * b.elem(i, j) / b.elem(j, j);
	    dfb.elem(i, j) = 0.;
	 }

	 for (int k = min(i - 1, j - 1); k >= lb; k--)
	 {
	    // ssum-=b.elem(i,k)*b.elem(k,j);
	    dfb.elem(i, k) -= dfssum * b.elem(k, j);
	    dfb.elem(k, j) -= dfssum * b.elem(i, k);
	 }
	 // ssum=value(a(indx.elem(i),j);
	 save_dmatrix_derivatives(a_pos, dfssum, indx.elem(i), j);	// like this
	 dfssum = 0.;
      }
   }
}

#undef TINY
#undef HOME_VERSION
