/**
 * $Id: fvar_m42.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB Foundation
 */
#include <fvar.hpp>
#ifdef DEBUG
  #include <cassert>
  #include <climits>
#endif
#ifdef __TURBOC__
  #pragma hdrstop
  #include <iomanip.h>
#endif

#ifdef __ZTC__
  #include <iomanip.hpp>
#endif

#define TINY 1.0e-20;
void dfinvpret(void);

// int min(int a,int b);
void df_xldet(void);

#if defined(max)
#undef max
#endif
#if defined(min)
#undef min
#endif

dvariable ln_det(const dvar_matrix& aa, int& sgn);

dvariable ln_det(const dvar_matrix& a)
{
  int sgn = 1;
  return ln_det(a, sgn);
}
/**
\n\n The implementation of this algorithm was inspired by
"Numerical Recipes in C", 2nd edition,
Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
dvariable ln_det(const dvar_matrix& aa, int& sgn)
{
  int errflag=0;
  int i,j,k;
#if defined(DEBUG) && (__cplusplus >= 201103L)
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
  ivector indx(lb,ub);
  if (lb!=aa.rowmin()||ub!=aa.colmax())
  {
    cerr << "Error matrix not square in det()"<<endl;
    ad_exit(1);
  }
  int One=1;
  indx.fill_seqadd(lb,One);
  double ld;
  double big,dum,sum,temp;
  dvar_matrix_position dmp(aa,1);
  dmatrix bb=value(aa);
  dvector vv(lb,ub);
  dvector part_prod(lb,ub);

  ld=0.0;

  dvector* pbbi = &bb(lb);
  double* pvvi = vv.get_v() + lb;
  for (i=lb;i<=ub;i++)
  {
    big=0.0;
    double* pbbij = pbbi->get_v() + lb;
    for (j=lb;j<=ub;j++)
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
      cerr << "Error in matrix inverse -- matrix singular in "
      "inv(dvar_matrix)\n";
      big=1.e+10;
      errflag=1;
    }
    *pvvi = 1.0 / big;

    ++pbbi;
    ++pvvi;
  }

  dvector* pbbj = &bb(lb);
  double* pvvj = vv.get_v() + lb;
  for (j=lb;j<=ub;j++)
  {
    pbbi = &bb(lb);
    for (i=lb;i<j;i++)
    {
      sum = *(pbbi->get_v() + j);

      double* pbbik = pbbi->get_v() + lb;
      dvector* pbbk = &bb(lb);
      for (k=lb;k<i;k++)
      {
        sum = sum - *pbbik * *(pbbk->get_v() + j);

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
    pvvi = vv.get_v() + j;
    for (i=j;i<=ub;i++)
    {
      sum = *(pbbi->get_v() + j);

      double* pbbik = pbbi->get_v() + lb;
      dvector* pbbk = &bb(lb);
      for (k=lb;k<j;k++)
      {
        sum = sum - *pbbik * *(pbbk->get_v() + j);
        ++pbbik;
        ++pbbk;
      }
      *(pbbi->get_v() + j) = sum;
      dum = *pvvi * fabs(sum);
      if ( dum >= big)
      {
        big=dum;
        imax=i;
      }
      ++pbbi;
      ++pvvi;
    }
    if (j != imax)
    {
      double* pbbimaxk = bb(imax).get_v() + lb;
      double* pbbjk = pbbj->get_v() + lb;
      for (k=lb;k<=ub;k++)
      {
        dum = *pbbimaxk;
        *pbbimaxk = *pbbjk;
        *pbbjk = dum;

        ++pbbimaxk;
        ++pbbjk;
      }
      //d = -1.*d;
      sgn=-1*sgn;
      vv.elem(imax) = *pvvj;

      //if (j<ub)
      {
        int itemp=indx.elem(imax);
        indx.elem(imax)=indx.elem(j);
        indx.elem(j)=itemp;
      }
      //cout << "indx= " <<indx<<endl;
    }

    double* pbbjj = pbbj->get_v() + j;
    if (*pbbjj == 0.0)
    {
      *pbbjj = TINY;
    }

    if (j != n)
    {
      dum = 1.0 / *pbbjj;

      dvector* pbbi = &bb(j + 1);
      for (i=j+1;i<=ub;i++)
      {
        *(pbbi->get_v() + j) *= dum;
        ++pbbi;
      }
    }
    ++pvvj;
    ++pbbj;
  }
  double bb11 = bb(1, 1);
  if (bb11 > 0)
    part_prod(1)=ld+log(bb11);
  else
  {
    part_prod(1)=ld+log(-bb11);
    sgn=-sgn;
  }

  for (j=lb+1;j<=ub;j++)
  {
    double bbjj = bb(j, j);
    if (bbjj > 0)
      part_prod(j)=part_prod(j-1)+log(bbjj);
    else
    {
      part_prod(j)=part_prod(j-1)+log(-(bbjj));
      sgn=-sgn;
    }
  }
  double ldet=part_prod(ub);
  dvariable rdet=nograd_assign(ldet);

  grad_stack* GRAD_STACK1 = gradient_structure::GRAD_STACK1;
  DF_FILE* fp = gradient_structure::fp;
  save_identifier_string("PLACE7");
  fp->save_dvector_value(part_prod);
  fp->save_dvector_position(part_prod);
  fp->save_ivector_value(indx);
  fp->save_ivector_position(indx);
  save_identifier_string("PLACE3");
  fp->save_dvar_matrix_position(aa);
  fp->save_prevariable_position(rdet);
  fp->save_dmatrix_value(bb);
  save_identifier_string("PLACE2");
  fp->save_dmatrix_position(bb);
  save_identifier_string("PLACE1");
  fp->save_double_value(ld);
  save_identifier_string("PLACE0");
  GRAD_STACK1->set_gradient_stack(df_xldet);

  if (errflag) sgn=-1;
  return rdet;
}

/// Adjoint code for dvariable ln_det(const dvar_matrix& aa, int& sgn).
void df_xldet(void)
{
  DF_FILE* fp = gradient_structure::fp;

  verify_identifier_string("PLACE0");
  /*double ld=*/fp->restore_double_value();
  verify_identifier_string("PLACE1");
  dmatrix_position bpos=fp->restore_dmatrix_position();
  verify_identifier_string("PLACE2");
  dmatrix b=fp->restore_dmatrix_value(bpos);
  //dvar_matrix_position rdet_pos=restore_prevariable_position();
  double dfdet=fp->restore_prevariable_derivative();
  dvar_matrix_position a_pos=fp->restore_dvar_matrix_position();
  verify_identifier_string("PLACE3");
  ivector_position indx_pos=fp->restore_ivector_position();
  ivector indx=restore_ivector_value(indx_pos);
  dvector_position part_prod_pos=fp->restore_dvector_position();
  dvector part_prod=fp->restore_dvector_value(part_prod_pos);
  verify_identifier_string("PLACE7");
  int lb=b.colmin();
  int ub=b.colmax();
  dmatrix dfb(lb,ub,lb,ub);

  dvector dfpart_prod(lb,ub);

  #ifndef SAFE_INITIALIZE
    dfb.initialize();
    dfpart_prod.initialize();
  #endif

  dfpart_prod(ub)=dfdet;

  double* pdfpart_prodj = dfpart_prod.get_v() + ub;
  double* pdfpart_prodj_1 = dfpart_prod.get_v() + ub - 1;
  dvector* pbj = &b(ub);
  dvector* pdfbj = &dfb(ub);
  for (int j=ub;j>=lb+1;j--)
  {
    double bjj = *(pbj->get_v() + j);
    double* pdfbjj = pdfbj->get_v() + j;
    if (bjj > 0)
    {
      // part_prod(j)=part_prod(j-1)+log(b(j,j));
      *pdfpart_prodj_1 += *pdfpart_prodj;
      *pdfbjj += *pdfpart_prodj / bjj;
    }
    else
    {
      // part_prod(j)=part_prod(j-1)+log(-b(j,j));
      *pdfpart_prodj_1 += *pdfpart_prodj;
      *pdfbjj += *pdfpart_prodj / bjj;
    }
    *pdfpart_prodj = 0.0;

    --pdfpart_prodj;
    --pdfpart_prodj_1;
    --pbj;
    --pdfbj;
  }
  //part_prod(1)=ld+log(b(lb,lb));
  dfb(lb,lb)+=dfpart_prod(lb)/b(lb,lb);
  dfpart_prod(lb) = 0.0;

  double dfsum = 0.0;
  pdfbj = &dfb(ub);
  pbj = &b(ub);
  for (int j=ub;j>=lb;j--)
  {
    double bjj = *(pbj->get_v() + j);
    double* pdfbjj = pdfbj->get_v() + j;
    dvector* pdfbi = &dfb(ub);
    int* pindxi = indx.get_v() + ub;
    dvector* pbi = &b(ub);
    for (int i=ub;i>=lb;i--)
    {
      double* pdfbij = pdfbi->get_v() + j;
      if (i<=j)
      {
        // b(i,j)=sum;
        dfsum += *pdfbij;
        *pdfbij = 0.0;
      }
      else
      {
        // b(i,j)=sum/b(j,j);
        dfsum += *pdfbij / bjj;
        *pdfbjj -= *pdfbij * *(pbi->get_v() + j) / bjj;
        *pdfbij = 0.0;
      }

      for (int k=min(i-1,j-1);k>=lb;k--)
      {
        // sum-=b(i,k)*b(k,j);
        dfb(i,k)-=dfsum*b(k,j);
        dfb(k,j)-=dfsum*b(i,k);
      }
      // sum=value(a(indx(i),j);
      save_dmatrix_derivatives(a_pos,dfsum,*pindxi,j); // like this
      dfsum = 0.0;

      --pdfbi;
      --pindxi;
      --pbi;
    }

    --pdfbj;
    --pbj;
  }
}

#undef TINY
