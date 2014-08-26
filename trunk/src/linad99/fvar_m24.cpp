/**
 * $Id: fvar_m24.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: Unknown
 */
#include <fvar.hpp>

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

/** Solve a linear sysgem using LU decomposition.
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

  RETURN_ARRAYS_INCREMENT();
  int i,j,k,n;
  n=aa.colsize();
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
      "solve(dvar_dmatrix)\n";
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
        sum -= bb.elem(i,k)*bb.elem(k,j);
      }
      //a[i][j]=sum;
      bb.elem(i,j)=sum;
    }
    int imax = j;
    big=0.0;
    for (i=j;i<=ub;i++)
    {
      sum=bb.elem(i,j);
      for (k=lb;k<j;k++)
      {
        sum -= bb.elem(i,k)*bb.elem(k,j);
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
      for (k=lb;k<=ub;k++)
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
      for (i=j+1;i<=ub;i++)
      {
        bb.elem(i,j) = bb.elem(i,j) * dum;
      }
    }
  }

  // get the determinant
  sign=d;
  dvector part_prod(lb,ub);
  part_prod(lb)=log(fabs(bb(lb,lb)));
  if (bb(lb,lb)<0) sign=-sign;
  for (j=lb+1;j<=ub;j++)
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
  for (i=lb;i<=ub;i++)
  {
    indxinv(indx.elem(i))=i;
  }

  for (i=lb;i<=ub;i++)
  {
    y.elem(indxinv(i))=z.elem_value(i);
  }

  for (i=lb;i<=ub;i++)
  {
    sum=y.elem(i);
    for (int j=lb;j<=i-1;j++)
    {
      sum-=b.elem(i,j)*y.elem(j);
    }
    y.elem(i)=sum;
  }
  for (i=ub;i>=lb;i--)
  {
    sum=y.elem(i);
    for (int j=i+1;j<=ub;j++)
    {
      sum-=b.elem(i,j)*x.elem(j);
    }
    x.elem(i)=sum/b.elem(i,i);
  }

  vc=nograd_assign(x);
  save_identifier_string("PLACE8");
  ln_unsigned_det.save_prevariable_position();
  save_identifier_string("PLACE7");
  part_prod.save_dvector_value();
  part_prod.save_dvector_position();
  save_identifier_string("PLACE6");
  y.save_dvector_value();
  x.save_dvector_value();
  save_identifier_string("PLACE5");
  x.save_dvector_position();
  save_identifier_string("PLACE4");
  y.save_dvector_position();
  indx.save_ivector_value();
  save_identifier_string("PLACE3a");
  indx.save_ivector_position();
  save_identifier_string("PLACE3");
  aa.save_dvar_matrix_position();
  save_identifier_string("PLACE2b");
  vc.save_dvar_vector_position();
  save_identifier_string("PLACE2a");
  bb.save_dmatrix_value();
  save_identifier_string("PLACE2");
  bb.save_dmatrix_position();
  save_identifier_string("PLACE1");
  z.save_dvar_vector_position();
  save_identifier_string("PLACE0");
  gradient_structure::GRAD_STACK1->
     set_gradient_stack(dmdv_solve);
  RETURN_ARRAYS_DECREMENT();
  return vc;
}

/// Adjoint code for
/// dvar_vector solve(const dvar_matrix& aa, const dvar_vector& z,
void dmdv_solve(void)
{
  verify_identifier_string("PLACE0");
  dvar_vector_position zpos=restore_dvar_vector_position();
  verify_identifier_string("PLACE1");
  dmatrix_position bpos=restore_dmatrix_position();
  verify_identifier_string("PLACE2");
  dmatrix b=restore_dmatrix_value(bpos);
  verify_identifier_string("PLACE2a");
  dvar_vector_position v_pos=restore_dvar_vector_position();
  verify_identifier_string("PLACE2b");
  dvar_matrix_position a_pos=restore_dvar_matrix_position();
  verify_identifier_string("PLACE3");
  ivector_position indx_pos=restore_ivector_position();
  verify_identifier_string("PLACE3a");
  ivector indx=restore_ivector_value(indx_pos);
  dvector_position y_pos=restore_dvector_position();
  verify_identifier_string("PLACE4");
  dvector_position x_pos=restore_dvector_position();
  verify_identifier_string("PLACE5");
  dvector x=restore_dvector_value(x_pos);
  dvector y=restore_dvector_value(y_pos);
  verify_identifier_string("PLACE6");
  dvector_position part_prod_pos=restore_dvector_position();
  dvector part_prod=restore_dvector_value(part_prod_pos);
  verify_identifier_string("PLACE7");
  double df_ln_det=restore_prevariable_derivative();
  verify_identifier_string("PLACE8");
  int lb=b.colmin();
  int ub=b.colmax();
  dmatrix dfb(lb,ub,lb,ub);
  dvector dfz(lb,ub);
  dvector dfx=restore_dvar_vector_derivatives(v_pos);
  dvector dfy(lb,ub);
  dvector dfpart_prod(lb,ub);
  ivector indxinv(lb,ub);
  int i;
  for (i=lb;i<=ub;i++)
  {
    indxinv(indx.elem(i))=i;
  }

  double dfsum=0.;
  #ifndef SAFE_INITIALIZE
    dfb.initialize();
    dfy.initialize();
    dfz.initialize();
    dfpart_prod.initialize();
  #endif

  for (i=lb;i<=ub;i++)
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

  for (i=ub;i>=lb;i--)
  {
    // y.elem(i)=sum;
    dfsum+=dfy.elem(i);
    dfy.elem(i)=0.;
    for (int j=i-1;j>=lb;j--)
    {
      // sum-=b.elem(i,j)*y.elem(j);
      dfb.elem(i,j)-=dfsum*y.elem(j);
      dfy.elem(j)-=dfsum*b.elem(i,j);
    }
    //sum=y.elem(i);
    dfy.elem(i)=dfsum;
    dfsum=0.;
  }

  for (i=ub;i>=lb;i--)
  {
    //y.elem(indxinv(i))=z.elem_value(i);
    dfz.elem(i)=dfy.elem(indxinv(i));
  }

  dfz.save_dvector_derivatives(zpos);

  //ln_unsigned_det=part_prod(ub);
  dfpart_prod(ub)+=df_ln_det;
  df_ln_det=0.0;

  int j;
  for (j=ub;j>=lb+1;j--)
  {
    //part_prod(j)=part_prod(j-1)+log(fabs(bb(j,j));
    dfpart_prod(j-1)+=dfpart_prod(j);
    dfb(j,j)+=dfpart_prod(j)/b(j,j);
    dfpart_prod(j)=0.0;
  }

  //part_prod(lb)=log(fabs(bb(lb,lb));
  dfb(lb,lb)+=dfpart_prod(lb)/b(lb,lb);
  dfpart_prod(lb)=0.0;

  for (j=ub;j>=lb;j--)
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
