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

static double cc=0.39894228040143267794;

typedef double (*pinit_f)(double y,double a); 

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
double  nr_generic(double y,double a,pinit_f p_get_initial_x,
  pinit_f pfun,pinit_f pdfun);

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
//********************************************************
//********************************************************
//********************************************************
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
double robust_normal_logistic_mixture_deviate(double x,double spread)
{

  double y=cumd_norm(x);
  y = 0.99999999*y + 0.000000005; // To gain numerical stability
  double z = inv_cumd_normal_logistic_mixture(y,spread);
  return z;
}

/**
 * Description not yet available.
 * \param
 */
double robust_normal_mixture_deviate(double x,double spread)
{
  double y=cumd_norm(x);
  y = 0.99999999*y + 0.000000005; // To gain numerical stability
  double z = inv_cumd_normal_mixture(y,spread);
  return z;
}

/**
 * Description not yet available.
 * \param
 */
double inv_cumd_normal_logistic_mixture(double yy,double a)
{
  double  x=nr_generic(yy,a,cumd_normal_logistic_mixture_initx,
    cumd_normal_logistic_mixture,df_cumd_normal_logistic_mixture);
  return x;
}
