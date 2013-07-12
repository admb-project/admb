/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

static double cc=0.39894228040143267794;   // 1/sqrt(2*pi)

typedef double (*pinit_f)(double y,double a);

/**
 * Description not yet available.
 * \param
 */
static double cumd_normal_mixture(double x,double a)
{
  // "normal" value for a is 3.0
  double y=0.95*cumd_norm(x)+0.05*cumd_norm(x/a);
  return y;
}

/**
 * Description not yet available.
 * \param
 */
static double df_cumd_normal_mixture(double x,double a)
{
  double x2=x*x;
  double dfx=cc*(0.95*exp(-0.5*x2)+0.05/a*exp(-0.5*x2/(a*a)) );

  return dfx;
}

/**
 * Description not yet available.
 * \param
 */
static double cumd_normal_mixture_initx(double y,double a)
{
  double x;
  if (y>0.999)
  {
    x= a*inv_cumd_norm((y-0.95)/0.05);
  }
  else if (y<.001)
  {
    x= 1.0-a*inv_cumd_norm((.05-y)/0.05);
  }
  else
  {
    x=inv_cumd_norm(y);
  }
  return x;
}

/**
 * Description not yet available.
 * \param
 */
double  nr_generic(double y,pinit_f p_get_initial_x,
  pinit_f pfun,pinit_f pdfun)
{
  double x=(*p_get_initial_x)(y,3.0);

  const int imax=15;
  int icount=0;
  do
  {
    icount++;
    double cy=(*pfun)(x,3.0);
    double der=(*pdfun)(x,3.0);
    double diff=y-cy;
    double h=diff/der;
    x+=h;
    if (fabs(h)<1.e-12) break;
  }
  while(icount<imax);
  //cout << " x = " << x << " icount = " << icount << endl;


  return x;
}

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_normal_mixture(const prevariable& _yy,double a)
{
  ADUNCONST(dvariable,yy)
  double  x=nr_generic(value(yy),cumd_normal_mixture_initx,cumd_normal_mixture,
    df_cumd_normal_mixture);
  dvariable z;
  value(z)=x;
  double dfx=1.0/df_cumd_normal_mixture(x,a);
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
     &(value(z)), &(value(yy)),dfx);
  return z;
}
