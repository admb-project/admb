/**
 * $Id: dmat34.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB Foundation
 */
#include <fvar.hpp>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#if defined (__WAT32__)
  #include <iostream.h>
  #include <strstrea.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#define TINY 1.0e-20;
void dmdv_solve(void);


/** Solve a linear system using LU decomposition. */
dvector csolve(const dmatrix& aa,const dvector& z)
{
  double ln_unsigned_det;
  double sign;
  dvector sol=solve(aa,z,ln_unsigned_det,sign);
  return sol;
}

/** Solve a linear system using LU decomposition.
    \param aa A dmatrix containing LU decomposition of input matrix. \f$a\f$.
    \param z A dvector containing the RHS, \f$b\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A dvector containing solution vector \f$X\f$.
*/
dvector solve(const dmatrix& aa,const dvector& z)
{
  double ln_unsigned_det;
  double sign;
  dvector sol=solve(aa,z,ln_unsigned_det,sign);
  return sol;
}

/** Solve a linear system using LU decomposition.
    \param aa A dmatrix containing LU decomposition of input matrix. \f$a\f$.
    \param z A dvector containing the RHS, \f$b\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \param _ln_unsigned_deg
    \param sign
    \return A dvector containing solution vector \f$X\f$.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
dvector solve(const dmatrix& aa,const dvector& z,
  const double& _ln_unsigned_det,double& sign)
{
  double& ln_unsigned_det=(double&) (_ln_unsigned_det);
#if !defined(OPT_LIB) && (__cplusplus >= 201103L)
  int n = [](unsigned int colsize) -> int
  {
    assert(colsize <= INT_MAX);
    return static_cast<int>(colsize);
  } (aa.colsize());
#else
  int n = static_cast<int>(aa.colsize());
#endif
  int lb=aa.colmin();
  int ub=aa.colmax();
  if (lb!=aa.rowmin()||ub!=aa.rowmax())
  {
    cerr << "Error matrix not square in solve()"<<endl;
    ad_exit(1);
  }
  dmatrix bb(lb,ub,lb,ub);
  bb=aa;
  ivector indx(lb,ub);
  int One=1;
  indx.fill_seqadd(lb,One);
  double d;
  double big,dum,sum,temp;
  dvector vv(lb,ub);

  d=1.0;
  dvector* pbbi = &bb(lb);
  double* pvvi = &vv(lb);
  for (int i=lb;i<=ub;i++)
  {
    big=0.0;
    double* pbbij = pbbi->get_v() + lb;
    for (int j=lb;j<=ub;j++)
    {
      temp=fabs(*pbbij);
      if (temp > big)
      {
        big=temp;
      }
      ++pbbij;
    }
    if (big == 0.0)
    {
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
    }
    *pvvi = 1.0 / big;

    ++pvvi;
    ++pbbi;
  }

  for (int j=lb;j<=ub;j++)
  {
    dvector* pbbi = &bb(lb);
    for (int i=lb;i<j;i++)
    {
      sum = *(pbbi->get_v() + j);
      double* pbbik = pbbi->get_v() + lb;
      dvector* pbbk = &bb(lb);
      for (int k=lb;k<i;k++)
      {
        sum -= *pbbik * *(pbbk->get_v() + j);

	++pbbik;
	++pbbk;
      }
      //a[i][j]=sum;
      *(pbbi->get_v() + j) = sum;

      ++pbbi;
    }
    int imax = j;
    big=0.0;

    pbbi = &bb(j);
    for (int i=j;i<=ub;i++)
    {
      sum = *(pbbi->get_v() + j);
      double* pbbik = pbbi->get_v() + lb;
      dvector* pbbk = &bb(lb);
      for (int k=lb;k<j;k++)
      {
        sum -= *pbbik * *(pbbk->get_v() + j);

	++pbbik;
	++pbbk;
      }
      *(pbbi->get_v() + j) = sum;
      dum=vv[i]*fabs(sum);
      if (dum >= big)
      {
        big = dum;
        imax = i;
      }
      ++pbbi;
    }
    if (j != imax)
    {
      for (int k=lb;k<=ub;k++)
      {
        dum=bb(imax,k);
        bb(imax,k)=bb(j,k);
        bb(j,k)=dum;
      }
      d = -1.*d;
      vv[imax]=vv[j];

      //if (j<ub)
      {
        int itemp=indx(imax);
        indx(imax)=indx(j);
        indx(j)=itemp;
      }
      //cout << "indx= " <<indx<<endl;
    }

    if (bb(j,j) == 0.0)
    {
      bb(j,j)=TINY;
    }

    if (j != n)
    {
      dum=1.0/bb(j,j);
      for (int i=j+1;i<=ub;i++)
      {
        bb(i,j) = bb(i,j) * dum;
      }
    }
  }

  // get the determinant
  sign=d;
  dvector part_prod(lb,ub);
  part_prod(lb)=log(fabs(bb(lb,lb)));
  if (bb(lb,lb)<0) sign=-sign;
  for (int j=lb+1;j<=ub;j++)
  {
    if (bb(j,j)<0) sign=-sign;
    part_prod(j)=part_prod(j-1)+log(fabs(bb(j,j)));
  }
  ln_unsigned_det=part_prod(ub);

  dvector x(lb,ub);
  dvector y(lb,ub);
  //int lb=rowmin;
  //int ub=rowmax;
  dmatrix& b=bb;
  ivector indxinv(lb,ub);

  int* pindxi = indx.get_v() + lb;
  for (int i=lb;i<=ub;i++)
  {
    indxinv(*pindxi) = i;
    ++pindxi;
  }

  int* pindxinvi = indxinv.get_v() + lb;
  for (int i=lb;i<=ub;i++)
  {
    y(*pindxinvi)=z(i);
    ++pindxinvi;
  }

  dvector* pbi = &b(lb);
  double* pyi = &y(lb);
  for (int i=lb;i<=ub;i++)
  {
    sum = *pyi;

    double* pbij = pbi->get_v() + lb;
    double* pyj = &y(lb);
    for (int j=lb;j<=i-1;j++)
    {
      sum -= *pbij * *pyj;

      ++pyj;
      ++pbij;
    }
    *pyi = sum;

    ++pyi;
    ++pbi;
  }
  pbi = &b(ub);
  pyi = &y(ub);
  double* pxi = x.get_v() + ub;
  for (int i=ub;i>=lb;i--)
  {
    sum = *pyi;

    double* pbij = pbi->get_v() + i + 1;
    double* pxj = x.get_v() + i + 1;
    for (int j=i+1;j<=ub;j++)
    {
      sum -= *pbij * *pxj;

      ++pbij;
      ++pxj;
    }
    *pxi = sum / *(pbi->get_v() + i);

    --pbi;
    --pyi;
    --pxi;
  }

  return x;
}
#undef TINY
