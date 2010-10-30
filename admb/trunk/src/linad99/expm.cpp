/*
 * $Id$
 *
 * For AD Model Builder by Anders Nielsen <anders@nielsensweb.org> and Casper Berg <cbe@aqua.dtu.dk> 
 * Aug. 2010
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */

#include <fvar.hpp>
  #include "ludcmp.hpp"
  dvar_matrix solve(const dvar_matrix& aa, const dvar_matrix& zz);
  cltudecomp xludecomp_pivot(const dvar_matrix & M);
  static void df_mm_solve(void);

#define TINY 1.0e-20;

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

#undef TINY


/** Solve a linear system using LU decomposition.
    \param aa A variable matrix. \f$A\f$. 
    \param z A matrix containing the RHS, \f$B\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A matrix containing solution \f$X\f$.
*/
  dvar_matrix solve(const dvar_matrix& aa, const dvar_matrix& zz)
  {
  int n=aa.colsize();
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
    
    cltudecomp clu1=xludecomp_pivot(aa);
    ivector index2=clu1.get_index2();
    dmatrix & gamma=clu1.get_U();
    dmatrix & alpha=clu1.get_L();

  //check if invertable
  int i = 0;
  double det=1.0;
  for(i=lb;i<=ub;i++)
  {
    det*=clu1(i,i);
  }
  if (det==0.0)
  {
    cerr << "Error in matrix inverse -- matrix singular in solve(dmatrix)\n";
    ad_exit(1);
  }

  dmatrix yy(lb,ub,lb,ub);
  dmatrix ttmp1(lb,ub,lb,ub);
  dmatrix ttmp2(lb,ub,lb,ub);
  for(int k=lb;k<=lb;k++)
  {

    dvar_vector z = column(zz,k);

    //Solve L*y=b with forward-substitution (before solving Ux=y)
    dvector y = column(yy,k);
    dvector tmp1 = column(ttmp1,k);
    tmp1.initialize();

    for(i=lb;i<=ub;i++)
    {
      for(int j=lb;j<i;j++)
      {
        tmp1(i)+=alpha(i,j)*y(j);
      }
      y(i)=value(z(index2(i)))-tmp1(i);
    }
  
    //Now solve U*x=y with back substitution
    dvector tmp2 = column(ttmp2,k);
    tmp2.initialize();
    dvar_vector x(lb,ub);
    for(i=ub;i>=lb;i--)
    {
      for(int j=ub;j>i;j--)
      {
        tmp2(i)+=gamma(j,i)*value(x(j));
      }
      value(x(i))=(y(i)-tmp2(i))/gamma(i,i);
    }

    xx.colfill(k,x);
    yy.colfill(k,y);
    ttmp1.colfill(k,tmp1);
    ttmp2.colfill(k,tmp2);
  }

    dmatrix xx_val(lb,ub,lb,ub);
    xx_val=value(xx);
     
    save_identifier_string("FIRST");
    zz.save_dvar_matrix_position();
    save_identifier_string("PLACE2");
    yy.save_dmatrix_value();
    yy.save_dmatrix_position();
    save_identifier_string("PLACE3");
    index2.save_ivector_value();
    index2.save_ivector_position();
    save_identifier_string("PLACE4");
    xx_val.save_dmatrix_value();
    xx_val.save_dmatrix_position();
    save_identifier_string("PLACE5");
    ttmp1.save_dmatrix_value();
    ttmp1.save_dmatrix_position();
    ttmp2.save_dmatrix_value();
    ttmp2.save_dmatrix_position();
    save_identifier_string("PLACE6");
    xx.save_dvar_matrix_position();
    save_identifier_string("LAST");
    gradient_structure::GRAD_STACK1->
          set_gradient_stack(df_mm_solve);

    return(xx);
  }
  static void df_mm_solve(void)
  {
    verify_identifier_string("LAST");
    dvar_matrix_position xx_pos=restore_dvar_matrix_position();
    verify_identifier_string("PLACE6");
    dmatrix_position ttmp2_pos=restore_dmatrix_position();
    dmatrix ttmp2=restore_dmatrix_value(ttmp2_pos);
    dmatrix_position ttmp1_pos=restore_dmatrix_position();
    dmatrix ttmp1=restore_dmatrix_value(ttmp1_pos);
    verify_identifier_string("PLACE5");
    dmatrix_position xx_val_pos=restore_dmatrix_position();
    dmatrix xx=restore_dmatrix_value(xx_val_pos);
    verify_identifier_string("PLACE4");
    ivector_position index2_pos=restore_ivector_position();
    ivector index2=restore_ivector_value(index2_pos);
    verify_identifier_string("PLACE3");
    dmatrix_position yy_pos=restore_dmatrix_position();
    dmatrix yy=restore_dmatrix_value(yy_pos);
    verify_identifier_string("PLACE2");
    dvar_matrix_position zz_pos=restore_dvar_matrix_position();
    verify_identifier_string("FIRST");
    dmatrix dfxx=restore_dvar_matrix_derivatives(xx_pos);
    
    int rlb = zz_pos.rowmin();
    int rub = zz_pos.rowmax();
    dmatrix dfzz(rlb,rub,rlb,rub);
    dmatrix dfyy(rlb,rub,rlb,rub);
    dmatrix dfttmp1(rlb,rub,rlb,rub);
    dmatrix dfttmp2(rlb,rub,rlb,rub);
    dfzz.initialize();
    dfyy.initialize();
    dfttmp1.initialize();
    dfttmp2.initialize();

     //adjoint code for solve calc
    cltudecomp_for_adjoint clu1;
    clu1.ludecomp_pivot_for_adjoint_1();
    cltudecomp dfclu1=clu1.get_dfclu();
    dmatrix_for_adjoint gamma=clu1.get_U();
    dmatrix_for_adjoint alpha=clu1.get_L();
    dmatrix dfgamma=dfclu1.get_U();
    dmatrix dfalpha=dfclu1.get_L();
    dfalpha.initialize();
    dfgamma.initialize();
    int lb=clu1.indexmin();
    int ub=clu1.indexmax();
     int i,k;

  for(k=ub;k>=lb;k--)
  {
    dvector tmp2 = column(ttmp2,k);
    dvector dftmp2 = column(dfttmp2,k);
    dvector y = column(yy,k);
    dvector dfy = column(dfyy,k);
    dvector dfx = column(dfxx,k);
    dvector x = column(xx,k);

    for(i=lb;i<=ub;i++)
    {
      //value(x(i))=(y(i)-tmp2(i))/gamma(i,i);
      dfgamma(i,i)=((tmp2(i)-y(i))*dfx(i))/(gamma(i,i)*gamma(i,i));
      dftmp2(i)=-dfx(i)/gamma(i,i);
      dfy(i)=dfx(i)/gamma(i,i);
      for(int j=i+1;j<=ub;j++)
      {
        //tmp2(i)+=gamma(j,i)*value(x(j));
        dfgamma(j,i)=dfgamma(j,i)+dftmp2(i)*x(j);
        dfx(j)+=dftmp2(i)*gamma(j,i);
      }
    }
    //tmp2.initialize();
    dftmp2.initialize();



    dvector dftmp1 = column(dfttmp1,k);
    dvector dfz  =column(dfzz,k);

    for(i=ub;i>=lb;i--)
    {
      //y(i)=value(z(index2(i)))-tmp1(i);
      dftmp1(i)=-dfy(i);
      dfz(index2(i))=dfy(i);
      for(int j=i-1;j>=lb;j--)
      {
        //tmp1(i)+=alpha(i,j)*y(j);
        dfalpha(i,j)+=dftmp1(i)*y(j);
        dfy(j)+=dftmp1(i)*alpha(i,j);
      }
    }
    //tmp1.initialize();
    dftmp1.initialize();

    dfttmp1.colfill(k,dftmp1);
    dfzz.colfill(k,dfz);
    ttmp2.colfill(k,tmp2);
    dfttmp2.colfill(k,dftmp2);
    yy.colfill(k,y);
    dfyy.colfill(k,dfy);
    dfxx.colfill(k,dfx);
    xx.colfill(k,x);

  }

    clu1.ludecomp_pivot_for_adjoint_2();
    dfzz.save_dmatrix_derivatives(zz_pos);
  }
