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

double get_values(double x,double y,int print_switch);
dvariable igam(const dvariable & _a, const dvariable & _x);
dvariable igamc(const dvariable & _a, const dvariable & _x);
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
 * Gamma Function \f$\Gamma(x)\f$
 * \param xx1 \f$x\f$
 * \return The Gamma Function
 * 
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier 
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
static dvariable gamma(const dvariable & xx1)
{
   using namespace Cephes;
   dvariable x;
   x = xx1;
   dvariable MYBIG;
   MYBIG = 1.e+300;
   dvariable p, q, z, tmp;
   dvariable zero;
   zero = 0.0;
   int i;

   sgngam = 1;

/*#ifdef NANS
   if (isnan(value(x)))
      return (x);
#endif*/
/*#ifdef INFINITIES
#ifdef NANS
   if (value(x) == MYINF)
      return (x);
   if (value(x) == -MYINF)
   {
      x = NAN;
      return (x);
   }
#else
   if (!isfinite(value(x)))
      return (x);
#endif
#endif*/
   q = fabs(x);

   if (value(q) > 33.0)
   {
      if (value(x) < 0.0)
      {
	 p = floor(value(q));
	 if (value(p) == value(q))
	 {
/*#ifdef NANS
	  gamnan:
	    cerr << "gamma DOMAIN" << endl;
	    return (zero);
#else*/
	    goto goverf;
//#endif
	 }
	 i = value(p);

	 if ((i & 1) == 0)
	    sgngam = -1;
	 z = q - p;

	 if (value(z) > 0.5)
	 {
	    p += 1.0;
	    z = q - p;
	 }
	 z = q * sin(PI * z);

	 if (value(z) == 0.0)
	 {
/*#ifdef INFINITIES
	    tmp = sgngam * MYINF;
	    return (tmp);
#else*/
	  goverf:
	    //( "gamma", OVERFLOW );
	    return (sgngam * MYBIG);
	    //return( sgngam * MAXNUM);
//#endif
	 }
	 z = fabs(z);
	 z = PI / (z * stirf(q));
      } else
      {
	 z = stirf(x);
      }
      return (sgngam * z);
   }

   z = 1.0;
   while (value(x) >= 3.0)
   {
      x -= 1.0;
      z *= x;
   }

   while (value(x) < 0.0)
   {
      if (value(x) > -1.E-9)
	 goto SMALL;
      z /= x;
      x += 1.0;
   }

   while (value(x) < 2.0)
   {
      if (value(x) < 1.e-9)
	 goto SMALL;
      z /= x;
      x += 1.0;
   }

   if (value(x) == 2.0)
   {
      //return(z);
   }

   x -= 2.0;
   p = polevl(x, P, 6);
   q = polevl(x, Q, 7);
   z = z * p / q;
   return (z);

 SMALL:
   if (value(x) == 0.0)
   {
/*#ifdef INFINITIES
#ifdef NANS
      goto gamnan;
#else
      return (MYINF);
#endif
#else*/
      cerr << "gamma SING " << endl;
      return (MYBIG);
//#endif
   } else
      return (z / ((1.0 + 0.5772156649015329 * x) * x));
}

/**
 * \ingroup gammafunc
 * Log-gamma function \f$\ln(|\Gamma(x)|)\f$
 * \param xx \f$x\f$
 * \return natural log of the absolute
 *   value of the gamma function
 *
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
dvariable lgam(const dvariable & xx)
{
   using namespace Cephes;
   dvariable x = xx;
   dvariable p, q, u, w, z, tmp;
   int i;

   sgngam = 1;
/*#ifdef NANS
   if (isnan(value(x)))
      return (x);
#endif

#ifdef INFINITIES
   if (!isfinite(value(x)))
   {
      tmp = MYINF;
      return (tmp);
   }
#endif*/

   if (x < -34.0)
   {
      q = -x;
      w = lgam(q);		// note this modifies sgngam! 
      p = floor(value(q));
      if (p == q)
      {
       lgsing:
/*#ifdef INFINITIES
	 mtherr("lgam", SING);
	 tmp = MYINF;
	 return (tmp);
#else*/
	 goto loverf;
//#endif
      }
      i = value(p);

      if ((i & 1) == 0)
	 sgngam = -1;
      else
	 sgngam = 1;

      z = q - p;

      if (z > 0.5)
      {
	 p += 1.0;
	 z = p - q;
      }

      z = q * sin(PI * z);

      if (z == 0.0)
	 goto lgsing;

      //z = log(PI) - log( z ) - w;
      z = LOGPI - log(z) - w;
      return (z);
   }

   if (x < 13.0)
   {
      z = 1.0;
      p = 0.0;
      u = x;
      while (u >= 3.0)
      {
	 p -= 1.0;
	 u = x + p;
	 z *= u;
      }
      while (u < 2.0)
      {
	 if (u == 0.0)
	    goto lgsing;
	 z /= u;
	 p += 1.0;
	 u = x + p;
      }
      if (z < 0.0)
      {
	 sgngam = -1;
	 z = -z;
      } else
	 sgngam = 1;

      if (u == 2.0)
      {
	 z = x;
	 z = gamma(z);
	 return (log(z));
      }
      p -= 2.0;
      x = x + p;
      p = x * polevl(x, B, 5) / p1evl(x, C, 6);
      return (log(z) + p);
   }

   if (x > MAXLGM)
   {
/*#ifdef INFINITIES
      tmp = sgngam * MYINF;
      return (tmp);
#else*/
    loverf:
      mtherr("lgam", OVERFLOW);
      dvariable tmp;
      tmp = sgngam * MAXNUM;
      return tmp;
//#endif
   }

   q = (x - 0.5) * log(x) - x + LS2PI;
   if (x > 1.0e8)
      return (q);

   p = 1.0 / (x * x);
   if (x >= 1000.0)
      q += ((7.9365079365079365079365e-4 * p
	     - 2.7777777777777777777778e-3) * p
	    + 0.0833333333333333333333) / x;
   else
      q += polevl(p, A, 4) / x;
   return (q);
}

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
