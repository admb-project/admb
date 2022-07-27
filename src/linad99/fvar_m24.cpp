/**
 * $Id: fvar_m24.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: Unknown
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

dvar_vector solve(const dvar_matrix& aa, const dvar_vector& z,
  prevariable& ln_unsigned_det, const prevariable& sign);
/** Solve a linear system using LU decomposition.
\param aa A dvar_matrix containing LU decomposition of input matrix. \f$a\f$.
    \param z A dvar_vector containing the RHS, \f$b\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A dvar_vector containing solution vector \f$X\f$.
*/
dvar_vector solve(const dvar_matrix& aa, const dvar_vector& z)
{
  dvariable ln_unsigned_det;
  dvariable sign;
  dvar_vector sol=solve(aa,z,ln_unsigned_det,sign);
  return sol;
}

/** Solve a linear system using LU decomposition.
\param aa A dvar_matrix containing LU decomposition of input matrix. \f$a\f$.
    \param z A dvar_vector containing the RHS, \f$b\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \param _ln_unsigned_deg
    \param sign
    \return A dvar_vector containing solution vector \f$X\f$.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
dvar_vector solve(const dvar_matrix& aa, const dvar_vector& z,
  prevariable& ln_unsigned_det, const prevariable& _sign)
{
  prevariable& sign=(prevariable&) _sign;

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  gs->RETURN_ARRAYS_INCREMENT();

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
  if (lb!=aa.rowmin()||ub!=aa.colmax())
  {
    cerr << "Error matrix not square in solve()"<<endl;
    ad_exit(1);
  }
  ivector indx(lb,ub);
  int One=1;
  indx.fill_seqadd(lb,One);
  double d;
  double big,dum,sum,temp;
  dvar_matrix_position dmp(aa,0);
  dmatrix bb=value(aa);
  kkludge_object kkk;
  dvar_vector vc(lb,ub,kkk);
  dvector vv(lb,ub);

  d=1.0;
  double* pvv = vv.get_v() + lb;
  dvector* pbbi = &bb.elem(lb);
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
      cerr << "Error in matrix inverse -- matrix singular in "
      "solve(dvar_dmatrix)\n";
    }
    *pvv = 1.0/big;
    ++pvv;
    ++pbbi;
  }

  dvector* pbbj = &bb.elem(lb);
  for (int j=lb;j<=ub;j++)
  {
    dvector* pbbi = &bb.elem(lb);
    for (int i = lb; i < j; ++i)
    {
      double* pbbij = pbbi->get_v() + j;
      sum = *pbbij;

      double* pbbik = pbbi->get_v() + lb;
      dvector* pbbk = &bb.elem(lb);
      for (int k=lb;k<i;k++)
      {
        sum -= *pbbik * *(pbbk->get_v() + j);
        ++pbbik;
        ++pbbk;
      }

      //a[i][j]=sum;
      *pbbij = sum;

      ++pbbi;
    }

    int imax = j;
    big=0.0;
    pvv = vv.get_v() + j;

    pbbi = pbbj;
    for (int i=j;i<=ub;i++)
    {
      double* pbbij = pbbi->get_v() + j;
      sum = *pbbij;

      double* pbbik = pbbi->get_v() + lb;
      dvector* pbbk = &bb.elem(lb);
      for (int k=lb;k<j;k++)
      {
        sum -= *pbbik * *(pbbk->get_v() + j);
        ++pbbik;
        ++pbbk;
      }
      *pbbij = sum;
      dum = *pvv * fabs(sum);
      if (dum >= big)
      {
        big = dum;
        imax = i;
      }
      ++pvv;
      ++pbbi;
    }

    if (j != imax)
    {
      double* pbbimaxk = bb.elem(imax).get_v() + lb;
      double* pbbjk = pbbj->get_v() + lb;
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
      int* pindximax = indx.get_v() + imax;
      int* pindxj = indx.get_v() + j;
      {
        int itemp = *pindximax;
        *pindximax = *pindxj;
        *pindxj = itemp;
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
      dvector* pbbi = &bb.elem(j + 1);
      for (int i=j+1;i<=ub;i++)
      {
        double* pbbij = pbbi->get_v() + j;
        *pbbij = *pbbij * dum;

        ++pbbi;
      }
    }

    ++pbbj;
  }

  // get the determinant
  sign=d;
  dvector part_prod(lb,ub);
  part_prod(lb)=log(fabs(bb(lb,lb)));
  if (bb(lb,lb)<0) sign=-sign;
  for (int j=lb+1;j<=ub;j++)
  {
    double bbjj = bb(j, j);
    if (bbjj < 0) sign=-sign;
    part_prod(j)=part_prod(j-1)+log(fabs(bbjj));
  }
  ln_unsigned_det=part_prod(ub);

  dvector x(lb,ub);
  dvector y(lb,ub);
  //int lb=rowmin;
  //int ub=rowmax;
  dmatrix& b=bb;
  ivector indxinv(lb,ub);

  int* pindx = indx.get_v() + lb;
  int* pindxinv = indxinv.get_v();
  for (int i = lb; i <= ub; ++i)
  {
    *(pindxinv + *pindx) = i;
    ++pindx;
  }

  double_and_int* pz = z.get_va() + lb;
  pindxinv = indxinv.get_v() + lb;
  double* py = y.get_v();
  for (int i = lb; i <= ub; ++i)
  {
    *(py + *pindxinv) = pz->x;

    ++pz;
    ++pindxinv;
  }

  py = y.get_v() + lb;
  dvector* pbi = &b.elem(lb);
  for (int i=lb;i<=ub;i++)
  {
    sum = *py;

    double* pyj = y.get_v() + lb;
    double* pbij = pbi->get_v() + lb;
    for (int j=lb;j<=i-1;j++)
    {
      sum -= *pbij * *pyj;

      ++pyj;
      ++pbij;
    }

    *py = sum;

    ++py;
    ++pbi;
  }

  py = y.get_v() + ub;
  double* px = x.get_v() + ub;
  pbi = &b.elem(ub);
  for (int i=ub;i>=lb;i--)
  {
    sum = *py;

    double* pxj = x.get_v() + i + 1;
    double* pbij = pbi->get_v() + i + 1;
    for (int j=i+1;j<=ub;j++)
    {
      sum -= *pbij * *pxj;

      ++pxj;
      ++pbij;
    }
    *px = sum / *(pbi->get_v() + i);

    --pbi;
    --py;
    --px;
  }

  vc=nograd_assign(x);
  save_identifier_string("PLACE8");
  fp->save_prevariable_position(ln_unsigned_det);
  save_identifier_string("PLACE7");
  fp->save_dvector_value(part_prod);
  fp->save_dvector_position(part_prod);
  save_identifier_string("PLACE6");
  fp->save_dvector_value(y);
  fp->save_dvector_value(x);
  save_identifier_string("PLACE5");
  fp->save_dvector_position(x);
  save_identifier_string("PLACE4");
  fp->save_dvector_position(y);
  fp->save_ivector_value(indx);
  save_identifier_string("PLACE3a");
  fp->save_ivector_position(indx);
  save_identifier_string("PLACE3");
  fp->save_dvar_matrix_position(aa);
  save_identifier_string("PLACE2b");
  fp->save_dvar_vector_position(vc);
  save_identifier_string("PLACE2a");
  fp->save_dmatrix_value(bb);
  save_identifier_string("PLACE2");
  fp->save_dmatrix_position(bb);
  save_identifier_string("PLACE1");
  fp->save_dvar_vector_position(z);
  save_identifier_string("PLACE0");
  gs->GRAD_STACK1->set_gradient_stack(dmdv_solve);
  gs->RETURN_ARRAYS_DECREMENT();
  return vc;
}

/// Adjoint code for
/// dvar_vector solve(const dvar_matrix& aa, const dvar_vector& z,
void dmdv_solve(void)
{
  DF_FILE* fp = gradient_structure::fp;

  verify_identifier_string("PLACE0");
  dvar_vector_position zpos=fp->restore_dvar_vector_position();
  verify_identifier_string("PLACE1");
  dmatrix_position bpos=fp->restore_dmatrix_position();
  verify_identifier_string("PLACE2");
  dmatrix b=fp->restore_dmatrix_value(bpos);
  verify_identifier_string("PLACE2a");
  dvar_vector_position v_pos=fp->restore_dvar_vector_position();
  verify_identifier_string("PLACE2b");
  dvar_matrix_position a_pos=fp->restore_dvar_matrix_position();
  verify_identifier_string("PLACE3");
  ivector_position indx_pos=fp->restore_ivector_position();
  verify_identifier_string("PLACE3a");
  ivector indx=restore_ivector_value(indx_pos);
  dvector_position y_pos=fp->restore_dvector_position();
  verify_identifier_string("PLACE4");
  dvector_position x_pos=fp->restore_dvector_position();
  verify_identifier_string("PLACE5");
  dvector x=fp->restore_dvector_value(x_pos);
  dvector y=fp->restore_dvector_value(y_pos);
  verify_identifier_string("PLACE6");
  dvector_position part_prod_pos=fp->restore_dvector_position();
  dvector part_prod=fp->restore_dvector_value(part_prod_pos);
  verify_identifier_string("PLACE7");
  double df_ln_det=fp->restore_prevariable_derivative();
  verify_identifier_string("PLACE8");
  int lb=b.colmin();
  int ub=b.colmax();
  dmatrix dfb(lb,ub,lb,ub);
  dvector dfz(lb,ub);
  dvector dfx=restore_dvar_vector_derivatives(v_pos);
  dvector dfy(lb,ub);
  dvector dfpart_prod(lb,ub);
  ivector indxinv(lb,ub);

  int* pindx = indx.get_v() + lb;
  int* pindxinv = indxinv.get_v();
  for (int i = lb; i <= ub; ++i)
  {
    *(pindxinv + *pindx) = i;
    ++pindx;
  }

  double dfsum=0.;
  #ifndef SAFE_INITIALIZE
    dfb.initialize();
    dfy.initialize();
    dfz.initialize();
    dfpart_prod.initialize();
  #endif

  double* pdfxi = dfx.get_v() + lb;
  double* pdfyi = dfy.get_v() + lb;
  double* pxi = x.get_v() + lb;
  dvector* pbi = &b.elem(lb);
  dvector* pdfbi = &dfb.elem(lb);
  for (int i = lb; i <= ub; ++i)
  {
    double* pbii = pbi->get_v() + i;

    // x.elem(i)=sum/b.elem(i,i);
    dfsum += *pdfxi / *pbii;
    *(pdfbi->get_v() + i) -= *pdfxi * *pxi / *pbii;
    *pdfxi = 0.0;

    double* pxj = x.get_v() + ub;
    double* pdfxj = dfx.get_v() + ub;
    double* pbij = pbi->get_v() + ub;
    double* pdfbij = pdfbi->get_v() + ub;
    for (int j = ub; j >= i + 1; --j)
    {
      // sum -=b.elem(i,j)*x.elem(j);
      *pdfbij -= dfsum* *pxj;
      *pdfxj -= dfsum * *pbij;
      --pxj;
      --pdfxj;
      --pbij;
      --pdfbij;
    }

    // sum=y.elem(i);
    *pdfyi += dfsum;
    dfsum = 0.0;

    ++pdfxi;
    ++pdfyi;
    ++pxi;
    ++pbi;
    ++pdfbi;
  }

  pdfyi = dfy.get_v() + ub;
  pdfbi = &dfb.elem(ub);
  pbi = &b.elem(ub);
  for (int i=ub;i>=lb;i--)
  {
    // y.elem(i)=sum;
    dfsum += *pdfyi;
    *pdfyi = 0.0;

    double* pdfyj = dfy.get_v() + i - 1;
    double* pyj = y.get_v() + i - 1;
    double* pdfbij = pdfbi->get_v() + i - 1;
    double* pbij = pbi->get_v() + i - 1;
    for (int j=i-1;j>=lb;j--)
    {
      // sum-=b.elem(i,j)*y.elem(j);
      *pdfbij -= dfsum * *pyj;
      *pdfyj -= dfsum * *pbij;

      --pdfyj;
      --pyj;
      --pdfbij;
      --pbij;
    }
    //sum=y.elem(i);
    *pdfyi = dfsum;
    dfsum = 0.0;

    --pdfyi;
    --pdfbi;
    --pbi;
  }

  double* pdfz = dfz.get_v() + ub;
  double* pdfy = dfy.get_v();
  pindxinv = indxinv.get_v() + ub;
  for (int i=ub;i>=lb;i--)
  {
    //y.elem(indxinv(i))=z.elem_value(i);
    *pdfz = *(pdfy + *pindxinv);
    --pdfz;
    --pindxinv;
  }

  dfz.save_dvector_derivatives(zpos);

  double* pdfpart_prod = dfpart_prod.get_v() + ub;
  //ln_unsigned_det=part_prod(ub);
  *pdfpart_prod += df_ln_det;
  df_ln_det=0.0;

  dvector* pbj = &b.elem(ub);
  dvector* pdfbj = &dfb.elem(ub);
  for (int j=ub;j>=lb+1;j--)
  {
    double* pdfpart_prod2 = pdfpart_prod - 1;
    //part_prod(j)=part_prod(j-1)+log(fabs(bb(j,j));
    *pdfpart_prod2 += *pdfpart_prod;
    *(pdfbj->get_v() + j) += *pdfpart_prod / *(pbj->get_v() + j);
    *pdfpart_prod = 0.0;

    --pdfpart_prod;
    --pbj;
    --pdfbj;
  }

  //part_prod(lb)=log(fabs(bb(lb,lb));
  *(pdfbj->get_v() + lb) += *pdfpart_prod / *(pbj->get_v() + lb);
  *pdfpart_prod = 0.0;

  pdfbj = &dfb(ub);
  for (int j = ub; j >= lb; --j)
  {
    double bjj = b(j, j);
    double* pdfbjj = pdfbj->get_v() + j;

    int* pindxi = indx.get_v() + ub;

    dvector* pdfbi = &dfb(ub);
    dvector* pbi = &b(ub);
    for (int i = ub; i >= lb; --i)
    {
      double* pdfbij = pdfbi->get_v() + j;
      double* pbij = pbi->get_v() + j;
      if (i<=j)
      {
        // b.elem(i,j)=sum;
        dfsum += *pdfbij;
        *pdfbij = 0.0;
      }
      else
      {
        // b.elem(i,j)=sum/b.elem(j,j);
        dfsum+= *pdfbij / bjj;
        *pdfbjj -= *pdfbij * *pbij / bjj;
        *pdfbij = 0.0;
      }

      int kmax = min(i - 1, j - 1);
      if (kmax >= lb)
      {
        double* pdfbik = pdfbi->get_v() + kmax;
        dvector* pdfbk = &dfb(kmax);
        double* pbik = pbi->get_v() + kmax;
        dvector* pbk = &b(kmax);
        for (int k = kmax; k >= lb; --k)
        {
          // sum-=b.elem(i,k)*b.elem(k,j);
          *pdfbik -= dfsum * *(pbk->get_v() + j);
          *(pdfbk->get_v() + j) -= dfsum * *pbik;

          --pdfbik;
          --pdfbk;
          --pbik;
          --pbk;
        }
      }
      // sum=value(a(indx.elem(i),j);
      save_dmatrix_derivatives(a_pos, dfsum, *pindxi, j); // like this
      dfsum=0.;

      --pindxi;
      --pdfbi;
      --pbi;
    }
    --pdfbj;
  }
}
#undef TINY
