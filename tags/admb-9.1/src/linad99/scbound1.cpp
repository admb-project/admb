/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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


double boundpin(const prevariable& xx, double fmin, double fmax,const double& s)
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

