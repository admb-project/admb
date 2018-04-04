/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>

double inv_cumd_norm_inner(double x);

/**
 * Description not yet available.
 * \param
 */
double cumd_logistic(const double& x)
{
  if (x>=0.0)
  {
    return 1.0/(1.0+exp(-x));
  }
  else
  {
    double y=exp(x);
    return y/(1.0+y);
  }
}

/**
 * Description not yet available.
 * \param
 */
double inv_cumd_logistic(const double& x)
{
  return log(x/(1.0-x));
}

/**
 * Description not yet available.
 * \param
 */
double inv_cumd_norm_logistic(double x,double p)
{
#if defined(DEBUG)
  if (0.0<p || 1.0>p)
  {
    cerr << "Error in double inv_cumd_norm_logistic -- illegal p value = "
         << p << endl;
    exit(1);
  }
#endif
  cout << log(x) << " ";
  double y=inv_cumd_logistic(x);
  cout << log(cumd_norm_logistic(y,p)) << " ";
  if (y>0)
  {
    for (int i=1;i<=10;i++)
    {
      double yp=(1.0-p)*0.39894228*exp(-.5*y*y) + p*exp(-y)/square(1.0+exp(-y));
      y+= 1/yp* (x-cumd_norm_logistic(y,p));
      cout << cumd_norm_logistic(y,p) << " ";
    }
  }
  else
  {
    for (int i=1;i<=10;i++)
    {
      double yp=(1.0-p)*0.39894228*exp(-.5*y*y) + p*exp(y)/square(1.0+exp(y));
      y+= 1/yp* (x-cumd_norm_logistic(y,p));
      cout << cumd_norm_logistic(y,p) << " ";
    }
  }
  cout << endl;
  return y;
}

/**
 * Description not yet available.
 * \param
 */
double cumd_norm_logistic(double _x,double p)
{
  return (1.0-p)*cumd_norm(_x)+p*cumd_logistic(_x);
}
