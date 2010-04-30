/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>
#include "mconf.h"
#define ITMAX 100
#define EPS 1.e-9
#define FPMIN 1.0e-30
#ifdef INFINITIES
#undef INFINITIES
#endif
#ifdef NANS
#undef NANS
#endif

#define MAXGAM 171.624376956302725
//void gcf(double& gammcf,double a,double x,double &gln);
//void gser(double& gamser,double a,double x,double& gln);

static double MAXLOG=200;//
static double big = 4.503599627370496e15;
static double biginv =  2.22044604925031308085e-16;
static double MACHEP=2.22045e-16;
static int sgngam = 0;
static double MAXNUM=1.7976931348623158E+308;
static double LOGPI = 1.14472988584940017414;
static double PI = 3.14159265358979323844;

double polevl( double x, void * _coef, int N );
double p1evl( double x, void * _coef, int N );

double igam(const double & a, const double & x );
double igamc(const double & a, const double & x);

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
// 1.00000000000000000000E0,
-3.51815701436523470549E2,
-1.70642106651881159223E4,
-2.20528590553854454839E5,
-1.13933444367982507207E6,
-2.53252307177582951285E6,
-2.01889141433532773231E6
};
// log( sqrt( 2*pi ) )
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
//0040200,0000000,0000000,0000000
0142257,0164150,0163630,0112622,
0143605,0050153,0156116,0135272,
0144527,0056045,0145642,0062332,
0145213,0012063,0106250,0001025,
0145432,0111254,0044577,0115142,
0145366,0071133,0050217,0005122
};
// log( sqrt( 2*pi ) )
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
//0x0000,0x0000,0x0000,0x3ff0,
0x12b2,0x1cf3,0xfd0d,0xc075,
0xd757,0x7b89,0xaa0d,0xc0d0,
0x4c9b,0xb974,0xeb84,0xc10a,
0x0043,0x7195,0x6286,0xc131,
0xf34c,0x892f,0x5255,0xc143,
0xe14a,0x6a11,0xce4b,0xc13e
};
// log( sqrt( 2*pi ) )
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
// log( sqrt( 2*pi ) )
static unsigned short LS2P[] = {
0x3fed,0x67f1,0xc864,0xbeb5
};
#define LS2PI *(double *)LS2P
#define MAXLGM 2.556348e305
#endif

//int mtherr(char* s,int n){ /*ad_exit(1);*/  return 0;}

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
double lgam(double x)
{
double p, q, u, w, z;
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
	p = floor(q);
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
	i = p;
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
		{

		return( log(z) );

		}
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
	return( sgngam * MAXNUM );
#endif
	}

q = ( x - 0.5 ) * log(x) - x + LS2PI;
if( x > 1.0e8 ){
	return( q );
	}
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


double polevl( double  x, void * _coef, int N )
{
double * coef=(double *)(_coef);
double  ans;
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
/**
 * Evaluate polynomial when coefficient of \f$x^N\f$  is \f$1.0\f$.
 * Otherwise same as polevl.
 * Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */


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


/**
 * Complemented incomplete gamma integral.
 * The function is defined by:
 * igamc(a,x) = \f$1-\f$ igam(a,x) \f$ = \frac{1}{\Gamma(a)}\int_{x}^{\infty}e^{-t}t^{a-1}dt \f$.
 * Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
double igamc(const double & a, const double & x)
   {
     //ADUNCONST(df1_two_variable,a)
     //ADUNCONST(df1_two_variable,x)
   double ans, ax, c, yc, r, t, y, z;
   double pk, pkm1, pkm2, qk, qkm1, qkm2;
   
   if( (x <= 0) || ( a <= 0) )
   {
     double tmp;
     tmp=0.0;
     return(tmp);
   }
   
   if( (x < 1.0) || (x < a )){
   	return( 1.0 - igam(a,x) ); }
   
   ax = a * log(x) - x - lgam(a);
   if( ax < -MAXLOG )
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
   	if( qk != 0 )
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
   	if( fabs(pk) > big )
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

/**
 * Incomplete gamma integral.
 * The function is defined by
 * igam(a,x)\f$ = \frac{1}{\Gamma(a)}\int_{0}^{x}e^{-t}t^{a-1}dt \f$.
 * Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
double igam(const double & a, const double & x )
   {
      //ADUNCONST(df1_two_variable,a)
      //ADUNCONST(df1_two_variable,x)

   double ans, ax, c, r;
   
   if( (x <= 0) || ( a <= 0) )
   {
     double tmp;
     tmp=0.0;
     return(tmp);
   }
   
   if( (x > 1.0) && (x > a ) )
   	return( 1.0 - igamc(a,x) );
   
   // Compute  x**a * exp(-x) / gamma(a)
   ax = a * log(x) - x - lgam(a);
   if( ax < -MAXLOG )
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


double gammp(double a,double x)
{
  return igam(a,x);
}

/*
double gammp(double a,double x)
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

double cumd_gamma(double x,double a)
{
  return igam(a,x);
}

/*
double cumd_gamma(double x,double a)
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

/** Incomplete gamma function.
    Continued fraction approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
/*void gcf(double& gammcf,double a,double x,double &gln)
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
}*/

/** Incomplete gamma function.
    Series approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
/*void gser(double& gamser,double a,double x,double& gln)
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
}*/

double get_initial_u(double a,double y);

double Sn(double x,double a);

double inv_cumd_gamma(double y,double a)
{
  if (a<0.05)
  {
    cerr << "a musdt be > 0.1" << endl;
    ad_exit(1);
  }
  double u=get_initial_u(a,y);
  double h;
  do
  {
    double z=gammp(a,a*exp(u));
    double d=y-z;
    //cout << d << endl;
    double log_fprime=a*log(a)+a*(u-exp(u)) -gammln(a);
    double fprime=exp(log_fprime);
    h=d/fprime;
    u+=h;
  }
  while(fabs(h)>1.e-12);
  double x=a*exp(u);
  return x;
}

#undef ITMAX
#undef EPS

double Sn(double x,double a)
{
  int i=1;
  double xp=x;
  double prod=1.0;
  double summ=1.0;
  double summand;
  do
  {
    prod*=(a+i);
    summand=xp/prod;
    if (summand<1.e-4) break;
    summ+=summand;
    i++;
    if (i>50)
    {
      cerr << "convergence error" << endl;
      ad_exit(1);
    }
  } 
  while(1);
  return summ;
}
    
    

double get_initial_u(double a,double y)
{
  const double c=0.57721;
  // note that P = y;
  double logP=log(y);
  double logQ=log(1-y);
  double logB=logQ+gammln(a);
  double x0=1.e+100;
  double log_x0=1.e+100;

  if (a<1.0)
  {
    if ( logB>log(.6) || (logB > log(.45) && a>=.3) )
    {
      double logu;
      if (logB+logQ > log(1.e-8))
      {
        logu=(logP+gammln(1.0+a))/a;
      }
      else
      {
        logu=-exp(logQ)/a -c;
      }
      double u=exp(logu);
      x0=u/(1-u/(1.0+a));
      double tmp=log(1-u/(1.0+a));
      log_x0=logu;
      log_x0-=tmp;
    }
    else if ( a<.3 && log(.35) <= logB && logB <= log(.6) )
    {
      double t=exp(-c-exp(logB));
      double logt=-c-exp(logB);
      double u=t*exp(t);
      x0=t*exp(u);
      log_x0=logt+u;
    }
    else if ( (log(.15)<=logB && logB <=log(.35)) ||
       ((log(.15)<=logB && logB <=log(.45)) && a>=.3) )
    {
      double y=-logB;
      double v=y-(1-a)*log(y);
      x0=y-(1-a)*log(v)-log(1+(1.0-a)/(1.0+v));  
      log_x0=log(x0);
    }
    else if (log(.01)<logB && logB < log(.15))
    {
      double y=-logB;
      double v=y-(1-a)*log(y);
      x0=y-(1-a)*log(v)-log((v*v+2*(3-a)*v+(2-a)*(3-a))/(v*v +(5-a)*v+2));
      log_x0=log(x0);
    }
    else if (logB < log(.01))
    {
      double y=-logB;
      double v=y-(1-a)*log(y);
      x0=y-(1-a)*log(v)-log((v*v+2*(3-a)*v+(2-a)*(3-a))/(v*v +(5-a)*v+2));
      log_x0=log(x0);
    }
    else
    {
      cerr << "this can't happen" << endl;
      ad_exit(1);
    }
  }
  else  if (a>=1.0) 
  {
    const double a0 = 3.31125922108741;
    const double b1 = 6.61053765625462;
    const double a1 = 11.6616720288968;
    const double b2 = 6.40691597760039;
    const double a2 = 4.28342155967104;
    const double b3 = 1.27364489782223;
    const double a3 = .213623493715853;
    const double b4 = .03611708101884203;
  
    int sgn=1;
    double logtau;
    if (logP< log(0.5))
    {
      logtau=logP;
      sgn=-1;
    }
    else
    {
      logtau=logQ;
      sgn=1;
    }
  
    double t=sqrt(-2.0*logtau);
  
  
    double num = (((a3*t+a2)*t+a1)*t)+a0;
    double den = ((((b4*t+b3)*t+b2)*t)+b1)*t+1;
    double s=sgn*(t-num/den);
    double s2=s*s;
    double s3=s2*s;
    double s4=s3*s;
    double s5=s4*s;
    double roota=sqrt(a);
    double w=a+s*roota+(s2-1)/3.0+(s3-7.0*s)/(36.*roota)
      -(3.0*s4+7.0*s2-16)/(810.0*a)
      +(9.0*s5+256.0*s3-433.0*s)/(38880.0*a*roota);
    if (logP< log(0.5))
    {
      if (w>.15*(a+1))
      {
        x0=w;
      }
      else
      {
        double v=logP+gammln(a+1);
        double u1=exp(v+w)/a;
        double S1=1+u1/(a+1);
        double u2=exp((v+u1-log(S1))/a);
        double S2=1+u2/(a+1)+u2*u2/((a+1)*(a+2));
        double u3=exp((v+u2-log(S2))/a);
        double S3=1+u3/(a+1)+u3*u3/((a+1)*(a+2))
         + u3*u3*u3/((a+1)*(a+2)*(a+3));
        double z=exp((v+u3-log(S3))/a);
        if (z<.002*(a+1.0))
        {
          x0=z;
        }
        else
        {
          double sn=Sn(z,a);
          double zbar=exp((v+z-log(sn))/a);
          x0=zbar*(1.0-(a*log(zbar)-zbar-v+log(sn))/(a-zbar));
        }
       
      }
      log_x0=log(x0);
    }
    else
    {
      double u = -logB +(a-1.0)*log(w)-log(1.0+(1.0-a)/(1+w));
      x0=u;
      log_x0=log(x0);
    }
  }
  if (a==1.0)
  {
    x0=-log(1.0-y);
    log_x0=log(x0);
  }
  return log_x0-log(a);
}

