/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>
//#include "mconf.h"
//#define ITMAX 100
//#define EPS 1.0e-9
//#define FPMIN 1.0e-30
//static void gcf(double& gammcf,double a,double x,double &gln);
//static void gser(double& gamser,double a,double x,double& gln);

namespace Cephes
{
   extern const double A[];
   extern const double B[];
   extern const double C[];
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

   double polevl(double x, void *_coef, int N);
   double p1evl(double x, void *_coef, int N);

/*
Cephes Math Library Release 2.1:  December, 1988
Copyright 1984, 1987, 1988 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

   double polevl(double x, void *_coef, int N)
   {
      double *coef = (double *) (_coef);
      double ans;
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
/**
 * Evaluate polynomial when coefficient of \f$x^N\f$  is \f$1.0\f$.
 * Otherwise same as polevl.
 * Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */


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


}				// Cephes namespace



static double igam(const double &a, const double &x);
static double igamc(const double &a, const double &x);
int mtherr(char *s, int n)
{				/*ad_exit(1); */
   return 0;
}

dvariable gamma_deviate(const prevariable & _x, const prevariable & _a)
{
   prevariable & x = (prevariable &) (_x);
   prevariable & a = (prevariable &) (_a);

   dvariable y = cumd_norm(x);

   y = .9999 * y + .00005;

   dvariable z = inv_cumd_gamma(y, a);

   return z;
}



/**
 * \f$y = \ln(\Gamma(x))\f$.
 * Returns the base \f$e\f$ logarithm of the absolute
 * value of the gamma function of the argument.
 * The sign (+1 or -1) of the gamma function is returned in a
 * global (extern) variable named sgngam.
 * Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
static double lgam(double x)
{
   using namespace Cephes;
   double p, q, u, w, z;
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
      w = lgam(q);		// note this modifies sgngam!
      p = floor(q);
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
      i = p;
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
//      z = log(PI) - log( z ) - w;
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

	 return (log(z));

      }
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
      return (sgngam * MAXNUM);
#endif
   }

   q = (x - 0.5) * log(x) - x + LS2PI;
   if (x > 1.0e8)
   {
      return (q);
   }
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
 * Complemented incomplete gamma integral.
 * The function is defined by:
 * igamc(a,x) = \f$1-\f$ igam(a,x) \f$ = \frac{1}{\Gamma(a)}\int_{x}^{\infty}e^{-t}t^{a-1}dt \f$.
 * Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
static double igamc(const double &a, const double &x)
{
   using namespace Cephes;

   double ans, ax, c, yc, r, t, y, z;
   double pk, pkm1, pkm2, qk, qkm1, qkm2;

   if ((x <= 0) || (a <= 0))
   {
      double tmp;
      tmp = 0.0;
      return (tmp);
   }

   if ((x < 1.0) || (x < a))
   {
      return (1.0 - igam(a, x));
   }

   ax = a * log(x) - x - lgam(a);
   if (ax < -MAXLOG)
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
      if (qk != 0)
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
      if (fabs(pk) > big)
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

/**
 * Incomplete gamma integral.
 * The function is defined by
 * igam(a,x)\f$ = \frac{1}{\Gamma(a)}\int_{0}^{x}e^{-t}t^{a-1}dt \f$.
 * Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
static double igam(const double &a, const double &x)
{
   using namespace Cephes;

   double ans, ax, c, r;

   if ((x <= 0) || (a <= 0))
   {
      double tmp;
      tmp = 0.0;
      return (tmp);
   }

   if ((x > 1.0) && (x > a))
      return (1.0 - igamc(a, x));

   // Compute  x**a * exp(-x) / gamma(a)
   ax = a * log(x) - x - lgam(a);
   if (ax < -MAXLOG)
   {
      cerr << "igam UNDERFLOW " << endl;
      ad_exit(1);
   }
   ax = exp(ax);

   // power series
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


static double gammp(double a, double x)
{
   //return igamc(a,x);
   return igam(a, x);
}

/*
static double gammp(double a,double x)
{
  double gamser,gammcf,gln;

  if (x < 0.0 || a <= 0.0) 
    cerr << "Invalid arguments in routine gammp" << endl;
  if (x < (a+1.0)) {
    gser(gamser,a,x,gln);
    return gamser;
  } else {
    gcf(gammcf,a,x,gln);
    return 1.0-gammcf;
  }
}
*/

/* Incomplete gamma function.
    Continued fraction approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
/*
static void gcf(double& gammcf,double a,double x,double &gln)
{
  int i;
  double an,b,c,d,del,h;

  gln=gammln(a);
  b=x+1.0-a;
  c=1.0/FPMIN;
  d=1.0/b;
  h=d;
  for (i=1;i<=ITMAX;i++) {
    an = -i*(i-a);
    b += 2.0;
    d=an*d+b;
    if (fabs(d) < FPMIN) d=FPMIN;
    c=b+an/c;
    if (fabs(c) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(del-1.0) < EPS) break;
  }
  if (i > ITMAX) 
    cerr << "a too large, ITMAX too small in gcf" << endl;
  gammcf=exp(-x+a*log(x)-(gln))*h;
}
*/
/* Incomplete gamma function.
    Series approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
/*
static void gser(double& gamser,double a,double x,double& gln)
{
  int n;
  double sum,del,ap;

  gln=gammln(a);
  if (x <= 0.0) {
    if (x < 0.0) 
      cerr << "x less than 0 in routine gser" << endl;
    gamser=0.0;
    return;
  } else {
    ap=a;
    del=sum=1.0/a;
    for (n=1;n<=ITMAX;n++) {
      ++ap;
      del *= x/ap;
      sum += del;
      if (fabs(del) < fabs(sum)*EPS) {
        gamser=sum*exp(-x+a*log(x)-(gln));
        return;
      }
    }
    cerr << "a too large, ITMAX too small in routine gser" << endl;
    return;
  }
}
*/

static double get_initial_u(double a, double y);

static double Sn(double x, double a);

#if defined(USE_LAPLACE)
#include <df1b2fun.h>
df3_two_variable cumd_gamma(const df3_two_variable & x,
			    const df3_two_variable & a);


dvariable inv_cumd_gamma(const prevariable & _y, const prevariable & _a)
{
   double a = value(_a);
   double y = value(_y);

   if (a < 0.05)
   {
      cerr << "a must be > 0.1" << endl;
      ad_exit(1);
   }
   double u = get_initial_u(a, y);

   double h;
   int loop_counter = 0;
   do
   {
      loop_counter++;
      double z = gammp(a, a * exp(u));
      double d = y - z;
      double log_fprime = a * log(a) + a * (u - exp(u)) - gammln(a);
      double fprime = exp(log_fprime);
      h = d / fprime;
      u += h;

      if (loop_counter > 1000)
      {
	 cerr << "Error in inv_cumd_gamma"
	    " maximum number of interations exceeded for values"
	    << endl << "  x = " << y << "  a =  " << a << "  h =  " << h <<
	    endl;
      }
   }
   while (fabs(h) > 1.e-12);

   double x = a * exp(u);
   init_df3_two_variable xx(x);
   init_df3_two_variable aa(a);
   *xx.get_u_x() = 1.0;
   *aa.get_u_y() = 1.0;

   df3_two_variable z = cumd_gamma(xx, aa);
   double F_x = 1.0 / (*z.get_u_x());
   double F_y = -F_x * (*z.get_u_y());

   dvariable vz = 0.0;
   value(vz) = x;

   gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
						       &(vz.v->x),
						       &(_y.v->x), F_x,
						       &(_a.v->x), F_y);

   return vz;
}

#endif

#undef ITMAX
#undef EPS

static double Sn(double x, double a)
{
   int i = 1;
   double xp = x;
   double prod = 1.0;
   double summ = 1.0;
   double summand;
   do
   {
      prod *= (a + i);
      summand = xp / prod;
      if (summand < 1.e-4)
	 break;
      summ += summand;
      i++;
      if (i > 50)
      {
	 cerr << "convergence error" << endl;
	 ad_exit(1);
      }
   }
   while (1);
   return summ;
}



static double get_initial_u(double a, double y)
{
   const double c = 0.57721;
   // note that P = y;
   double logP = log(y);
   double logQ = log(1 - y);
   double logB = logQ + gammln(a);
   double x0 = 1.e+100;
   double log_x0 = 1.e+100;

   if (a < 1.0)
   {
      if (logB > log(.6) || (logB > log(.45) && a >= .3))
      {
	 double logu;
	 if (logB + logQ > log(1.e-8))
	 {
	    logu = (logP + gammln(1.0 + a)) / a;
	 } else
	 {
	    logu = -exp(logQ) / a - c;
	 }
	 double u = exp(logu);
	 x0 = u / (1 - u / (1.0 + a));
	 double tmp = log(1 - u / (1.0 + a));
	 log_x0 = logu;
	 log_x0 -= tmp;
      } else if (a < .3 && log(.35) <= logB && logB <= log(.6))
      {
	 double t = exp(-c - exp(logB));
	 double logt = -c - exp(logB);
	 double u = t * exp(t);
	 x0 = t * exp(u);
	 log_x0 = logt + u;
      } else if ((log(.15) <= logB && logB <= log(.35)) ||
		 ((log(.15) <= logB && logB <= log(.45)) && a >= .3))
      {
	 double y = -logB;
	 double v = y - (1 - a) * log(y);
	 x0 = y - (1 - a) * log(v) - log(1 + (1.0 - a) / (1.0 + v));
	 log_x0 = log(x0);
      } else if (log(.01) < logB && logB < log(.15))
      {
	 double y = -logB;
	 double v = y - (1 - a) * log(y);
	 x0 =
	    y - (1 - a) * log(v) -
	    log((v * v + 2 * (3 - a) * v + (2 - a) * (3 - a)) / (v * v +
								 (5 -
								  a) * v +
								 2));
	 log_x0 = log(x0);
      } else if (logB < log(.01))
      {
	 double y = -logB;
	 double v = y - (1 - a) * log(y);
	 x0 =
	    y - (1 - a) * log(v) -
	    log((v * v + 2 * (3 - a) * v + (2 - a) * (3 - a)) / (v * v +
								 (5 -
								  a) * v +
								 2));
	 log_x0 = log(x0);
      } else
      {
	 cerr << "this can't happen" << endl;
	 ad_exit(1);
      }
   } else if (a >= 1.0)
   {
      const double a0 = 3.31125922108741;
      const double b1 = 6.61053765625462;
      const double a1 = 11.6616720288968;
      const double b2 = 6.40691597760039;
      const double a2 = 4.28342155967104;
      const double b3 = 1.27364489782223;
      const double a3 = .213623493715853;
      const double b4 = .03611708101884203;

      int sgn = 1;
      double logtau;
      if (logP < log(0.5))
      {
	 logtau = logP;
	 sgn = -1;
      } else
      {
	 logtau = logQ;
	 sgn = 1;
      }

      double t = sqrt(-2.0 * logtau);


      double num = (((a3 * t + a2) * t + a1) * t) + a0;
      double den = ((((b4 * t + b3) * t + b2) * t) + b1) * t + 1;
      double s = sgn * (t - num / den);
      double s2 = s * s;
      double s3 = s2 * s;
      double s4 = s3 * s;
      double s5 = s4 * s;
      double roota = sqrt(a);
      double w =
	 a + s * roota + (s2 - 1) / 3.0 + (s3 - 7.0 * s) / (36. * roota) -
	 (3.0 * s4 + 7.0 * s2 - 16) / (810.0 * a) + (9.0 * s5 +
						     256.0 * s3 -
						     433.0 * s) /
	 (38880.0 * a * roota);
      if (logP < log(0.5))
      {
	 if (w > .15 * (a + 1))
	 {
	    x0 = w;
	 } else
	 {
	    double v = logP + gammln(a + 1);
	    double u1 = exp(v + w) / a;
	    double S1 = 1 + u1 / (a + 1);
	    double u2 = exp((v + u1 - log(S1)) / a);
	    double S2 = 1 + u2 / (a + 1) + u2 * u2 / ((a + 1) * (a + 2));
	    double u3 = exp((v + u2 - log(S2)) / a);
	    double S3 = 1 + u3 / (a + 1) + u3 * u3 / ((a + 1) * (a + 2))
	       + u3 * u3 * u3 / ((a + 1) * (a + 2) * (a + 3));
	    double z = exp((v + u3 - log(S3)) / a);
	    if (z < .002 * (a + 1.0))
	    {
	       x0 = z;
	    } else
	    {
	       double sn = Sn(z, a);
	       double zbar = exp((v + z - log(sn)) / a);
	       x0 =
		  zbar * (1.0 -
			  (a * log(zbar) - zbar - v + log(sn)) / (a -
								  zbar));
	    }

	 }
	 log_x0 = log(x0);
      } else
      {
	 double u =
	    -logB + (a - 1.0) * log(w) - log(1.0 + (1.0 - a) / (1 + w));
	 x0 = u;
	 log_x0 = log(x0);
      }
   }
   if (a == 1.0)
   {
      x0 = -log(1.0 - y);
      log_x0 = log(x0);
   }
   return log_x0 - log(a);
}
