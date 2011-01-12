/*
 * $Id$
 *
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>
#include <df1b2fun.h>
#include <df33fun.h>

namespace replacement
{

static df3_three_variable igam(const df3_three_variable & a,const df3_three_variable & x);
//  what should MAXLOG MINLOG be?
  double MAXLOG=200;
  double MINLOG=-200;
  static double big = 4.503599627370496e15;
  static double biginv =  2.22044604925031308085e-16;
  static double MACHEP=2.22045e-16;
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

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1989, 1992, 2000 by Stephen L. Moshier
*/


#include "mconf.h"
#ifdef INFINITIES
#undef INFINITIES
#endif
#ifdef NANS
#undef NANS
#endif

#ifdef UNK
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
#define MAXGAM 171.624376956302725
static double LOGPI = 1.14472988584940017414;
#endif
static double PI = 3.14159265358979323844;

#ifdef DEC
static unsigned short P[] = {
0035047,0162701,0146301,0005234,
0035634,0023437,0032065,0176530,
0036452,0137157,0047330,0122574,
0037103,0017310,0143041,0017232,
0037524,0066516,0162563,0164605,
0037775,0004671,0146237,0014222,
0040200,0000000,0000000,0000000
};
static unsigned short Q[] = {
0134302,0041724,0020006,0116565,
0035415,0072121,0044251,0025634,
0136222,0003447,0035205,0121114,
0036501,0107552,0154335,0104271,
0037022,0135717,0014776,0171471,
0137560,0034324,0165024,0037021,
0037222,0045046,0047151,0161213,
0040200,0000000,0000000,0000000
};
#define MAXGAM 34.84425627277176174
static unsigned short LPI[4] = {
0040222,0103202,0043475,0006750,
};
#define LOGPI *(double *)LPI
#endif

#ifdef IBMPC
static unsigned short P[] = {
0x2153,0x3998,0xfcb8,0x3f24,
0xbfab,0xe686,0x84e3,0x3f53,
0x14b0,0xe9db,0x57cd,0x3f85,
0x23d3,0x18c4,0x63d9,0x3fa8,
0x7d31,0xdcae,0x8da9,0x3fca,
0xe312,0x3993,0xa137,0x3fdf,
0x0000,0x0000,0x0000,0x3ff0
};
static unsigned short Q[] = {
0xd3af,0x8400,0x487a,0xbef8,
0x2573,0x2915,0xae8a,0x3f41,
0xb44a,0xe750,0x40e4,0xbf72,
0xb117,0x5b1b,0x31ed,0x3f88,
0xde67,0xe33f,0x5779,0x3fa2,
0x87c2,0x9d42,0x071a,0xbfce,
0x3c51,0xc9cd,0x4944,0x3fb2,
0x0000,0x0000,0x0000,0x3ff0
};
#define MAXGAM 171.624376956302725
static unsigned short LPI[4] = {
0xa1bd,0x48e7,0x50d0,0x3ff2,
};
#define LOGPI *(double *)LPI
#endif 

#ifdef MIEEE
static unsigned short P[] = {
0x3f24,0xfcb8,0x3998,0x2153,
0x3f53,0x84e3,0xe686,0xbfab,
0x3f85,0x57cd,0xe9db,0x14b0,
0x3fa8,0x63d9,0x18c4,0x23d3,
0x3fca,0x8da9,0xdcae,0x7d31,
0x3fdf,0xa137,0x3993,0xe312,
0x3ff0,0x0000,0x0000,0x0000
};
static unsigned short Q[] = {
0xbef8,0x487a,0x8400,0xd3af,
0x3f41,0xae8a,0x2915,0x2573,
0xbf72,0x40e4,0xe750,0xb44a,
0x3f88,0x31ed,0x5b1b,0xb117,
0x3fa2,0x5779,0xe33f,0xde67,
0xbfce,0x071a,0x9d42,0x87c2,
0x3fb2,0x4944,0xc9cd,0x3c51,
0x3ff0,0x0000,0x0000,0x0000
};
#define MAXGAM 171.624376956302725
static unsigned short LPI[4] = {
0x3ff2,0x50d0,0x48e7,0xa1bd,
};
#define LOGPI *(double *)LPI
#endif 

/* Stirling's formula for the gamma function */
#if UNK
static double STIR[5] = {
 7.87311395793093628397E-4,
-2.29549961613378126380E-4,
-2.68132617805781232825E-3,
 3.47222221605458667310E-3,
 8.33333333333482257126E-2,
};
#define MAXSTIR 143.01608
static double SQTPI = 2.50662827463100050242E0;
#endif
#if DEC
static unsigned short STIR[20] = {
0035516,0061622,0144553,0112224,
0135160,0131531,0037460,0165740,
0136057,0134460,0037242,0077270,
0036143,0107070,0156306,0027751,
0037252,0125252,0125252,0146064,
};
#define MAXSTIR 26.77
static unsigned short SQT[4] = {
0040440,0066230,0177661,0034055,
};
#define SQTPI *(double *)SQT
#endif
#if IBMPC
static unsigned short STIR[20] = {
0x7293,0x592d,0xcc72,0x3f49,
0x1d7c,0x27e6,0x166b,0xbf2e,
0x4fd7,0x07d4,0xf726,0xbf65,
0xc5fd,0x1b98,0x71c7,0x3f6c,
0x5986,0x5555,0x5555,0x3fb5,
};
#define MAXSTIR 143.01608
static unsigned short SQT[4] = {
0x2706,0x1ff6,0x0d93,0x4004,
};
#define SQTPI *(double *)SQT
#endif
#if MIEEE
static unsigned short STIR[20] = {
0x3f49,0xcc72,0x592d,0x7293,
0xbf2e,0x166b,0x27e6,0x1d7c,
0xbf65,0xf726,0x07d4,0x4fd7,
0x3f6c,0x71c7,0x1b98,0xc5fd,
0x3fb5,0x5555,0x5555,0x5986,
};
#define MAXSTIR 143.01608
static unsigned short SQT[4] = {
0x4004,0x0d93,0x1ff6,0x2706,
};
#define SQTPI *(double *)SQT
#endif

static int sgngam = 0;
static double MAXNUM=1.7976931348623158E+308;
#ifdef ANSIPROT
double polevl ( double, void *, int );
extern df3_three_variable polevl (const df3_three_variable&, void *, int );
extern double p1evl ( double, void *, int );
extern df3_three_variable p1evl ( const df3_three_variable& , void *, int );
//extern int isnan ( double );
//extern int isfinite ( double );
//static double stirf ( double );
double lgam ( double );
#else
double  sin(), polevl(), p1evl();
int isnan(), isfinite();
static double stirf();
double lgam();
#endif
#ifdef INFINITIES
//extern double INFINITY;
#endif
#ifdef NANS
//extern double NAN;
#endif
const double MYINF=1.7976931348623158E+308;

/**
 * Gamma function computed by Stirling's formula.
 * \param _x \f$33 \le x \le 172\f$
 */
static df3_three_variable stirf(const df3_three_variable & _x)
{
   ADUNCONST(df3_three_variable,x)
df3_three_variable y, w, v;

w = 1.0/x;
w = 1.0 + w * polevl( w, STIR, 4 );
y = exp(x);
if( value(x) > MAXSTIR )
	{ /* Avoid overflow in pow() */
	v = pow( x, 0.5 * x - 0.25 );
	y = v * (v / y);
	}
else
	{
	y = pow( x, x - 0.5 ) / y;
	}
y = SQTPI * y * w;
return( y );
}

/**
 * Description not yet available.
 * \param
 */
static df3_three_variable gamma(const df3_three_variable & xx1)
{
   df3_three_variable x;
  x=xx1;
   df3_three_variable MYBIG;
   MYBIG=1.e+300;
df3_three_variable p, q, z;
df3_three_variable zero;
zero=0.0;
int i;

sgngam = 1;
#ifdef NANS
if( isnan(x) )
	return(x);
#endif
#ifdef INFINITIES
#ifdef NANS
if( value(x) == MYINF )
	return(x);
if( value(x) == -MYINF )
	return(NAN);
#else
if( !isfinite(value(x)) )
	return(x);
#endif
#endif
q = fabs(x);

if( value(q) > 33.0 )
	{
	if( value(x) < 0.0 )
		{
		p = floor(value(q));
		if( value(p) == value(q) )
			{
#ifdef NANS
gamnan:
			cerr <<  "gamma DOMAIN" << endl;
			return (zero);
#else
			goto goverf;
#endif
			}
		i = value(p);
		if( (i & 1) == 0 )
			sgngam = -1;
		z = q - p;
		if( value(z) > 0.5 )
			{
			p += 1.0;
			z = q - p;
			}
		z = q * sin( PI * z );
		if( value(z) == 0.0 )
			{
#ifdef INFINITIES
			return( sgngam * MYINF);
#else
goverf:
			//mtherr( "gamma", OVERFLOW );
			return( sgngam * MYBIG);
			//return( sgngam * MAXNUM);
#endif
			}
		z = fabs(z);
		z = PI/(z * stirf(q) );
		}
	else
		{
		z = stirf(x);
		}
	return( sgngam * z );
	}

z = 1.0;
while( value(x) >= 3.0 )
	{
	x -= 1.0;
	z *= x;
	}

while( value(x) < 0.0 )
	{
	if( value(x) > -1.E-9 )
		goto SMALL;
	z /= x;
	x += 1.0;
	}

while( value(x) < 2.0 )
	{
	if( value(x) < 1.e-9 )
		goto SMALL;
	z /= x;
	x += 1.0;
	}

if( value(x) == 2.0 )
	return(z);

x -= 2.0;
p = polevl( x, P, 6 );
q = polevl( x, Q, 7 );
return( z * p / q );

SMALL:
if( value(x) == 0.0 )
	{
#ifdef INFINITIES
#ifdef NANS
	  goto gamnan;
#else
	  return( MYINF );
#endif
#else
	cerr <<  "gamma SING " << endl;
	return( MYBIG);
#endif
	}
else
	return( z/((1.0 + 0.5772156649015329 * x) * x) );
}



/* A[]: Stirling's formula expansion of log gamma
 * B[], C[]: log gamma function between 2 and 3
 */
#ifdef UNK
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
static double LS2PI  =  0.91893853320467274178;
#define MAXLGM 2.556348e305
#endif

#ifdef DEC
static unsigned short A[] = {
0035524,0141201,0034633,0031405,
0135433,0176755,0126007,0045030,
0035520,0006371,0003342,0172730,
0136066,0005540,0132605,0026407,
0037252,0125252,0125252,0125132
};
static unsigned short B[] = {
0142654,0044014,0077633,0035410,
0144027,0110641,0125335,0144760,
0144641,0165637,0142204,0047447,
0145215,0162027,0146246,0155211,
0145322,0026110,0010317,0110130,
0145120,0061472,0120300,0025363
};
static unsigned short C[] = {
/*0040200,0000000,0000000,0000000*/
0142257,0164150,0163630,0112622,
0143605,0050153,0156116,0135272,
0144527,0056045,0145642,0062332,
0145213,0012063,0106250,0001025,
0145432,0111254,0044577,0115142,
0145366,0071133,0050217,0005122
};
/* log( sqrt( 2*pi ) ) */
static unsigned short LS2P[] = {040153,037616,041445,0172645,};
#define LS2PI *(double *)LS2P
#define MAXLGM 2.035093e36
#endif

#ifdef IBMPC
static unsigned short A[] = {
0x6661,0x2733,0x9850,0x3f4a,
0xe943,0xb580,0x7fbd,0xbf43,
0x5ebb,0x20dc,0x019f,0x3f4a,
0xa5a1,0x16b0,0xc16c,0xbf66,
0x554b,0x5555,0x5555,0x3fb5
};
static unsigned short B[] = {
0x6761,0x8ff3,0x8901,0xc095,
0xb93e,0x355b,0xf234,0xc0e2,
0x89e5,0xf890,0x3d73,0xc114,
0xdb51,0xf994,0xbc82,0xc131,
0xf20b,0x0219,0x4589,0xc13a,
0x055e,0x5418,0x0c67,0xc12a
};
static unsigned short C[] = {
/*0x0000,0x0000,0x0000,0x3ff0,*/
0x12b2,0x1cf3,0xfd0d,0xc075,
0xd757,0x7b89,0xaa0d,0xc0d0,
0x4c9b,0xb974,0xeb84,0xc10a,
0x0043,0x7195,0x6286,0xc131,
0xf34c,0x892f,0x5255,0xc143,
0xe14a,0x6a11,0xce4b,0xc13e
};
/* log( sqrt( 2*pi ) ) */
static unsigned short LS2P[] = {
0xbeb5,0xc864,0x67f1,0x3fed
};
#define LS2PI *(double *)LS2P
#define MAXLGM 2.556348e305
#endif

#ifdef MIEEE
static unsigned short A[] = {
0x3f4a,0x9850,0x2733,0x6661,
0xbf43,0x7fbd,0xb580,0xe943,
0x3f4a,0x019f,0x20dc,0x5ebb,
0xbf66,0xc16c,0x16b0,0xa5a1,
0x3fb5,0x5555,0x5555,0x554b
};
static unsigned short B[] = {
0xc095,0x8901,0x8ff3,0x6761,
0xc0e2,0xf234,0x355b,0xb93e,
0xc114,0x3d73,0xf890,0x89e5,
0xc131,0xbc82,0xf994,0xdb51,
0xc13a,0x4589,0x0219,0xf20b,
0xc12a,0x0c67,0x5418,0x055e
};
static unsigned short C[] = {
0xc075,0xfd0d,0x1cf3,0x12b2,
0xc0d0,0xaa0d,0x7b89,0xd757,
0xc10a,0xeb84,0xb974,0x4c9b,
0xc131,0x6286,0x7195,0x0043,
0xc143,0x5255,0x892f,0xf34c,
0xc13e,0xce4b,0x6a11,0xe14a
};
/* log( sqrt( 2*pi ) ) */
static unsigned short LS2P[] = {
0x3fed,0x67f1,0xc864,0xbeb5
};
#define LS2PI *(double *)LS2P
#define MAXLGM 2.556348e305
#endif


/* Logarithm of gamma function */

int operator < (const df3_three_variable& x,double n) { return value(x) < n; }
int operator > (const df3_three_variable& x,double n) { return value(x) > n; }
int operator >= (const df3_three_variable& x,double n) { return value(x) >= n; }
int operator == (const df3_three_variable& x,const df3_three_variable& n) { return value(x)==value(n); }
int operator == (const df3_three_variable& x,double n) { return value(x)==n; }
int operator == (double x,const df3_three_variable& n) { return x==value(n); }
int operator < (const df3_three_variable& x,const df3_three_variable& n) { return value(x)<value(n); }
int operator > (const df3_three_variable& x,const df3_three_variable& n) { return value(x)>value(n); }

/**
 * Description not yet available.
 * \param
 */
df3_three_variable lgam(const df3_three_variable& _x)
{
df3_three_variable  x,p,q, u, w, z,p1;
x=_x;
int i;

sgngam = 1;
#ifdef NANS
if( isnan(x) )
	return(x);
#endif

#ifdef INFINITIES
if( !isfinite(x) )
	return(MYINF);
#endif

if( x < -34.0 )
	{
	q = -x;
	w = lgam(q); /* note this modifies sgngam! */
	p = floor(value(q));
	if( p == q )
		{
lgsing:
#ifdef INFINITIES
		//mtherr( "lgam", SING );
		return (MYINF);
#else
		goto loverf;
#endif
		}
	i = value(p);
	if( (i & 1) == 0 )
		sgngam = -1;
	else
		sgngam = 1;
	z = q - p;
	if( z > 0.5 )
		{
		p += 1.0;
		z = p - q;
		}
	z = q * sin( PI * z );
	if( z == 0.0 )
		goto lgsing;
/*	z = log(PI) - log( z ) - w;*/
	z = LOGPI - log( z ) - w;
	return( z );
	}

if( x < 13.0 )
	{
	z = 1.0;
	p = 0.0;
	u = x;
	while( u >= 3.0 )
		{
		p -= 1.0;
		u = x + p;
		z *= u;
		}
	while( u < 2.0 )
		{
		if( u == 0.0 )
			goto lgsing;
		z /= u;
		p += 1.0;
		u = x + p;
		}
	if( z < 0.0 )
		{
		sgngam = -1;
		z = -z;
		}
	else
		sgngam = 1;
	if( u == 2.0 )
		return( log(z) );
	p -= 2.0;
	x = x + p;
	p = x * polevl( x, B, 5 ) / p1evl( x, C, 6);
	return( log(z) + p );
	}

if( x > MAXLGM )
	{
#ifdef INFINITIES
	return( sgngam * MYINF );
#else
loverf:
	//mtherr( "lgam", OVERFLOW );
	df3_three_variable tmp;
        tmp=sgngam * MAXNUM;
	return tmp;
#endif
	}

q = ( x - 0.5 ) * log(x) - x + LS2PI;
if( x > 1.0e8 )
	return( q );

p = 1.0/(x*x);
if( x >= 1000.0 )
	q += ((   7.9365079365079365079365e-4 * p
		- 2.7777777777777777777778e-3) *p
		+ 0.0833333333333333333333) / x;
else
	q += polevl( p, A, 4 ) / x;
return( q );
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


/*
Cephes Math Library Release 2.1:  December, 1988
Copyright 1984, 1987, 1988 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/


 // static double polevl( double  x, void * _coef, int N )
 // {
 // double * coef=(double *)(_coef);
 // double  ans;
 // int i;
 // double *p;
 // 
 // p = coef;
 // ans = *p++;
 // i = N;
 // 
 // do
 // 	ans = ans * x  +  *p++;
 // while( --i );
 // 
 // return( ans );
 // }

/**
 * Description not yet available.
 * \param
 */
df3_three_variable polevl( const df3_three_variable&  x, void * _coef, int N )
{
double * coef=(double *)(_coef);
df3_three_variable  ans;
int i;
double *p;

p = coef;
ans = *p++;
i = N;

do
	ans = ans * x  +  *p++;
while( --i );

return( ans );
}


/*							p1evl()	*/
/*                                          N
 * Evaluate polynomial when coefficient of x  is 1.0.
 * Otherwise same as polevl.
 */

/*
double p1evl( double x, void * _coef, int N )
{
double * coef= (double*)(_coef);
double ans;
double *p;
int i;

p = coef;
ans = x + *p++;
i = N-1;

do
	ans = ans * x  + *p++;
while( --i );

return( ans );
}
*/

/**
 * Description not yet available.
 * \param
 */
df3_three_variable p1evl(const df3_three_variable & x, void * _coef, int N )
{
double * coef= (double*)(_coef);
df3_three_variable ans;
double *p;
int i;

p = coef;
ans = x + *p++;
i = N-1;

do
	ans = ans * x  + *p++;
while( --i );

return( ans );
}
 
/*
 int isnan(double) {return 0;}
_INFINITY' referenced from module all.cpp
'_NAN' referenced from module all.cpp
'mtherr(char*,int)' referenced from module all.cpp
'_PI' referenced from module all.cpp
'isfinite(double)' referenced from module all.cpp
*/

//int mtherr(char* s,int n);
 df3_three_variable incbet(const df3_three_variable & _aa, 
   const df3_three_variable & _bb, const df3_three_variable & _xx );

/**
 * this is the wrapper to call the main inbet function
 * \param
 */
df1b2variable incbet(const df1b2variable& _a,const df1b2variable& _b,
  const df1b2variable& _x)
{
  ADUNCONST(df1b2variable,a)
  ADUNCONST(df1b2variable,b)
  ADUNCONST(df1b2variable,x)
  // these three lines will automatically put in the
  // derivatvie glue
  init_df3_three_variable vx(x);
  init_df3_three_variable va(a);
  init_df3_three_variable vb(b);
  df3_three_variable vy;
  vy = replacement::incbet( va, vb, vx );
  df1b2variable z;
  z=vy;
  return z;
}


  // main()
  // {
  //   double a=0.5;
  //   double b=0.75;
  //   double delta=1.e-6;
  //   for (double x=.01;x<=.999;x+=0.01)
  //   {
  //     df3_three_variable va,vb,vx;
  //     va.initialize();
  //     vb.initialize();
  //     vx.initialize();
  //     va=a;
  //     vb=b;
  //     vx=x;
  //     *vx.get_u_x()=1.0;
  //     *va.get_u_y()=1.0;
  //     *vb.get_u_z()=1.0;
  //     df3_three_variable vy = incbet(va,vb,vx);
  // 
  //     // just so that we can do the finite diff derivative comparison
  //   }
  // }

 // static double lgam(double x)
 // {
 // double p, q, u, w, z;
 // int i;
 // 
 //  sgngam = 1;
 // #ifdef NANS
 // if( isnan(x) )
 // 	return(x);
 // #endif
 // 
 // #ifdef INFINITIES
 // if( !isfinite(x) )
 // 	return(MYINF);
 // #endif
 // 
 // if( x < -34.0 )
 // 	{
 // 	q = -x;
 // 	w = lgam(q); /* note this modifies sgngam! */
 // 	p = floor(q);
 // 	if( p == q )
 // 		{
 // lgsing:
 // #ifdef INFINITIES
 // 		mtherr( "lgam", SING );
 // 		return (MYINF);
 // #else
 // 		goto loverf;
 // #endif
 // 		}
 // 	i = p;
 // 	if( (i & 1) == 0 )
 // 		sgngam = -1;
 // 	else
 // 		sgngam = 1;
 // 	z = q - p;
 // 	if( z > 0.5 )
 // 		{
 // 		p += 1.0;
 // 		z = p - q;
 // 		}
 // 	z = q * sin( PI * z );
 // 	if( z == 0.0 )
 // 		goto lgsing;
 // /*	z = log(PI) - log( z ) - w;*/
 // 	z = LOGPI - log( z ) - w;
 // 	return( z );
 // 	}
 // 
 // if( x < 13.0 )
 // 	{
 // 	z = 1.0;
 // 	p = 0.0;
 // 	u = x;
 // 	while( u >= 3.0 )
 // 		{
 // 		p -= 1.0;
 // 		u = x + p;
 // 		z *= u;
 // 		}
 // 	while( u < 2.0 )
 // 		{
 // 		if( u == 0.0 )
 // 			goto lgsing;
 // 		z /= u;
 // 		p += 1.0;
 // 		u = x + p;
 // 		}
 // 	if( z < 0.0 )
 // 		{
 // 		sgngam = -1;
 // 		z = -z;
 // 		}
 // 	else
 // 		sgngam = 1;
 // 	if( u == 2.0 )
 // 		return( log(z) );
 // 	p -= 2.0;
 // 	x = x + p;
 // 	p = x * polevl( x, B, 5 ) / p1evl( x, C, 6);
 // 	return( log(z) + p );
 // 	}
 // 
 // if( x > MAXLGM )
 // 	{
 // #ifdef INFINITIES
 // 	return( sgngam * MYINF );
 // #else
 // loverf:
 // 	mtherr( "lgam", OVERFLOW );
 // 	return( sgngam * MAXNUM );
 // #endif
 // 	}
 // 
 // q = ( x - 0.5 ) * log(x) - x + LS2PI;
 // if( x > 1.0e8 )
 // 	return( q );
 // 
 // p = 1.0/(x*x);
 // if( x >= 1000.0 )
 // 	q += ((   7.9365079365079365079365e-4 * p
 // 		- 2.7777777777777777777778e-3) *p
 // 		+ 0.0833333333333333333333) / x;
 // else
 // 	q += polevl( p, A, 4 ) / x;
 // return( q );
 // }

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

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1985, 1987, 2000 by Stephen L. Moshier
*/
static df3_three_variable igam(const df3_three_variable & a,const df3_three_variable & x);

  // #include "mconf.h"
  // #ifdef ANSIPROT
  // extern double lgam ( double );
  // extern double exp ( double );
  // extern double log ( double );
  // extern double fabs ( double );
  // extern double igam ( double, double );
  // extern double igamc ( double, double );
  // #else
  // double lgam(), exp(), log(), fabs(), igam(), igamc();
  // #endif
  // 
  // extern double MACHEP, MAXLOG;
  // static double big = 4.503599627370496e15;
  // static double biginv =  2.22044604925031308085e-16;
  // 
/**
 * Description not yet available.
 * \param
 */
   df3_three_variable igamc(const df3_three_variable & _a, 
     const df3_three_variable & _x)
   {
     ADUNCONST(df3_three_variable,a)
     ADUNCONST(df3_three_variable,x)
   df3_three_variable ans, ax, c, yc, r, t, y, z;
   df3_three_variable pk, pkm1, pkm2, qk, qkm1, qkm2;
   
   if( (value(x) <= 0) || ( value(a) <= 0) )
   {
     df3_three_variable tmp;
     tmp=0.0;
     return(tmp);
   }
   
   if( (value(x) < 1.0) || (value(x) < value(a) ))
   	return( 1.0 - igam(a,x) );
   
   ax = a * log(x) - x - lgam(a);
   if( value(ax) < -MAXLOG )
   	{
   	  cerr <<  "igamc UNDERFLOW " << endl; 
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
   ans = pkm1/qkm1;
   
   do
   	{
   	c += 1.0;
   	y += 1.0;
   	z += 2.0;
   	yc = y * c;
   	pk = pkm1 * z  -  pkm2 * yc;
   	qk = qkm1 * z  -  qkm2 * yc;
   	if( value(qk) != 0 )
   		{
   		r = pk/qk;
   		t = fabs( (ans - r)/r );
   		ans = r;
   		}
   	else
   		t = 1.0;
   	pkm2 = pkm1;
   	pkm1 = pk;
   	qkm2 = qkm1;
   	qkm1 = qk;
   	if( fabs(value(pk)) > big )
   		{
   		pkm2 *= biginv;
   		pkm1 *= biginv;
   		qkm2 *= biginv;
   		qkm1 *= biginv;
   		}
   	}
   while( t > MACHEP );
   
   return( ans * ax );
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
    const df3_three_variable & _x )
   {
      ADUNCONST(df3_three_variable,a)
      ADUNCONST(df3_three_variable,x)

   df3_three_variable ans, ax, c, r;
   
   if( (value(x) <= 0) || ( value(a) <= 0) )
   {
     df3_three_variable tmp;
     tmp=0.0;
     return(tmp);
   }
   
   if( (value(x) > 1.0) && (value(x) > value(a) ) )
   	return( 1.0 - igamc(a,x) );
   
   /* Compute  x**a * exp(-x) / gamma(a)  */
   ax = a * log(x) - x - lgam(a);
   if( value(ax) < -MAXLOG )
   	{
   	 cerr <<  "igam UNDERFLOW " << endl;
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
   	c *= x/r;
   	ans += c;
   	}
   while( c/ans > MACHEP );
   
   return( ans * ax/a );
   }



 // /*							incbet.c
 //  *
 //  *	Incomplete beta integral
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
 // 
 // #include "mconf.h"
 // 
 // #ifdef DEC
 // #define MAXGAM 34.84425627277176174
 // #else
 // #define MAXGAM 171.624376956302725
 // #endif
 // 
 // extern double MACHEP, MINLOG, MAXLOG;
 // #ifdef ANSIPROT
 // extern double gamma ( double );
 // extern double lgam ( double );
 // extern double exp ( double );
 // extern double log ( double );
 // extern double pow ( double, double );
 // extern double fabs ( double );
 // static double incbcf(double, double, double);
 // static double incbd(double, double, double);
 // static double pseries(double, double, double);
 // #else
 // double gamma(), lgam(), exp(), log(), pow(), fabs();
 // static double incbcf(), incbd(), pseries();
 // #endif
 // 
 // static double big = 4.503599627370496e15;
 // static double biginv =  2.22044604925031308085e-16;
 // 
 // 
static   df3_three_variable incbcf(const df3_three_variable & _a, const df3_three_variable & _b, const df3_three_variable & _x );
static   df3_three_variable pseries(const df3_three_variable & _a, const df3_three_variable & _b, const df3_three_variable & _x );
static  df3_three_variable incbd(const df3_three_variable & _a, const df3_three_variable & _b, const df3_three_variable & _x );

/**
 * Description not yet available.
 * \param
 */
df3_three_variable incbet(const df3_three_variable & _aa, 
   const df3_three_variable & _bb, const df3_three_variable & _xx )
 {

   df3_three_variable aa;
   df3_three_variable bb;
   df3_three_variable xx;
   aa=_aa;
   bb=_bb;
   xx=_xx;

 df3_three_variable a, b, t, x, xc, w, y;

 int flag;
 df3_three_variable one;
 df3_three_variable zero;
 one=1.0;
 zero=0.0;
 
 if( value(aa) <= 0.0 || value(bb) <= 0.0 )
 	goto domerr;
 
 if( (value(xx) <= 0.0) || ( value(xx) >= 1.0) )
 	{
 	if( value(xx) == 0.0 )
 		return(zero);
 	if( value(xx) == 1.0 )
 		return(one );
 domerr:
 	cerr <<  "incbet DOMAIN " << endl;
        
 	return( zero );
 	}
 
 flag = 0;
 if( value(bb * xx) <= 1.0 && value(xx) <= 0.95)
 	{
 	t = pseries(aa, bb, xx);
 		goto done;
 	}
 
 w = 1.0 - xx;
 
 /* Reverse a and b if x is greater than the mean. */
 if( value(xx) > (value(aa)/value(aa+bb)) )
 	{
 	flag = 1;
 	a = bb;
 	b = aa;
 	xc = xx;
 	x = w;
 	}
 else
 	{
 	a = aa;
 	b = bb;
 	xc = w;
 	x = xx;
 	}
 
 if( flag == 1 && value((b * x)) <= 1.0 && value(x) <= 0.95)
 	{
 	t = pseries(a, b, x);
 	goto done;
 	}
 
 /* Choose expansion for better convergence. */
 y = x * (a+b-2.0) - (a-1.0);
 if( value(y) < 0.0 )
 	w = incbcf( a, b, x );
 else
 	w = incbd( a, b, x ) / xc;
 
 /* Multiply w by the factor
      a      b   _             _     _
     x  (1-x)   | (a+b) / ( a | (a) | (b) ) .   */
 
 y = a * log(x);
 t = b * log(xc);
 if( value((a+b)) < MAXGAM && fabs(value(y)) < MAXLOG && fabs(value(t)) < MAXLOG )
 	{
 	t = pow(xc,b);
 	t *= pow(x,a);
 	t /= a;
 	t *= w;
 	t *= gamma(a+b) / (gamma(a) * gamma(b));
 	goto done;
 	}
 /* Resort to logarithms.  */
 y += t + lgam(a+b) - lgam(a) - lgam(b);
 y += log(w/a);
 if( value(y) < MINLOG )
 	t = 0.0;
 else
 	t = exp(y);
 
 done:
 
 if( flag == 1 )
 	{
 	if( value(t) <= MACHEP )
 		t = 1.0 - MACHEP;
 	else
 		t = 1.0 - t;
 	}
 return( t );
 }

/**
 * Continued fraction expansion number 1
 * for incomplete beta integral
 * \param
 */
  static df3_three_variable incbcf(const df3_three_variable & _a, const df3_three_variable & _b, const df3_three_variable & _x )
  {
  ADUNCONST(df3_three_variable,a) 
  ADUNCONST(df3_three_variable,b) 
  ADUNCONST(df3_three_variable,x) 
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
  	
  	xk = -( x * k1 * k2 )/( k3 * k4 );
  	pk = pkm1 +  pkm2 * xk;
  	qk = qkm1 +  qkm2 * xk;
  	pkm2 = pkm1;
  	pkm1 = pk;
  	qkm2 = qkm1;
  	qkm1 = qk;
  
  	xk = ( x * k5 * k6 )/( k7 * k8 );
  	pk = pkm1 +  pkm2 * xk;
  	qk = qkm1 +  qkm2 * xk;
  	pkm2 = pkm1;
  	pkm1 = pk;
  	qkm2 = qkm1;
  	qkm1 = qk;
  
  	if( value(qk) != 0 )
  		r = pk/qk;
  	if( value(r) != 0 )
  		{
  		t = fabs( (ans - r)/r );
  		ans = r;
  		}
  	else
  		t = 1.0;
  
  	if( value(t) < value(thresh) )
  		goto cdone;
  
  	k1 += 1.0;
  	k2 += 1.0;
  	k3 += 2.0;
  	k4 += 2.0;
  	k5 += 1.0;
  	k6 -= 1.0;
  	k7 += 2.0;
  	k8 += 2.0;
  
  	if( (value(fabs(qk)) + value(fabs(pk))) > big )
  		{
  		pkm2 *= biginv;
  		pkm1 *= biginv;
  		qkm2 *= biginv;
  		qkm1 *= biginv;
  		}
  	if( (value(fabs(qk)) < biginv) || (value(fabs(pk)) < biginv) )
  		{
  		pkm2 *= big;
  		pkm1 *= big;
  		qkm2 *= big;
  		qkm1 *= big;
  		}
  	}
  while( ++n < 300 );
  
  cdone:
  return(ans);
  }

/**
 * Continued fraction expansion number 2
 * for incomplete beta integral
 * \param
 */
 static  df3_three_variable incbd(const df3_three_variable & _a, const df3_three_variable & _b, const df3_three_variable & _x )
 {
  ADUNCONST(df3_three_variable,a) 
  ADUNCONST(df3_three_variable,b) 
  ADUNCONST(df3_three_variable,x) 
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
  z = x / (1.0-x);
  ans = 1.0;
  r = 1.0;
  n = 0;
  thresh = 3.0 * MACHEP;
  do
  	{
  	
  	xk = -( z * k1 * k2 )/( k3 * k4 );
  	pk = pkm1 +  pkm2 * xk;
  	qk = qkm1 +  qkm2 * xk;
  	pkm2 = pkm1;
  	pkm1 = pk;
  	qkm2 = qkm1;
  	qkm1 = qk;
  
  	xk = ( z * k5 * k6 )/( k7 * k8 );
  	pk = pkm1 +  pkm2 * xk;
  	qk = qkm1 +  qkm2 * xk;
  	pkm2 = pkm1;
  	pkm1 = pk;
  	qkm2 = qkm1;
  	qkm1 = qk;
  
  	if( value(qk) != 0 )
  		r = pk/qk;
  	if( value(r) != 0 )
  		{
  		t = fabs( (ans - r)/r );
  		ans = r;
  		}
  	else
  		t = 1.0;
  
  	if( value(t) < value(thresh) )
  		goto cdone;
  
  	k1 += 1.0;
  	k2 -= 1.0;
  	k3 += 2.0;
  	k4 += 2.0;
  	k5 += 1.0;
  	k6 += 1.0;
  	k7 += 2.0;
  	k8 += 2.0;
  
  	if( (value(fabs(qk)) + value(fabs(pk))) > big )
  		{
  		pkm2 *= biginv;
  		pkm1 *= biginv;
  		qkm2 *= biginv;
  		qkm1 *= biginv;
  		}
  	if( (value(fabs(qk)) < biginv) || (value(fabs(pk)) < biginv) )
  		{
  		pkm2 *= big;
  		pkm1 *= big;
  		qkm2 *= big;
  		qkm1 *= big;
  		}
  	}
  while( ++n < 300 );
  cdone:
  return(ans);
  }

/**
 * Power series for incomplete beta integral.
 * Use when b*x is small and x not too close to 1.
 * \param
 */
  df3_three_variable pseries(const df3_three_variable & _a, const df3_three_variable & _b, const df3_three_variable & _x )
 {
  df3_three_variable a; 
  df3_three_variable b; 
  df3_three_variable x; 
  a=_a;
  b=_b;
  x=_x;
 df3_three_variable s, t, u, v, n, t1, z, ai;
 
 ai = 1.0 / a;
 u = (1.0 - b) * x;
 v = u / (a + 1.0);
 t1 = v;
 t = u;
 n = 2.0;
 s = 0.0;
 z = MACHEP * ai;
 while( value(fabs(v)) > value(z) )
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
 if( value((a+b)) < MAXGAM && value(fabs(u)) < MAXLOG )
 	{
 	gamma(a+b);
        gamma(a);
        gamma(b);
        gamma(a)*gamma(b);
 	t = gamma(a+b)/(gamma(a)*gamma(b));
 	s = s * t * pow(x,a);
 	}
 else
 	{
 	t = lgam(a+b) - lgam(a) - lgam(b) + u + log(s);
 	if( value(t) < MINLOG )
 		s = 0.0;
 	else
 	s = exp(t);
 	}
 return(s);
 }

/**
 * Description not yet available.
 * \param
 */
static double get_values(double a,double b,double x)
{
   df3_three_variable va,vb,vx;
   va.initialize();
   vb.initialize();
   vx.initialize();
   va=a;
   vb=b;
   vx=x;
   *va.get_u_x()=1.0;
   *vb.get_u_y()=1.0;
   *vx.get_u_z()=1.0;
   df3_three_variable vy = replacement::incbet(va,vb,vx);
   return *vy.get_u();
}

/**
 * Description not yet available.
 * \param
 */
static df3_three_variable df3_get_values(double a,double b,double x)
{
   df3_three_variable va,vb,vx;
   va.initialize();
   vb.initialize();
   vx.initialize();
   va=a;
   vb=b;
   vx=x;
   *va.get_u_x()=1.0;
   *vb.get_u_y()=1.0;
   *vx.get_u_z()=1.0;
   df3_three_variable vy = replacement::incbet(va,vb,vx);
   return vy;
}


  //main()
  //{
  //do
  // {
  //
  //  int bd=3;
  //  int bd1=bd-1;
  //  int bd2=bd-2;
  //  int bd3=bd-3;
  //  d3_array f(-bd,bd,-bd,bd,-bd,bd);
  //  d3_array dfx(-bd1,bd1,-bd,bd,-bd,bd);
  //  d3_array dfy(-bd,bd,-bd1,bd1,-bd,bd);
  //  d3_array dfz(-bd,bd,-bd,bd,-bd1,bd1);
  //
  //  d3_array d2fxx(-bd2,bd2,-bd,bd,-bd,bd);
  //  d3_array d2fyy(-bd,bd,-bd2,bd2,-bd,bd);
  //  d3_array d2fzz(-bd,bd,-bd,bd,-bd2,bd2);
  //
  //  d3_array d2fxy(-bd1,bd1,-bd1,bd1,-bd,bd);
  //  d3_array d2fxz(-bd1,bd1,-bd,bd,-bd1,bd1);
  //  d3_array d2fyz(-bd,bd,-bd1,bd1,-bd1,bd1);
  //
  //  d3_array d3fxxy(-bd2,bd2,-bd1,bd1,-bd,bd);
  //  d3_array d3fxxz(-bd2,bd2,-bd,bd,-bd1,bd1);
  //  d3_array d3fxxx(-bd3,bd3,-bd,bd,-bd,bd);
  //  d3_array d3fxyy(-bd1,bd1,-bd2,bd2,-bd,bd);
  //  d3_array d3fyyy(-bd,bd,-bd3,bd3,-bd,bd);
  //  d3_array d3fxyz(-bd1,bd1,-bd1,bd1,-bd1,bd1);
  //  d3_array d3fyyz(-bd,bd,-bd2,bd2,-bd1,bd1);
  //  d3_array d3fyzz(-bd,bd,-bd1,bd1,-bd2,bd2);
  //  d3_array d3fxzz(-bd1,bd1,-bd,bd,-bd2,bd2);
  //  d3_array d3fzzz(-bd,bd,-bd,bd,-bd3,bd3);
  //
  //
  //  double x0=1.99; 
  //  double y0=0.4; 
  //  double z0=0.25;
  //  cout  << get_values(x0,y0,z0) << endl;
  //  double h=1.e-4;
  //  cout << "enter h" << endl;
  //  cin >> h;
  //  double h2=2*h;
  //  cout << "enter a" << endl;
  //  cin >> x0;
  //  df3_three_variable tp;
  //  df3_three_variable tm;
  //  tp=2.0+h;
  //  tm=2.0-h;
  //  cout << value(gamma(tp)-gamma(tm))/(2.0*h)<< endl;
  //
  //  int i,j,k;
  //
  //  {
  //  cout  << get_values(x0,y0,z0) << endl;
  //  ofstream ofs("ddd");
  //  for (double xx=1.9999;xx<=2.0001;xx+=.000002)
  //  {
  //    //tp=xx;
  //     ofs << xx << " " << get_values(xx,y0,z0) << endl;
  //     // cout  << get_values(x0,y0,z0) << endl;
  //  }
  //  }
  //  get_values(x0,y0,z0);
  //
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        f(i,j,k)=get_values(x0+i*h,y0+j*h,z0+k*h);
  //      }
  //    }
  //  }
  //  for (i=-bd1;i<=bd1;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        dfx(i,j,k)=(f(i+1,j,k)-f(i-1,j,k))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd1;j<=bd1;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        dfy(i,j,k)=(f(i,j+1,k)-f(i,j-1,k))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd1;k<=bd1;k++)
  //      {
  //        dfz(i,j,k)=(f(i,j,k+1)-f(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd1;i<=bd1;i++)
  //  {
  //    for (j=-bd1;j<=bd1;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        d2fxy(i,j,k)=(dfx(i,j+1,k)-dfx(i,j-1,k))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd2;i<=bd2;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        d2fxx(i,j,k)=(dfx(i+1,j,k)-dfx(i-1,j,k))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd2;j<=bd2;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        d2fyy(i,j,k)=(dfy(i,j+1,k)-dfy(i,j-1,k))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd2;k<=bd2;k++)
  //      {
  //        d2fzz(i,j,k)=(dfz(i,j,k+1)-dfz(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd1;i<=bd1;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd1;k<=bd1;k++)
  //      {
  //        d2fxz(i,j,k)=(dfx(i,j,k+1)-dfx(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //  
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd1;j<=bd1;j++)
  //    {
  //      for (k=-bd1;k<=bd1;k++)
  //      {
  //        d2fyz(i,j,k)=(dfy(i,j,k+1)-dfy(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //  
  //  for (i=-bd3;i<=bd3;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        d3fxxx(i,j,k)=(d2fxx(i+1,j,k)-d2fxx(i-1,j,k))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd2;j<=bd2;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        d2fyy(i,j,k)=(dfy(i,j+1,k)-dfy(i,j-1,k))/h2;
  //      }
  //    }
  //  }
  //  
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd3;j<=bd3;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        d3fyyy(i,j,k)=(d2fyy(i,j+1,k)-d2fyy(i,j-1,k))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd2;j<=bd2;j++)
  //    {
  //      for (k=-bd1;k<=bd1;k++)
  //      {
  //        d3fyyz(i,j,k)=(d2fyy(i,j,k+1)-d2fyy(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //
  //  for (i=-bd1;i<=bd1;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd2;k<=bd2;k++)
  //      {
  //        d3fxzz(i,j,k)=(d2fxz(i,j,k+1)-d2fxz(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd1;j<=bd1;j++)
  //    {
  //      for (k=-bd2;k<=bd2;k++)
  //      {
  //        d3fyzz(i,j,k)=(d2fyz(i,j,k+1)-d2fyz(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //
  //  for (i=-bd;i<=bd;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd3;k<=bd3;k++)
  //      {
  //        d3fzzz(i,j,k)=(d2fzz(i,j,k+1)-d2fzz(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //
  //  for (i=-bd2;i<=bd2;i++)
  //  {
  //    for (j=-bd1;j<=bd1;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        d3fxxy(i,j,k)=(d2fxx(i,j+1,k)-d2fxx(i,j-1,k))/h2;
  //      }
  //    }
  //  }
  //
  //  for (i=-bd2;i<=bd2;i++)
  //  {
  //    for (j=-bd;j<=bd;j++)
  //    {
  //      for (k=-bd1;k<=bd1;k++)
  //      {
  //        d3fxxz(i,j,k)=(d2fxx(i,j,k+1)-d2fxx(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd1;i<=bd1;i++)
  //  {
  //    for (j=-bd2;j<=bd2;j++)
  //    {
  //      for (k=-bd;k<=bd;k++)
  //      {
  //        d3fxyy(i,j,k)=(d2fyy(i+1,j,k)-d2fyy(i-1,j,k))/h2;
  //      }
  //    }
  //  }
  //  for (i=-bd1;i<=bd1;i++)
  //  {
  //    for (j=-bd1;j<=bd1;j++)
  //    {
  //      for (k=-bd1;k<=bd1;k++)
  //      {
  //        d3fxyz(i,j,k)=(d2fxy(i,j,k+1)-d2fxy(i,j,k-1))/h2;
  //      }
  //    }
  //  }
  //  df3_three_variable z3=df3_get_values(x0,y0,z0);
  //  //df3_three_variable z3= x0*y0*z0;
  //  
  //  cout << endl;
  //  
  //  cout << "dfx = " << dfx(0,0,0) << " " << *z3.get_u_x() << endl;
  //  cout << "dfy = " << dfy(0,0,0) << "  " << *z3.get_u_y()  << endl;
  //  cout << "dfz = " << dfz(0,0,0) << "  " << *z3.get_u_z()  << endl;
  //  cout << "d2fxx = " << d2fxx(0,0,0) << "  " << *z3.get_u_xx()  << endl;
  //  cout << "d2fxy = " << d2fxy(0,0,0) << "  " << *z3.get_u_xy() <<  endl;
  //  cout << "d2fxz = " << d2fxz(0,0,0) << "  " << *z3.get_u_xz() <<  endl;
  //  cout << "d2fyy = " << d2fyy(0,0,0) << "  " << *z3.get_u_yy()  << endl;
  //  cout << "d2fyz = " << d2fyz(0,0,0) << "  " << *z3.get_u_yz()  << endl;
  //  cout << "d2fzz = " << d2fzz(0,0,0) << "  " << *z3.get_u_zz()  << endl;
  //  cout << "d3fxxx = " << d3fxxx(0,0,0) << "  " << *z3.get_u_xxx()  << endl;
  //  cout << "d3fxxy = " << d3fxxy(0,0,0) << "  " << *z3.get_u_xxy()  << endl;
  //  cout << "d3fxxz = " << d3fxxz(0,0,0) << "  " << *z3.get_u_xxz()  << endl;
  //  cout << "d3fxyy = " << d3fxyy(0,0,0) << "  " << *z3.get_u_xyy()  << endl;
  // 
  //  cout << "d3fxyz = " << d3fxyz(0,0,0) << "  " << *z3.get_u_xyz()  << endl;
  //  cout << "d3fxzz = " << d3fxzz(0,0,0) << "  " << *z3.get_u_xzz()  << endl;
  //  cout << "d3fyyy = " << d3fyyy(0,0,0) << "  " << *z3.get_u_yyy()  << endl;
  //  cout << "d3fyyz = " << d3fyyz(0,0,0) << "  " << *z3.get_u_yyz()  << endl;
  //  cout << "d3fyzz = " << d3fyzz(0,0,0) << "  " << *z3.get_u_yzz()  << endl;
  //  cout << "d3fzzz = " << d3fzzz(0,0,0) << "  " << *z3.get_u_zzz()  << endl;
  //  cout << endl;
  //  cout << "f = " << f(0,0,0) << endl;
  //  cout << endl;
  // }
  // while(1);
  //  //cout << "dfx = " << dfx << endl;
  //}
}
