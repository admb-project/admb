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
#include <df1b2fun.h>

static double cc=0.39894228040143267794;

typedef double (*pinit_f)(double y,double a); 

double  nr_generic(double y,pinit_f p_get_initial_x,
  pinit_f pfun,pinit_f pdfun);

/**
 * Description not yet available.
 * \param
 */
static double cumd_normal_mixture(double x,double a)
{
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
df1b2variable inv_cumd_normal_mixture(const df1b2variable& _yy,double a)
{
  ADUNCONST(df1b2variable,yy)
  df1b2variable z;
  double  x=nr_generic(value(yy),cumd_normal_mixture_initx,cumd_normal_mixture,
    df_cumd_normal_mixture);

  // the derivatives of the inverse
  double x2=x*x;
  double a2=a*a;
  double a3=a2*a;
  double a5=a2*a3;
  double e1=exp(-0.5*x2);
  double e2=exp(-0.5*x2/a2);

  double dgx=cc*(0.95*e1+0.05/a*e2);

  double d2g=-cc*x*(0.95*e1+0.05/a3*e2);

  double d3g=-cc*(0.95*e1+0.05/a3*e2)
    +cc*x2*(0.95*e1+0.05/a5*e2);

  double dfx=1.0/dgx;
  double d2f=-d2g*cube(dfx);
  double d3f=-d3g*cube(dfx)*dfx-3.0*d2g*d2f*square(dfx);

  double * yd=yy.get_u_dot();
  double * zd=z.get_u_dot();
  *z.get_u()=x;
  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ =dfx * *yd++;
  }
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1(&yy,&z,dfx,d2f,d3f);

  return z;
}

