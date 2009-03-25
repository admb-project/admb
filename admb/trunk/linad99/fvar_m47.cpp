/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"

#ifdef __TURBOC__
#pragma hdrstop
#include <iostream.h>
#endif

#ifdef __ZTC__
#include <iostream.hpp>
#endif

#ifdef __SUN__
#include <iostream.h>
#endif
#ifdef __NDPX__
#include <iostream.h>
#endif
void dfcholeski_decomp_positive(void);
dvar_matrix choleski_decomp_positive(_CONST dvar_matrix& MM,double eps,
  dvariable& _fpen);

dvar_matrix positive_definite_matrix(_CONST dvar_matrix& MM,double eps,
  dvariable& _fpen)
{
  dvar_matrix ch_m=choleski_decomp_positive(MM,eps,_fpen);
  return ch_m*trans(ch_m);
}

dvar_matrix choleski_decomp_positive(_CONST dvar_matrix& MM,double eps,
  dvariable& _fpen)
{
  // kludge to deal with constantness
  dmatrix M=value(MM);
  double fpen;
  if (M.colsize() != M.rowsize())
  {
    cerr << "Error in chol_decomp. Matrix not square" << endl;
    ad_exit(1);
  }
  int rowsave=M.rowmin();
  int colsave=M.colmin();
  M.rowshift(1);
  M.colshift(1);
  int n=M.rowmax();

  dmatrix L(1,n,1,n);
  //dmatrix C(1,n,1,n);
  //imatrix B(1,n,1,n);
  //B.initialize();
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  double tmp;
  double ptmp;
  fpen=0.0;
  ptmp=posfun(M(1,1),eps,fpen);
  L(1,1)=sqrt(ptmp);
  for (i=2;i<=n;i++)
  {
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    for (j=2;j<=i-1;j++)
    {
      tmp=M(i,j);
      for (k=1;k<=j-1;k++)
      {
        tmp-=L(i,k)*L(j,k);
      }
      L(i,j)=tmp/L(j,j);
    }
    tmp=M(i,i);
    for (k=1;k<=i-1;k++)
    {
      tmp-=L(i,k)*L(i,k);
    }
    ptmp=posfun(tmp,eps,fpen);
    L(i,i)=sqrt(ptmp);
  }
  L.rowshift(rowsave);
  L.colshift(colsave);

  value(_fpen)=fpen;
  dvar_matrix vc=nograd_assign(L);
  save_identifier_string("qs");
  _fpen.save_prevariable_position();
  save_double_value(eps);
  vc.save_dvar_matrix_position();
  MM.save_dvar_matrix_value();
  save_identifier_string("rl");
  MM.save_dvar_matrix_position();
  save_identifier_string("lo");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfcholeski_decomp_positive);
  return vc;
}

void dfcholeski_decomp_positive(void)
{
  verify_identifier_string("lo");
  dvar_matrix_position MMpos=restore_dvar_matrix_position();
  verify_identifier_string("rl");
  dmatrix M=restore_dvar_matrix_value(MMpos);
  dvar_matrix_position vcpos=restore_dvar_matrix_position();
  double eps=restore_double_value();
  prevariable_position fpenpos=restore_prevariable_position();
  verify_identifier_string("qs");
  dmatrix dfL=restore_dvar_matrix_derivatives(vcpos);
  double dfpen=restore_prevariable_derivative(fpenpos);

  if (M.colsize() != M.rowsize())
  {
    cerr << "Error in chol_decomp. Matrix not square" << endl;
    ad_exit(1);
  }
  int rowsave=M.rowmin();
  int colsave=M.colmin();
  dfL.rowshift(1);
  dfL.colshift(1);
  M.rowshift(1);
  M.colshift(1);
  int n=M.rowmax();

  dmatrix L(1,n,1,n);
  dvector tmp(1,n);
  dvector ptmp(1,n);
  dmatrix tmp1(1,n,1,n);
  dmatrix dftmp1(1,n,1,n);
  dmatrix dfM(1,n,1,n);
  dvector dfptmp(1,n);
  dvector dftmp(1,n);
  tmp.initialize();
  tmp1.initialize();
  dftmp.initialize();
  dftmp1.initialize();
  dfM.initialize();
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  double fpen;
  int i,j,k;
  ptmp(1)=posfun(M(1,1),eps,fpen);
  L(1,1)=sqrt(ptmp(1));
  for (i=2;i<=n;i++)
  {
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    for (j=2;j<=i-1;j++)
    {
      tmp1(i,j)=M(i,j);
      for (k=1;k<=j-1;k++)
      {
        tmp1(i,j)-=L(i,k)*L(j,k);
      }
      L(i,j)=tmp1(i,j)/L(j,j);
    }
    tmp(i)=M(i,i);
    for (k=1;k<=i-1;k++)
    {
      tmp(i)-=L(i,k)*L(i,k);
    }
    double pen;
    ptmp(i)=posfun(tmp(i),eps,pen);
    L(i,i)=sqrt(ptmp(i));
  }

  dfptmp.initialize();

 //*******************************************************************8
 //*******************************************************************8
 //*******************************************************************8
  for (i=n;i>=2;i--)
  {
    //L(i,i)=sqrt(ptmp(i));
    dfptmp(i)+=dfL(i,i)/(2.0*L(i,i));
    dfL(i,i)=0.0;
    // ptmp(i)=posfun(tmp(i),eps);
    dftmp(i)=dfptmp(i)*dfposfun(tmp(i),eps);
    dftmp(i)+=dfpen*dfposfun1(tmp(i),eps);
    dfptmp(i)=0.0;
    
    for (k=i-1;k>=1;k--)
    {
      //tmp(i)-=L(i,k)*L(i,k);
      dfL(i,k)-=2.*dftmp(i)*L(i,k);
    }
    //tmp(i)=M(i,i);
    dfM(i,i)+=dftmp(i);
    dftmp(i)=0.0;
    for (j=i-1;j>=2;j--)
    {
      //L(i,j)=tmp1(i,j)/L(j,j);
      double linv=1./L(j,j);
      dftmp1(i,j)+=dfL(i,j)*linv;
      dfL(j,j)-=dfL(i,j)*tmp1(i,j)*linv*linv;
      dfL(i,j)=0.0;
      for (k=j-1;k>=1;k--)
      {
        //tmp1(i,j)-=L(i,k)*L(j,k);
        dfL(i,k)-=dftmp1(i,j)*L(j,k);
        dfL(j,k)-=dftmp1(i,j)*L(i,k);
      }
      //tmp1(i,j)=M(i,j);
      dfM(i,j)+=dftmp1(i,j);
      dftmp1(i,j)=0.0;
    }
  }
  double linv=1./L(1,1);
  for (i=n;i>=2;i--)
  {
    //L(i,1)=M(i,1)/L(1,1);
    dfM(i,1)+=dfL(i,1)*linv;
    dfL(1,1)-=dfL(i,1)*M(i,1)*linv*linv;
    dfL(i,1)=0.0;
  }
  //L(1,1)=sqrt(ptmp(1));
  dfptmp(1)+=dfL(1,1)/(2.*L(1,1));
  dfL(1,1)=0.0;
  //ptmp(1)=posfun(M(1,1),eps,fpen);
  dfM(1,1)+=dfptmp(1)*dfposfun(M(1,1),eps);
  dfM(1,1)+=dfpen*dfposfun1(M(1,1),eps);;
  dfptmp(1)=0.0;


 //*******************************************************************8
 //*******************************************************************8
 //*******************************************************************8
  
  dfM.rowshift(rowsave);
  dfM.colshift(colsave);

  dfM.save_dmatrix_derivatives(MMpos);
}

