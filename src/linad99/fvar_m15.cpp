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
  for (int i=lb;i<=ub;i++)
  {
    big=0.0;
    for (int j=lb;j<=ub;j++)
    {
      temp=fabs(bb.elem(i,j));
      if (temp > big)
      {
        big=temp;
      }
    }
    if (big == 0.0)
    {
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
      ad_exit(1);
    }
    vv[i]=1.0/big;
  }

  for (int j=lb;j<=ub;j++)
  {
    for (int i=lb;i<j;i++)
    {
      sum=bb.elem(i,j);
      for (int k=lb;k<i;k++)
      {
        sum = sum - bb.elem(i,k)*bb.elem(k,j);
      }
      //a[i][j]=sum;
      bb.elem(i,j)=sum;
    }
    big=0.0;
    for (int i=j;i<=ub;i++)
    {
      sum=bb.elem(i,j);
      for (int k=lb;k<j;k++)
      {
        sum = sum - bb.elem(i,k)*bb.elem(k,j);
      }
      bb.elem(i,j)=sum;
      dum=vv[i]*fabs(sum);
      if ( dum >= big)
      {
        big=dum;
        imax=i;
      }
    }
    if (j != imax)
    {
      for (int k=lb;k<=ub;k++)
      {
        dum=bb.elem(imax,k);
        bb.elem(imax,k)=bb.elem(j,k);
        bb.elem(j,k)=dum;
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
      for (int i=j+1;i<=ub;i++)
      {
        bb.elem(i,j) = bb.elem(i,j) * dum;
      }
    }
  }

  dvector y(lb,ub);
  dvector x(lb,ub);
  //int lb=rowmin;
  //int ub=rowmax;
  dmatrix& b=bb;
  ivector indxinv(lb,ub);
  for (int i=lb;i<=ub;i++)
  {
    indxinv(indx.elem(i))=i;
  }
  for (int ii=lb;ii<=ub;ii++)
  {
    y.initialize();
    y(indxinv(ii))=1.;
    for (int i=indxinv(ii);i<=ub;i++)
    {
      // sum=y(ii,i);
      if (i==indxinv(ii))
      {
        sum=1.;
      }
      else
      {
        sum=0.;
      }
      for (int j=indxinv(ii);j<=i-1;j++)
      {
        sum-=b.elem(i,j)*y.elem(j);
      }
      y.elem(i)=sum;
    }
    for (int i=ub;i>=lb;i--)
    {
      sum=y.elem(i);
      for (int j=i+1;j<=ub;j++)
      {
        sum-=b.elem(i,j)*x.elem(j);
      }
      x.elem(i)=sum/b.elem(i,i);
    }
    y.save_dvector_value();
    x.save_dvector_value();
    nograd_assign_column(vc,x,ii);
  }

  save_identifier_string("P5");
  x.save_dvector_position();
  y.save_dvector_position();
  indx.save_ivector_value();
  indx.save_ivector_position();
  aa.save_dvar_matrix_position();
  vc.save_dvar_matrix_position();
  bb.save_dmatrix_value();
  bb.save_dmatrix_position();
  save_identifier_string("P1");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfinvpret);
  return vc;
}

/** Adjoint code for dvar_matrix inv(const dvar_matrix& aa).
*/
void dfinvpret(void)
{
  verify_identifier_string("P1");
  dmatrix_position bpos=restore_dmatrix_position();
  dmatrix b=restore_dmatrix_value(bpos);
  dvar_matrix_position v_pos=restore_dvar_matrix_position();
  dvar_matrix_position a_pos=restore_dvar_matrix_position();
  ivector_position indx_pos=restore_ivector_position();
  ivector indx=restore_ivector_value(indx_pos);
  dvector_position y_pos=restore_dvector_position();
  dvector_position x_pos=restore_dvector_position();
  verify_identifier_string("P5");
  int lb=b.colmin();
  int ub=b.colmax();
  dmatrix dfb(lb,ub,lb,ub);
  ivector indxinv(lb,ub);
  for (int i=lb;i<=ub;i++)
  {
    indxinv(indx.elem(i))=i;
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
    dvector x=restore_dvector_value(x_pos);
    //y.save_dvector_value();
    dvector y=restore_dvector_value(y_pos);
    dvector dfx=restore_dvar_matrix_derivative_column(v_pos,ii);
    for (int i=lb;i<=ub;i++)
    {
      // x.elem(i)=sum/b.elem(i,i);
      dfsum+=dfx.elem(i)/b.elem(i,i);
      dfb.elem(i,i)-=dfx.elem(i)*x.elem(i)/b.elem(i,i);
      dfx.elem(i)=0.;
      for (int j=ub;j>=i+1;j--)
      {
        // sum -=b.elem(i,j)*x.elem(j);
        dfb.elem(i,j)-=dfsum*x.elem(j);
        dfx.elem(j)-=dfsum*b.elem(i,j);
      }
      // sum=y.elem(i);
      dfy.elem(i)+=dfsum;
      dfsum=0.;
    }

    //for (i=ub;i>=lb;i--)
    int i2;
    for (i2=ub;i2>=indxinv(ii);i2--)
    {
      // y.elem(i)=sum;
      dfsum+=dfy.elem(i2);
      dfy.elem(i2)=0.;
      // for (int j=i-1;j>=lb;j--)
      for (int j=i2-1;j>=indxinv(ii);j--)
      {
        // sum-=b.elem(i,j)*y.elem(j);
        dfb.elem(i2,j)-=dfsum*y.elem(j);
        dfy.elem(j)-=dfsum*b.elem(i2,j);
      }
      //sum=y.elem(i);
      dfy.elem(i2)=dfsum;
      dfsum=0.;
    }
    //x.initialize()
    //y.initialize()
    dfx.initialize();
    dfy.initialize();
  }

  for (int j=ub;j>=lb;j--)
  {
    for (int i=ub;i>=lb;i--)
    {
      if (i<=j)
      {
        // b.elem(i,j)=sum;
        dfsum+=dfb.elem(i,j);
        dfb.elem(i,j)=0.;
      }
      else
      {
        // b.elem(i,j)=sum/b.elem(j,j);
        dfsum+=dfb.elem(i,j)/b.elem(j,j);
        dfb.elem(j,j)-=dfb.elem(i,j)*b.elem(i,j)/b.elem(j,j);
        dfb.elem(i,j)=0.;
      }

      for (int k=min(i-1,j-1);k>=lb;k--)
      {
        // sum-=b.elem(i,k)*b.elem(k,j);
        dfb.elem(i,k)-=dfsum*b.elem(k,j);
        dfb.elem(k,j)-=dfsum*b.elem(i,k);
      }
      // sum=value(a(indx.elem(i),j);
      save_dmatrix_derivatives(a_pos,dfsum,indx.elem(i),j); // like this
      dfsum=0.;
    }
  }
}

#undef TINY
