/*
 * $Id$
 * Author: Unknown
 */
/**
 * \file
 * Description not yet available.
 */

#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#endif

#include <admodel.h>
#include <df12fun.h>

df1_two_variable incbet(const df1_two_variable& a,
  const df1_two_variable& b,double x);

/**
 * Description not yet available.
 * \param
 */
static double lnbeta(double a,double b)
{
  return gammln(a)+gammln(b)-gammln(a+b);
}

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_beta_stable(const prevariable& _a,const prevariable& _b,
  const prevariable& _y,double eps)
{
  ADUNCONST(prevariable,a);
  ADUNCONST(prevariable,b);
  ADUNCONST(prevariable,y);

  double eps1=1.0-eps;
  // this gets the inverse without derivatives
  double ca=value(a);
  double cb=value(b);
  double cx=inv_cumd_beta_stable(ca,cb,value(y),eps);

  init_df1_two_variable va(_a);
  init_df1_two_variable vb(_b);

  // this gets the derivatives for the function itself

  df1_two_variable z=(incbet(va,vb,cx)-incbet(va,vb,eps))/
    (incbet(va,vb,eps1)-incbet(va,vb,eps));
   
  double dga=*z.get_u_x();
  double dgb=*z.get_u_y();

  double denom=1.0/(incbet(ca,cb,eps1)-incbet(ca,cb,eps));
  double dgx=pow(cx,value(a)-1.0)*pow(1.0-cx,value(b)-1.0)/
    exp(lnbeta(value(a),value(b)))*denom;

  // now solve for the derivatves of the inverse function

  double dfx=1.0/dgx;
  double dfa=-dfx*dga;
  double dfb=-dfx*dgb;

  dvariable tmp;
  value(tmp)=cx;

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3ind,
    &(value(tmp)) ,&(value(_a)),dfa ,&(value(_b)),dfb ,&(value(_y)),dfx);

  return tmp;
}
