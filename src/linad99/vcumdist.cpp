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

dvariable inv_cumd_norm(_CONST prevariable& x);
prevariable& cumd_norm(_CONST prevariable& x);
/*
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
*/
  
/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_norm_inner(_CONST prevariable& x)
{
 if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
   gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
 RETURN_ARRAYS_INCREMENT();
  const double c0=2.515517;
  const double c1=0.802853;
  const double c2=0.010328;
  const double d1=1.432788;
  const double d2=0.189269;
  const double d3=0.001308;
  if (x<=0 || x>=1.0) 
  {
    //cerr << "Illegal argument to inv_cumd_norm = " << x << endl;
    RETURN_ARRAYS_DECREMENT();
    return 0.0;
  }
   
  if (x<=0.5)
  {
    //dvariable t = sqrt(-2.*log(x));
    //dvariable p=((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1)-t;
    //RETURN_ARRAYS_DECREMENT();
    //return p;

    double tt = sqrt(-2.*log(value(x)));
    double u=(c2*tt+c1)*tt+c0;
    double v=((d3*tt+d2)*tt+d1)*tt+1;
    double vinv=1.0/v;
    double pp=u*vinv-tt;

    //double pp=u*vinv-tt;
    double dfu=vinv;
    double dfvinv=u;
    double dftt=-1.0;
    //double vinv=1.0/v;
    double dfv=-vinv*vinv*dfvinv;
    //double v=((d3*tt+d2)*tt+d1)*tt+1;
    dftt+=((3*d3*tt+2.0*d2)*tt+d1)*dfv;
    //double u=(c2*tt+c1)*tt+c0;
    dftt+=(2.0*c2*tt+c1)*dfu;
    //double tt = sqrt(-2.*log(value(x)));
    double dfx=-1.0/(tt*value(x))*dftt;

    RETURN_ARRAYS_DECREMENT();
    gradient_structure::RETURN_PTR->v->x=pp;
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
       &(gradient_structure::RETURN_PTR->v->x), &(x.v->x),dfx);
    return(*gradient_structure::RETURN_PTR);
  }
  else if (x==0.5)
  {
    cout << "can't happen" << endl;
    exit(1);    
    return 0.0;
  }
  else
  {
    //dvariable y=1.-x;
    //dvariable t = sqrt(-2.*log(y));

    //dvariable p=t-((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1);
    //RETURN_ARRAYS_DECREMENT();
    //return p;

    double yy=1.-value(x);
    double tt = sqrt(-2.*log(yy));
    double u=((c2*tt+c1)*tt+c0);
    double v=((d3*tt+d2)*tt+d1)*tt+1;
    double vinv=1/v;
    double pp=tt-u*vinv;
    
    //double pp=tt-u*vinv;
    double dfu=-vinv;
    double dfvinv=-u;
    double dftt=1.0;
    //double vinv=1.0/v;
    double dfv=-vinv*vinv*dfvinv;
    //double v=((d3*tt+d2)*tt+d1)*tt+1;
    dftt+=((3*d3*tt+2.0*d2)*tt+d1)*dfv;
    //double u=(c2*tt+c1)*tt+c0;
    dftt+=(2.0*c2*tt+c1)*dfu;
    //double tt = sqrt(-2.*log(yy));
    double dfy=-1.0/(tt*yy)*dftt;
    //double yy=1.-value(x);
    double dfx=-dfy;

    RETURN_ARRAYS_DECREMENT();
    gradient_structure::RETURN_PTR->v->x=pp;
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
       &(gradient_structure::RETURN_PTR->v->x), &(x.v->x),dfx);
    return(*gradient_structure::RETURN_PTR);
  } 
}

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_norm(_CONST prevariable& x)
{
  dvariable y=inv_cumd_norm_inner(x);
  if (x>1.e-30)
    y+=2.50662827*exp(.5*y*y)*(x-cumd_norm(y));
  return y;
}

/**
 * Description not yet available.
 * \param
 */
dvariable old_cumd_norm(_CONST prevariable& x)
{
  RETURN_ARRAYS_INCREMENT();
  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double p=.2316419;
  if (x>=0)
  {
    dvariable u=1./(1+p*x);
    dvariable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    dvariable z=1.0-0.3989422804*exp(-.5*x*x)*y;
    RETURN_ARRAYS_DECREMENT();
    return z;
  }
  else
  {
    dvariable w=-x;
    dvariable u=1./(1+p*w);
    dvariable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    dvariable z=0.3989422804*exp(-.5*x*x)*y;
    RETURN_ARRAYS_DECREMENT();
    return z;
  }
}

/** Culative normal distribution; variable objects.
\param _x Normalized "Z" score (subtact the mean and divide by the stdard deviation).
\return Probablity that of an observation will exceed the argument.
\ingroup PDF
*/
prevariable& cumd_norm(_CONST prevariable& _x)
{
 if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
   gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;

  double x=value(_x);
  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double b55=b5*5;
  const double b44=b4*4;
  const double b33=b3*3;
  const double b22=b2*2;
  const double p=.2316419;
  if (x>=0)
  {
    double u=1./(1+p*x);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double tmp1=-0.3989422804*exp(-.5*x*x);
    double z=1.0+tmp1*y;
    gradient_structure::RETURN_PTR->v->x=z;


    // double z=1.0+tmp1*y;
    double dftmp1=y;
    double dfy=tmp1;

    // double tmp1=-0.3989422804*exp(-.5*x*x);
    double dfx=-tmp1*x*dftmp1;

    //double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double dfu=  ((((b55*u+b44)*u+b33)*u+b22)*u+b1)*dfy;
    
    //double u=1./(1+p*x);
    dfx-=u*u*p*dfu;

    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
       &(gradient_structure::RETURN_PTR->v->x), &(_x.v->x), dfx);
  }
  else
  {
    double w=-x;
    double u=1./(1+p*w);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double tmp1=0.3989422804*exp(-.5*x*x);
    double z=tmp1*y;

    //double z=tmp1*y;
    double dftmp1=y;
    double dfy=tmp1;

    //double tmp1=0.3989422804*exp(-.5*x*x);
    double dfx=-tmp1*x*dftmp1;

    //double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double dfu=  ((((b55*u+b44)*u+b33)*u+b22)*u+b1)*dfy;

    //double u=1./(1+p*w);
    double dfw=-u*u*p*dfu;

    //double w=-value(x);
    dfx-=dfw;

    gradient_structure::RETURN_PTR->v->x=z;
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
       &(gradient_structure::RETURN_PTR->v->x), &(_x.v->x),dfx);
  }
  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector inv_cumd_norm(_CONST dvar_vector& x)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  dvar_vector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=inv_cumd_norm(x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& bounded_cumd_norm(_CONST prevariable& _x,double beta)
{
 if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
   gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;

  double x=value(_x);
  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double b55=b5*5;
  const double b44=b4*4;
  const double b33=b3*3;
  const double b22=b2*2;
  const double p=.2316419;
  if (x>=0)
  {
    double u=1./(1+p*x);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double tmp1=-0.3989422804*exp(-.5*x*x);
    double z1=1.0+tmp1*y;
    double z=beta*(z1-0.5)+0.5;
    gradient_structure::RETURN_PTR->v->x=z;

    //double z=beta*(z1-0.5)+0.5
    double dfz1=beta;

    // double z1=1.0+tmp1*y;
    double dftmp1=y*dfz1;
    double dfy=tmp1*dfz1;

    // double tmp1=-0.3989422804*exp(-.5*x*x);
    double dfx=-tmp1*x*dftmp1;

    //double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double dfu=  ((((b55*u+b44)*u+b33)*u+b22)*u+b1)*dfy;
    
    //double u=1./(1+p*x);
    dfx-=u*u*p*dfu;

    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
       &(gradient_structure::RETURN_PTR->v->x), &(_x.v->x), dfx);
  }
  else
  {
    double w=-x;
    double u=1./(1+p*w);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double tmp1=0.3989422804*exp(-.5*x*x);
    double z1=tmp1*y;
    double z=beta*(z1-0.5)+0.5;

    //double z=beta*(z1-0.5)+0.5;
    double dfz1=beta;

    //double z1=tmp1*y;
    double dftmp1=y*dfz1;
    double dfy=tmp1*dfz1;

    //double tmp1=0.3989422804*exp(-.5*x*x);
    double dfx=-tmp1*x*dftmp1;

    //double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double dfu=  ((((b55*u+b44)*u+b33)*u+b22)*u+b1)*dfy;

    //double u=1./(1+p*w);
    double dfw=-u*u*p*dfu;

    //double w=-value(x);
    dfx-=dfw;

    gradient_structure::RETURN_PTR->v->x=z;
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
       &(gradient_structure::RETURN_PTR->v->x), &(_x.v->x),dfx);
  }
  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_norm_logistic(_CONST prevariable& x,double p)
{
#if defined(SAFE_ALL)
  if (0.0<p || 1.0>p)
  {
    cerr << "Error in dvariable inv_cumd_norm_logistic -- illegal p value = " 
         << p << endl;
    exit(1);
  }    
#endif   
  dvariable y=inv_cumd_norm_inner(x);
  y+=( (1.0-p)*2.50662827*exp(.5*y*y) + 
    p*exp(-x)/square(1.0+exp(-x)) ) * (x-cumd_norm_logistic (y,p));
  return y;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& cumd_norm_logistic(_CONST prevariable& _x,double p)
{
  return (1.0-p)*cumd_norm(_x)+p*cumd_logistic(_x);
}  
