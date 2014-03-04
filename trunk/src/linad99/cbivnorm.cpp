/*
 * $Id$
 *
 * Authors: Alan Genz and Yihong Ge
 * Copyright (c) 2009-2012 ADMB foundation
 *
 * Ported to C++ and extensively modified by David Fournier
 */
/**
 * \file
 * Description not yet available.
 */
/* t.f -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
    -lf2c -lm   (in that order)
*/
#include <fvar.hpp>
//#include <fstream.h>
#ifdef __cplusplus
extern "C" {
#endif

/* f2c.h  --  Standard Fortran to C header file */

/**  barf  [ba:rf]  2.  "He suggested using FORTRAN, and everybody barfed."

    - From The Shogakukan DICTIONARY OF NEW ENGLISH (Second edition) */

#ifndef F2C_INCLUDE
#define F2C_INCLUDE

#if defined(USE_DDOUBLE)
# define doublereal dd_real
#endif
typedef long int integer;
typedef unsigned long int uinteger;
//typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
typedef long int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;
#ifdef INTEGER_STAR_8    /* Adjust for integer*8. */
typedef long long longint;        /* system-dependent */
typedef unsigned long long ulongint;    /* system-dependent */
#define qbit_clear(a,b)    ((a) & ~((ulongint)1 << (b)))
#define qbit_set(a,b)    ((a) |  ((ulongint)1 << (b)))
#endif

#define TRUE_ (1)
#define FALSE_ (0)

/* Extern is for use with -E */
#ifndef Extern
#define Extern extern
#endif

/* I/O stuff */

#ifdef f2c_i2
/* for -i2 */
typedef short flag;
typedef short ftnlen;
typedef short ftnint;
#else
typedef long int flag;
typedef long int ftnlen;
typedef long int ftnint;
#endif

/*external read, write*/
typedef struct
{
    flag cierr;
    ftnint ciunit;
    flag ciend;
    char *cifmt;
    ftnint cirec;
} cilist;

/*internal read, write*/
typedef struct
{
    flag icierr;
    char *iciunit;
    flag iciend;
    char *icifmt;
    ftnint icirlen;
    ftnint icirnum;
} icilist;

/*open*/
typedef struct
{
    flag oerr;
    ftnint ounit;
    char *ofnm;
    ftnlen ofnmlen;
    char *osta;
    char *oacc;
    char *ofm;
    ftnint orl;
    char *oblnk;
} olist;

/*close*/
typedef struct
{
    flag cerr;
    ftnint cunit;
    char *csta;
} cllist;

/*rewind, backspace, endfile*/
typedef struct
{
    flag aerr;
    ftnint aunit;
} alist;

/* inquire */
typedef struct
{
    flag inerr;
    ftnint inunit;
    char *infile;
    ftnlen infilen;
    ftnint    *inex;    /*parameters in standard's order*/
    ftnint    *inopen;
    ftnint    *innum;
    ftnint    *innamed;
    char    *inname;
    ftnlen    innamlen;
    char    *inacc;
    ftnlen    inacclen;
    char    *inseq;
    ftnlen    inseqlen;
    char     *indir;
    ftnlen    indirlen;
    char    *infmt;
    ftnlen    infmtlen;
    char    *inform;
    ftnint    informlen;
    char    *inunf;
    ftnlen    inunflen;
    ftnint    *inrecl;
    ftnint    *innrec;
    char    *inblank;
    ftnlen    inblanklen;
} inlist;

#define VOID void
 //
 //
 // union Multitype {    /* for multiple entry points */
 //     integer1 g;
 //     shortint h;
 //     integer i;
 //     /* longint j; */
 //     real r;
 //     doublereal d;
 //     complex c;
 //     doublecomplex z;
 //     };
 //
 // typedef union Multitype Multitype;
 //

/*typedef long int Long;*/    /* No longer used; formerly in Namelist */

struct Vardesc {    /* for Namelist */
    char *name;
    char *addr;
    ftnlen *dims;
    int  type;
    };
typedef struct Vardesc Vardesc;

struct Namelist {
    char *name;
    Vardesc **vars;
    int nvars;
    };
typedef struct Namelist Namelist;

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define dabs(x) (doublereal)abs(x)
#define min(a,b) ((a) <= (b) ? (a) : (b))
#define max(a,b) ((a) >= (b) ? (a) : (b))
#define dmin(a,b) (doublereal)min(a,b)
#define dmax(a,b) (doublereal)max(a,b)
#define bit_test(a,b)    ((a) >> (b) & 1)
#define bit_clear(a,b)    ((a) & ~((uinteger)1 << (b)))
#define bit_set(a,b)    ((a) |  ((uinteger)1 << (b)))

/* procedure parameter types for -A and -C++ */

#define F2C_proc_par_types 1
#ifdef __cplusplus
typedef int /* Unknown procedure type */ (*U_fp)(...);
typedef shortint (*J_fp)(...);
typedef integer (*I_fp)(...);
typedef real (*R_fp)(...);
typedef doublereal (*D_fp)(...), (*E_fp)(...);
typedef /* Complex */ VOID (*C_fp)(...);
typedef /* Double Complex */ VOID (*Z_fp)(...);
typedef logical (*L_fp)(...);
typedef shortlogical (*K_fp)(...);
typedef /* Character */ VOID (*H_fp)(...);
typedef /* Subroutine */ int (*S_fp)(...);
#else
typedef int /* Unknown procedure type */ (*U_fp)();
typedef shortint (*J_fp)();
typedef integer (*I_fp)();
typedef real (*R_fp)();
typedef doublereal (*D_fp)(), (*E_fp)();
typedef /* Complex */ VOID (*C_fp)();
typedef /* Double Complex */ VOID (*Z_fp)();
typedef logical (*L_fp)();
typedef shortlogical (*K_fp)();
typedef /* Character */ VOID (*H_fp)();
typedef /* Subroutine */ int (*S_fp)();
#endif
/* E_fp is for real functions when -R is not specified */
typedef VOID C_f;    /* complex function */
typedef VOID H_f;    /* character function */
typedef VOID Z_f;    /* double complex function */
typedef doublereal E_f;    /* real function with -R not specified */

/* undef any lower-case symbols that your C compiler predefines, e.g.: */

#ifndef Skip_f2c_Undefs
#undef cray
#undef gcos
#undef mc68010
#undef mc68020
#undef mips
#undef pdp11
#undef sgi
#undef sparc
#undef sun
#undef sun2
#undef sun3
#undef sun4
#undef u370
#undef u3b
#undef u3b2
#undef u3b5
#undef unix
#undef vax
#endif
#endif
double cmvbvu_(const double *sh,const  double *sk,
  const double  *r__);

#ifdef __cplusplus
}
#endif

/** Cumulative bivariate normal distribution.
  Assumes two distributions X and Y both N(0,1).
  \param x Upper limit of inetegration on X.
  \param y Upper limit of inetegration on Y
  \param rho correlation coefficient.
  \return Probability that X is larger than x; and Y is larger than y
*/
double cumbvn(const double& x,const double& y,const double& rho)
{
  RETURN_ARRAYS_INCREMENT();
  double retval;
  double mx=-x;
  double my=-y;
  retval=cmvbvu_(&mx,&my,&rho);
  RETURN_ARRAYS_DECREMENT();
  return retval;
}

/** Cumulative bivariate normal distribution.
  Assumes two distributions X and Y both N(0,1).
  \param xl Lower limit of inetegration on X.
  \param yl Lower limit of inetegration on Y.
  \param xu Upper limit of inetegration on X.
  \param yu Upper limit of inetegration on Y.
  \param rho correlation coefficient.
  \return Probability that X is between xl and xu and Y is between yl and yu
*/
double cumbvn(const double& xl,const double& yl,
  const double& xu,const double& yu,const double& rho)
{
  RETURN_ARRAYS_INCREMENT();
  double my=cumbvn(xl,yl,rho);
  my+=cumbvn(xu,yu,rho);
  my-=cumbvn(xl,yu,rho);
  my-=cumbvn(xu,yl,rho);
  RETURN_ARRAYS_DECREMENT();
  return my;
}

#ifdef __cplusplus
extern "C" {
#endif
/* BVN - calculate the probability that X is larger than SH and Y is */
/*       larger than SK. */
double cmvbvu_(const double *sh,const double *sk,const double *r__)
{
  RETURN_ARRAYS_INCREMENT();
    /* Initialized data */

    static struct {
    doublereal e_1[3];
    doublereal fill_2[7];
    doublereal e_3[6];
    doublereal fill_4[4];
    doublereal e_5[10];
    } equiv_21 = { {.1713244923791705, .3607615730481384,
        .4679139345726904}, {0, 0, 0, 0, 0, 0, 0},
        {.04717533638651177, .1069393259953183,
         .1600783285433464, .2031674267230659, .2334925365383547,
        .2491470458134029}, {0, 0, 0, 0}, {.01761400713915212,
        .04060142980038694, .06267204833410906, .08327674157670475,
        .1019301198172404, .1181945319615184, .1316886384491766,
        .1420961093183821, .1491729864726037, .1527533871307259}};

#define w ((doublereal *)&equiv_21)

    static struct {
    doublereal e_1[3];
    doublereal fill_2[7];
    doublereal e_3[6];
    doublereal fill_4[4];
    doublereal e_5[10];
    } equiv_22 = { {-.9324695142031522, -.6612093864662647,
        -.238619186083197}, {0, 0, 0, 0, 0, 0, 0}, {-.9815606342467191,
        -.904117256370475,
         -.769902674194305, -.5873179542866171, -.3678314989981802,
        -.1252334085114692}, {0, 0, 0, 0}, {-.9931285991850949,
        -.9639719272779138, -.9122344282513259, -.8391169718222188,
        -.7463319064601508, -.636053680726515, -.5108670019508271,
        -.3737060887154196, -.2277858511416451, -.07652652113349733}};

#define x ((doublereal *)&equiv_22)


    /* System generated locals */
    integer i__1;
    double  ret_val, d__1, d__2,d__3,d__4;

    /* Builtin functions */
    //double asin(doublereal), sin(doublereal), exp(doublereal), sqrt(
//        doublereal);

    /* Local variables */
    static double  a, b, c__, d__, h__;
    static integer i__;
    //static doublereal k;
    static double k;
    extern double cmvphi_(double *);
    static integer lg;
    //static doublereal as;
    static double as;
    static integer ng;
    static double  bs,rs,xs;
    static double hs, hk, sn, asr, bvn;


/*     A function for computing bivariate normal probabilities; */
/*       developed using */
/*         Drezner, Z. and Wesolowsky, G. O. (1989), */
/*         On the Computation of the Bivariate Normal Integral, */
/*         J. Stat. Comput. Simul.. 35 pp. 101-107. */
/*       with extensive modications for double precisions by */
/*         Alan Genz and Yihong Ge */
/*         Department of Mathematics */
/*         Washington State University */
/*         Pullman, WA 99164-3113 */
/*         Email : alangenz@wsu.edu */

/* BVN - calculate the probability that X is larger than SH and Y is */
/*       larger than SK. */

/* Parameters */

/*   SH  REAL, integration limit */
/*   SK  REAL, integration limit */
/*   R   REAL, correlation coefficient */
/*   LG  INTEGER, number of Gauss Rule Points and Weights */

/*     Gauss Legendre Points and Weights, N =  6 */
/*     Gauss Legendre Points and Weights, N = 12 */
/*     Gauss Legendre Points and Weights, N = 20 */
    if (abs(*r__) < (float).3) {
        ng = 1;
        lg = 3;
    } else if (abs(*r__) < (float).75) {
        ng = 2;
        lg = 6;
    } else {
        ng = 3;
        lg = 10;
    }
    h__ = *sh;
    k = *sk;
    hk = h__ * k;
    bvn = 0.;
    if (abs(*r__) < (float).925) {
    hs = (h__ * h__ + k * k) / 2;
    asr = asin(*r__);
    i__1 = lg;
    for (i__ = 1; i__ <= i__1; ++i__) {
        sn = sin(asr * (x[i__ + ng * 10 - 11] + 1) / 2);
        bvn += w[i__ + ng * 10 - 11] * exp((sn * hk - hs) / (1 - sn * sn));
        sn = sin(asr * (-x[i__ + ng * 10 - 11] + 1) / 2);
        bvn += w[i__ + ng * 10 - 11] * exp((sn * hk - hs) / (1 - sn * sn));
    }
    d__1 = -h__;
    d__2 = -k;
    bvn = bvn * asr / 12.566370614359172 + cmvphi_(&d__1) * cmvphi_(&d__2);
    } else {
        if (*r__ < 0.) {
            k = -k;
            hk = -hk;
        }
        if (abs(*r__) < 1.) {
            as = (1 - *r__) * (*r__ + 1);
            a = sqrt(as);
/* Computing 2nd power */
            d__1 = h__ - k;
            bs = d__1 * d__1;
            c__ = (4 - hk) / 8;
            d__ = (12 - hk) / 16;
            bvn = a * exp(-(bs / as + hk) / 2) * (1 - c__ * (bs - as) * (1 -
                d__ * bs / 5) / 3 + c__ * d__ * as * as / 5);
            if (hk > -160.) {
                b = sqrt(bs);
                d__1 = -b / a;
                bvn -= exp(-hk / 2) * sqrt(6.283185307179586) * cmvphi_(&d__1)
                * b * (1 - c__ * bs * (1 - d__ * bs / 5) / 3);
            }
            a /= 2;
            i__1 = lg;
            for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing 2nd power */
                d__1 = a * (x[i__ + ng * 10 - 11] + 1);
                xs = d__1 * d__1;
                rs = sqrt(1 - xs);
                bvn += a * w[i__ + ng * 10 - 11] * (exp(-bs / (xs * 2) - hk /
                    (rs + 1)) / rs - exp(-(bs / xs + hk) / 2) * (c__ * xs
                    * (d__ * xs + 1) + 1));
/* Computing 2nd power */
                d__1 = -x[i__ + ng * 10 - 11] + 1;
                xs = as * (d__1 * d__1) / 4;
                rs = sqrt(1 - xs);
                bvn += a * w[i__ + ng * 10 - 11] * exp(-(bs / xs + hk) / 2) *
                    (exp(-hk * (1 - rs) / ((rs + 1) * 2)) / rs - (c__ *
                    xs * (d__ * xs + 1) + 1));
            }
            bvn = -bvn / 6.283185307179586;
        }
        if (*r__ > 0.) {
            d__1 = -max(h__,k);
            bvn += cmvphi_(&d__1);
        }
        if (*r__ < 0.) {
/* Computing MAX */
            d__3 = -h__;
            d__4 = -k;
            d__1 = 0., d__2 = cmvphi_(&d__3) - cmvphi_(&d__4);
            bvn = -bvn + max(d__1,d__2);
        }
    }
    ret_val = bvn;
    RETURN_ARRAYS_DECREMENT();
    return ret_val;
} /* cmvbvu_ */

#undef x
#undef w

double cmvphi_(double *z__)
{
  RETURN_ARRAYS_INCREMENT();
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
#if !defined(USE_DDOUBLE)
    double exp(doublereal);
#endif

    /* Local variables */
    static doublereal zabs, p, expntl;


/*     Normal distribution probabilities accurate to 1.e-15. */
/*     Z = no. of standard deviations from the mean. */

/*     Based upon algorithm 5666 for the error function, from: */
/*     Hart, J.F. et al, 'Computer Approximations', Wiley 1968 */

/*     Programmer: Alan Miller */

/*     Latest revision - 30 March 1986 */


    zabs = abs(*z__);

/*     |Z| > 37 */

    if (zabs > 37.) {
        p = 0.;
    } else {
/*     |Z| <= 37 */

/* Computing 2nd power */
    d__1 = zabs;
    expntl = exp(-(d__1 * d__1) / 2);

/*     |Z| < CUTOFF = 10/SQRT(2) */

        if (zabs < 7.071067811865475) {
            p = expntl * ((((((zabs * .03526249659989109 + .7003830644436881)
                * zabs + 6.37396220353165) * zabs + 33.912866078383) *
                zabs + 112.0792914978709) * zabs + 221.2135961699311) *
                zabs + 220.2068679123761) / (((((((zabs *
                .08838834764831844 + 1.755667163182642) * zabs +
                16.06417757920695) * zabs + 86.78073220294608) * zabs +
                296.5642487796737) * zabs + 637.3336333788311) * zabs +
                793.8265125199484) * zabs + 440.4137358247522);

/*     |Z| >= CUTOFF. */

        } else {
            p = expntl / (zabs + 1 / (zabs + 2 / (zabs + 3 / (zabs + 4 / (
                zabs + .65))))) / 2.506628274631001;
        }
    }
    if (*z__ > 0.) {
        p = 1 - p;
    }
    ret_val = p;
    RETURN_ARRAYS_DECREMENT();
    return ret_val;
} /* cmvphi_ */

#ifdef __cplusplus
}
#endif
