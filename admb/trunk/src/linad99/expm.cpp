/*
 * $Id$
 *
 * Authors: Anders Nielsen <anders@nielsensweb.org> and Casper Berg <cbe@aqua.dtu.dk> 
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
  #include "ludcmp.hpp"
  dvar_matrix solve(const dvar_matrix& aa, const dvar_matrix& zz);
  dvar_vector solve(const dvar_matrix & aa, const dvar_vector & z);
  dvar_vector solve_work(const dvar_matrix & aa, const dvar_vector & z, const cltudecomp & _clu1);
  cltudecomp xludecomp_pivot_for_expm_solve(const dvar_matrix& M, const ivector& _index2);
  //static void df_mm_solve(void);
  static void df_solve(void);

//#define TINY 1.0e-20;

/**
 * Description not yet available.
 * \param
 */
dmatrix fabs(const dmatrix & X){
  int rmin = X.rowmin();
  int rmax = X.rowmax();
  int cmin = X.colmin();
  int cmax = X.colmax(); 
  dmatrix ret(rmin,rmax,cmin,cmax);
  for(int i=rmin; i<=rmax; ++i){
    for(int j=cmin; j<=cmax; ++j){
      ret(i,j)=fabs(X(i,j));
    }
  }
  return ret;
}

  /**
  \ingroup PDF
   Matrix exponential using (6,6) Padé approximation adapted from Moler and van Loan 
  \param A square dvar_matrix
  \returns The matrix exponentiel of A
  */
dvar_matrix expm(const dvar_matrix & A)
{
  RETURN_ARRAYS_INCREMENT();    
  int rmin = A.rowmin();
  int rmax = A.rowmax();

  if(rmax != A.colmax()){cout<<"Error: Not square matrix in expm."<<endl; ad_exit(1);}
  if(rmin != A.colmin()){cout<<"Error: Not square matrix in expm."<<endl; ad_exit(1);}

  dvar_matrix I(rmin,rmax,rmin,rmax);
  dvar_matrix AA(rmin,rmax,rmin,rmax);
  dvar_matrix X(rmin,rmax,rmin,rmax);
  dvar_matrix E(rmin,rmax,rmin,rmax);
  dvar_matrix D(rmin,rmax,rmin,rmax);
  dvar_matrix cX(rmin,rmax,rmin,rmax);

  I.initialize();
  for(int i=rmin; i<=rmax; ++i){I(i,i)=1.0;}

  dvariable log2NormInf;
  log2NormInf=log(max(rowsum(fabs(value(A)))));
  log2NormInf/=log(2.0);
  int e = (int)value(log2NormInf) + 1;
  int s = e+1;
  s = (s<0) ? 0 : s;
  AA=1.0/pow(2.0,s)*A;

  X=AA;
  dvariable c=0.5;

  E=I+c*AA;
  D=I-c*AA;
  int q=6, p=1, k;
  for(k=2;  k<=q; ++k){
    c*=((double)q-k+1.0)/((double)k*(2*q-k+1));
    X=AA*X;
    cX=c*X;
    E+=cX;
    if(p==1){D+=cX;}else{D-=cX;}
    p = (p==1) ? 0 : 1;
  }
  //E=inv(D)*E;
  E = solve(D,E);
  for(k=1; k<=s; ++k){
    E=E*E;
  }
  RETURN_ARRAYS_DECREMENT();
  return E;
}

//#undef TINY


void savetostack(const dvar_matrix& M, const ivector& index2)
{
     save_identifier_string("OZ1");
     M.save_dvar_matrix_value();
     M.save_dvar_matrix_position();
     save_identifier_string("OZ2");
     index2.save_ivector_value();
     index2.save_ivector_position();
     save_identifier_string("OZ");
}

/** Solve a linear system using LU decomposition.
 *  \param aa A variable matrix. \f$A\f$. 
 *  \param z A matrix containing the RHS, \f$B\f$ of the linear equation
 *  \f$A\cdot X = B\f$, to be solved.
 *  \return A matrix containing solution \f$X\f$.
 */
dvar_matrix solve(const dvar_matrix& aa, const dvar_matrix& zz)
{
  //int n=aa.colsize();
   int lb=aa.colmin();
   int ub=aa.colmax();
   if (lb!=aa.rowmin()||ub!=aa.colmax())
   {
     cerr << "Error matrix not square in "
          << "solve(const dvar_matrix& aa, const dvar_matrix& zz)"<<endl;
     ad_exit(1);
   }
   if (zz.rowmin()!=aa.rowmin()||zz.colmax()!=aa.colmax())
   {
     cerr << "Error matrices not compatible in "
          << "solve(const dvar_matrix& aa, const dvar_matrix& zz)"<<endl;
     ad_exit(1);
   }

   dvar_matrix xx(lb,ub,lb,ub);

   if(ub==lb)
   {
     xx=zz*inv(aa);
     return(xx);
   }
    
   ivector index2(lb,ub);
   cltudecomp clu = xludecomp_pivot_for_expm_solve(aa,index2);

   //check if invertable
   double det = 1.0;
   for (int i = lb; i <= ub; i++)
   {
      det *= clu(i, i);
   }
   if (det == 0.0)
   {
      cerr <<
	 "Error in matrix inverse -- matrix singular in solve(dvar_matrix)\n";
      ad_exit(1);
   }

   for(int k=lb;k<=ub;k++)
   {
      savetostack(aa,index2);
      dvar_vector z = column(zz,k);
      dvar_vector x = solve_work(aa,z,clu);
      xx.colfill(k,x);
   }

   return xx;
}

/** Solve a linear system using LU decomposition. To be used for multiple calls for solve.
 *  \param aa A variable matrix. \f$A\f$. 
 *  \param z A matrix containing the RHS, \f$B\f$ of the linear equation
 *  \param clu1 The LU Decomposition of A
 *  \f$A\cdot X = B\f$, to be solved.
 *  \return A matrix containing solution \f$X\f$.
 */
dvar_vector solve_work(const dvar_matrix & aa, const dvar_vector & z, const cltudecomp & _clu1)
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

   cltudecomp & clu1 = (cltudecomp &) _clu1;
   ivector index2 = clu1.get_index2();
   dmatrix & gamma = clu1.get_U();
   dmatrix & alpha = clu1.get_L();

   //check if invertable --- may be able to get rid of this check
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
