/*
 * $Id$
 *
 * Copyright (c) 2009-2011 ADMB Foundation
 */
/**
 * \file
 * This file contains the routines necessary to solve
 * a linear system of equations given in Matrix-vector form
 */

#include <ludcmp.hpp>

cltudecomp ludecomp_pivot(const dmatrix & M);
cltudecomp xludecomp_pivot(const dvar_matrix & M);
static void df_solve(void);

/** Solve a linear system using LU decomposition.
    \param aa A dvar_matrix \f$A\f$. 
    \param z A dvector containing the RHS, \f$B\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A dvar_vector containing solution vector \f$X\f$.
*/
dvar_vector solve(const dvar_matrix& aa,const dvector& z)
{
  dvar_vector zz(z.indexmin(),z.indexmax());
  for(int i=z.indexmin();i<=z.indexmax();i++)
  {
    zz(i) = 0.0;
    zz(i) = z(i);
  }
  return solve(aa,zz);
}

/** Solve a linear system using LU decomposition.
    \param aa A constant matrix. \f$A\f$. 
    \param z A dvector containing the RHS, \f$B\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A dvector containing solution vector \f$X\f$.
*/
dvector solve(const dmatrix & aa, const dvector & z)
{
   int n = aa.colsize();
   int lb = aa.colmin();
   int ub = aa.colmax();
   if (lb != aa.rowmin() || ub != aa.colmax())
   {
      cerr << "Error matrix not square in solve(dmatrix)" << endl;
      ad_exit(1);
   }
   if ( lb != z.indexmin() || ub != z.indexmax() )
   {
      cerr << "Error matrix and vector not of same size in solve(dmatrix)" << endl;
      ad_exit(1);
   }
   dvector x(lb, ub);
   x.initialize();
   if (n == 1)
   {
     if( aa(lb,lb) == 0.0 )
     {
       cerr << "Error division by zero in solve(dvar_matrix)" << endl;
       ad_exit(1);
     }
     x(lb) = z(lb)/aa(lb,lb);
     return x;
   }
   dmatrix bb(lb, ub, lb, ub);
   bb.initialize();
   bb = aa;
   cltudecomp dcmp;
   dcmp = ludecomp_pivot(bb);
   ivector index2 = dcmp.get_index2();

   //check if invertable
   double det = 1.0;
   for (int i = lb; i <= ub; i++)
   {
      det *= dcmp(i, i);
   }
   if (det == 0.0)
   {
      cerr <<
	 "Error in matrix inverse -- matrix singular in solve(dmatrix)\n";
      ad_exit(1);
   }
   //Solve L*y=b with forward-substitution (before solving Ux=y)
   dvector y(lb, ub);
   y.initialize();
   for (int i = lb; i <= ub; i++)
   {
      double tmp = 0.0;
      for (int j = lb; j < i; j++)
      {
	 tmp += dcmp(i, j) * y(j);
      }
      y(i) = z(index2(i)) - tmp;
   }

   //Now solve U*x=y with back substitution
   for (int i = ub; i >= lb; i--)
   {
      double tmp = 0.0;
      for (int j = ub; j > i; j--)
      {
	 tmp += dcmp(i, j) * x(j);
      }
      x(i) = (y(i) - tmp) / dcmp(i, i);
   }

   return x;
}

/** Solve a linear system using LU decomposition.
    \param aa A dvar_matrix containing LU decomposition of input matrix. \f$a\f$. 
    \param z A dvar_vector containing the RHS, \f$b\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A dvar_vector containing solution vector \f$X\f$.
*/
dvar_vector solve(const dvar_matrix & aa, const dvar_vector & z)
{
   int n = aa.colsize();
   int lb = aa.colmin();
   int ub = aa.colmax();
   if (lb != aa.rowmin() || ub != aa.colmax())
   {
      cerr << "Error matrix not square in solve(dvar_matrix)" << endl;
      ad_exit(1);
   }
   if ( lb != z.indexmin() || ub != z.indexmax() )
   {
      cerr << "Error matrix and vector not of same size in solve(dvar_matrix)" << endl;
      ad_exit(1);
   }

   dvar_vector x(lb, ub);

   if (ub == lb)
   {
      if( aa(lb,lb) == 0.0 )
      {
        cerr << "Error division by zero in solve(dvar_matrix)" << endl;
        ad_exit(1);
      }
      x(lb) = z(lb) / aa(lb, lb);
      return (x);
   }

   cltudecomp clu1 = xludecomp_pivot(aa);
   ivector index2 = clu1.get_index2();
   dmatrix & gamma = clu1.get_U();
   dmatrix & alpha = clu1.get_L();

   //check if invertable
   double det = 1.0;
   for (int i = lb; i <= ub; i++)
   {
      det *= clu1(i, i);
   }
   if (det == 0.0)
   {
      cerr <<
	 "Error in matrix inverse -- matrix singular in solve(dvar_matrix)\n";
      ad_exit(1);
   }

   //Solve L*y=b with forward-substitution (before solving Ux=y)
   dvector y(lb, ub);
   dvector tmp1(lb, ub);
   y.initialize();
   tmp1.initialize();

   for (int i = lb; i <= ub; i++)
   {
      for (int j = lb; j < i; j++)
      {
	 tmp1(i) += alpha(i, j) * y(j);
      }
      y(i) = value(z(index2(i))) - tmp1(i);
   }

   //Now solve U*x=y with back substitution
   dvector tmp2(lb, ub);
   tmp2.initialize();
   for (int i = ub; i >= lb; i--)
   {
      for (int j = ub; j > i; j--)
      {
	 tmp2(i) += gamma(j, i) * value(x(j));
      }
      value(x(i)) = (y(i) - tmp2(i)) / gamma(i, i);
   }

   dvector x_val(lb, ub);
   x_val.initialize();
   x_val = value(x);

   save_identifier_string("FIRST");
   z.save_dvar_vector_position();
   save_identifier_string("PLACE2");
   y.save_dvector_value();
   y.save_dvector_position();
   save_identifier_string("PLACE3");
   index2.save_ivector_value();
   index2.save_ivector_position();
   save_identifier_string("PLACE4");
   x_val.save_dvector_value();
   x_val.save_dvector_position();
   save_identifier_string("PLACE5");
   tmp1.save_dvector_value();
   tmp1.save_dvector_position();
   tmp2.save_dvector_value();
   tmp2.save_dvector_position();
   save_identifier_string("PLACE6");
   x.save_dvar_vector_position();
   save_identifier_string("LAST");
   gradient_structure::GRAD_STACK1->set_gradient_stack(df_solve);

   return (x);
}

/**
 * Adjoint code for the dvar_vector solve function
 */
static void df_solve(void)
{
   verify_identifier_string("LAST");
   dvar_vector_position x_pos = restore_dvar_vector_position();
   verify_identifier_string("PLACE6");
   dvector_position tmp2_pos = restore_dvector_position();
   dvector tmp2 = restore_dvector_value(tmp2_pos);
   dvector_position tmp1_pos = restore_dvector_position();
   dvector tmp1 = restore_dvector_value(tmp1_pos);
   verify_identifier_string("PLACE5");
   dvector_position x_val_pos = restore_dvector_position();
   dvector x = restore_dvector_value(x_val_pos);
   verify_identifier_string("PLACE4");
   ivector_position index2_pos = restore_ivector_position();
   ivector index2 = restore_ivector_value(index2_pos);
   verify_identifier_string("PLACE3");
   dvector_position y_pos = restore_dvector_position();
   dvector y = restore_dvector_value(y_pos);
   verify_identifier_string("PLACE2");
   dvar_vector_position z_pos = restore_dvar_vector_position();
   verify_identifier_string("FIRST");
   dvector dfx = restore_dvar_vector_derivatives(x_pos);

   dvector dfz(z_pos.indexmin(), z_pos.indexmax());
   dvector dfy(y_pos.indexmin(), y_pos.indexmax());
   dvector dftmp1(tmp1_pos.indexmin(), tmp1_pos.indexmax());
   dvector dftmp2(tmp2_pos.indexmin(), tmp2_pos.indexmax());
   dfz.initialize();
   dfy.initialize();
   dftmp1.initialize();
   dftmp2.initialize();

   //adjoint code for solve calc
   cltudecomp_for_adjoint clu1;
   clu1.ludecomp_pivot_for_adjoint_1();
   cltudecomp dfclu1 = clu1.get_dfclu();
   dmatrix_for_adjoint gamma = clu1.get_U();
   dmatrix_for_adjoint alpha = clu1.get_L();
   dmatrix dfgamma = dfclu1.get_U();
   dmatrix dfalpha = dfclu1.get_L();
   dfalpha.initialize();
   dfgamma.initialize();
   int lb = clu1.indexmin();
   int ub = clu1.indexmax();
   for (int i = lb; i <= ub; i++)
   {
      //value(x(i))=(y(i)-tmp2(i))/gamma(i,i);
      dfgamma(i, i) =
	 ((tmp2(i) - y(i)) * dfx(i)) / (gamma(i, i) * gamma(i, i));
      dftmp2(i) = -dfx(i) / gamma(i, i);
      dfy(i) = dfx(i) / gamma(i, i);
      for (int j = i + 1; j <= ub; j++)
      {
	 //tmp2(i)+=gamma(j,i)*value(x(j));
	 dfgamma(j, i) = dfgamma(j, i) + dftmp2(i) * x(j);
	 dfx(j) += dftmp2(i) * gamma(j, i);
      }
   }
   //tmp2.initialize();
   dftmp2.initialize();

   for (int i = ub; i >= lb; i--)
   {
      //y(i)=value(z(index2(i)))-tmp1(i);
      dftmp1(i) = -dfy(i);
      dfz(index2(i)) = dfy(i);
      for (int j = i - 1; j >= lb; j--)
      {
	 //tmp1(i)+=alpha(i,j)*y(j);
	 dfalpha(i, j) += dftmp1(i) * y(j);
	 dfy(j) += dftmp1(i) * alpha(i, j);
      }
   }
   //tmp1.initialize();
   dftmp1.initialize();

   clu1.ludecomp_pivot_for_adjoint_2();
   dfz.save_dvector_derivatives(z_pos);
}

/** 
 * Solve a linear system using LU decomposition.
 * \param aa A dvar_matrix containing LU decomposition of input matrix. \f$A\f$. 
 * \param z A dvar_vector containing the RHS, \f$b\f$ of the linear equation
 * \param ln_unsigned_det holds the log-determinant on return
 * \param _sign the sign of the lo
 * \f$A\cdot X = B\f$, to be solved.
 * \return A dvar_vector containing solution vector \f$X\f$.
 * \return The log-determinant of \f$A\f$.
 */
dvar_vector solve(const dvar_matrix & aa, const dvar_vector & z,
		  prevariable & ln_unsigned_det,
		  const prevariable & _sign)
{
   ADUNCONST(dvariable, sign)
   sign = 0.0;
   dvariable lndet = ln_det(aa);
   ln_unsigned_det = lndet;
   //dvariable sign = 0.0;
   //_sign = sign;

   dvar_vector sol = solve(aa, z);
   return sol;
}
