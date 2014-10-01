/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

double function_minimizer::projected_hess_determinant(const dvector& g,
  const int underflow_flag, const dvector& xscale,
  const double& _ln_det_proj_jac)
{
 double& ln_det_proj_jac=(double&) _ln_det_proj_jac;
 int ibreak=-1;
 int sgn=0;
 double lndet=0.0;
 //char ch;
 if (!underflow_flag)
 {
  uistream ifs("admodel.hes");
  if (!ifs)
  {
    cerr << "Error opening file admodel.hes" << endl;
  }
  int nvar = 0;
  ifs >> nvar;
  //dmatrix S(1,nvar,1,nvar);
  if (nvar > 0)
  {
    if ((size_t)nvar != initial_params::nvarcalc())
    {
      cout << "the number of independent variables is wrong in admodel.hes"
         << endl;
    }
    dmatrix p(1,nvar,1,nvar);
    dmatrix p1(1,nvar-1,1,nvar);
    dmatrix h(1,nvar,1,nvar);
    dvector ss(1,nvar);
    ifs >> h;
    if (!ifs)
    {
      cerr << "Error reading the hessian from file admodel.hes" << endl;
    }
    dvector n=g/norm(g);
    // project the standard basis vectors onto the tangent space
    int i;
    for (i=1;i<=nvar;i++)
    {
      p(i)=-n(i)*n;
      p(i,i)+=1;
    }

    for (i=1;i<=nvar;i++)
    {
      ss(i)=norm(p(i));
    }
    double minsize = min(ss);

    for (i=1;i<=nvar;i++)
    {
      if (ss(i) == minsize)
      {
        ibreak = i;
        break;
      }
      p1(i)=p(i);
    }

    int ii;
    for (ii=i+1;ii<=nvar;ii++)
    {
      p1(ii-1)=p(ii);
    }

    dmatrix tmpS(1,nvar-1,1,nvar-1);

    //for (ii=1;ii<=nvar-1;ii++)
    //{
      //for (i=1;i<=nvar;i++)
      //{
        //p1(ii,i)*=xscale(i);
      //}
    //}

    for (i=1;i<=nvar-1;i++)
    {
      tmpS(i,i)=p1(i)*p1(i);
      for (int j=1;j<i;j++)
      {
        tmpS(i,j)=p1(i)*p1(j);
        tmpS(j,i)=tmpS(i,j);
      }
    }
    ln_det_proj_jac=ln_det(tmpS,sgn);

    // reset the p1 basis
    for (i=1;i<=nvar;i++)
    {
      if (i==ibreak) break;
      p1(i)=p(i);
    }

    for (ii=i+1;ii<=nvar;ii++)
    {
      p1(ii-1)=p(ii);
    }

    for (i=1;i<=nvar;i++)
    {
      for (int j=1;j<i;j++)
      {
        double tmp=(h(i,j)+h(j,i))/2.;
        h(i,j)=tmp;
        h(j,i)=tmp;
      }
    }

    // move to "model space"
    for (i=1;i<=nvar;i++)
    {
      for (int j=1;j<=nvar;j++)
      {
        h(i,j)/=(xscale(i)*xscale(j));
      }
    }

    for (i=1;i<nvar;i++)
    {
      dvector tmp = h*p1(i);
      tmpS(i,i)=tmp*p1(i);
      for (int j=1;j<i;j++)
      {
        tmpS(i,j)=tmp*p1(j);
        tmpS(j,i)=tmpS(i,j);
      }
    }
    lndet=ln_det(tmpS,sgn);
  }
  if (sgn <= 0)
  {
    cerr << "Error restricted Hessian is not positive definite" << endl;
  }
 }
 else
 {
   lndet=-50.0;
 }
 return lndet;
}
