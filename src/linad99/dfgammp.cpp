/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009-2011 ADMB Foundation
 */

/**
 * \file
 * This file deals with the Incomplete Gamma Functions
 * of variable types. All supporting mathematical functions
 * required to compute the Inmomplete Gamma Function
 * are included. They being: gamma function, log gamma,
 * and some polynomial evaluation functions.
 */

#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#else
#  include <fvar.hpp>
#endif
#include <admodel.h>  
#include <df11fun.h>
#include <df12fun.h>

double get_values(double x,double y,int print_switch);
dvariable igam(const dvariable & _a, const dvariable & _x);
dvariable igamc(const dvariable & _a, const dvariable & _x);
dvariable lgam(_CONST prevariable& v1);
dvariable private_lgam(const dvariable& v);
df3_one_variable lgam(const df3_one_variable& _x);

extern int mtherr(char* s,int n);

namespace Cephes
{
   extern const double A[];
   extern const double B[];
   extern const double C[];
   extern const double Q[];
   extern const double P[];
   extern const double STIR[];
   extern int sgngam;
   extern const double MAXLOG;
   extern const double MAXNUM;
   extern const double PI;
   extern const double LOGPI;
   extern const double big;
   extern const double biginv;
   extern const double MACHEP;
   extern const double MYINF;
   extern const double SQTPI;
   extern const double MAXLGM;
   extern const double LS2PI;
   extern const double MAXSTIR;

   dvariable polevl(const dvariable & x, const void *_coef, int N);
   dvariable p1evl(const dvariable & x, const void *_coef, int N);

   /**
    * \ingroup gammafunc
    * Stirling's formula (approximation to large factorials)
    * \param _x \f$x\f$
    * \return Sterling's approximation to \f$x!\f$
    * 
    * \n\n Cephes Math Library Release 2.1:  December, 1988
    * Copyright 1984, 1987, 1988 by Stephen L. Moshier 
    * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
    */
   dvariable stirf(const dvariable & _x)
   {
      ADUNCONST(dvariable, x) dvariable y, w, v;

      w = 1.0 / x;
      w = 1.0 + w * polevl(w, STIR, 4);
      y = exp(x);
      if (value(x) > MAXSTIR)
      {				/* Avoid overflow in pow() */
	 v = pow(x, 0.5 * x - 0.25);
	 y = v * (v / y);
      } else
      {
	 y = pow(x, x - 0.5) / y;
      }
      y = SQTPI * y * w;
      return (y);
   }

   /**
    * \ingroup gammafunc
    * Polynomial evaluation
    * \param x \f$x\f$ the point to be evaluated
    * \param _coef The coefficents of the polynomial
    * \param N \f$N\f$ The degree of the polynomial
    * \return The polynomial evaluated at \f$x\f$
    * 
    * \n\n Cephes Math Library Release 2.1:  December, 1988
    * Copyright 1984, 1987, 1988 by Stephen L. Moshier 
    * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
    */
   dvariable polevl(const dvariable & x, const void *_coef, int N)
   {
      double *coef = (double *) (_coef);
      dvariable ans;
      int i;
      double *p;

      p = coef;
      ans = *p++;
      i = N;

      do
	 ans = ans * x + *p++;
      while (--i);

      return (ans);
   }

   /**
    * \ingroup gammafunc
    * Polynomial evaluation when leading coefficent is 1
    * (i.e. leading term is \f$x^N\f$)
    * \param x \f$x\f$ the point to be evaluated
    * \param _coef The coefficents of the polynomial
    * \param N \f$N\f$ The degree of the polynomial
    * \return The polynomial evaluated at \f$x\f$
    * 
    * \n\n Cephes Math Library Release 2.1:  December, 1988
    * Copyright 1984, 1987, 1988 by Stephen L. Moshier 
    * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
    */
   dvariable p1evl(const dvariable & x, const void *_coef, int N)
   {
      double *coef = (double *) (_coef);
      dvariable ans;
      double *p;
      int i;

      p = coef;
      ans = x + *p++;
      i = N - 1;

      do
	 ans = ans * x + *p++;
      while (--i);

      return (ans);
   }
} // End Cephes namespace


/**
 * \ingroup gammafunc
 * Incomplete gamma integral \f$\gamma(a,x) = \frac{1}{\Gamma(a)}\int_{0}^{x}e^{-t}t^{a-1}dt \f$
 * \param aa \f$a, \, a>0\f$
 * \param xx \f$x\f$
 * \return Incomplete gamma integral
 *
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
dvariable igam(const dvariable & aa, const dvariable & xx)
{
   using namespace Cephes;
   dvariable a = aa;
   dvariable x = xx;

   dvariable ans, ax, c, r, t;

   if ((value(x) <= 0) || (value(a) <= 0))
   {
      dvariable tmp;
      tmp = 0.0;
      return (tmp);
   }

   if ((value(x) > 1.0) && (value(x) > value(a)))
   {
      return (1.0 - igamc(a, x));
   }
   // Compute  x**a * exp(-x) / gamma(a)
   ax = a * log(x) - x - lgam(a);

   if (value(ax) < -MAXLOG)
   {
      cerr << "igam UNDERFLOW " << endl;
      ad_exit(1);
   }

   ax = exp(ax);

   // power series 
   r = a;
   c = 1.0 / a;
   ans = 1.0 / a;

   do
   {
      r += 1.0;
      c *= x / r;
      ans += c;
      t = c / ans;
   }
   while( fabs(t) > MACHEP);

   return (ans * ax);
}

/**
 * \ingroup gammafunc
 * Incomplete gamma integral complement
 * \f$\Gamma(a,x) = 1-\gamma(a,x) = \frac{1}{\Gamma(a)}\int_{x}^{\infty}e^{-t}t^{a-1}dt \f$
 * \param aa \f$a, \, a>0\f$
 * \param xx \f$x\f$
 * \return complement of th incomplete gamma integral
 * 
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
dvariable igamc(const dvariable & aa, const dvariable & xx)
{
   using namespace Cephes;
   dvariable a = aa;
   dvariable x = xx;

   dvariable ans, ax, c, yc, r, t, y, z;
   dvariable pk, pkm1, pkm2, qk, qkm1, qkm2;

   if ((value(x) <= 0) || (value(a) <= 0))
   {
      dvariable tmp;
      tmp = 0.0;
      return (tmp);
   }

   if ((value(x) < 1.0) || (value(x) < value(a)))
   {
      return (1.0 - igam(a, x));
   }

   ax = a * log(x) - x - lgam(a);

   if (value(ax) < -MAXLOG)
   {
      cerr << "igamc UNDERFLOW " << endl;
      ad_exit(1);
   }

   ax = exp(ax);

   // continued fraction 
   y = 1.0 - a;
   z = x + y + 1.0;
   c = 0.0;
   pkm2 = 1.0;
   qkm2 = x;
   pkm1 = x + 1.0;
   qkm1 = z * x;
   ans = pkm1 / qkm1;

   do
   {
      c += 1.0;
      y += 1.0;
      z += 2.0;
      yc = y * c;
      pk = pkm1 * z - pkm2 * yc;
      qk = qkm1 * z - qkm2 * yc;
      if (value(qk) != 0)
      {
	 r = pk / qk;
	 t = fabs((ans - r) / r);
	 ans = r;
      } else
      {
	 t = 1.0;
      }
      pkm2 = pkm1;
      pkm1 = pk;
      qkm2 = qkm1;
      qkm1 = qk;
      if (fabs(value(pk)) > big)
      {
	 pkm2 *= biginv;
	 pkm1 *= biginv;
	 qkm2 *= biginv;
	 qkm1 *= biginv;
      }
   }
   while( fabs(t) > MACHEP );

   return (ans * ax);
}

/**
 * Log Gamma Function
 *
 * Used to find the Natural log of the gamma function.
 *
 * \param _x the argument
 *
 */  
dvariable lgam(_CONST prevariable& v1)
{
  dvariable tmp;
  static double phi = 0.5772156649015328606065121;


  if (value(v1)==1.0)
  {
    // value of lgam(1.0) is 0 and derivative is -phi 
    value(tmp)=0;
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(value(tmp)),
                                &(value(v1)),-phi );
  }
  else if (value(v1)==2.0)
  {
    // value of lgam(2.0) is 0 and derivative is 1.0-phi 
    value(tmp)=0;
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(value(tmp)),
                                &(value(v1)),1.0-phi );
  }
  else
  {
    // need to deal with this case
     tmp=private_lgam(v1);
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
df1_one_variable lgam(const df1_one_variable& _x)
{
   df1_one_variable&  x = (df1_one_variable&)_x;
   df1_one_variable x0;
   df1_one_variable x2;
   df1_one_variable xp;
   df1_one_variable gl;
   df1_one_variable gl0;
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
       df1_one_variable ret;
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

/**
 * Used by dvariable lgam.
 *
 */  
dvariable private_lgam(const dvariable& v)
{
  init_df1_one_variable va(v);

  dvariable tmp;
  df1_one_variable z;
  z=lgam(va);
  double dfz=*z.get_u_x();
  value(tmp)=value(z);

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
    &(value(tmp)) ,&(value(v)),dfz);

  return tmp;
}


/**
 * A wrapper for igam
 */
dvariable cumd_gamma(const dvariable& x, const dvariable& a)
{
   dvariable z=igam(a,x);
   return z;
}

/**
 * A wrapper for lgam
 */
dvariable gammln(_CONST dvariable& xx)
{
   dvariable z=lgam(xx);
   return z;
}

/**
 * A wrapper for lgam
 */
dvariable gammln(const prevariable& z)
{
   dvariable y=lgam(z);
   return y;
}
