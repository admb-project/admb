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


static double MAXLOG = 200;
static double MINLOG = -200;
static double big = 4.503599627370496e15;
static double biginv = 2.22044604925031308085e-16;
static double MACHEP = 2.22045e-16;

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
/* Stirling's formula for the gamma function */
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

static df1_two_variable polevl(const df1_two_variable & x, void *_coef,
				 int N);

static int mtherr(char *s, int n)
{
   cerr << "Error code " << n << "in " << *s << endl;
   ad_exit(1);
   return 0;
}


/**
 * Gamma function computed by Stirling's formula.
 * The polynomial STIR is valid for 33 <= x <= 172.
 * \param _x \f$33 \le x \le 172 \f$
 */
static df1_two_variable stirf(const df1_two_variable & _x)
{
   ADUNCONST(df1_two_variable, x) df1_two_variable y, w, v;

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
static df1_two_variable gamma(const df1_two_variable & xx1)
{
   df1_two_variable x;
   x = xx1;
   df1_two_variable MYBIG;
   MYBIG = 1.e+300;
   df1_two_variable p, q, z;
   df1_two_variable zero;
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

static double LS2PI = 0.91893853320467274178;
static double MAXLGM = 2.556348e305;

/* Logarithm of gamma function */

int operator <(const df1_two_variable & x, double n)
{
   return value(x) < n;
}

int operator >(const df1_two_variable & x, double n)
{
   return value(x) > n;
}

int operator >=(const df1_two_variable & x, double n)
{
   return value(x) >= n;
}

int operator ==(const df1_two_variable & x, const df1_two_variable & n)
{
   return value(x) == value(n);
}

int operator ==(const df1_two_variable & x, double n)
{
   return value(x) == n;
}

int operator ==(double x, const df1_two_variable & n)
{
   return x == value(n);
}

int operator <(const df1_two_variable & x, const df1_two_variable & n)
{
   return value(x) < value(n);
}

int operator >(const df1_two_variable & x, const df1_two_variable & n)
{
   return value(x) > value(n);
}


df1_two_variable lgam(const df1_two_variable & _x);
df1_two_variable pseries(const df1_two_variable & _a,
			   const df1_two_variable & _b,
			   double _x);
df1_two_variable pseries(const df1_two_variable & _a,
			   const df1_two_variable & _b,
			   const df1_two_variable & _x);
static df1_two_variable incbd(const df1_two_variable & _a,
				const df1_two_variable & _b,
				const df1_two_variable & _x);
static df1_two_variable incbcf(const df1_two_variable & _a,
				 const df1_two_variable & _b,
				 const df1_two_variable & _x);


df1_two_variable incbet(const df1_two_variable & _aa,
				 const df1_two_variable & _bb,
				 double _xx)
{

   df1_two_variable aa;
   df1_two_variable bb;
   double xx;
   aa = _aa;
   bb = _bb;
   xx = _xx;

   df1_two_variable a, b, t, x, xc, w, y;

   int flag;
   df1_two_variable one;
   df1_two_variable zero;
   one = 1.0;
   zero = 0.0;

   if (value(aa) <= 0.0 || value(bb) <= 0.0)
      goto domerr;

   if ((xx <= 0.0) || (xx >= 1.0))
   {
      if (xx == 0.0)
	 return (zero);
      if (xx == 1.0)
	 return (one);
    domerr:
      cerr << "incbet DOMAIN " << endl;

      return (zero);
   }

   flag = 0;
   if (value(bb * xx) <= 1.0 && xx <= 0.95)
   {
      t = pseries(aa, bb, xx);
      goto done;
   }

   w = 1.0 - xx;

   /* Reverse a and b if x is greater than the mean. */
   if (xx > (value(aa) / value(aa + bb)))
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
static df1_two_variable incbcf(const df1_two_variable & _a,
				 const df1_two_variable & _b,
				 const df1_two_variable & _x)
{
   ADUNCONST(df1_two_variable, a)
      ADUNCONST(df1_two_variable, b)
      ADUNCONST(df1_two_variable, x)
      df1_two_variable xk, pk, pkm1, pkm2, qk, qkm1, qkm2;
   df1_two_variable k1, k2, k3, k4, k5, k6, k7, k8;
   df1_two_variable r, t, ans, thresh;
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
static df1_two_variable incbd(const df1_two_variable & _a,
				const df1_two_variable & _b,
				const df1_two_variable & _x)
{
   ADUNCONST(df1_two_variable, a)
      ADUNCONST(df1_two_variable, b) ADUNCONST(df1_two_variable, x)
      //df1_two_variable s, t, u, v, n, t1, z, ai;
   df1_two_variable xk, pk, pkm1, pkm2, qk, qkm1, qkm2;
   df1_two_variable k1, k2, k3, k4, k5, k6, k7, k8;
   df1_two_variable r, t, ans, z, thresh;
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
 * Use when b*x is small and x not too close to 1
 * \param
 */
df1_two_variable pseries(const df1_two_variable & _a,
			   const df1_two_variable & _b,
			   const df1_two_variable & _x)
{
   df1_two_variable a;
   df1_two_variable b;
   df1_two_variable x;
   a = _a;
   b = _b;
   x = _x;
   df1_two_variable s, t, u, v, n, t1, z, ai;

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
 * Power series for incomplete beta integral.
 * Use when b*x is small and x not too close to 1
 * \param
 */
df1_two_variable pseries(const df1_two_variable & _a,
			   const df1_two_variable & _b,
			   double _x)
{
   df1_two_variable a;
   df1_two_variable b;
   double x;
   a = _a;
   b = _b;
   x = _x;
   df1_two_variable s, t, u, v, n, t1, z, ai;

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

static df1_two_variable p1evl(const df1_two_variable & x, void *_coef,
				int N);

/**
 * Description not yet available.
 * \param
 */
df1_two_variable lgam(const df1_two_variable & _x)
{
   df1_two_variable x, p, q, u, w, z, p1;
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
      df1_two_variable tmp;
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


/**
 * Description not yet available.
 * \param
 */
static df1_two_variable polevl(const df1_two_variable & x, void *_coef,
				 int N)
{
   double *coef = (double *) (_coef);
   df1_two_variable ans;
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

static df1_two_variable p1evl(const df1_two_variable & x, void *_coef,
				int N)
{
   double *coef = (double *) (_coef);
   df1_two_variable ans;
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


