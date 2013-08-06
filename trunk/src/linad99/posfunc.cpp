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
  Adjoint code for posfun; possibly not used.
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
  Retuns a positive function of the argument \f$x\f$ and sets a penalty for
  \f$x<0\f$. The penalty should be added to the objective function.
  \param x Argument, \f$x\f$.
  \param eps Threshold, \f$\epsilon\f$, 
   a double constant containing the minimum allowed value of \f$x\f$.
  \param  _pen The penalty value \b incremented by \f$ 0.01(x-\epsilon)^2 \f$ 
   if \f$x<\epsilon\f$. 
  \return \f$\left\{\begin{array} {r@{\quad:\quad}l}
             x\ge\epsilon & x\\
               x<\epsilon & \frac{\epsilon}{2-x/\epsilon}
           \end{array}\right.\f$
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
  Retuns a positive function of the argument \f$x\f$ and sets a penalty for
  \f$x<0\f$. The penalty should be added to the objective function. 
   A more coersive version.
  \param x Argument, \f$x\f$.
  \param eps Threshold, \f$\epsilon\f$, 
   a double constant containing the minimum allowed value of \f$x\f$.
  \param  _pen The penalty value \b incremented by \f$ 0.01(x-\epsilon)^3 \f$ 
   if \f$x<\epsilon\f$. 
  \return \f$\left\{\begin{array} {r@{\quad:\quad}l}
             x\ge\epsilon & x\\
               x<\epsilon & \frac{\epsilon}{1+x/\epsilon
                                             +(x/\epsilon)^2
                                             +(x/\epsilon)^3}
           \end{array}\right.\f$
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
