/*
 * $Id: posfunc.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
double dfposfun(const double &x, const double eps)
{
  if (x>=eps) 
  {
    return 1;
  }
  else
  {
    //double z=eps/(2-x/eps);
    double dfx=1.0/square(2-x/eps);
    //double z= 0.5*eps*(1.0+1.0/(3.0-2.0*x/eps));
    //double dfx=1.0/square(3.0-2.0*x/eps);
    return dfx;
  }
}

/**
 * Description not yet available.
 * \param
 */
double dfposfun1(const double &x, const double eps)
{
  if (x>=eps) 
  {
    return 0;
  }
  else
  {
    double dfx=.02*(x-eps);
    return dfx;
  }
}

/**
 * Description not yet available.
 * \param
 */
double posfun(const double &x, const double eps, const double& _pen)
{
  double& pen=(double&)_pen;
  if (x>=eps) 
  {
    return x;
  }
  else
  {
    pen+=.01*square(x-eps);
    //return 0.5*eps*(1.0+1.0/(3.0-2.0*x/eps));
    return eps/(2.0-x/eps);
  }
}

/**
 * Description not yet available.
 * \param
 */
double posfun2(const double &x, const double eps, const double& _pen)
{
  double& pen=(double&)_pen;
  if (x>=eps) 
  {
    return x;
  }
  else
  {
    double y=eps-x;
    double tmp=y/eps;
    double tmp2=tmp*tmp;
    double tmp3=tmp2*tmp;
    pen+=.01*cube(tmp3);
    return eps/(1.0+tmp+tmp2+tmp3);
  }
}
