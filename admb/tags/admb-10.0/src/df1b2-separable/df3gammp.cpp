/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009-2011 ADMB Foundation
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>
#include <df13fun.h>
#include "mconf.h"

#ifdef NANS
#undef NANS
#endif
#ifdef INFINITIES
#undef INFINITIES
#endif

double get_values(double x, double y, int print_switch);
df3_two_variable igam(const df3_two_variable & _a,
		      const df3_two_variable & _x);
df3_two_variable igamc(const df3_two_variable & _a,
		       const df3_two_variable & _x);

namespace Cephes
{

   int sgngam = 0;
   extern const double MAXLOG = 200;
   extern const double MAXNUM = 1.7976931348623158E+308;
   extern const double PI = 3.14159265358979323844;
   extern const double LOGPI = 1.14472988584940017414;
   extern const double big = 4.503599627370496e15;
   extern const double biginv = 2.22044604925031308085e-16;
   extern const double MACHEP = 2.22045e-16;
   extern const double MYINF = 1.7976931348623158E+308;

   df3_two_variable polevl(const df3_two_variable & x, const double *_coef, int N);
   df3_two_variable p1evl(const df3_two_variable & x, const double *_coef, int N);

/* Coefficents used for the rational function in gamma(x) */
#ifdef UNK
   extern const double P[] = {
      1.60119522476751861407E-4,
      1.19135147006586384913E-3,
      1.04213797561761569935E-2,
      4.76367800457137231464E-2,
      2.07448227648435975150E-1,
      4.94214826801497100753E-1,
      9.99999999999999996796E-1
   };

   extern const double Q[] = {
      -2.31581873324120129819E-5,
      5.39605580493303397842E-4,
      -4.45641913851797240494E-3,
      1.18139785222060435552E-2,
      3.58236398605498653373E-2,
      -2.34591795718243348568E-1,
      7.14304917030273074085E-2,
      1.00000000000000000320E0
   };

#define MAXGAM 171.624376956302725
#endif

#ifdef DEC
   unsigned short P[] = {
      0035047, 0162701, 0146301, 0005234,
      0035634, 0023437, 0032065, 0176530,
      0036452, 0137157, 0047330, 0122574,
      0037103, 0017310, 0143041, 0017232,
      0037524, 0066516, 0162563, 0164605,
      0037775, 0004671, 0146237, 0014222,
      0040200, 0000000, 0000000, 0000000
   };

   unsigned short Q[] = {
      0134302, 0041724, 0020006, 0116565,
      0035415, 0072121, 0044251, 0025634,
      0136222, 0003447, 0035205, 0121114,
      0036501, 0107552, 0154335, 0104271,
      0037022, 0135717, 0014776, 0171471,
      0137560, 0034324, 0165024, 0037021,
      0037222, 0045046, 0047151, 0161213,
      0040200, 0000000, 0000000, 0000000
   };

#define MAXGAM 34.84425627277176174
   unsigned short LPI[4] = {
      0040222, 0103202, 0043475, 0006750,
   };

#define LOGPI *(double *)LPI
#endif

#ifdef IBMPC
   unsigned short P[] = {
      0x2153, 0x3998, 0xfcb8, 0x3f24,
      0xbfab, 0xe686, 0x84e3, 0x3f53,
      0x14b0, 0xe9db, 0x57cd, 0x3f85,
      0x23d3, 0x18c4, 0x63d9, 0x3fa8,
      0x7d31, 0xdcae, 0x8da9, 0x3fca,
      0xe312, 0x3993, 0xa137, 0x3fdf,
      0x0000, 0x0000, 0x0000, 0x3ff0
   };

   unsigned short Q[] = {
      0xd3af, 0x8400, 0x487a, 0xbef8,
      0x2573, 0x2915, 0xae8a, 0x3f41,
      0xb44a, 0xe750, 0x40e4, 0xbf72,
      0xb117, 0x5b1b, 0x31ed, 0x3f88,
      0xde67, 0xe33f, 0x5779, 0x3fa2,
      0x87c2, 0x9d42, 0x071a, 0xbfce,
      0x3c51, 0xc9cd, 0x4944, 0x3fb2,
      0x0000, 0x0000, 0x0000, 0x3ff0
   };

#define MAXGAM 171.624376956302725
   unsigned short LPI[4] = {
      0xa1bd, 0x48e7, 0x50d0, 0x3ff2,
   };

#define LOGPI *(double *)LPI
#endif

#ifdef MIEEE
   unsigned short P[] = {
      0x3f24, 0xfcb8, 0x3998, 0x2153,
      0x3f53, 0x84e3, 0xe686, 0xbfab,
      0x3f85, 0x57cd, 0xe9db, 0x14b0,
      0x3fa8, 0x63d9, 0x18c4, 0x23d3,
      0x3fca, 0x8da9, 0xdcae, 0x7d31,
      0x3fdf, 0xa137, 0x3993, 0xe312,
      0x3ff0, 0x0000, 0x0000, 0x0000
   };

   unsigned short Q[] = {
      0xbef8, 0x487a, 0x8400, 0xd3af,
      0x3f41, 0xae8a, 0x2915, 0x2573,
      0xbf72, 0x40e4, 0xe750, 0xb44a,
      0x3f88, 0x31ed, 0x5b1b, 0xb117,
      0x3fa2, 0x5779, 0xe33f, 0xde67,
      0xbfce, 0x071a, 0x9d42, 0x87c2,
      0x3fb2, 0x4944, 0xc9cd, 0x3c51,
      0x3ff0, 0x0000, 0x0000, 0x0000
   };

#define MAXGAM 171.624376956302725
   unsigned short LPI[4] = {
      0x3ff2, 0x50d0, 0x48e7, 0xa1bd,
   };

#define LOGPI *(double *)LPI
#endif

/* Stirling's formula for the gamma function */
#if UNK
   extern const double STIR[5] = {
      7.87311395793093628397E-4,
      -2.29549961613378126380E-4,
      -2.68132617805781232825E-3,
      3.47222221605458667310E-3,
      8.33333333333482257126E-2,
   };

   extern const double MAXSTIR = 143.01608;
   extern const double SQTPI = 2.50662827463100050242E0;
#endif
#if DEC
   unsigned short STIR[20] = {
      0035516, 0061622, 0144553, 0112224,
      0135160, 0131531, 0037460, 0165740,
      0136057, 0134460, 0037242, 0077270,
      0036143, 0107070, 0156306, 0027751,
      0037252, 0125252, 0125252, 0146064,
   };

   extern const double MAXSTIR = 26.77;
   unsigned short SQT[4] = {
      0040440, 0066230, 0177661, 0034055,
   };

   extern const double SQTPI = *(double *)SQT;
#endif
#if IBMPC
   unsigned short STIR[20] = {
      0x7293, 0x592d, 0xcc72, 0x3f49,
      0x1d7c, 0x27e6, 0x166b, 0xbf2e,
      0x4fd7, 0x07d4, 0xf726, 0xbf65,
      0xc5fd, 0x1b98, 0x71c7, 0x3f6c,
      0x5986, 0x5555, 0x5555, 0x3fb5,
   };

   extern const double MAXSTIR = 143.01608;
   unsigned short SQT[4] = {
      0x2706, 0x1ff6, 0x0d93, 0x4004,
   };

   extern const double SQTPI = *(double *)SQT;
#endif
#if MIEEE
   unsigned short STIR[20] = {
      0x3f49, 0xcc72, 0x592d, 0x7293,
      0xbf2e, 0x166b, 0x27e6, 0x1d7c,
      0xbf65, 0xf726, 0x07d4, 0x4fd7,
      0x3f6c, 0x71c7, 0x1b98, 0xc5fd,
      0x3fb5, 0x5555, 0x5555, 0x5986,
   };

   extern const double MAXSTIR = 143.01608;
   unsigned short SQT[4] = {
      0x4004, 0x0d93, 0x1ff6, 0x2706,
   };

   extern const double SQTPI = *(double *)SQT;
#endif

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
   df3_two_variable stirf(const df3_two_variable & _x)
   {
      ADUNCONST(df3_two_variable, x) df3_two_variable y, w, v;

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

/* A[]: Stirling's formula expansion of log gamma
 * B[], C[]: log gamma function between 2 and 3
 */
#ifdef UNK
   extern const double A[] = {
      8.11614167470508450300E-4,
      -5.95061904284301438324E-4,
      7.93650340457716943945E-4,
      -2.77777777730099687205E-3,
      8.33333333333331927722E-2
   };

   extern const double B[] = {
      -1.37825152569120859100E3,
      -3.88016315134637840924E4,
      -3.31612992738871184744E5,
      -1.16237097492762307383E6,
      -1.72173700820839662146E6,
      -8.53555664245765465627E5
   };

   extern const double C[] = {
/* 1.00000000000000000000E0, */
      -3.51815701436523470549E2,
      -1.70642106651881159223E4,
      -2.20528590553854454839E5,
      -1.13933444367982507207E6,
      -2.53252307177582951285E6,
      -2.01889141433532773231E6
   };

/* log( sqrt( 2*pi ) ) */
   extern const double LS2PI = 0.91893853320467274178;
   extern const double MAXLGM = 2.556348e305;
#endif

#ifdef DEC
   unsigned short A[] = {
      0035524, 0141201, 0034633, 0031405,
      0135433, 0176755, 0126007, 0045030,
      0035520, 0006371, 0003342, 0172730,
      0136066, 0005540, 0132605, 0026407,
      0037252, 0125252, 0125252, 0125132
   };

   unsigned short B[] = {
      0142654, 0044014, 0077633, 0035410,
      0144027, 0110641, 0125335, 0144760,
      0144641, 0165637, 0142204, 0047447,
      0145215, 0162027, 0146246, 0155211,
      0145322, 0026110, 0010317, 0110130,
      0145120, 0061472, 0120300, 0025363
   };

   unsigned short C[] = {
/*0040200,0000000,0000000,0000000*/
      0142257, 0164150, 0163630, 0112622,
      0143605, 0050153, 0156116, 0135272,
      0144527, 0056045, 0145642, 0062332,
      0145213, 0012063, 0106250, 0001025,
      0145432, 0111254, 0044577, 0115142,
      0145366, 0071133, 0050217, 0005122
   };

/* log( sqrt( 2*pi ) ) */
   unsigned short LS2P[] = { 040153, 037616, 041445, 0172645, };

   extern const double LS2PI = *(double *)LS2P;
   extern const double MAXLGM = 2.035093e36;
#endif

#ifdef IBMPC
   unsigned short A[] = {
      0x6661, 0x2733, 0x9850, 0x3f4a,
      0xe943, 0xb580, 0x7fbd, 0xbf43,
      0x5ebb, 0x20dc, 0x019f, 0x3f4a,
      0xa5a1, 0x16b0, 0xc16c, 0xbf66,
      0x554b, 0x5555, 0x5555, 0x3fb5
   };

   unsigned short B[] = {
      0x6761, 0x8ff3, 0x8901, 0xc095,
      0xb93e, 0x355b, 0xf234, 0xc0e2,
      0x89e5, 0xf890, 0x3d73, 0xc114,
      0xdb51, 0xf994, 0xbc82, 0xc131,
      0xf20b, 0x0219, 0x4589, 0xc13a,
      0x055e, 0x5418, 0x0c67, 0xc12a
   };

   unsigned short C[] = {
/*0x0000,0x0000,0x0000,0x3ff0,*/
      0x12b2, 0x1cf3, 0xfd0d, 0xc075,
      0xd757, 0x7b89, 0xaa0d, 0xc0d0,
      0x4c9b, 0xb974, 0xeb84, 0xc10a,
      0x0043, 0x7195, 0x6286, 0xc131,
      0xf34c, 0x892f, 0x5255, 0xc143,
      0xe14a, 0x6a11, 0xce4b, 0xc13e
   };

/* log( sqrt( 2*pi ) ) */
   unsigned short LS2P[] = {
      0xbeb5, 0xc864, 0x67f1, 0x3fed
   };

   extern const double LS2PI = *(double *)LS2P
   extern const double MAXLGM = 2.556348e305;
#endif

#ifdef MIEEE
   unsigned short A[] = {
      0x3f4a, 0x9850, 0x2733, 0x6661,
      0xbf43, 0x7fbd, 0xb580, 0xe943,
      0x3f4a, 0x019f, 0x20dc, 0x5ebb,
      0xbf66, 0xc16c, 0x16b0, 0xa5a1,
      0x3fb5, 0x5555, 0x5555, 0x554b
   };

   unsigned short B[] = {
      0xc095, 0x8901, 0x8ff3, 0x6761,
      0xc0e2, 0xf234, 0x355b, 0xb93e,
      0xc114, 0x3d73, 0xf890, 0x89e5,
      0xc131, 0xbc82, 0xf994, 0xdb51,
      0xc13a, 0x4589, 0x0219, 0xf20b,
      0xc12a, 0x0c67, 0x5418, 0x055e
   };

   unsigned short C[] = {
      0xc075, 0xfd0d, 0x1cf3, 0x12b2,
      0xc0d0, 0xaa0d, 0x7b89, 0xd757,
      0xc10a, 0xeb84, 0xb974, 0x4c9b,
      0xc131, 0x6286, 0x7195, 0x0043,
      0xc143, 0x5255, 0x892f, 0xf34c,
      0xc13e, 0xce4b, 0x6a11, 0xe14a
   };

/* log( sqrt( 2*pi ) ) */
   unsigned short LS2P[] = {
      0x3fed, 0x67f1, 0xc864, 0xbeb5
   };

   extern const double LS2PI = *(double *)LS2P
   extern const double MAXLGM = 2.556348e305;
#endif

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
   df3_two_variable polevl(const df3_two_variable & x, const double *_coef, int N)
   {
      double *coef = (double *) (_coef);
      df3_two_variable ans;
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
   df3_two_variable p1evl(const df3_two_variable & x, const double *_coef, int N)
   {
      double *coef = (double *) (_coef);
      df3_two_variable ans;
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

} //end namespace Cephes

/**
 * \ingroup gammafunc
 * Gamma Function
 * \param xx1 \f$x\f$
 * \return The Gamma Function \f$\Gamma(x)\f$
 * 
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier 
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
static df3_two_variable gamma(const df3_two_variable & xx1)
{
   using namespace Cephes;
   df3_two_variable x;
   x = xx1;
   df3_two_variable MYBIG;
   MYBIG = 1.e+300;
   df3_two_variable p, q, z, tmp;
   df3_two_variable zero;
   zero = 0.0;
   int i;

   sgngam = 1;

#ifdef NANS
   if (isnan(value(x)))
      return (x);
#endif
#ifdef INFINITIES
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
#ifdef NANS
	  gamnan:
	    cerr << "gamma DOMAIN" << endl;
	    return (zero);
#else*/
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
	    tmp = sgngam * MYINF;
	    return (tmp);
#else
	  goverf:
	    //( "gamma", OVERFLOW );
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

/**
 * \ingroup gammafunc
 * Log-gamma function
 * \param xx \f$x\f$
 * \return natural log of the absolute
 *   value of the gamma function \f$\ln(|\Gamma(x)|)\f$
 *
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
df3_two_variable lgam(const df3_two_variable & xx)
{
   using namespace Cephes;
   df3_two_variable x = xx;
   df3_two_variable p, q, u, w, z, tmp;
   int i;

   sgngam = 1;
#ifdef NANS
   if (isnan(value(x)))
      return (x);
#endif

#ifdef INFINITIES
   if (!isfinite(value(x)))
   {
      tmp = MYINF;
      return (tmp);
   }
#endif

   if (x < -34.0)
   {
      q = -x;
      w = lgam(q);		// note this modifies sgngam! 
      p = floor(value(q));
      if (p == q)
      {
       lgsing:
#ifdef INFINITIES
	 mtherr("lgam", SING);
	 tmp = MYINF;
	 return (tmp);
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
#ifdef INFINITIES
      tmp = sgngam * MYINF;
      return (tmp);
#else
    loverf:
      mtherr("lgam", OVERFLOW);
      df3_two_variable tmp;
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
 * \ingroup gammafunc
 * Incomplete gamma integral.
 * \param aa \f$a\f$
 * \param xx \f$x\f$
 * \return Incomplete gamma integral \f$\gamma(a,x) = \frac{1}{\Gamma(a)}\int_{0}^{x}e^{-t}t^{a-1}dt \f$
 *
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
df3_two_variable igam(const df3_two_variable & aa,
		      const df3_two_variable & xx)
{
   using namespace Cephes;
   df3_two_variable a = aa;
   df3_two_variable x = xx;

   df3_two_variable ans, ax, c, r, t;

   if ((value(x) <= 0) || (value(a) <= 0))
   {
      df3_two_variable tmp;
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
//  while( fabs(t) > MACHEP);
   while ((fabs(*t.get_u()) > MACHEP) &&
	  (fabs(*t.get_u_x()) > MACHEP) &&
	  (fabs(*t.get_u_xx()) > MACHEP) &&
	  (fabs(*t.get_u_xxx()) > MACHEP) &&
	  (fabs(*t.get_u_y()) > MACHEP) &&
	  (fabs(*t.get_u_yy()) > MACHEP) &&
	  (fabs(*t.get_u_yyy()) > MACHEP) &&
	  (fabs(*t.get_u_xy()) > MACHEP) &&
	  (fabs(*t.get_u_xxy()) > MACHEP) &&
	  (fabs(*t.get_u_xyy()) > MACHEP));

   return (ans * ax);
}

/**
 * \ingroup gammafunc
 * Incomplete gamma integral complement .
 * \param aa \f$a\f$
 * \param xx \f$x\f$
 * \return complement of th incomplete gamma integral
 *   \f$\Gamma(a,x) = 1-\gamma(a,x) = \frac{1}{\Gamma(a)}\int_{x}^{\infty}e^{-t}t^{a-1}dt \f$
 *
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
df3_two_variable igamc(const df3_two_variable & aa,
		       const df3_two_variable & xx)
{
   using namespace Cephes;
   df3_two_variable a = aa;
   df3_two_variable x = xx;

   df3_two_variable ans, ax, c, yc, r, t, y, z;
   df3_two_variable pk, pkm1, pkm2, qk, qkm1, qkm2;

   if ((value(x) <= 0) || (value(a) <= 0))
   {
      df3_two_variable tmp;
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
//  while( fabs(t) > MACHEP );
   while ((fabs(*t.get_u()) > MACHEP) &&
	  (fabs(*t.get_u_x()) > MACHEP) &&
	  (fabs(*t.get_u_xx()) > MACHEP) &&
	  (fabs(*t.get_u_xxx()) > MACHEP) &&
	  (fabs(*t.get_u_y()) > MACHEP) &&
	  (fabs(*t.get_u_yy()) > MACHEP) &&
	  (fabs(*t.get_u_yyy()) > MACHEP) &&
	  (fabs(*t.get_u_xy()) > MACHEP) &&
	  (fabs(*t.get_u_xxy()) > MACHEP) &&
	  (fabs(*t.get_u_xyy()) > MACHEP));

   return (ans * ax);
}

df1b2variable log_negbinomial_density(double x, const df1b2variable & _xmu,
				      const df1b2variable & _xtau)
{
   ADUNCONST(df1b2variable, xmu)
      ADUNCONST(df1b2variable, xtau) init_df3_two_variable mu(xmu);
   init_df3_two_variable tau(xtau);
   *mu.get_u_x() = 1.0;
   *tau.get_u_y() = 1.0;
   if (value(tau) - 1.0 < 0.0)
   {
      cerr << "tau <=1 in log_negbinomial_density " << endl;
      ad_exit(1);
   }
   df3_two_variable r = mu / (1.e-120 + (tau - 1.0));
   df3_two_variable tmp;
   tmp = gammln(x + r) - gammln(r) - gammln(x + 1)
      + r * log(r) + x * log(mu) - (r + x) * log(r + mu);
   df1b2variable tmp1;
   tmp1 = tmp;
   return tmp1;
}

df3_two_variable gammln(const df3_two_variable & xx)
{
   df3_two_variable x = xx;
   return lgam(x);
}

df3_two_variable cumd_gamma(const df3_two_variable & x,
			    const df3_two_variable & a)
{
   df3_two_variable gamma = igam(a, x);
   return (gamma);
}

df3_two_variable cumd_exponential(const df3_two_variable & x,
				  const df3_two_variable & a)
{
   df3_two_variable tmp;
   if (value(x) <= 0)
      return 0.5 * exp(x);
   else
      return 1.0 - 0.5 * exp(-x);
}

df3_two_variable cumd_cauchy(const df3_two_variable & x,
			     const df3_two_variable & a)
{
   return atan(x / a);
}
