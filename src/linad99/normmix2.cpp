/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>

static double cc=0.39894228040143267794;

typedef double (*pinit_f)(double y,double a); 


static double cumd_normal_logistic_mixture(double x,double a)
{
  // "normal" value for a is 3.0
  double y;
  if (x>-20.0)
  {
    y=0.95*cumd_norm(x)+0.05/(1.0+exp(-x/a));
  }
  else
  {
    y=0.95*cumd_norm(x)+0.05/(1.0+exp(-x/a));
  }
  return y;
}

static double df_cumd_normal_logistic_mixture(double x,double a)
{
  // "normal" value for a is 3.0
  //double y=0.95*cumd_norm(x)+0.05*cumd_norm(x/a)
  double x2=x*x;
  double dfx;
  if (x>-20.0)
  {
    dfx=cc*0.95*exp(-0.5*x2)+0.05/a*exp(-x/a)/square(1.0+exp(-x/a));
  }
  else
  {
    dfx=cc*0.95*exp(-0.5*x2)+0.05/a*exp(-x/a)/square(1.0+exp(-x/a));
  }

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

double  nr_generic(double y,double a,pinit_f p_get_initial_x,
  pinit_f pfun,pinit_f pdfun)
{
  double x=(*p_get_initial_x)(y,a);

  const int imax=15;
  int icount=0;
  double h;
  do
  {
    icount++;
    double cy=(*pfun)(x,a);
    double der=(*pdfun)(x,a);
    double diff=y-cy;
    h=diff/der;
    x+=h;
    if (fabs(h)<1.e-12) break;
  }
  while(icount<imax);
  //cout << " x = " << x << " icount = " << icount << endl;
  if (fabs(h)>1.e-8)
  {
    cerr << "shit" << endl;
  }


  return x;
}

dvariable inv_cumd_normal_logistic_mixture(const prevariable& _yy,double a)
{
  ADUNCONST(dvariable,yy)
  double  x=nr_generic(value(yy),a,cumd_normal_logistic_mixture_initx,
    cumd_normal_logistic_mixture,df_cumd_normal_logistic_mixture);
  dvariable z;
  value(z)=x;
  double dfx=1.0/df_cumd_normal_logistic_mixture(x,a);
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
     &(value(z)), &(value(yy)),dfx);
  return z;
}

/*
main()
{
  gradient_structure gs(10000);
  dvariable y;
  cin >> y;
  dvariable x=inv_cumd_normal_logistic_mixture(y,3.0);
}
*/
