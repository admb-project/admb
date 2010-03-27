/*
  * $Id$
  *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <df1b2fun.h>
#include <df13fun.h>

#define ITMAX 100
#define EPS 1.0e-9
//#define EPS 3.0e-7
#define FPMIN 1.0e-30

  double MAXLOG=200;
  static double big = 4.503599627370496e15;
  static double biginv =  2.22044604925031308085e-16;
  static double MACHEP=2.22045e-16;

int sgngam = 0;
extern int sgngam;
static double MAXNUM=1.7976931348623158E+308;

extern df3_two_variable polevl (const df3_two_variable&, void *, int );
extern df3_two_variable p1evl ( const df3_two_variable& , void *, int );

double get_values(double x,double y,int print_switch);

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



df1b2variable log_negbinomial_density(double x,const df1b2variable& _xmu, 
  const df1b2variable& _xtau)
{
  ADUNCONST(df1b2variable,xmu)
  ADUNCONST(df1b2variable,xtau)
  init_df3_two_variable mu(xmu);
  init_df3_two_variable tau(xtau);
  *mu.get_u_x()=1.0;
  *tau.get_u_y()=1.0;
  if (value(tau)-1.0<0.0)
  {
    cerr << "tau <=1 in log_negbinomial_density " << endl;
    ad_exit(1);
  }
  df3_two_variable r=mu/(1.e-120+(tau-1.0));
  df3_two_variable tmp;
  tmp=gammln(x+r)-gammln(r) -gammln(x+1)
    +r*log(r)+x*log(mu)-(r+x)*log(r+mu);
  df1b2variable tmp1;
  tmp1=tmp;
  return tmp1;
}

/** Log gamma function.
    \param xx \f$x\f$
    \return \f$\ln\bigr(\Gamma(x)\bigl)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
df3_two_variable gammln(const df3_two_variable& xx)
{
  df3_two_variable x,tmp,ser,tmp1;
  static double cof[6]={76.18009173,-86.50532033,24.01409822,
    -1.231739516,0.120858003e-2,-0.536382e-5};
  int j;
  x=xx-1.0;
  tmp=x+5.5;
  tmp -= (x+0.5)*log(tmp);
  ser=1.0;
  for (j=0;j<=5;j++) 
  {
    x += 1.0;
    ser += cof[j]/x;
  }
  return -tmp+log(2.50662827465*ser);
}


/** Incomplete gamma function.
    Continued fraction approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
/*
void gcf(const df3_two_variable& _gammcf,const df3_two_variable& a,
  const df3_two_variable& x,const df3_two_variable& _gln)
{
  ADUNCONST(df3_two_variable,gln)
  ADUNCONST(df3_two_variable,gammcf)
  int i;
  df3_two_variable an,b,c,d,del,h;

  gln=gammln(a);
  b=x+1.0-a;
  c=1.0/FPMIN;
  d=1.0/b;
  h=d;
  for (i=1;i<=ITMAX;i++) {
    an = -i*(i-a);
    b += 2.0;
    d=an*d+b;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    c=b+an/c;
    if (fabs(value(c)) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(value(del)-1.0) < EPS) break;
  }
  if (i > ITMAX) 
    cerr << "a too large, ITMAX too small in gcf" << endl;
  gammcf=exp(-x+a*log(x)-(gln))*h;
}
*/
/** Incomplete gamma function.
    Continued fraction approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
/*
void gser(const df3_two_variable& _gamser,const df3_two_variable& a,
  const df3_two_variable& x,const df3_two_variable& _gln)
{
  int n;
  ADUNCONST(df3_two_variable,gln)
  ADUNCONST(df3_two_variable,gamser)
  df3_two_variable sum,del,ap;

  gln=gammln(a);

  if (value(x) <= 0.0) {
    if (value(x) < 0.0) 
      cerr << "x less than 0 in routine gser" << endl;
    gamser=0.0;
    return;
  } 
  else 
  {
    ap=a;
    del=sum=1.0/a;
    for (n=1;n<=ITMAX;n++) {
      ap+=1.0;
      del *= x/ap;
      sum += del;
      if (fabs(value(del)) < fabs(value(sum))*EPS) {
        gamser=sum*exp(-x+a*log(x)-(gln));
        return;
      }
    }
    cerr << "a too large, ITMAX too small in routine gser" << endl;
    return;
  }
}
*/

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

int operator < (const df3_two_variable& x,double n) { return value(x) < n; }
int operator > (const df3_two_variable& x,double n) { return value(x) > n; }
int operator >= (const df3_two_variable& x,double n) { return value(x) >= n; }
int operator == (const df3_two_variable& x,const df3_two_variable& n) { return value(x)==value(n); }
int operator == (const df3_two_variable& x,double n) { return value(x)==n; }
int operator == (double x,const df3_two_variable& n) { return x==value(n); }
int operator < (const df3_two_variable& x,const df3_two_variable& n) { return value(x)<value(n); }
int operator > (const df3_two_variable& x,const df3_two_variable& n) { return value(x)>value(n); }

df3_two_variable lgam(df3_two_variable& x) //Worry about htis too!
{

df3_two_variable  p,q, u, w, z,p1;
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
	w = lgam(q); // note this modifies sgngam! 
	p = floor(value(q));
	if( p == q )
		{
lgsing:
#ifdef INFINITIES
		mtherr( "lgam", SING );
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
//	z = log(PI) - log( z ) - w;
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
	mtherr( "lgam", OVERFLOW );
	df3_two_variable tmp;
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


df3_two_variable polevl( const df3_two_variable&  x, void * _coef, int N )
{
double * coef=(double *)(_coef);
df3_two_variable  ans;
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

 
df3_two_variable p1evl(const df3_two_variable & x, void * _coef, int N )
{
double * coef= (double*)(_coef);
df3_two_variable ans;
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

int mtherr(char* s,int n){ /*ad_exit(1);*/  return 0;}


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

df3_two_variable igam(const df3_two_variable & _a, const df3_two_variable & _x );

df3_two_variable igamc(const df3_two_variable & _a, const df3_two_variable & _x)
{
     ADUNCONST(df3_two_variable,a)
     ADUNCONST(df3_two_variable,x)
   df3_two_variable ans, ax, c, yc, r, t, y, z;
   df3_two_variable pk, pkm1, pkm2, qk, qkm1, qkm2;

   if( (value(x) <= 0) || ( value(a) <= 0) )
   {
     df3_two_variable tmp;
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

   // continued fraction 
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


   df3_two_variable igam(const df3_two_variable & _a, 
    const df3_two_variable & _x )
   {
      ADUNCONST(df3_two_variable,a)
      ADUNCONST(df3_two_variable,x)

   df3_two_variable ans, ax, c, r;

   if( (value(x) <= 0) || ( value(a) <= 0) )
   {
     df3_two_variable tmp;
     tmp=0.0;
     return(tmp);
   }

   if( (value(x) > 1.0) && (value(x) > value(a) ) )
   	return( 1.0 - igamc(a,x) );

   // Compute  x**a * exp(-x) / gamma(a)
   ax = a * log(x) - x - lgam(a);

   if( value(ax) < -MAXLOG )
   	{
   	 cerr <<  "igam UNDERFLOW " << endl;
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
   	c *= x/r;
   	ans += c;
   	}
   while( c/ans > MACHEP );
   
   return( ans * ax/a );
   }

df3_two_variable cumd_gamma(const df3_two_variable& x,
  const df3_two_variable& a)
{
  //ADUNCONST(df3_two_variable, a)
  //ADUNCONST(df3_two_variable, x)

  df3_two_variable gamma = igam(a,x);
  return (gamma);
  /*
  df3_two_variable gamser,gammcf,gln;

  if (value(x) < 0.0 || value(a) <= 0.0) 
    cerr << "Invalid arguments in routine gammp" << endl;
  if (value(x) < (value(a)+1.0)) {
    gser(gamser,a,x,gln);
    return gamser;
  } else {
    gcf(gammcf,a,x,gln);
    return 1.0-gammcf;
  }
  */
}
df3_two_variable cumd_exponential(const df3_two_variable& x,
  const df3_two_variable& a)
{
  df3_two_variable tmp;
  if (value(x)<=0)
    return 0.5*exp(x);
  else
    return 1.0-0.5*exp(-x);
}
df3_two_variable cumd_cauchy(const df3_two_variable& x,const df3_two_variable& a)
{
  return atan(x/a);
}
