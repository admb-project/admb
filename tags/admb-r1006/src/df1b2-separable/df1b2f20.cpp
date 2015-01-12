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
#include "df3fun.h"

df3_one_variable lgam(const df3_one_variable& _x);

/**
 * Log Gamma Function
 *
 * Used to find the Natural log of the gamma function.
 *
 * \param _x the argument
 *
 */  
df1b2variable lgam(const df1b2variable& _v1)
{
  df1b2variable tmp;
  tmp = 0.0;
  const double phi = 0.5772156649015328606065121;
  const double pi = 3.1415926535897932384626432;
  const double zeta = 1.2020569031595942853997382;
  init_df3_one_variable v1(_v1);

  if (value(v1)==1.0)
  {
    // value of lgam(1.0) is 0
    // 1st derivative is -phi
    // 2nd deriv is pi*pi/6
    // 3rd deriv is -2*zeta
    df3_one_variable v;
    v = 0.0;
    *v.get_udot() = -phi; 
    *v.get_udot2() = pi*pi/6;
    *v.get_udot3() = -2*zeta;
    tmp=v;

  }
  else if (value(v1)==2.0)
  {
    // value of lgam(2.0) is 0 and
    // 1st derivative is 1-phi
    // 2nd deriv is pi*pi/6 - 1
    // 3rd deriv is 2*(1-zeta)
    df3_one_variable v;
    v = 0.0;
    *v.get_udot() = 1 - phi; 
    *v.get_udot2() = pi*pi/6 - 1;
    *v.get_udot3() = -2*(1-zeta);
    tmp=v;
  }
  else
  {
     tmp=lgam(v1);
  }
  return(tmp);
}

/**
 * Log Gamma Function
 *
 * Used to find the Natural log of the gamma function.
 *
 *
 * \n\n Modified from lgamma.cpp (http://www.crbond.com/download/lgamma.cpp),
 *      an algorithm that was translated by C. Bond
 *      from "Computation of Special Functions", Zhang and Jin, John Wiley and Sons, 1996.
 */ 
df3_one_variable lgam(const df3_one_variable& _x)
{
   df3_one_variable&  x = (df3_one_variable&)_x;
   df3_one_variable x0;
   df3_one_variable x2;
   df3_one_variable xp;
   df3_one_variable gl;
   df3_one_variable gl0;
   x0 = 0.0;
   x2 = 0.0;
   xp = 0.0;
   gl = 0.0;
   gl0 = 0.0;
   int n = 0;
   int k = 0;
   const double pi = 3.1415926535897932384626432;
   static double a[] = {
       8.333333333333333e-02,
      -2.777777777777778e-03,
       7.936507936507937e-04,
      -5.952380952380952e-04,
       8.417508417508418e-04,
      -1.917526917526918e-03,
       6.410256410256410e-03,
      -2.955065359477124e-02,
       1.796443723688307e-01,
      -1.39243221690590};

    x0 = x;
    if (value(x) <= 0.0)
    {
       df3_one_variable ret;
       ret = 1e308;
       return ret;
    }
    else if (value(x) <= 7.0)
    {
        n = (int)(7-value(x));
        x0 = x+n;
    }
    x2 = 1.0/(x0*x0);
    xp = 2.0*pi;
    gl0 = a[9];
    for (k=8;k>=0;k--)
    {
        gl0 = gl0*x2 + a[k];
    }
    gl = gl0/x0+0.5*log(xp)+(x0-0.5)*log(x0)-x0;
    if (value(x) <= 7.0)
    {
        for (k=1;k<=n;k++)
        {
            gl -= log(x0-1.0);
            x0 -= 1.0;
        }
    }
    return gl;
}



df1b2variable gammln(const df1b2variable& z)
{
   return lgam(z);
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector gammln(const df1b2vector&  z){
  int from=z.indexmin();
  int to=z.indexmax();
  df1b2vector ret(from,to);
  for(int i=from; i<=to; ++i){
    ret(i)=gammln(z(i));
 }
 return(ret);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable log_comb(_CONST df1b2variable& n,double k)
{
  return factln(n)-factln(k)-factln(n-k);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable log_comb(_CONST df1b2variable& n,_CONST df1b2variable& k)
{
  return factln(n)-factln(k)-factln(n-k);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable log_comb(double n,_CONST df1b2variable& k)
{
  return factln(n)-factln(k)-factln(n-k);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable factln(_CONST df1b2variable& n)
{
  return gammln(n+1.0);
}
