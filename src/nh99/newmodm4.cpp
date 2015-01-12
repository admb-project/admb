/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

double function_minimizer::unrestricted_hess_determinant(void)
{
  adstring tmpstring="admodel.hes";
  if (ad_comm::wd_flag)
     tmpstring = ad_comm::adprogram_name + ".hes";
  uistream ifs((char*)tmpstring);
    
  if (!ifs)
  {
    cerr << "Error opening file " << (char*) tmpstring
      << " in unrestricted_hess_determinant" << endl;
  }
  int nvar;

  ifs >> nvar;
  cout << "nvar =" << nvar << endl;
  dmatrix S(1,nvar,1,nvar);
  {
    if (nvar != initial_params::nvarcalc())
    {
      cout << "the number of independent variables is wrong in admodel.hes"
         << endl;
    }
    dmatrix p(1,nvar,1,nvar);
    dmatrix h(1,nvar,1,nvar);
    ifs >> h;
    if (!ifs)
    {
      cerr << "Error reading the hessian from file admodel.hes" << endl;
    }

    for (int i=1;i<=nvar;i++)
    {
      for (int j=1;j<i;j++)
      {
        double tmp=(h(i,j)+h(j,i))/2.;
        h(i,j)=tmp;
        h(j,i)=tmp;
      }
    }

    int sgn=0;
    double lndet=ln_det(h,sgn);
    if (sgn <= 0)
    {
      cerr << "sgn = " << sgn << endl;
      cerr << "Error Hessian is not positive definite" << endl;
    }
    return lndet;
  }
}
