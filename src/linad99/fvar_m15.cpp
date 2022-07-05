/**
 * $Id: fvar_m15.cpp 789 2010-10-05 01:01:09Z johnoel $
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

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#define TINY 1.0e-20;
void dfinvpret(void);

/**
Return smallest value of two integers a or b
\param a An integer
\param b An integer
\return A integer \f$ z = \min(a,b)\f$
*/
int min(const int a, const int b)
{
  return a <= b ? a : b;
}

/** Inverse of a varaiable matrix.
    \param aa dvar_matrix conaining matrix to be inverted,\f$A\f$.
    \return dvar_matrix containing \f$A^{-1}\f$.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
dvar_matrix inv(const dvar_matrix& aa)
{
  int imax = 0;
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
  dvar_matrix vc(lb,ub,lb,ub);
  if (n==1)
  {
    if (aa(lb,lb)==0.0)
    {
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
      ad_exit(1);
    }
    else
    {
      vc(lb,lb)=1.0/aa(lb,lb);
      return vc;
    }
  }
  ivector indx(lb,ub);
  int One=1;
  indx.fill_seqadd(lb,One);
  double d;
  double big,dum,sum,temp;
  dvar_matrix_position dmp(aa,0);
  dmatrix bb=value(aa);
  dvector vv(lb,ub);

  d=1.0;
  dvector* pbbi = &bb.elem(lb);
  double* pvvi = vv.get_v() + lb;
  for (int i=lb;i<=ub;i++)
  {
    big=0.0;
    double* pbbij = pbbi->get_v() + lb;
    for (int j=lb;j<=ub;j++)
    {
      temp = fabs(*pbbij);
      if (temp > big)
      {
        big=temp;
      }
      ++pbbij;
    }
    if (big == 0.0)
    {
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
      ad_exit(1);
    }
    *pvvi = 1.0 / big;

    ++pbbi;
    ++pvvi;
  }

  for (int j=lb;j<=ub;j++)
  {
    dvector* pbbi = &bb.elem(lb);
    for (int i=lb;i<j;i++)
    {
      sum = *(pbbi->get_v() +j);

      double* pbbik = pbbi->get_v() + lb;
      dvector* pbbk = &bb.elem(lb);
      for (int k=lb;k<i;k++)
      {
        sum = sum - *pbbik * *(pbbk->get_v() + j);
        ++pbbik;
        ++pbbk;
      }
      //a[i][j]=sum;
      *(pbbi->get_v() +j) = sum;

      ++pbbi;
    }
    big=0.0;
    pbbi = &bb.elem(j);
    for (int i=j;i<=ub;i++)
    {
      sum = *(pbbi->get_v() + j);

      double* pbbik = pbbi->get_v() + lb;
      dvector* pbbk = &bb.elem(lb);
      for (int k=lb;k<j;k++)
      {
        sum = sum - *pbbik * *(pbbk->get_v() + j);
        ++pbbik;
        ++pbbk;
      }
      *pbbik = sum;

      dum=vv[i]*fabs(sum);
      if ( dum >= big)
      {
        big=dum;
        imax=i;
      }
      ++pbbi;
    }
    if (j != imax)
    {
      double* pbbimaxk = bb.elem(imax).get_v() + lb;
      double* pbbjk = bb.elem(j).get_v() + lb;
      for (int k=lb;k<=ub;k++)
      {
        dum = *pbbimaxk;
        *pbbimaxk = *pbbjk;
        *pbbjk = dum;

        ++pbbimaxk;
        ++pbbjk;
      }
      d = -1.*d;
      vv[imax]=vv[j];

      //if (j<ub)
      {
        int itemp=indx.elem(imax);
        indx.elem(imax)=indx.elem(j);
        indx.elem(j)=itemp;
      }
      //cout << "indx= " <<indx<<endl;
    }

    if (bb.elem(j,j) == 0.0)
    {
      bb.elem(j,j)=TINY;
    }

    if (j != n)
    {
      dum=1.0/bb.elem(j,j);
      pbbi = &bb.elem(j + 1);
      for (int i=j+1;i<=ub;i++)
      {
        *(pbbi->get_v() + j) *= dum;
        ++pbbi;
      }
    }
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  dvector y(lb,ub);
  dvector x(lb,ub);
  //int lb=rowmin;
  //int ub=rowmax;
  dmatrix& b=bb;
  ivector indxinv(lb,ub);
  int* pindx = indx.get_v() + lb;
  int* pindxinv = indxinv.get_v();
  for (int i=lb;i<=ub;i++)
  {
    *(pindxinv + *pindx)=i;
    ++pindx;
  }

  pindxinv = indxinv.get_v() + lb;
  for (int ii=lb;ii<=ub;ii++)
  {
    y.initialize();
    const int indxinvii = *pindxinv;
    y(indxinvii) = 1.;

    dvector* pbi = &b.elem(indxinvii);
    double* pyi = y.get_v() + indxinvii;
    for (int i=indxinvii;i<=ub;i++)
    {
      // sum=y(ii,i);
      if (i==indxinvii)
      {
        sum=1.;
      }
      else
      {
        sum=0.;
      }
      double* pbij = pbi->get_v() + indxinvii;
      double* pyj = y.get_v() + indxinvii;
      for (int j=indxinvii;j<=i-1;j++)
      {
        sum -= *pbij * *pyj;

        ++pbij;
        ++pyj;
      }
      *pyi = sum;

      ++pbi;
      ++pyi;
    }
    pyi = y.get_v() + ub;
    double* pxi = x.get_v() + ub;
    pbi = &b.elem(ub);
    for (int i=ub;i>=lb;i--)
    {
      sum = *pyi;
      double* pxj = x.get_v() + i + 1;
      double* pbij = pbi->get_v() + i + 1;
      for (int j=i+1;j<=ub;j++)
      {
        sum -= *pbij * *pxj;

        ++pxj;
        ++pbij;
      }
      *pxi = sum / *(pbi->get_v() + i);

      --pyi;
      --pbi;
      --pxi;
    }
    fp->save_dvector_value(y);
    fp->save_dvector_value(x);
    nograd_assign_column(vc,x,ii);
    ++pindxinv;
  }

  save_identifier_string("P5");
  fp->save_dvector_position(x);
  fp->save_dvector_position(y);
  fp->save_ivector_value(indx);
  fp->save_ivector_position(indx);
  fp->save_dvar_matrix_position(aa);
  fp->save_dvar_matrix_position(vc);
  fp->save_dmatrix_value(bb);
  fp->save_dmatrix_position(bb);
  save_identifier_string("P1");
  gs->GRAD_STACK1->set_gradient_stack(dfinvpret);
  return vc;
}

/** Adjoint code for dvar_matrix inv(const dvar_matrix& aa).
*/
void dfinvpret(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  verify_identifier_string("P1");
  dmatrix_position bpos=fp->restore_dmatrix_position();
  dmatrix b=fp->restore_dmatrix_value(bpos);
  dvar_matrix_position v_pos=fp->restore_dvar_matrix_position();
  dvar_matrix_position a_pos=fp->restore_dvar_matrix_position();
  ivector_position indx_pos=fp->restore_ivector_position();
  ivector indx=restore_ivector_value(indx_pos);
  dvector_position y_pos=fp->restore_dvector_position();
  dvector_position x_pos=fp->restore_dvector_position();
  verify_identifier_string("P5");
  int lb=b.colmin();
  int ub=b.colmax();
  dmatrix dfb(lb,ub,lb,ub);
  ivector indxinv(lb,ub);

  int* pindx = indx.get_v() + lb;
  int* pindxinv = indxinv.get_v();
  for (int i=lb;i<=ub;i++)
  {
    *(pindxinv + *pindx) = i;
    ++pindx;
  }

  double dfsum=0.;
  dvector dfy(lb,ub);
  #ifndef SAFE_INITIALIZE
    dfb.initialize();
    dfy.initialize();
  #endif
  for (int ii=ub;ii>=lb;ii--)
  {
    //x.save_dvector_value();
    dvector x=fp->restore_dvector_value(x_pos);
    //y.save_dvector_value();
    dvector y=fp->restore_dvector_value(y_pos);
    dvector dfx=restore_dvar_matrix_derivative_column(v_pos,ii);

    double* pdfxi = dfx.get_v() + lb;
    double* pxi = x.get_v() + lb;
    dvector* pdfbi = &dfb.elem(lb);
    dvector* pbi = &b.elem(lb);
    for (int i=lb;i<=ub;i++)
    {
      // x.elem(i)=sum/b.elem(i,i);
      dfsum+= *pdfxi / b.elem(i,i);
      *(pdfbi->get_v() + i) -= *pdfxi * *pxi / b.elem(i,i);
      *pdfxi = 0.0;

      double* pdfxj = dfx.get_v() + ub;
      double* pxj = x.get_v() + ub;
      double* pdfbij = pdfbi->get_v() + ub;
      double* pbij = pbi->get_v() + ub;
      for (int j=ub;j>=i+1;j--)
      {
        // sum -=b.elem(i,j)*x.elem(j);
        *pdfbij -= dfsum * *pxj;
        *pdfxj -= dfsum * *pbij;

        --pdfxj;
        --pxj;
        --pdfbij;
        --pbij;
      }
      // sum=y.elem(i);
      dfy.elem(i)+=dfsum;
      dfsum=0.;

      ++pdfxi;
      ++pxi;
      ++pdfbi;
      ++pbi;
    }

    //for (i=ub;i>=lb;i--)
    int indxinvii = indxinv(ii);
    double* pdfyi2 = dfy.get_v() + ub;
    for (int i2=ub;i2>=indxinvii;i2--)
    {
      // y.elem(i)=sum;
      dfsum += *pdfyi2;
      *pdfyi2 = 0.0;
      // for (int j=i-1;j>=lb;j--)
      double* pyj = y.get_v() + i2 - 1;
      double* pdfyj = dfy.get_v() + i2 - 1;
      for (int j=i2-1;j>=indxinvii;j--)
      {
        // sum-=b.elem(i,j)*y.elem(j);
        dfb.elem(i2,j) -= dfsum * *pyj;
        *pdfyj -= dfsum*b.elem(i2,j);

        --pyj;
        --pdfyj;
      }
      //sum=y.elem(i);
      *pdfyi2 = dfsum;
      dfsum = 0.0;

      --pdfyi2;
    }
    //x.initialize()
    //y.initialize()
    dfx.initialize();
    dfy.initialize();
  }

  for (int j=ub;j>=lb;j--)
  {
    double bjj = b.elem(j, j);
    dvector* pdfbi = &dfb.elem(ub);
    int* pindxi = indx.get_v() + ub;
    for (int i=ub;i>=lb;i--)
    {
      double* pdfbij = pdfbi->get_v() + j;
      if (i<=j)
      {
        // b.elem(i,j)=sum;
        dfsum+= *pdfbij;
        *pdfbij = 0.0;
      }
      else
      {
        // b.elem(i,j)=sum/b.elem(j,j);
        dfsum += *pdfbij / bjj;
        dfb.elem(j,j) -= *pdfbij * b.elem(i,j) / bjj;
        *pdfbij = 0.0;
      }

      for (int k=min(i-1,j-1);k>=lb;k--)
      {
        // sum-=b.elem(i,k)*b.elem(k,j);
        dfb.elem(i,k)-=dfsum*b.elem(k,j);
        dfb.elem(k,j)-=dfsum*b.elem(i,k);
      }
      // sum=value(a(indx.elem(i),j);
      save_dmatrix_derivatives(a_pos,dfsum, *pindxi, j); // like this
      dfsum=0.;

      --pindxi;
      --pdfbi;
    }
  }
}

#undef TINY
