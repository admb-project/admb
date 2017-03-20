/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
  \file boundfun.cpp
  \brief Code to implement placing constraints on parameters.
  See in Section 10.1 of the AUTODIF manual.
  The code in thse section of the AUTODIF manual appears to be
  out of date with respect to some of the code in this file.
*/
#include "fvar.hpp"

/**
\details
Use penalties recomended in Bard, Y. (1974) Nonlinear parameter estimation.
Academic Press, New York.
*/
#define USE_BARD_PEN

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// function prototypes duplicated in fvar.hpp
// double dmin(double, double);
// double dmax(double, double);

/**
  Scale input variable between upper and lower bounds
  and compute a penalty for exceeding the bounds.
  \param x Variable to be scaled
  \param fmin Lower bound of x
  \param fmin Upper bound of x
  \param _fpen On return, contains penalty if x > fmax or x < fmin
  \return Scaled value of x between fmin and fmax in the range [-1,1]
 */
dvariable dfatan1(dvariable x, double fmin, double fmax,
  const prevariable&  _fpen)
{
  prevariable&  fpen=(prevariable&)  _fpen;
  dvariable t;

  t= (atan(x)/PI);
  t=( t +.5 );
  t= t *( fmax-fmin ) + fmin;
  t=( (atan(x)/PI) +.5 )*( fmax-fmin ) + fmin;

  if (x < -12.)
  {
    fpen+=.1*(x+12.)*(x+12.);
  }

  if (x > 12.)
  {
    fpen+=.1*(x-12.)*(x-12.);
  }
  return(t);
}
/**
Inverse of \ref dvariable dfatan1(dvariable x, double fmin, double fmax,
  const prevariable&  _fpen)
\param x Variable to be scaled
\param fmin Lower bound of x
\param fmin Upper bound of x
*/
double dftinv(double x, double fmin, double fmax)
{
  if (x <= fmin)
  {
    if (ad_printf)
    {
      (*ad_printf)("variable out of bounds in dftinv\nvariable = %lg", x);
      (*ad_printf)("lower bound = %lg", fmin);
      (*ad_printf)("upper bound = %lg\n", fmax);
    }

    x=dmin(fmin+.001,fmin+.01*(fmax-fmin));
  }

  double tinv = tan( ((x-fmin)/(fmax-fmin) -.5) * PI);
  return tinv;
}
/**
Compute penalty for exceeding bounds on parameter; variable ojbects.
\param x Variable scaled between [-1,1]
\param fmin Lower bound of x
\param fmin Upper bound of x
\param _fpen On return, contains penalty if x > 1 or x < -1
\param s Divide x by s before scaling and setting bounds
\return The variable x in original units
*/
dvariable boundp(const prevariable& x, double fmin, double fmax,
  const prevariable& _fpen,double s)
{
  return boundp(x/s,fmin,fmax,_fpen);
}
/**
  Compute penalty for exceeding bounds on parameter; variable ojbects.
  \param x Variable scaled between [-1,1]
  \param fmin Lower bound of x
  \param fmin Upper bound of x
  \param _fpen On return, contains penalty if x > 1 or x < -1
  \return The variable x in original units
*/
dvariable boundp(const prevariable& x, double fmin, double fmax,
  const prevariable& _fpen)
{
  if (gradient_structure::Hybrid_bounded_flag==0)
  {
    prevariable&  fpen=(prevariable&)  _fpen;
    dvariable t,y;
    double diff=fmax-fmin;
    const double l4=log(4.0);
    dvariable ss=0.4999999999999999*sin(x*1.57079632679489661)+0.50;
    t=fmin + diff*ss;

  #ifdef USE_BARD_PEN
    double pen=.000001/diff;
    fpen-=pen*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4);
  #else
    if (x < -.9999)
    {
      fpen+=cube(-0.9999-x);
      if (x < -1.)
      {
        fpen+=1.e+6*cube(-1.0-x);
        if (x < -1.02)
        {
          fpen+=1.e+10*cube(-1.02-x);
        }
      }
    }
    if (x > 0.9999)
    {
      fpen+=cube(x-0.9999);
      if (x > 1.)
      {
        fpen+=1.e+6*cube(x-1.);
        if (x > 1.02)
        {
          fpen+=1.e+10*cube(x-1.02);
        }
      }
    }
  #endif
    return(t);
  }
  else
  {
    double diff=fmax-fmin;
    dvariable t,y;
    if (x>-20)
    {
      y=1.0/(1+exp(-x));
    }
    else
    {
      dvariable u=exp(x);
      y=u/(1.0+u);
    }
    t=fmin + diff*y;
    return(t);
  }
}
/**
Computes the derivative of \ref dvariable boundp(const prevariable& x,
  double fmin, double fmax,const prevariable& _fpen)
\param x Variable to be scaled
\param fmin Lower bound of x
\param fmin Upper bound of x
\return Derivative of scaled variable
 */
dvariable dfboundp(const prevariable& x, double fmin,double fmax)
{
  if (gradient_structure::Hybrid_bounded_flag==0)
  {
    return (fmax-fmin)*0.499999999999999*1.57079632679489661
      *cos(x*1.57079632679489661);
  }
  else
  {
    double diff=fmax-fmin;
    dvariable dfy;
    if (x>-20)
    {
      dvariable u=exp(-x);
      //y=1.0/(1+u);
      dfy=u/square(1.0+u);
    }
    else
    {
      dvariable u=exp(x);
      //y=u/(1.0+u);
      dfy=u/square(1.0+u);
    }
    if (dfy==0)
    {
      // cout << "error in dfboundp" << endl;
    }
    return diff*dfy;
  }
}

/**
Derivatative code for \ref double nd2fboundp( double x, double fmin,
  double fmax,const double& fpen)
\param x Variable to be scaled
\param fmin Lower bound of x
\param fmin Upper bound of x
\param fpen Unchanged on return.
\return Derivative of scaled variable
*/
double ndfboundp( double x, double fmin, double fmax,const double& fpen)
{
  if (gradient_structure::Hybrid_bounded_flag==0)
  {
    return (fmax-fmin)*0.499999999999999*1.57079632679489661
      *cos(x*1.57079632679489661);
  }
  else
  {
    double diff=fmax-fmin;
    double dfy;
    if (x>-20)
    {
      double u=exp(-x);
      //y=1.0/(1+u);
      dfy=u/square(1.0+u);
    }
    else
    {
      double u=exp(x);
      //y=u/(1.0+u);
      dfy=u/square(1.0+u);
    }
    return diff*dfy;
  }
}

/**
  Return scaled variable to original units; constant objects.
  \param x Variable scaled between [-1,1]
  \param fmin Lower bound of x
  \param fmin Upper bound of x
  \return The variable x in original units
 */
double boundp(double x, double fmin, double fmax)
{
  if (gradient_structure::Hybrid_bounded_flag==0)
  {
    double t;
    double diff=fmax-fmin;
    double ss=0.49999999999999999*sin(x*1.57079632679489661)+0.50;
    t=fmin + diff*ss;
    return(t);
  }
  else
  {
    double diff=fmax-fmin;
    double t,y;
    if (x>-20)
    {
      y=1.0/(1+exp(-x));
    }
    else
    {
      double u=exp(x);
      y=u/(1.0+u);
    }
    t=fmin + diff*y;
    return(t);
  }
}

/**
  Scale input variable between upper and lower bounds
  and compute a penalty for exceeding the bounds.
  Intended for use with df1b2 variables.
  \param x Variable to be scaled
  \param fmin Lower bound of x
  \param fmin Upper bound of x
  \param _fpen On return, contains penalty if x > fmax or x < fmin
  \return Scaled value of x between fmin and fmax in the range [-1,1]
 */
double nd2fboundp( double x, double fmin, double fmax,const double& fpen)
{
  if (x<-0.99999)
  {
    return (boundp(x,fmin,fmax,fpen)-2.*boundp(x+1.e-6,fmin,fmax,fpen)
      +boundp(x+2.e-6,fmin,fmax,fpen))/1.e-12;
  }
  else if (x>0.99999)
  {
    return (boundp(x-2.e-6,fmin,fmax,fpen)-2.*boundp(x-1.e-6,fmin,fmax,fpen)
      +boundp(x,fmin,fmax,fpen))/1.e-12;
  }
  else
  {
    return (boundp(x+1.e-6,fmin,fmax,fpen)-2.*boundp(x,fmin,fmax,fpen)
      +boundp(x-1.e-6,fmin,fmax,fpen))/1.e-12;
  }
}
/**
Compute penalty for exceeding bounds on parameter; constant ojbects.
Inverse of \ref double boundp(const double& x, double fmin, double fmax,
  const double& _fpen).
\param x Model variable
\param fmin Lower bound of x
\param fmin Upper bound of x
\param _fpen On return, contains penalty if x > fmax or x < fmin
\return The variable x in original units
 */
double boundp( double x, double fmin, double fmax,const double& _fpen)
{
  if (gradient_structure::Hybrid_bounded_flag==0)
  {
    double t;
    double& fpen=(double&) _fpen;
    double diff=fmax-fmin;
    const double l4=log(4.0);
    double ss=0.499999999999999*sin(x*1.57079632679489661)+0.50;
    t=fmin + diff*ss;
  #ifdef USE_BARD_PEN
    double pen=.001/diff;
    fpen-=pen*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4);
  #else
    if (x < -.9999)
    {
      fpen+=(x+0.9999)*(x+0.9999);
      if (x < -1.)
      {
        fpen+=1.e+6*(x+1.)*(x+1.);
        if (x < -1.02)
        {
          fpen+=1.e+10*(x+1.02)*(x+1.02);
        }
      }
    }
    if (x > 0.9999)
    {
      fpen+=(x-0.9999)*(x-0.9999);
      if (x > 1.)
      {
        fpen+=1.e+6*(x-1.)*(x-1.);
        if (x > 1.02)
        {
          fpen+=1.e+10*(x-1.02)*(x-1.02);
        }
      }
    }
  #endif
    return(t);
  }
  else
  {
    double diff=fmax-fmin;
    double t,y;
    if (x>-20)
    {
      y=1.0/(1+exp(-x));
    }
    else
    {
      double u=exp(x);
      y=u/(1.0+u);
    }
    t=fmin + diff*y;
    return(t);
  }
}

/**
  Scale model variable over [-1,1]; constant objects.
  Inverse of \ref double boundp(double x, double fmin, double fmax)
  \param x Model variable
  \param fmin Lower bound of x
  \param fmin Upper bound of x
  \param s Divide x by s before scaling and setting bounds
  \return The variable x in original units
 */
double boundpin(double x, double fmin, double fmax,double s)
{
  return s*boundpin(x,fmin,fmax);
}

/**
  Scale model variable over [-1,1]; constant objects.
  Inverse of \ref double boundp(double x, double fmin, double fmax)
  \param x Model variable
  \param fmin Lower bound of x
  \param fmin Upper bound of x
  \return Scaled model variable over [-1,1].
 */
double boundpin(double x, double fmin, double fmax)
{
  if (x < fmin)
  {
    if (ad_printf)
    {
      (*ad_printf)("variable out of bounds in boundpin: variable = %lg", x);
      (*ad_printf)("; min = %lg", fmin);
      (*ad_printf)("; max = %lg\n", fmax);
    }
    x=dmin(fmin+.001,fmin+.01*(fmax-fmin));
  }

  if (x > fmax)
  {
    if (ad_printf)
      (*ad_printf)("variable out of bounds in boundpin: variable = %lg", x);
    if (ad_printf) (*ad_printf)("; min = %lg", fmin);
    if (ad_printf) (*ad_printf)("; max = %lg\n", fmax);

    x=dmax(fmax-.001,fmax-.01*(fmax-fmin));
  }

  double tinv;
  if (gradient_structure::Hybrid_bounded_flag==0)
  {
    tinv=::asin(2.*(x-fmin)/(fmax-fmin)-1.)/1.57079632679489661;
  }
  else
  {
    //double y=(x-fmin)/(fmax-fmin);
    //double u=1.e-20+y/(1.e-20+(1.0-y));
    double y=1.e-20+(fmax-x)/(1.e-20+(x-fmin));
    tinv=-log(y);
  }
  return(tinv);
}
/**
Scale model variable over [-1,1]; variable objects.
Inverse of \ref dvariable boundp(const prevariable& x, double fmin,
double fmax,const prevariable& _fpen, double s).
\param x Model variable
\param fmin Lower bound of x
\param fmin Upper bound of x
\param s Divide x by s before scaling and setting bounds
\return Scaled model variable over [-1,1].
*/
double boundpin(const prevariable& x, double fmin, double fmax,double s)
{
  return s*boundpin(x,fmin,fmax);
}

/**
  Scale model variable over [-1,1]; variable objects.
  Inverse of \ref dvariable boundp(const prevariable& x, double fmin, double fmax,const prevariable& _fpen).
  \param x Model variable
  \param fmin Lower bound of x
  \param fmin Upper bound of x
  \return Scaled model variable over [-1,1].
 */
double boundpin(const prevariable& xx, double fmin, double fmax)
{
  double tinv;
  double x=value(xx);

  if (x < fmin)
  {
    if (ad_printf)
      (*ad_printf)("variable out of bounds in boundpin: variable = %lg", x);
    if (ad_printf) (*ad_printf)("; min = %lg", fmin);
    if (ad_printf) (*ad_printf)("; max = %lg\n", fmax);

    x=dmin(fmin+.001,fmin+.01*(fmax-fmin));
  }

  if (x > fmax)
  {
    if (ad_printf)
    {
      (*ad_printf)("variable out of bounds in boundpin: variable = %lg", x);
      (*ad_printf)("; min = %lg", fmin);
      (*ad_printf)("; max = %lg\n", fmax);
    }

    x=dmax(fmax-.001,fmax-.01*(fmax-fmin));
  }
  if (gradient_structure::Hybrid_bounded_flag==0)
  {
    tinv=::asin(2.*(x-fmin)/(fmax-fmin)-1.)/1.57079632679489661;
  }
  else
  {
    //double y=(x-fmin)/(fmax-fmin);
    //double u=1.e-20+y/(1.e-20+(1.0-y));
    //tinv=-log(u);
    double y=1.e-20+(fmax-x)/(1.e-20+(x-fmin));
    tinv=-log(y);
  }

  return(tinv);
}
/**
  Returns the minimum of two numbers
  \param x First number
  \param y Second number
 */
double dmin(double x, double y)
{
  if (x<y)
  {
    return (x);
  }
  else
  {
    return(y);
  }
}
/**
  Returns the maximum of two numbers
  \param x First number
  \param y Second number
 */
double dmax(double x, double y)
{
  if (x>y)
  {
    return (x);
  }
  else
  {
    return(y);
  }
}
