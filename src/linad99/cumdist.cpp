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
#include <fvar.hpp>

double inv_cumd_norm(_CONST double& x);
double cumd_norm(_CONST double& x);

/**
 * Description not yet available.
 * \param
 */
double normal_tail_right(_CONST double& x)
{
  const double a3=5;
  const double a4=9;
  const double a5=129;
  double x2=x*x;
  double z=0.3989422804*exp(-.5*x2);
  double b1=x2+2;
  double b2=b1*(x2+4);
  double b3=b2*(x2+6);
  double b4=b3*(x2+8);
  double b5=b4*(x2+10);
  double tmp=z/x*(1.0 -1.0/b1 +1.0/b2 - a3/b3 +a4/b4 -a5/b5);
  return tmp;
}
  
/**
 * Description not yet available.
 * \param
 */
double inv_cumd_norm_inner(double x)
{
  const double c0=2.515517;
  const double c1=0.802853;
  const double c2=0.010328;
  const double d1=1.432788;
  const double d2=0.189269;
  const double d3=0.001308;
  if (x<=0 || x>=1.0) 
  {
    cerr << "Illegal argument to inv_cumd_norm = " << x << endl;
    return 0;
  }
   
  if (x<0.5)
  {
    double t = sqrt(-2.*log(x));
    double p=((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1)-t;
    return p;
  }
  else if (x==0.5)
  {
    return 0.0;
  }
  else
  {
    double y=1.-x;
    //double t = sqrt(-log(y*y));
    double t = sqrt(-2.*log(y));
    double p=t-((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1);
    return p;
  } 
}

/**
 * Description not yet available.
 * \param
 */
double inv_cumd_norm(_CONST double& x)
{
  double y=inv_cumd_norm_inner(x);
  y+=2.50662827*exp(.5*y*y)*(x-cumd_norm(y));
  return y;
}

/** Culative normal distribution; constant objects.
\param x Normalized "Z" score (subtact the mean and divide by the stdard deviation).
\return Probablity that of an observation will exceed the argument.
\ingroup PDF
*/
double cumd_norm(_CONST double& x)
{
  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double p=.2316419;
  if (x>=0)
  {
    double u=1./(1+p*x);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double z=1.0-0.3989422804*exp(-.5*x*x)*y;
    return z;
  }
  else
  {
    double w=-x;
    double u=1./(1+p*w);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double z=0.3989422804*exp(-.5*x*x)*y;
    return z;
  }
}

/**
 * Description not yet available.
 * \param
 */
double bounded_cumd_norm(const double x,double beta)
{
  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double p=.2316419;
  if (x>=0)
  {
    double u=1./(1+p*x);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double z=1.0-0.3989422804*exp(-.5*x*x)*y;
    z=beta*(z-0.5)+0.5;
    return z;
  }
  else
  {
    double w=-x;
    double u=1./(1+p*w);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double z=0.3989422804*exp(-.5*x*x)*y;
    z=beta*(z-0.5)+0.5;
    return z;
  }
}
