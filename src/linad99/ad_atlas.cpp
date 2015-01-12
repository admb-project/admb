/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 * 
 */

#include <admodel.h>

#if defined USE_ATLAS

#include <clapack.h>

dvector atlas_solve_spd(const dmatrix & M, const dvector & x)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (mmin != M(mmin).indexmin() ||
     mmax != M(mmin).indexmax())
  {
    cerr << "Matrix not square in dvector atlas_solve_spd"
         << endl;
    ad_exit(1);
  }
  if (mmin != x.indexmin() || mmax != x.indexmax()) 
  {
    cerr << "Incompatible matrix and vector sizes in dvector atlas_solve_spd"
         << endl;
    ad_exit(1);
  }
  dvector v(mmin,mmax);
  int sz=mmax-mmin+1;
  dvector M1(1,sz*sz);
  int ii=1;
  int i,j;
  for (i=mmin;i<=mmax;i++)
  {
    for (j=mmin;j<=mmax;j++)
    {
      M1(ii++)=M(i,j);
    }
  }
  v=x;
  double *Ap= &(M1(1)); 
  double *X = &(v(mmin)); const int incX=1;
   
  const enum CBLAS_ORDER Order=CblasRowMajor;
  const enum CBLAS_UPLO Uplo=CblasLower;
  const enum CBLAS_TRANSPOSE TransA=CblasNoTrans; 
  const enum CBLAS_DIAG Diag=CblasNonUnit;
      
  int retr=clapack_dposv(Order, Uplo, sz,1, Ap, sz, X, sz);
  return v;
}

dvector atlas_solve_spd(const dmatrix & M, const dvector & x, int& ierr)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (mmin != M(mmin).indexmin() ||
     mmax != M(mmin).indexmax())
  {
    cerr << "Matrix not square in dvector atlas_solve_spd"
         << endl;
    ad_exit(1);
  }
  if (mmin != x.indexmin() || mmax != x.indexmax()) 
  {
    cerr << "Incompatible matrix and vector sizes in dvector atlas_solve_spd"
         << endl;
    ad_exit(1);
  }
  dvector v(mmin,mmax);
  int sz=mmax-mmin+1;
  dvector M1(1,sz*sz);
  int ii=1;
  int i,j;
  for (i=mmin;i<=mmax;i++)
  {
    for (j=mmin;j<=mmax;j++)
    {
      M1(ii++)=M(i,j);
    }
  }
  v=x;
  double *Ap= &(M1(1)); 
  double *X = &(v(mmin)); const int incX=1;
   
  const enum CBLAS_ORDER Order=CblasRowMajor;
  const enum CBLAS_UPLO Uplo=CblasLower;
  const enum CBLAS_TRANSPOSE TransA=CblasNoTrans; 
  const enum CBLAS_DIAG Diag=CblasNonUnit;
      
  int retr=clapack_dposv(Order, Uplo, sz,1, Ap, sz, X, sz);
  ierr=retr;
  return v;
}


dmatrix atlas_solve_spd(const dmatrix & M, const dmatrix & N)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int nmin=N.indexmin();
  int nmax=N.indexmax();
  if (mmin != M(mmin).indexmin() ||
     mmax != M(mmin).indexmax())
  {
    cerr << "Matrix not square in dvector atlas_solve_spd"
         << endl;
    ad_exit(1);
  }
  if (mmin != N(nmin).indexmin() || mmax != N(nmin).indexmax() ) 
  {
    cerr << "Incompatible matrix and vector sizes in dmatrix atlas_solve_spd"
         << endl;
    ad_exit(1);
  }
  int sz=mmax-mmin+1;
  int szn=nmax-nmin+1;
  dvector M1(1,sz*sz);
  dvector N1(1,sz*szn);
  int ii=1;
  int i,j;
  for (i=mmin;i<=mmax;i++)
  {
    for (j=mmin;j<=mmax;j++)
    {
      M1(ii++)=M(i,j);
    }
  }
  ii=1;
  for (i=nmin;i<=nmax;i++)
  {
    for (j=mmin;j<=mmax;j++)
    {
      N1(ii++)=N(i,j);
    }
  }
  double *Ap= &(M1(1)); 
  double *X = &(N1(1)); const int incX=1;
   
  const enum CBLAS_ORDER Order=CblasRowMajor;
  const enum CBLAS_UPLO Uplo=CblasLower;
  const enum CBLAS_TRANSPOSE TransA=CblasNoTrans; 
  const enum CBLAS_DIAG Diag=CblasNonUnit;
      
  //int retr=clapack_dposv(Order, Uplo, sz,1  , Ap, sz, X, sz);
  int retr=clapack_dposv(Order, Uplo, sz,szn, Ap, sz, X, sz);
  dmatrix tmp(nmin,nmax,mmin,mmax);

  ii=0;
  for (i=nmin;i<=nmax;i++)
  {
    for (j=mmin;j<=mmax;j++)
    {
      tmp(i,j)=X[ii++];
    }
  }
  return tmp;
}

dmatrix atlas_solve_spd_trans(const dmatrix & M, const dmatrix & N)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (mmin != M(mmin).indexmin() ||
     mmax != M(mmin).indexmax())
  {
    cerr << "Matrix not square in dvector atlas_solve_spd"
         << endl;
    ad_exit(1);
  }
  if (mmin != N.indexmin() || mmax != N.indexmax() ) 
  {
    cerr << "Incompatible matrix and vector sizes in dmatrix atlas_solve_spd"
         << endl;
    ad_exit(1);
  }
  int nmin=N(mmin).indexmin();
  int nmax=N(mmin).indexmax();
  int sz=mmax-mmin+1;
  int szn=nmax-nmin+1;
  dvector M1(1,sz*sz);
  dvector N1(1,sz*szn);
  int ii=1;
  int i,j;
  for (i=mmin;i<=mmax;i++)
  {
    for (j=mmin;j<=mmax;j++)
    {
      M1(ii++)=M(i,j);
    }
  }
  ii=1;
  for (j=nmin;j<=nmax;j++)
  {
    for (i=mmin;i<=mmax;i++)
    {
      N1(ii++)=N(i,j);
    }
  }
  double *Ap= &(M1(1)); 
  double *X = &(N1(1)); const int incX=1;
   
  const enum CBLAS_ORDER Order=CblasRowMajor;
  const enum CBLAS_UPLO Uplo=CblasLower;
  const enum CBLAS_TRANSPOSE TransA=CblasNoTrans; 
  const enum CBLAS_DIAG Diag=CblasNonUnit;
      
  //int retr=clapack_dposv(Order, Uplo, sz,1  , Ap, sz, X, sz);
  int retr=clapack_dposv(Order, Uplo, sz,szn, Ap, sz, X, sz);
  dmatrix tmp(mmin,mmax,nmin,nmax);

  ii=0;
  for (j=nmin;j<=nmax;j++)
  {
    for (i=mmin;i<=mmax;i++)
    {
      tmp(i,j)=X[ii++];
    }
  }
  return tmp;
}



#endif //#if defined USE_ATLAS
