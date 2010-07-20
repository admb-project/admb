/*
 * $Id$
 *
 * Copyright (c) 2009 ADMB Foundation
 */

#include <ludcmp.hpp>

cltudecomp ludecomp(const dmatrix & M);

/** Solve a linear system using LU decomposition.
    \param aa A dmatrix containing LU decomposition of input matrix. \f$a\f$. 
    \param z A dvector containing the RHS, \f$b\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved.
    \return A dvector containing solution vector \f$X\f$.
*/
dvector solve(const dmatrix& aa,const dvector& z)
{
  int n=aa.colsize();
  int lb=aa.colmin();
  int ub=aa.colmax();
  if (lb!=aa.rowmin()||ub!=aa.colmax())
  {
    cerr << "Error matrix not square in solve(dmatrix)"<<endl;
    ad_exit(1);
  }
  dmatrix bb(lb,ub,lb,ub);
  bb=aa;
  cltudecomp dcmp;
  dcmp = ludecomp(bb);

  dmatrix alpha=dcmp.get_L();
  dmatrix beta=dcmp.get_U();

  //check if invertable
  double det=1.0;
  for(int i=lb;i<=ub;i++)
  {
    det*=dcmp(i,i);
  }
  if (det==0.0)
  {
    cerr << "Error in matrix inverse -- matrix singular in solve(dmatrix)\n";
    ad_exit(1);
  }

  //Solve L*y=b with forward-substitution (before solving Ux=y)
  dvector y(lb,ub);
  for(i=lb;i<=ub;i++)
  {
    double tmp=0.0;
    for(int j=1;j<i;j++)
    {
      tmp+=dcmp(i,j)*y(j);
    }
    y(i)=z(i)-tmp;
  }

  //Now solve U*x=y with back substitution
  dvector x(lb,ub);
  for(i=ub;i>=lb;i--)
  {
    double tmp=0.0;
    for(int j=ub;j>i;j--)
    {
      tmp+=dcmp(i,j)*x(j);
    }
    x(i)=(y(i)-tmp)/dcmp(i,i);
  }

  return x;
}



