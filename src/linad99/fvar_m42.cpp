/**
 * $Id: fvar_m42.cpp 789 2010-10-05 01:01:09Z johnoel $
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
  for (i=lb;i<=ub;i++)
  {
    big=0.0;
    for (j=lb;j<=ub;j++)
    {
      temp=fabs(bb.elem(i,j));
      if (temp > big)
      {
        big=temp;
      }
    }
    if (big == 0.0)
    {
      cerr << "Error in matrix inverse -- matrix singular in "
      "inv(dvar_matrix)\n";
      big=1.e+10;
      errflag=1;
    }
    vv[i]=1.0/big;
  }

  for (j=lb;j<=ub;j++)
  {
    for (i=lb;i<j;i++)
    {
      sum=bb.elem(i,j);
      for (k=lb;k<i;k++)
      {
        sum = sum - bb.elem(i,k)*bb.elem(k,j);
      }
      //a[i][j]=sum;
      bb(i,j)=sum;
    }
    int imax = j;
    big=0.0;
    for (i=j;i<=ub;i++)
    {
      sum=bb.elem(i,j);
      for (k=lb;k<j;k++)
      {
        sum = sum - bb(i,k)*bb(k,j);
      }
      bb(i,j)=sum;
      dum=vv.elem(i)*fabs(sum);
      if ( dum >= big)
      {
        big=dum;
        imax=i;
      }
    }
    if (j != imax)
    {
      for (k=lb;k<=ub;k++)
      {
        dum=bb.elem(imax,k);
        bb.elem(imax,k)=bb.elem(j,k);
        bb.elem(j,k)=dum;
      }
      //d = -1.*d;
      sgn=-1*sgn;
      vv.elem(imax)=vv.elem(j);

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
      bb(j,j)=TINY;
    }

    if (j != n)
    {
      dum=1.0/bb(j,j);
      for (i=j+1;i<=ub;i++)
      {
        bb.elem(i,j) *= dum;
      }
    }
  }
  if (bb(1,1)>0)
    part_prod(1)=ld+log(bb(1,1));
  else
  {
    part_prod(1)=ld+log(-bb(1,1));
    sgn=-sgn;
  }
  for (j=lb+1;j<=ub;j++)
  {
    if (bb(j,j)>0)
      part_prod(j)=part_prod(j-1)+log(bb(j,j));
    else
    {
      part_prod(j)=part_prod(j-1)+log(-bb(j,j));
      sgn=-sgn;
    }
  }
  double ldet=part_prod(ub);
  dvariable rdet=nograd_assign(ldet);
  save_identifier_string("PLACE7");
  part_prod.save_dvector_value();
  part_prod.save_dvector_position();
  indx.save_ivector_value();
  indx.save_ivector_position();
  save_identifier_string("PLACE3");
  aa.save_dvar_matrix_position();
  rdet.save_prevariable_position();
  bb.save_dmatrix_value();
  save_identifier_string("PLACE2");
  bb.save_dmatrix_position();
  save_identifier_string("PLACE1");
  save_double_value(ld);
  save_identifier_string("PLACE0");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(df_xldet);
  if (errflag) sgn=-1;
  return rdet;
}

/// Adjoint code for dvariable ln_det(const dvar_matrix& aa, int& sgn).
void df_xldet(void)
{
  verify_identifier_string("PLACE0");
  /*double ld=*/restore_double_value();
  verify_identifier_string("PLACE1");
  dmatrix_position bpos=restore_dmatrix_position();
  verify_identifier_string("PLACE2");
  dmatrix b=restore_dmatrix_value(bpos);
  //dvar_matrix_position rdet_pos=restore_prevariable_position();
  double dfdet=restore_prevariable_derivative();
  dvar_matrix_position a_pos=restore_dvar_matrix_position();
  verify_identifier_string("PLACE3");
  ivector_position indx_pos=restore_ivector_position();
  ivector indx=restore_ivector_value(indx_pos);
  dvector_position part_prod_pos=restore_dvector_position();
  dvector part_prod=restore_dvector_value(part_prod_pos);
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
  int j;
  for (j=ub;j>=lb+1;j--)
  {
    if (b(j,j)>0)
    {
      // part_prod(j)=part_prod(j-1)+log(b(j,j));
      dfpart_prod(j-1)+=dfpart_prod(j);
      dfb(j,j)+=dfpart_prod(j)/b(j,j);
    }
    else
    {
      // part_prod(j)=part_prod(j-1)+log(-b(j,j));
      dfpart_prod(j-1)+=dfpart_prod(j);
      dfb(j,j)+=dfpart_prod(j)/b(j,j);
    }
    dfpart_prod(j)=0.;
  }
  //part_prod(1)=ld+log(b(lb,lb));
  dfb(lb,lb)+=dfpart_prod(lb)/b(lb,lb);
  dfpart_prod(lb)=0.;

  double dfsum=0.;
  for (j=ub;j>=lb;j--)
  {
    for (int i=ub;i>=lb;i--)
    {
      if (i<=j)
      {
        // b(i,j)=sum;
        dfsum+=dfb(i,j);
        dfb(i,j)=0.;
      }
      else
      {
        // b(i,j)=sum/b(j,j);
        dfsum+=dfb(i,j)/b(j,j);
        dfb(j,j)-=dfb(i,j)*b(i,j)/b(j,j);
        dfb(i,j)=0.;
      }

      for (int k=min(i-1,j-1);k>=lb;k--)
      {
        // sum-=b(i,k)*b(k,j);
        dfb(i,k)-=dfsum*b(k,j);
        dfb(k,j)-=dfsum*b(i,k);
      }
      // sum=value(a(indx(i),j);
      save_dmatrix_derivatives(a_pos,dfsum,indx(i),j); // like this
      dfsum=0.;
    }
  }
}

#undef TINY
