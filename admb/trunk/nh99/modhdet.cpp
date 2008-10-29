

#include <admodel.h>

// char cc[43]={"Copyright (c) 1993,1994 Otter Research Ltd"};

double function_minimizer::hess_determinant(int underflow_flag)
{
 int sgn=0;
 double lndet=0.0;
 if (!underflow_flag)
 {
  uistream ifs("admodel.hes");
  if (!ifs)
  {
    cerr << "Error opening file admodel.hes" << endl;
  }
  int nvar;

  ifs >> nvar;
  {
    if (nvar != initial_params::nvarcalc())
    {
      cout << "the number of independent variables is wrong in admodel.hes"
         << endl;
    }
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
    lndet=ln_det(h,sgn);
  }
  if (sgn <= 0)
  {
    cerr << "Error restricted Hessian is not positive definite" << endl;
  }
 }
 else
 {
   lndet=50.0;
 }
 return lndet;
}

#undef HOME_VERSION
