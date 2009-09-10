/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */

#include "fvar.hpp"
#include <math.h>

static double eps0=1.e-50;

void lubksb(dvar_matrix a,_CONST ivector&  indx,dvar_vector b);
void ludcmp(BOR_CONST dvar_matrix& a,BOR_CONST ivector& indx,_CONST prevariable& d);

/** Lu decomposition of a variable matrix.
    \param _a  A dmatrix; replaced by the by its resulting LU decomposition
    \param _indx An ivector containing the row permutations generated by partial pivoting
    \param _d A double containing -1 or +1 depending whether the number of row interchanges was even or odd, repectively.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
void ludcmp(BOR_CONST dvar_matrix& _a,BOR_CONST ivector& _indx,BOR_CONST prevariable& _d)
{
  ADUNCONST(dvar_matrix,a)
  ADUNCONST(prevariable,d)
  ivector& indx= (ivector&) _indx;
  int i,imax = 0,j,k,n;

  n=a.colsize();
  int lb=a.colmin();
  int ub=a.colmax();

  dvariable big,dum,sum,temp;

  dvar_vector vv(lb,ub);


  d=1.0;

  for (i=lb;i<=ub;i++)
  {
    big=0.0;
    for (j=lb;j<=ub;j++)
    {
      temp=fabs(a(i,j));
      if (temp > big)
      {
        big=temp;
      }
    }
    if (big == 0.0) 
    {
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
    }
    vv(i)=1.0/big;
  }

  for (j=lb;j<=ub;j++)
  {
    for (i=lb;i<j;i++) 
    {
      sum=a(i,j);
      for (k=lb;k<i;k++)
      {
        sum = sum - a(i,k)*a(k,j);
      }
      a(i,j)=sum;
    }
    big=0.0;
    for (i=j;i<=ub;i++) 
    {
      sum=a(i,j);
      for (k=lb;k<j;k++)
      {
        sum = sum - a(i,k)*a(k,j);
      }
      a(i,j)=sum;
      dum=vv(i)*fabs(sum);
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
        dum=a(imax,k);
        a(imax,k)=a(j,k);
        a(j,k)=dum;
      }
      d = -1.*d;
      vv(imax)=vv(j);
    }
    indx(j)=imax;

    if (a(j,j) == 0.0)
    {
      a(j,j)=eps0;
    }

    if (j != n)
    {
      dum=1.0/(a(j,j));
      for (i=j+1;i<=ub;i++)
      {
        a(i,j) = a(i,j) * dum;
      }
    }
  }
}

/** LU decomposition back susbstitution alogrithm for variable object.
    \param a A dmatrix containing LU decomposition of input matrix. \f$a\f$. 
    \param indx Permutation vector from ludcmp.
    \param b A dvector containing the RHS, \f$b\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved, and containing on return the solution vector \f$X\f$.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
void lubksb(dvar_matrix a,_CONST ivector& indx,dvar_vector b)
{
  int i,ii=0,ip,j,iiflag=0;
  dvariable sum;
  //int n=a.colsize();
  int lb=a.colmin();
  int ub=a.colmax();
  for (i=lb;i<=ub;i++) 
  {
    ip=indx(i);
    sum=b(ip);
    b(ip)=b(i);
    if (iiflag)
    {
      for (j=ii;j<=i-1;j++)
      {
        sum -= a.elem(i,j)*b.elem(j);
      }
    }
    else if ( value(sum) )
    {
      ii=i;
      iiflag=1;
    }
    b(i)=sum;
  }
 
  for (i=ub;i>=lb;i--) 
  {
    sum=b(i);
    for (j=i+1;j<=ub;j++) 
    {                        // !!! remove to show bug
      sum -= a.elem(i,j)*b.elem(j);
    }                        // !!! remove to show bug
    b.elem(i)=sum/a.elem(i,i);
  }
}


