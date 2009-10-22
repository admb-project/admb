/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>

static double cc=0.39894228040143267794;   // 1/sqrt(2*pi)

typedef double (*pinit_f)(double y,double a); 


static double cumd_normal_mixture(double x,double a)
{
  // "normal" value for a is 3.0
  double y=0.95*cumd_norm(x)+0.05*cumd_norm(x/a);
  return y;
}

static double df_cumd_normal_mixture(double x,double a)
{
  double x2=x*x;
  double dfx=cc*(0.95*exp(-0.5*x2)+0.05/a*exp(-0.5*x2/(a*a)) );

  return dfx;
}

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


static double  nr_generic(double y,pinit_f p_get_initial_x,
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

double inv_cumd_normal_mixture(double yy,double a)
{
  double  x=nr_generic(yy,cumd_normal_mixture_initx,cumd_normal_mixture,
    df_cumd_normal_mixture);
  return x;
}

