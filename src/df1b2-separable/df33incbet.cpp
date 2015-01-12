/*
 * $Id:  $
 *
 * Based on code from Cephes C and C++ language special functions math library
 * and adapeted for automatic differentiation.
 * http://www.moshier.net/#Cephes or
 * http://www.netlib.org/cephes/
 *
 * Author: David Fournier
 * Copyright (c) 2009-2011 ADMB Foundation
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
#include <df1b2fun.h>
#include <df33fun.h>

static int mtherr(char *s, int n);
static df3_three_variable igam(const df3_three_variable & a,
			       const df3_three_variable & x);

static double MAXLOG = 200;
static double MINLOG = -200;
static double big = 4.503599627370496e15;
static double biginv = 2.22044604925031308085e-16;
static double MACHEP = 2.22045e-16;
/*							gamma.c
 *
 *	Gamma function
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, gamma();
 * extern int sgngam;
 *
 * y = gamma( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns gamma function of the argument.  The result is
 * correctly signed, and the sign (+1 or -1) is also
 * returned in a global (extern) variable named sgngam.
 * This variable is also filled in by the logarithmic gamma
 * function lgam().
 *
 * Arguments |x| <= 34 are reduced by recurrence and the function
 * approximated by a rational function of degree 6/7 in the
 * interval (2,3).  Large arguments are handled by Stirling's
 * formula. Large negative arguments are made positive using
 * a reflection formula.  
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC      -34, 34      10000       1.3e-16     2.5e-17
 *    IEEE    -170,-33      20000       2.3e-15     3.3e-16
 *    IEEE     -33,  33     20000       9.4e-16     2.2e-16
 *    IEEE      33, 171.6   20000       2.3e-15     3.2e-16
 *
 * Error for arguments outside the test range will be larger
 * owing to error amplification by the exponential function.
 *
 */
/*							lgam()
 *
 *	Natural logarithm of gamma function
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, lgam();
 * extern int sgngam;
 *
 * y = lgam( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the base e (2.718...) logarithm of the absolute
 * value of the gamma function of the argument.
 * The sign (+1 or -1) of the gamma function is returned in a
 * global (extern) variable named sgngam.
 *
 * For arguments greater than 13, the logarithm of the gamma
 * function is approximated by the logarithmic version of
 * Stirling's formula using a polynomial approximation of
 * degree 4. Arguments between -33 and +33 are reduced by
 * recurrence to the interval [2,3] of a rational approximation.
 * The cosecant reflection formula is employed for arguments
 * less than -33.
 *
 * Arguments greater than MAXLGM return MAXNUM and an error
 * message.  MAXLGM = 2.035093e36 for DEC
 * arithmetic or 2.556348e305 for IEEE arithmetic.
 *
 *
 *
 * ACCURACY:
 *
 *
 * arithmetic      domain        # trials     peak         rms
 *    DEC     0, 3                  7000     5.2e-17     1.3e-17
 *    DEC     2.718, 2.035e36       5000     3.9e-17     9.9e-18
 *    IEEE    0, 3                 28000     5.4e-16     1.1e-16
 *    IEEE    2.718, 2.556e305     40000     3.5e-16     8.3e-17
 * The error criterion was relative when the function magnitude
 * was greater than one but absolute when it was less than one.
 *
 * The following test used the relative error criterion, though
 * at certain points the relative error could be much higher than
 * indicated.
 *    IEEE    -200, -4             10000     4.8e-16     1.3e-16
 *
 */

/*							gamma.c	*/
/*	gamma function	*/

static double P[] = {
   1.60119522476751861407E-4,
   1.19135147006586384913E-3,
   1.04213797561761569935E-2,
   4.76367800457137231464E-2,
   2.07448227648435975150E-1,
   4.94214826801497100753E-1,
   9.99999999999999996796E-1
};

static double Q[] = {
   -2.31581873324120129819E-5,
   5.39605580493303397842E-4,
   -4.45641913851797240494E-3,
   1.18139785222060435552E-2,
   3.58236398605498653373E-2,
   -2.34591795718243348568E-1,
   7.14304917030273074085E-2,
   1.00000000000000000320E0
};
static double MAXGAM = 171.624376956302725;
static double LOGPI = 1.14472988584940017414;
static double PI = 3.14159265358979323844;

/**
 * Stirling's formula for the gamma function.
 */
static double STIR[5] = {
   7.87311395793093628397E-4,
   -2.29549961613378126380E-4,
   -2.68132617805781232825E-3,
   3.47222221605458667310E-3,
   8.33333333333482257126E-2,
};
static double MAXSTIR = 143.01608;
static double SQTPI = 2.50662827463100050242E0;

static int sgngam = 0;
static double MAXNUM = 1.7976931348623158E+308;

static double polevl(double, void *, int);
static df3_three_variable polevl(const df3_three_variable &, void *, int);
static double p1evl(double, void *, int);
static df3_three_variable p1evl(const df3_three_variable &, void *, int);

const double MYINF = 1.7976931348623158E+308;

/**
 * Gamma function computed by Stirling's formula.
 * \param _x, \f$33 \le x \le 172\f$
 */
static df3_three_variable stirf(const df3_three_variable & _x)
{
   ADUNCONST(df3_three_variable, x) df3_three_variable y, w, v;

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
 * Description not yet available.
 * \param
 */
static df3_three_variable gamma(const df3_three_variable & xx1)
{
   df3_three_variable x;
   x = xx1;
   df3_three_variable MYBIG;
   MYBIG = 1.e+300;
   df3_three_variable p, q, z;
   df3_three_variable zero;
   zero = 0.0;
   int i;

   sgngam = 1;
#ifdef NANS
   if (isnan(x))
      return (x);
#endif
#ifdef INFINITIES
#ifdef NANS
   if (value(x) == MYINF)
      return (x);
   if (value(x) == -MYINF)
      return (NAN);
#else
   if (!isfinite(value(x)))
      return (x);
#endif
#endif
   q = fabs(x);

   if (value(q) > 33.0)
   {
      if (value(x) < 0.0)
      {
	 p = floor(value(q));
	 if (value(p) == value(q))
	 {
#ifdef NANS
	  gamnan:
	    cerr << "gamma DOMAIN" << endl;
	    return (zero);
#else
	    goto goverf;
#endif
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
#ifdef INFINITIES
	    return (sgngam * MYINF);
#else
	  goverf:
	    mtherr("gamma", OVERFLOW);
	    return (sgngam * MYBIG);
	    //return( sgngam * MAXNUM);
#endif
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
      return (z);

   x -= 2.0;
   p = polevl(x, P, 6);
   q = polevl(x, Q, 7);
   return (z * p / q);

 SMALL:
   if (value(x) == 0.0)
   {
#ifdef INFINITIES
#ifdef NANS
      goto gamnan;
#else
      return (MYINF);
#endif
#else
      cerr << "gamma SING " << endl;
      return (MYBIG);
#endif
   } else
      return (z / ((1.0 + 0.5772156649015329 * x) * x));
}



/* A[]: Stirling's formula expansion of log gamma
 * B[], C[]: log gamma function between 2 and 3
 */
static double A[] = {
   8.11614167470508450300E-4,
   -5.95061904284301438324E-4,
   7.93650340457716943945E-4,
   -2.77777777730099687205E-3,
   8.33333333333331927722E-2
};

static double B[] = {
   -1.37825152569120859100E3,
   -3.88016315134637840924E4,
   -3.31612992738871184744E5,
   -1.16237097492762307383E6,
   -1.72173700820839662146E6,
   -8.53555664245765465627E5
};

static double C[] = {
/* 1.00000000000000000000E0, */
   -3.51815701436523470549E2,
   -1.70642106651881159223E4,
   -2.20528590553854454839E5,
   -1.13933444367982507207E6,
   -2.53252307177582951285E6,
   -2.01889141433532773231E6
};

/* log( sqrt( 2*pi ) ) */
static double LS2PI = 0.91893853320467274178;
static double MAXLGM = 2.556348e305;

/**
 * Description not yet available.
 * \param
 */
int operator <(const df3_three_variable & x, double n)
{
   return value(x) < n;
}

/**
 * Description not yet available.
 * \param
 */
int operator >(const df3_three_variable & x, double n)
{
   return value(x) > n;
}

/**
 * Description not yet available.
 * \param
 */
int operator >=(const df3_three_variable & x, double n)
{
   return value(x) >= n;
}

/**
 * Description not yet available.
 * \param
 */
int operator ==(const df3_three_variable & x, const df3_three_variable & n)
{
   return value(x) == value(n);
}

/**
 * Description not yet available.
 * \param
 */
int operator ==(const df3_three_variable & x, double n)
{
   return value(x) == n;
}

/**
 * Description not yet available.
 * \param
 */
int operator ==(double x, const df3_three_variable & n)
{
   return x == value(n);
}

/**
 * Description not yet available.
 * \param
 */
int operator <(const df3_three_variable & x, const df3_three_variable & n)
{
   return value(x) < value(n);
}

/**
 * Description not yet available.
 * \param
 */
int operator >(const df3_three_variable & x, const df3_three_variable & n)
{
   return value(x) > value(n);
}

/**
 * Description not yet available.
 * \param
 */
df3_three_variable lgam(const df3_three_variable & _x)
{
   df3_three_variable x, p, q, u, w, z, p1;
   x = _x;
   int i;

   sgngam = 1;
#ifdef NANS
   if (isnan(x))
      return (x);
#endif

#ifdef INFINITIES
   if (!isfinite(x))
      return (MYINF);
#endif

   if (x < -34.0)
   {
      q = -x;
      w = lgam(q);		/* note this modifies sgngam! */
      p = floor(value(q));
      if (p == q)
      {
       lgsing:
#ifdef INFINITIES
	 mtherr("lgam", SING);
	 return (MYINF);
#else
	 goto loverf;
#endif
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
/*	z = log(PI) - log( z ) - w;*/
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
	 return (log(z));
      p -= 2.0;
      x = x + p;
      p = x * polevl(x, B, 5) / p1evl(x, C, 6);
      return (log(z) + p);
   }

   if (x > MAXLGM)
   {
#ifdef INFINITIES
      return (sgngam * MYINF);
#else
    loverf:
      mtherr("lgam", OVERFLOW);
      df3_three_variable tmp;
      tmp = sgngam * MAXNUM;
      return tmp;
#endif
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

/*							polevl.c
 *							p1evl.c
 *
 *	Evaluate polynomial
 *
 *
 *
 * SYNOPSIS:
 *
 * int N;
 * double x, y, coef[N+1], polevl[];
 *
 * y = polevl( x, coef, N );
 *
 *
 *
 * DESCRIPTION:
 *
 * Evaluates polynomial of degree N:
 *
 *                     2          N
 * y  =  C  + C x + C x  +...+ C x
 *        0    1     2          N
 *
 * Coefficients are stored in reverse order:
 *
 * coef[0] = C  , ..., coef[N] = C  .
 *            N                   0
 *
 *  The function p1evl() assumes that coef[N] = 1.0 and is
 * omitted from the array.  Its calling arguments are
 * otherwise the same as polevl().
 *
 *
 * SPEED:
 *
 * In the interest of speed, there are no checks for out
 * of bounds arithmetic.  This routine is used by most of
 * the functions in the library.  Depending on available
 * equipment features, the user may wish to rewrite the
 * program in microcode or assembly language.
 *
 */

/**
 * Description not yet available.
 * \param
 */
static df3_three_variable polevl(const df3_three_variable & x, void *_coef,
				 int N)
{
   double *coef = (double *) (_coef);
   df3_three_variable ans;
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


/*							p1evl()	*/
/*                                          N
 * Evaluate polynomial when coefficient of x  is 1.0.
 * Otherwise same as polevl.
 */

/*
double p1evl(double x, void *_coef, int N)
{
   double *coef = (double *) (_coef);
   double ans;
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
*/

/**
 * Description not yet available.
 * \param
 */
df3_three_variable p1evl(const df3_three_variable & x, void *_coef, int N)
{
   double *coef = (double *) (_coef);
   df3_three_variable ans;
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

/**
 * Description not yet available.
 * \param
 */
static int mtherr(char *s, int n)
{
   cerr << "Error code " << n << "in " << *s << endl;
   ad_exit(1);
   return 0;
}

df3_three_variable incbet(const df3_three_variable & _aa,
			  const df3_three_variable & _bb,
			  const df3_three_variable & _xx);

/**
 * This is the wrapper to call the main inbet function.
 * \param
 */
df1b2variable incbet(const df1b2variable & _a, const df1b2variable & _b,
		     const df1b2variable & _x)
{
   ADUNCONST(df1b2variable, a)
   ADUNCONST(df1b2variable, b) ADUNCONST(df1b2variable, x)
   // these three lines will automatically put in the
   // derivatvie glue
   init_df3_three_variable vx(x);
   init_df3_three_variable va(a);
   init_df3_three_variable vb(b);
   df3_three_variable vy;
   vy = incbet(va, vb, vx);
   df1b2variable z;
   z = vy;
   return z;
}


/*							igam.c
 *
 *	Incomplete gamma integral
 *
 *
 *
 * SYNOPSIS:
 *
 * double a, x, y, igam();
 *
 * y = igam( a, x );
 *
 * DESCRIPTION:
 *
 * The function is defined by
 *
 *                           x
 *                            -
 *                   1       | |  -t  a-1
 *  igam(a,x)  =   -----     |   e   t   dt.
 *                  -      | |
 *                 | (a)    -
 *                           0
 *
 *
 * In this implementation both arguments must be positive.
 * The integral is evaluated by either a power series or
 * continued fraction expansion, depending on the relative
 * values of a and x.
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      0,30       200000       3.6e-14     2.9e-15
 *    IEEE      0,100      300000       9.9e-14     1.5e-14
 */
/*							igamc()
 *
 *	Complemented incomplete gamma integral
 *
 *
 *
 * SYNOPSIS:
 *
 * double a, x, y, igamc();
 *
 * y = igamc( a, x );
 *
 * DESCRIPTION:
 *
 * The function is defined by
 *
 *
 *  igamc(a,x)   =   1 - igam(a,x)
 *
 *                            inf.
 *                              -
 *                     1       | |  -t  a-1
 *               =   -----     |   e   t   dt.
 *                    -      | |
 *                   | (a)    -
 *                             x
 *
 *
 * In this implementation both arguments must be positive.
 * The integral is evaluated by either a power series or
 * continued fraction expansion, depending on the relative
 * values of a and x.
 *
 * ACCURACY:
 *
 * Tested at random a, x.
 *                a         x                      Relative error:
 * arithmetic   domain   domain     # trials      peak         rms
 *    IEEE     0.5,100   0,100      200000       1.9e-14     1.7e-15
 *    IEEE     0.01,0.5  0,100      200000       1.4e-13     1.6e-15
 */

static df3_three_variable igam(const df3_three_variable & a,
			       const df3_three_variable & x);

/**
 * Description not yet available.
 * \param
 */
df3_three_variable igamc(const df3_three_variable & _a,
			 const df3_three_variable & _x)
{
   ADUNCONST(df3_three_variable, a)
      ADUNCONST(df3_three_variable, x)
      df3_three_variable ans, ax, c, yc, r, t, y, z;
   df3_three_variable pk, pkm1, pkm2, qk, qkm1, qkm2;

   if ((value(x) <= 0) || (value(a) <= 0))
   {
      df3_three_variable tmp;
      tmp = 0.0;
      return (tmp);
   }

   if ((value(x) < 1.0) || (value(x) < value(a)))
      return (1.0 - igam(a, x));

   ax = a * log(x) - x - lgam(a);
   if (value(ax) < -MAXLOG)
   {
      cerr << "igamc UNDERFLOW " << endl;
      ad_exit(1);
   }
   ax = exp(ax);

   /* continued fraction */
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
	 t = 1.0;
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
   while (t > MACHEP);

   return (ans * ax);
}

  // 
  // 
  // 
  // /* left tail of incomplete gamma function:
  //  *
  //  *          inf.      k
  //  *   a  -x   -       x
  //  *  x  e     >   ----------
  //  *           -     -
  //  *          k=0   | (a+k+1)
  //  *
  //  */
  // 
/**
 * Description not yet available.
 * \param
 */
df3_three_variable igam(const df3_three_variable & _a,
			const df3_three_variable & _x)
{
   ADUNCONST(df3_three_variable, a)
      ADUNCONST(df3_three_variable, x) df3_three_variable ans, ax, c, r;

   if ((value(x) <= 0) || (value(a) <= 0))
   {
      df3_three_variable tmp;
      tmp = 0.0;
      return (tmp);
   }

   if ((value(x) > 1.0) && (value(x) > value(a)))
      return (1.0 - igamc(a, x));

   /* Compute  x**a * exp(-x) / gamma(a)  */
   ax = a * log(x) - x - lgam(a);
   if (value(ax) < -MAXLOG)
   {
      cerr << "igam UNDERFLOW " << endl;
      ad_exit(1);
   }
   ax = exp(ax);

   /* power series */
   r = a;
   c = 1.0;
   ans = 1.0;

   do
   {
      r += 1.0;
      c *= x / r;
      ans += c;
   }
   while (c / ans > MACHEP);

   return (ans * ax / a);
}



 // /*                                                  incbet.c
 //  *
 //  *  Incomplete beta integral
 //  *
 //  *
 //  * SYNOPSIS:
 //  *
 //  * double a, b, x, y, incbet();
 //  *
 //  * y = incbet( a, b, x );
 //  *
 //  *
 //  * DESCRIPTION:
 //  *
 //  * Returns incomplete beta integral of the arguments, evaluated
 //  * from zero to x.  The function is defined as
 //  *
 //  *                  x
 //  *     -            -
 //  *    | (a+b)      | |  a-1     b-1
 //  *  -----------    |   t   (1-t)   dt.
 //  *   -     -     | |
 //  *  | (a) | (b)   -
 //  *                 0
 //  *
 //  * The domain of definition is 0 <= x <= 1.  In this
 //  * implementation a and b are restricted to positive values.
 //  * The integral from x to 1 may be obtained by the symmetry
 //  * relation
 //  *
 //  *    1 - incbet( a, b, x )  =  incbet( b, a, 1-x ).
 //  *
 //  * The integral is evaluated by a continued fraction expansion
 //  * or, when b*x is small, by a power series.
 //  *
 //  * ACCURACY:
 //  *
 //  * Tested at uniformly distributed random points (a,b,x) with a and b
 //  * in "domain" and x between 0 and 1.
 //  *                                        Relative error
 //  * arithmetic   domain     # trials      peak         rms
 //  *    IEEE      0,5         10000       6.9e-15     4.5e-16
 //  *    IEEE      0,85       250000       2.2e-13     1.7e-14
 //  *    IEEE      0,1000      30000       5.3e-12     6.3e-13
 //  *    IEEE      0,10000    250000       9.3e-11     7.1e-12
 //  *    IEEE      0,100000    10000       8.7e-10     4.8e-11
 //  * Outputs smaller than the IEEE gradual underflow threshold
 //  * were excluded from these statistics.
 //  *
 //  * ERROR MESSAGES:
 //  *   message         condition      value returned
 //  * incbet domain      x<0, x>1          0.0
 //  * incbet underflow                     0.0
 //  */
 // 
 // 
 // /*
 // Cephes Math Library, Release 2.8:  June, 2000
 // Copyright 1984, 1995, 2000 by Stephen L. Moshier
 // */

static df3_three_variable incbcf(const df3_three_variable & _a,
				 const df3_three_variable & _b,
				 const df3_three_variable & _x);
static df3_three_variable pseries(const df3_three_variable & _a,
				  const df3_three_variable & _b,
				  const df3_three_variable & _x);
static df3_three_variable incbd(const df3_three_variable & _a,
				const df3_three_variable & _b,
				const df3_three_variable & _x);

/**
 * Description not yet available.
 * \param
 */
df3_three_variable incbet(const df3_three_variable & _aa,
				 const df3_three_variable & _bb,
				 const df3_three_variable & _xx)
{

   df3_three_variable aa;
   df3_three_variable bb;
   df3_three_variable xx;
   aa = _aa;
   bb = _bb;
   xx = _xx;

   df3_three_variable a, b, t, x, xc, w, y;

   int flag;
   df3_three_variable one;
   df3_three_variable zero;
   one = 1.0;
   zero = 0.0;

   if (value(aa) <= 0.0 || value(bb) <= 0.0)
      goto domerr;

   if ((value(xx) <= 0.0) || (value(xx) >= 1.0))
   {
      if (value(xx) == 0.0)
	 return (zero);
      if (value(xx) == 1.0)
	 return (one);
    domerr:
      cerr << "incbet DOMAIN " << endl;

      return (zero);
   }

   flag = 0;
   if (value(bb * xx) <= 1.0 && value(xx) <= 0.95)
   {
      t = pseries(aa, bb, xx);
      goto done;
   }

   w = 1.0 - xx;

   /* Reverse a and b if x is greater than the mean. */
   if (value(xx) > (value(aa) / value(aa + bb)))
   {
      flag = 1;
      a = bb;
      b = aa;
      xc = xx;
      x = w;
   } else
   {
      a = aa;
      b = bb;
      xc = w;
      x = xx;
   }

   if (flag == 1 && value((b * x)) <= 1.0 && value(x) <= 0.95)
   {
      t = pseries(a, b, x);
      goto done;
   }

   /* Choose expansion for better convergence. */
   y = x * (a + b - 2.0) - (a - 1.0);
   if (value(y) < 0.0)
      w = incbcf(a, b, x);
   else
      w = incbd(a, b, x) / xc;

   /* Multiply w by the factor
      a      b   _             _     _
      x  (1-x)   | (a+b) / ( a | (a) | (b) ) .   */

   y = a * log(x);
   t = b * log(xc);
   if (value((a + b)) < MAXGAM && fabs(value(y)) < MAXLOG
       && fabs(value(t)) < MAXLOG)
   {
      t = pow(xc, b);
      t *= pow(x, a);
      t /= a;
      t *= w;
      t *= gamma(a + b) / (gamma(a) * gamma(b));
      goto done;
   }
   /* Resort to logarithms.  */
   y += t + lgam(a + b) - lgam(a) - lgam(b);
   y += log(w / a);
   if (value(y) < MINLOG)
      t = 0.0;
   else
      t = exp(y);

 done:

   if (flag == 1)
   {
      if (value(t) <= MACHEP)
	 t = 1.0 - MACHEP;
      else
	 t = 1.0 - t;
   }
   return (t);
}

/**
 * Continued fraction expansion number 1
 * for incomplete beta integral
 * \param
 */
static df3_three_variable incbcf(const df3_three_variable & _a,
				 const df3_three_variable & _b,
				 const df3_three_variable & _x)
{
   ADUNCONST(df3_three_variable, a)
      ADUNCONST(df3_three_variable, b)
      ADUNCONST(df3_three_variable, x)
      df3_three_variable xk, pk, pkm1, pkm2, qk, qkm1, qkm2;
   df3_three_variable k1, k2, k3, k4, k5, k6, k7, k8;
   df3_three_variable r, t, ans, thresh;
   int n;

   k1 = a;
   k2 = a + b;
   k3 = a;
   k4 = a + 1.0;
   k5 = 1.0;
   k6 = b - 1.0;
   k7 = k4;
   k8 = a + 2.0;

   pkm2 = 0.0;
   qkm2 = 1.0;
   pkm1 = 1.0;
   qkm1 = 1.0;
   ans = 1.0;
   r = 1.0;
   n = 0;
   thresh = 3.0 * MACHEP;
   do
   {

      xk = -(x * k1 * k2) / (k3 * k4);
      pk = pkm1 + pkm2 * xk;
      qk = qkm1 + qkm2 * xk;
      pkm2 = pkm1;
      pkm1 = pk;
      qkm2 = qkm1;
      qkm1 = qk;

      xk = (x * k5 * k6) / (k7 * k8);
      pk = pkm1 + pkm2 * xk;
      qk = qkm1 + qkm2 * xk;
      pkm2 = pkm1;
      pkm1 = pk;
      qkm2 = qkm1;
      qkm1 = qk;

      if (value(qk) != 0)
	 r = pk / qk;
      if (value(r) != 0)
      {
	 t = fabs((ans - r) / r);
	 ans = r;
      } else
	 t = 1.0;

      if (value(t) < value(thresh))
	 goto cdone;

      k1 += 1.0;
      k2 += 1.0;
      k3 += 2.0;
      k4 += 2.0;
      k5 += 1.0;
      k6 -= 1.0;
      k7 += 2.0;
      k8 += 2.0;

      if ((value(fabs(qk)) + value(fabs(pk))) > big)
      {
	 pkm2 *= biginv;
	 pkm1 *= biginv;
	 qkm2 *= biginv;
	 qkm1 *= biginv;
      }
      if ((value(fabs(qk)) < biginv) || (value(fabs(pk)) < biginv))
      {
	 pkm2 *= big;
	 pkm1 *= big;
	 qkm2 *= big;
	 qkm1 *= big;
      }
   }
   while (++n < 300);

 cdone:
   return (ans);
}

/**
 * Continued fraction expansion number 2
 * for incomplete beta integral
 * \param
 */
static df3_three_variable incbd(const df3_three_variable & _a,
				const df3_three_variable & _b,
				const df3_three_variable & _x)
{
   ADUNCONST(df3_three_variable, a)
      ADUNCONST(df3_three_variable, b) ADUNCONST(df3_three_variable, x)
      //df3_three_variable s, t, u, v, n, t1, z, ai;
   df3_three_variable xk, pk, pkm1, pkm2, qk, qkm1, qkm2;
   df3_three_variable k1, k2, k3, k4, k5, k6, k7, k8;
   df3_three_variable r, t, ans, z, thresh;
   int n;

   k1 = a;
   k2 = b - 1.0;
   k3 = a;
   k4 = a + 1.0;
   k5 = 1.0;
   k6 = a + b;
   k7 = a + 1.0;;
   k8 = a + 2.0;

   pkm2 = 0.0;
   qkm2 = 1.0;
   pkm1 = 1.0;
   qkm1 = 1.0;
   z = x / (1.0 - x);
   ans = 1.0;
   r = 1.0;
   n = 0;
   thresh = 3.0 * MACHEP;
   do
   {

      xk = -(z * k1 * k2) / (k3 * k4);
      pk = pkm1 + pkm2 * xk;
      qk = qkm1 + qkm2 * xk;
      pkm2 = pkm1;
      pkm1 = pk;
      qkm2 = qkm1;
      qkm1 = qk;

      xk = (z * k5 * k6) / (k7 * k8);
      pk = pkm1 + pkm2 * xk;
      qk = qkm1 + qkm2 * xk;
      pkm2 = pkm1;
      pkm1 = pk;
      qkm2 = qkm1;
      qkm1 = qk;

      if (value(qk) != 0)
	 r = pk / qk;
      if (value(r) != 0)
      {
	 t = fabs((ans - r) / r);
	 ans = r;
      } else
	 t = 1.0;

      if (value(t) < value(thresh))
	 goto cdone;

      k1 += 1.0;
      k2 -= 1.0;
      k3 += 2.0;
      k4 += 2.0;
      k5 += 1.0;
      k6 += 1.0;
      k7 += 2.0;
      k8 += 2.0;

      if ((value(fabs(qk)) + value(fabs(pk))) > big)
      {
	 pkm2 *= biginv;
	 pkm1 *= biginv;
	 qkm2 *= biginv;
	 qkm1 *= biginv;
      }
      if ((value(fabs(qk)) < biginv) || (value(fabs(pk)) < biginv))
      {
	 pkm2 *= big;
	 pkm1 *= big;
	 qkm2 *= big;
	 qkm1 *= big;
      }
   }
   while (++n < 300);
 cdone:
   return (ans);
}

/**
 * Power series for incomplete beta integral.
 * Use when b*x is small and x not too close to 1.
 * \param
 */
df3_three_variable pseries(const df3_three_variable & _a,
			   const df3_three_variable & _b,
			   const df3_three_variable & _x)
{
   df3_three_variable a;
   df3_three_variable b;
   df3_three_variable x;
   a = _a;
   b = _b;
   x = _x;
   df3_three_variable s, t, u, v, n, t1, z, ai;

   ai = 1.0 / a;
   u = (1.0 - b) * x;
   v = u / (a + 1.0);
   t1 = v;
   t = u;
   n = 2.0;
   s = 0.0;
   z = MACHEP * ai;
   while (value(fabs(v)) > value(z))
   {
      u = (n - b) * x / n;
      t *= u;
      v = t / (a + n);
      s += v;
      n += 1.0;
   }
   s += t1;
   s += ai;

   u = a * log(x);
   if (value((a + b)) < MAXGAM && value(fabs(u)) < MAXLOG)
   {
      gamma(a + b);
      gamma(a);
      gamma(b);
      gamma(a) * gamma(b);
      t = gamma(a + b) / (gamma(a) * gamma(b));
      s = s * t * pow(x, a);
   } else
   {
      t = lgam(a + b) - lgam(a) - lgam(b) + u + log(s);
      if (value(t) < MINLOG)
	 s = 0.0;
      else
	 s = exp(t);
   }
   return (s);
}

/**
 * Description not yet available.
 * \param
 */
static double get_values(double a, double b, double x)
{
   df3_three_variable va, vb, vx;
   va.initialize();
   vb.initialize();
   vx.initialize();
   va = a;
   vb = b;
   vx = x;
   *va.get_u_x() = 1.0;
   *vb.get_u_y() = 1.0;
   *vx.get_u_z() = 1.0;
   df3_three_variable vy = incbet(va, vb, vx);
   return *vy.get_u();
}

/**
 * Description not yet available.
 * \param
 */
static df3_three_variable df3_get_values(double a, double b, double x)
{
   df3_three_variable va, vb, vx;
   va.initialize();
   vb.initialize();
   vx.initialize();
   va = a;
   vb = b;
   vx = x;
   *va.get_u_x() = 1.0;
   *vb.get_u_y() = 1.0;
   *vx.get_u_z() = 1.0;
   df3_three_variable vy = incbet(va, vb, vx);
   return vy;
}
