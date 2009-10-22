/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>

static double cc=0.39894228040143267794;

typedef double (*pinit_f)(double y,double a); 

double  nr_generic(double y,double a,pinit_f p_get_initial_x,
  pinit_f pfun,pinit_f pdfun);

static double cumd_normal_logistic_mixture(double x,double a)
{
  // "normal" value for a is 3.0
  double y;
  y=0.95*cumd_norm(x)+0.05/(1.0+exp(-x/a));
 /*
  if (x>-20.0)
  {
    y=0.95*cumd_norm(x)+0.05/(1.0+exp(-x));
  }
  else
  {
    y=0.95*cumd_norm(x)+0.05*exp(x)/(1.0+exp(x));
  }
  */
  return y;
}

static double df_cumd_normal_logistic_mixture(double x,double a)
{
  // "normal" value for a is 3.0
  //double y=0.95*cumd_norm(x)+0.05*cumd_norm(x/a)
  double x2=x*x;
  double dfx;
    dfx=cc*0.95*exp(-0.5*x2)+0.05/a*exp(-x/a)/square(1.0+exp(-x/a));
 /*
  if (x>-20.0)
  {
    dfx=cc*0.95*exp(-0.5*x2)+0.05*exp(-x)/square(1.0+exp(-x));
  }
  else
  {
    dfx=cc*0.95*exp(-0.5*x2)+0.05*exp(x)/square(1.0+exp(x));
  }
  */

  return dfx;
}

static double cumd_normal_logistic_mixture_initx(double y,double a)
{
  double x;
  if (y>0.999)
  {
    x= a*inv_cumd_logistic((y-0.95)/0.05);
  }
  else if (y<.001)
  {
    x= 1.0-a*inv_cumd_logistic((.05-y)/0.05);
  }
  else
  {
    x=inv_cumd_norm(y);
  }
  return x;
}

df1b2variable inv_cumd_normal_logistic_mixture(const df1b2variable& _yy,double a)
{
  ADUNCONST(df1b2variable,yy)
  df1b2variable z;
  double  x=nr_generic(value(yy),a,cumd_normal_logistic_mixture_initx,
    cumd_normal_logistic_mixture,
    df_cumd_normal_logistic_mixture);

  // the derivatives of the inverse
  double x2=x*x;
  double e1=exp(-0.5*x2);

  double dgx=cc*0.95*e1+0.05/a*exp(-x/a)/square(1.0+exp(-x/a));

 /*
  double xp=x+1.e-5;
  double xm=x-1.e-5;
  double e1p=exp(-0.5*xp*xp);
  double e1m=exp(-0.5*xm*xm);
  double dgxp=cc*0.95*e1p+0.05*exp(-xp)/square(1.0+exp(-xp));
  double dgxm=cc*0.95*e1m+0.05*exp(-xm)/square(1.0+exp(-xm));
 */

  //cout << (dgxp-dgxm)/(2.0*1.e-5) << endl;
  //cout << (dgxp-2.0*dgx+dgxm)/(1.e-10) << endl;

  double d2g=-cc*0.95*x*e1+0.05/(a*a)*(
           -exp(-x/a)/square(1.0+exp(-x/a))
           +2.0*exp(-2.0*x/a)/cube(1.0+exp(-x/a)));

  double d3g=-cc*0.95*e1 +cc*x2*0.95*e1 +0.05/(a*a*a)*(
     exp(-x/a)/square(1.0+exp(-x/a)) -6.0*exp(-2.0*x/a)/cube(1.0+exp(-x/a))  
     +6.0*exp(-3.0*x/a)/square(square(1.0+exp(-x/a))));
   


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

