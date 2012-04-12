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

/**
 * Description not yet available.
 * \param
 */
dvar_matrix choleski_decomp(_CONST dvar_matrix& MM)
{
  // kludge to deal with constantness
  if (MM.colsize() != MM.rowsize())
  {
    cerr << "Error in chol_decomp. Matrix not square" << endl;
    ad_exit(1);
  }
  if (MM.colsize()==1)
  {
    int mmin=MM.indexmin();
    int mmax=MM.indexmax();
    if (MM(mmin,mmin)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }
    dvar_matrix  vc(mmin,mmax,mmin,mmax);
    vc(mmin,mmin)=sqrt(MM(mmin,mmin));
    return vc;
  }
  dmatrix M=value(MM);
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
    if (M(1,1)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }
  L(1,1)=sqrt(M(1,1));
  for (i=2;i<=n;i++)
  {
    /*
    if (!B(1,1))
    {
      C(1,1)=L(1,1);
      B(1,1)=1;
    }
    */
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    for (j=2;j<=i-1;j++)
    {
      tmp=M(i,j);
      for (k=1;k<=j-1;k++)
      {
	/*
	if (!B(i,k))
	{
	  C(i,k)=L(i,k);
	  B(i,k)=1;
        }
	if (!B(j,k))
	{
	  C(j,k)=L(j,k);
	  B(j,k)=1;
        }
	*/
        tmp-=L(i,k)*L(j,k);
      }
      /*
      if (!B(j,j))
      {
        C(j,j)=L(j,j);
        B(j,j)=1;
      }
      */
      L(i,j)=tmp/L(j,j);
    }
    tmp=M(i,i);
    for (k=1;k<=i-1;k++)
    {
      /*
      if (!B(i,k))
      {
        C(i,k)=L(i,k);
        B(i,k)=1;
      }
      */
      tmp-=L(i,k)*L(i,k);
    }
    if (tmp<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }
    L(i,i)=sqrt(tmp);
  }
  //C(n,n)=L(n,n);
  //B(n,n)=1;
  L.rowshift(rowsave);
  L.colshift(colsave);
  //cout << norm2(C-L) << endl;
  //cout << B << endl;
  //cout << L << endl;

  dvar_matrix vc=nograd_assign(L);
  save_identifier_string("rs");
  vc.save_dvar_matrix_position();
  save_identifier_string("rt");
  MM.save_dvar_matrix_value();
  save_identifier_string("rl");
  MM.save_dvar_matrix_position();
  save_identifier_string("ro");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfcholeski_decomp);
  return vc;
}

/**
 * Description not yet available.
 * \param
 */
void dfcholeski_decomp(void)
{
  verify_identifier_string("ro");
  dvar_matrix_position MMpos=restore_dvar_matrix_position();
  verify_identifier_string("rl");
  dmatrix M=restore_dvar_matrix_value(MMpos);
  verify_identifier_string("rt");
  dvar_matrix_position vcpos=restore_dvar_matrix_position();
  verify_identifier_string("rs");
  dmatrix dfL=restore_dvar_matrix_derivatives(vcpos);

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
  dmatrix tmp1(1,n,1,n);
  dmatrix dftmp1(1,n,1,n);
  dmatrix dfM(1,n,1,n);
  dvector dftmp(1,n);
  tmp.initialize();
  tmp1.initialize();
  dftmp.initialize();
  dftmp1.initialize();
  dfM.initialize();
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
 //*******************************************************************8
 //*******************************************************************8
 //*******************************************************************8
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
