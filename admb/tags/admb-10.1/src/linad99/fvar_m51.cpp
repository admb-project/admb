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
void dfcholeski_decomp(void);

// compute log of determinant of a spd matrix
void df_ln_det_choleski(void);

/**
 * Description not yet available.
 * \param
 */
dvariable ln_det_choleski(_CONST dvar_matrix& MM)
{
  // kludge to deal with constantness
  dmatrix M=value(MM);
  if (M.colsize() != M.rowsize())
  {
    cerr << "Error in chol_decomp. Matrix not square" << endl;
    ad_exit(1);
  }
  if (M.colsize() == 1)
  {
    int mmin=M.indexmin();
    return log(MM(mmin,mmin));
  }

  //int rowsave=M.rowmin();
  //int colsave=M.colmin();
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
    if (M(1,1)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }
  L(1,1)=sqrt(M(1,1));
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
    if (tmp<=0)
    {
      cerr << "Error matrix not positive definite in ln_det_choleski"
        <<endl;
      ad_exit(1);
    }
    L(i,i)=sqrt(tmp);
  }
  //L.rowshift(rowsave);
  //L.colshift(colsave);
  double log_det1=0.0;
  for (i=1;i<=k;i++)
  {
    log_det1+=log(L(i,i));
  }
 /*
  double minL=L(1,1);
  for (i=2;i<=k;i++)
  {
    if (L(i,i)<minL) minL=L(i,i);
  }
  cout << "min in choleski = " << minL << endl;
 */


  double log_det=2.0*log_det1;
  dvariable vlog_det=nograd_assign(log_det);
  save_identifier_string("ps");
  vlog_det.save_prevariable_position();
  save_identifier_string("rt");
  MM.save_dvar_matrix_value();
  save_identifier_string("pl");
  MM.save_dvar_matrix_position();
  save_identifier_string("pa");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(df_ln_det_choleski);
  return vlog_det;
}

/**
 * Description not yet available.
 * \param
 */
void df_ln_det_choleski(void)
{
  verify_identifier_string("pa");
  dvar_matrix_position MMpos=restore_dvar_matrix_position();
  verify_identifier_string("pl");
  dmatrix M=restore_dvar_matrix_value(MMpos);
  verify_identifier_string("rt");
  //prevariable_position vcpos=restore_prevariable_position();
  double dflog_det=restore_prevariable_derivative();
  verify_identifier_string("ps");

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
  dmatrix dfL(1,n,1,n);
  dvector tmp(1,n);
  dmatrix tmp1(1,n,1,n);
  dmatrix dftmp1(1,n,1,n);
  dmatrix dfM(1,n,1,n);
  dvector dftmp(1,n);
  tmp.initialize();
  tmp1.initialize();
  dftmp.initialize();
  dftmp1.initialize();
  dfM.initialize();
  dfL.initialize();
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  if (M(1,1)<=0)
  {
    cerr << "Error matrix not positive definite in choleski_decomp"
      <<endl;
    ad_exit(1);
  }
  L(1,1)=sqrt(M(1,1));
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
    if (tmp(i)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }
    L(i,i)=sqrt(tmp(i));
  }
  double log_det1=0.0;
  for (i=1;i<=n;i++)
  {
    log_det1+=log(L(i,i));
  }
  //double log_det=2.0*log_det1;

 //*******************************************************************8
 //*******************************************************************8
 //*******************************************************************8

  //double log_det=2.0*log_det1;
  double dflog_det1=2.0*dflog_det;
  for (i=1;i<=n;i++)
  {
    //log_det1+=log(L(i,i));
    dfL(i,i)=dflog_det1/L(i,i);
  }

  for (i=n;i>=2;i--)
  {
    //L(i,i)=sqrt(tmp(i));
    dftmp(i)+=dfL(i,i)/(2.0*L(i,i));
    dfL(i,i)=0.0;
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
        //tmp(i,j)-=L(i,k)*L(j,k);
        dfL(i,k)-=dftmp1(i,j)*L(j,k);
        dfL(j,k)-=dftmp1(i,j)*L(i,k);
      }
      //tmp(i,j)=M(i,j);
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
  //L(1,1)=sqrt(M(1,1));
  dfM(1,1)+=dfL(1,1)/(2.*L(1,1));


 //*******************************************************************8
 //*******************************************************************8
 //*******************************************************************8
  
  dfM.rowshift(rowsave);
  dfM.colshift(colsave);

  dfM.save_dmatrix_derivatives(MMpos);
}

/**
 * Description not yet available.
 * \param
 */
static dvariable error_condition(int &onerror)
{
  onerror=1;
  dvariable v=0.0;
  return v;
}
  
/**
 * Description not yet available.
 * \param
 */
dvariable ln_det_choleski_error(const dvar_matrix& MM,int & onerror)
{
  onerror=0;
  // kludge to deal with constantness
  dmatrix M=value(MM);
  if (M.colsize() != M.rowsize())
  {
    cerr << "Error in chol_decomp. Matrix not square" << endl;
    ad_exit(1);
  }
  if (M.colsize() == 1)
  {
    int mmin=M.indexmin();
    return log(MM(mmin,mmin));
  }

  //int rowsave=M.rowmin();
  //int colsave=M.colmin();
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
    if (M(1,1)<=0)
    {
      return error_condition(onerror);
    }
  L(1,1)=sqrt(M(1,1));
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
    if (tmp<=0)
    {
      return error_condition(onerror);
    }
    L(i,i)=sqrt(tmp);
  }
  //L.rowshift(rowsave);
  //L.colshift(colsave);
  double log_det1=0.0;
  for (i=1;i<=k;i++)
  {
    log_det1+=log(L(i,i));
  }
 /*
  double minL=L(1,1);
  for (i=2;i<=k;i++)
  {
    if (L(i,i)<minL) minL=L(i,i);
  }
  cout << "min in choleski = " << minL << endl;
 */


  double log_det=2.0*log_det1;
  dvariable vlog_det=nograd_assign(log_det);
  save_identifier_string("ps");
  vlog_det.save_prevariable_position();
  save_identifier_string("rt");
  MM.save_dvar_matrix_value();
  save_identifier_string("pl");
  MM.save_dvar_matrix_position();
  save_identifier_string("pa");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(df_ln_det_choleski);
  return vlog_det;
}
