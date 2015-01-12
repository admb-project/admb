/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double dmin(double,double);
double dmax(double, double);

#define USE_BARD_PEN

/**
 * Description not yet available.
 * \param
 */
  dvariable boundp( dvariable xx, double fmin, double fmax, const prevariable& _fpen,
    const double& s)
{
  prevariable& fpen=(prevariable&) _fpen;
  
  dvariable t,y,x;
  x=xx/s;
  const double l4=log(4.0);
  dvariable ss=(sin(x*1.57079632679489661)+1.)/2.;
  double diff=fmax-fmin;
  t=fmin + diff*ss;
#ifdef USE_BARD_PEN
  //cout << "xxxxx" << endl;
  double pen=.00001/diff;
  fpen=fpen-pen*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4); 
#else 

  if (x < -.9999)
  {
    fpen+=(x+0.9999)*(x+0.9999);
  }

  if (x > 0.9999)
  {
    fpen+=(x-0.9999)*(x-0.9999);
  }

  if (x < -1.)
  {
    fpen+=1000.*(x+1.)*(x+1.);
  }

  if (x > 1.)
  {
    fpen+=1000.*(x-1.)*(x-1.);
  }
#endif
  return(t);
}

/**
 * Description not yet available.
 * \param
 */
double boundp( double xx, double fmin, double fmax, const double& _fpen,
  const double& s)
{
  double& fpen = (double&)_fpen;
  double t,x;
  x=xx/s;
  const double l4=log(4.0);
  double ss=(sin(x*1.57079632679489661)+1.)/2.;
  double diff=fmax-fmin;
  t=fmin + diff*ss;
#ifdef USE_BARD_PEN
  //cout << "xxxxx" << endl;
  double pen=.00001/diff;
  fpen-=pen*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4); 
#else 
  if (x < -.9999)
  {
    fpen+=(x+0.9999)*(x+0.9999);
  }

  if (x > 0.9999)
  {
    fpen+=(x-0.9999)*(x-0.9999);
  }

  if (x < -1)
  {
    fpen+=1000*(x+1)*(x+1);
  }

  if (x > 1)
  {
    fpen+=1000*(x-1)*(x-1);
  }
#endif
  return(t);
}

/**
 * Description not yet available.
 * \param
 */
double boundpin(double x, double fmin, double fmax,const double& s)
{
  double tinv;

  if (x < fmin)
  {
    if (ad_printf) (*ad_printf)("variable out of bounds in boundpin: variable = %lg", x);
    if (ad_printf) (*ad_printf)("; min = %lg", fmin);
    if (ad_printf) (*ad_printf)("; max = %lg\n", fmax);

    x=dmin(fmin+.001,fmin+.01*(fmax-fmin));
  }

  if (x > fmax)
  {
    if (ad_printf) (*ad_printf)("variable out of bounds in boundpin: variable = %lg", x);
    if (ad_printf) (*ad_printf)("; min = %lg", fmin);
    if (ad_printf) (*ad_printf)("; max = %lg\n", fmax);

    x=dmax(fmax-.001,fmax-.01*(fmax-fmin));
  }

  tinv=::asin(2.*(x-fmin)/(fmax-fmin)-1.)/1.57079632679489661;
  return(s*tinv);
}

/*
double boundpin(BOR_CONST prevariable& xx, double fmin, double fmax,_CONST double& s)
{
  double tinv;
  double x=value(xx);

  if (x < fmin)
  {
    if (ad_printf) (*ad_printf)("variable out of bounds in boundpin: variable = %lg", x);
    if (ad_printf) (*ad_printf)("; min = %lg", fmin);
    if (ad_printf) (*ad_printf)("; max = %lg\n", fmax);

    x=dmin(fmin+.001,fmin+.01*(fmax-fmin));
  }

  if (x > fmax)
  {
    if (ad_printf) (*ad_printf)("variable out of bounds in boundpin: variable = %lg", x);
    if (ad_printf) (*ad_printf)("; min = %lg", fmin);
    if (ad_printf) (*ad_printf)("; max = %lg\n", fmax);

    x=dmax(fmax-.001,fmax-.01*(fmax-fmin));
  }

  tinv=::asin(2.*(x-fmin)/(fmax-fmin)-1.)/1.57079632679489661;
  return(s*tinv);
}
*/

