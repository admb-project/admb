/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
//#ifdef __TURBOC__
//#  pragma hdrstop
//#endif

#define USE_BARD_PEN

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double dmin(double,double);
double dmax(double, double);

  dvariable dfatan1( dvariable x, double fmin, double fmax,BOR_CONST prevariable&  _fpen)
{
  prevariable&  fpen=(prevariable&)  _fpen;
  dvariable t;

  t= (atan(x)/3.1415926);
  t=( t +.5 );
  t= t *( fmax-fmin ) + fmin;
  t=( (atan(x)/3.1415926) +.5 )*( fmax-fmin ) + fmin;

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

double dftinv(double x, double fmin, double fmax)
{
  double tinv;
  if (x <= fmin)
  {
    if (ad_printf) (*ad_printf)("variable out of bounds in dftinv\nvariable = %lg", x);
    if (ad_printf) (*ad_printf)("lower bound = %lg", fmin);
    if (ad_printf) (*ad_printf)("upper bound = %lg\n", fmax);

    x=dmin(fmin+.001,fmin+.01*(fmax-fmin));
  }

  tinv=tan( ((x-fmin)/(fmax-fmin) -.5) * 3.1415926);
  return(tinv);
}

dvariable boundp(const prevariable& x, double fmin, double fmax,const prevariable& _fpen,double s)
{
  return boundp(x/s,fmin,fmax,_fpen);
}

dvariable boundp(const prevariable& x, double fmin, double fmax,const prevariable& _fpen)
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
void xxjunk10(double){;}

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
      cout << "error in dfboundp" << endl;
    }
    return diff*dfy;
  }
} 

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

double boundpin(double x, double fmin, double fmax,double s)
{
  return s*boundpin(x,fmin,fmax); 
}

double boundpin(double x, double fmin, double fmax)
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

double boundpin(const prevariable& x, double fmin, double fmax,double s)
{
  return s*boundpin(x,fmin,fmax); 
}

double boundpin(const prevariable& xx, double fmin, double fmax)
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

