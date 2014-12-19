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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
double ADpow_fun(double x,double y)
{
  return pow(x,y);
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_1(double x,double y)
{
  return y*pow(x,y-1);
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_2(double x,double y)
{
  return pow(x,y)*log(x);
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_22(double x,double y)
{
  return pow(x,y)*square(log(x));
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_122(double x,double y)
{
  double xy1=pow(x,y-1.0);
  double lx=log(x);
  return xy1*lx*(y*lx + 2.0);
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_12(double x,double y)
{
  double xy1=pow(x,y-1.0);
  return xy1*(1.0 + y*log(x));
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_11(double x,double y)
{
  return (y-1.0)*y*pow(x,y-2.0);
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_111(double x,double y)
{
  return (y-2.0)*(y-1.0)*y*pow(x,y-3.0);
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_112(double x,double y)
{
  return pow(x,y-2)*(2.0*y-1.0 + y*(y-1)*log(x) + x);
}

/**
 * Description not yet available.
 * \param
 */
double AD_pow_222(double x,double y)
{
  return pow(x,y)*cube(log(x));
}

df1b2function2 ADf1b2_pow(ADpow_fun,
 AD_pow_1,AD_pow_2,
 AD_pow_11,AD_pow_12,AD_pow_22,
 AD_pow_111,AD_pow_112,AD_pow_122,
 AD_pow_222);
/*
df1b2variable pow(const df1b2variable& x,const df1b2variable& y)
{
  return ADf1b2_pow(x,y);
}
*/
