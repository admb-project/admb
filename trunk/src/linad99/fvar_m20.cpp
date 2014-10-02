/**
 * $Id: fvar_m20.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: Steve Martell made Changes on Dec 30, 2013
 * 
 */
#include <fvar.hpp>
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
void df_xdet(void);

/** Determinaant of matrix.
    \param aa dvar_matrix containing a square matrix,\f$A\f$.
    \return \f$\det(A)\f$.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2

    Edited by Steve Martell on Dec 30, 2013 to address a bug
    where the lower bound of the square dvar_matrix was greater than 1.
*/
dvariable det(const dvar_matrix& aa)
{
  int i,j,k;
  int n=aa.colsize();
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
  double d;
  double big,dum,sum,temp;
  dvar_matrix_position dmp(aa,1);
  dmatrix bb=value(aa);
  dvector vv(lb,ub);
  dvector part_prod(lb,ub);

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
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
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
      d = -1.*d;
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
  //double det=d;
  // SM Bug 129, issue appears to be at this line
  // part_prod is declared above as dvector(lb,ub)
  // cout<<"Bug 129 ="<<part_prod(lb)<<endl;
  // part_prod(1)=d*bb(1,1);  // replaced this line with:
  part_prod(lb) = d*bb(lb,lb);
  // cout<<"Ok got this far; det = "<<det<<endl;
  for (j=lb+1;j<=ub;j++)
  {
    part_prod(j)=part_prod(j-1)*bb(j,j);
  }
  double det=part_prod(ub);
  dvariable rdet=nograd_assign(det);
  save_identifier_string("PLACE7");
  part_prod.save_dvector_value();
  part_prod.save_dvector_position();
  indx.save_ivector_value();
  indx.save_ivector_position();
  save_identifier_string("PLACE3");
  aa.save_dvar_matrix_position();
  save_identifier_string("PLACE2b");
  rdet.save_prevariable_position();
  save_identifier_string("PLACE2a");
  bb.save_dmatrix_value();
  save_identifier_string("PLACE2");
  bb.save_dmatrix_position();
  save_identifier_string("PLACE1");
  save_double_value(d);
  save_identifier_string("PLACE0");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(df_xdet);
  return rdet;
}

/** Adjoint code for dvariable det(const dvar_matrix& aa) */
void df_xdet(void)
{
  verify_identifier_string("PLACE0");
  double d=restore_double_value();
  verify_identifier_string("PLACE1");
  dmatrix_position bpos=restore_dmatrix_position();
  verify_identifier_string("PLACE2");
  dmatrix b=restore_dmatrix_value(bpos);
  verify_identifier_string("PLACE2a");
  //dvar_matrix_position rdet_pos=restore_prevariable_position();
  double dfdet=restore_prevariable_derivative();
  verify_identifier_string("PLACE2b");
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
    // part_prod(j)=part_prod(j-1)*b(j,j);
    dfpart_prod(j-1)+=dfpart_prod(j)*b(j,j);
    dfb(j,j)+=dfpart_prod(j)*part_prod(j-1);
    dfpart_prod(j)=0.;
  }
  //part_prod(1)=d*b(lb,lb);
  dfb(lb,lb)+=dfpart_prod(lb)*d;
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
