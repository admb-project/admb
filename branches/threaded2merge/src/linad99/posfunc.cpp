/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

/** \file posfunc.cpp 
  posfun(...) source code for constant arguments.
*/


#include <fvar.hpp>

/**
   Adjoint code for posfun; possibly not used.
   Retained in source code to support legacy models with user-written adjoint code.
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
   \brief \copybrief dfposfun(const double&, const double)
   \details \copydetails dfposfun(const double&, const double)
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
 \brief \copybrief posfun(const dvariable&, const double, const prevariable&)
 \details \copydetails posfun(const dvariable&, const double, const prevariable&)
 \ingroup misc
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
 \brief \copybrief posfun2(const dvariable&, const double, const prevariable&)
 \details \copydetails posfun2(const dvariable&, const double, const prevariable&)
  \ingroup misc
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
