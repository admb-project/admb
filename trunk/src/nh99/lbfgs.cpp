/*
 * $Id$
 *
 * Author: Jorge Nodecal
 * Copyright (c) 2009-2012 ADMB Foundation
 *
 * License: Public domain
 * Translated from fortran and extensively modified for compliance with
 * ADMB.
 */
/**
 * \file
 * Description not yet available.
 */
/* lbfgs.f -- translated by f2c (version 19950110).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

#ifdef __cplusplus
extern "C" {
#endif

/* f2c.h  --  Standard Fortran to C header file */

/**  barf  [ba:rf]  2.  "He suggested using FORTRAN, and everybody barfed."

- From The Shogakukan DICTIONARY OF NEW ENGLISH (Second edition) */

#ifndef F2C_INCLUDE
#define F2C_INCLUDE

typedef long int integer;
typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
typedef long int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;
/* typedef long long longint; */ /* system-dependent */

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
  ftnint *inex;/*parameters in standard's order*/
  ftnint *inopen;
  ftnint *innum;
  ftnint *innamed;
  char *inname;
  ftnlen innamlen;
  char *inacc;
  ftnlen inacclen;
  char *inseq;
  ftnlen inseqlen;
  char *indir;
  ftnlen indirlen;
  char *infmt;
  ftnlen infmtlen;
  char *inform;
  ftnint informlen;
  char *inunf;
  ftnlen inunflen;
  ftnint *inrecl;
  ftnint *innrec;
  char *inblank;
  ftnlen inblanklen;
} inlist;

#define VOID void

union Multitype {/* for multiple entry points */
  integer1 g;
  shortint h;
  integer i;
  /* longint j; */
  real r;
  doublereal d;
  complex c;
  doublecomplex z;
};

typedef union Multitype Multitype;

/*typedef long int Long;*//* No longer used; formerly in Namelist */

struct Vardesc {/* for Namelist */
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
typedef VOID C_f;/* complex function */
typedef VOID H_f;/* character function */
typedef VOID Z_f;/* double complex function */
typedef doublereal E_f;/* real function with -R not specified */

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
/* Common Block Declarations */

struct lb3_1_ {
    integer mp, lp;
    doublereal gtol, stpmin, stpmax;
};

#define lb3_1 (*(struct lb3_1_ *) &lb3_)

/* Initialized data */

struct {
    integer e_1[2];
    doublereal e_2[3];
    } lb3_ = { {6, 6}, {.9, 1e-20, 1e20}};


/* Table of constant values */

static integer c__1 = 1;

/*    ----------------------------------------------------------------------*/
/*     This file contains the LBFGS algorithm and supporting routines */

/*     **************** */
/*     LBFGS SUBROUTINE */
/*     **************** */

/* Subroutine */ int lbfgs_(integer *n, integer *m, doublereal *x, doublereal
        *f, doublereal *g, logical *diagco, doublereal *diag, integer *iprint,
         doublereal *eps, doublereal *xtol, doublereal *w, integer *iflag,
   integer* iter, integer * info)
{
    /* Initialized data */

    static doublereal one = 1.;
    static doublereal zero = 0.;

    /* Format strings */
/*
    static char fmt_245[] = "(/\002  GTOL IS LESS THAN OR EQUAL TO 1.D-04\
\002,/\002 IT HAS BEEN RESET TO 9.D-01\002)";
    static char fmt_200[] = "(/\002 IFLAG= -1 \002,/\002 LINE SEARCH FAILED.\
 SEE DOCUMENTATION OF ROUTINE XXXXXX\002,/\002 ERROR RETURN OF LINE SEARCH: \
INFO= \002,i2,/\002 POSSIBLE CAUSES: FUNCTION OR GRADIENT ARE INCORRECT\002,/\
\002 OR INCORRECT TOLERANCES\002)";
    static char fmt_235[] = "(/\002 IFLAG= -2\002,/\002 THE\002,i5,\002-TH D\
IAGONAL ELEMENT OF THE\002,/,\002 INVERSE HESSIAN APPROXIMATION IS NOT POSIT\
IVE\002)";
    static char fmt_240[] = "(/\002 IFLAG= -3\002,/\002 IMPROPER INPUT PARAM\
ETERS (N OR M\002,\002 ARE NOT POSITIVE)\002)";
*/

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    //integer //s_wsfe(cilist *), e_wsfe();
    double sqrt(doublereal);
    //integer // do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static doublereal beta;
    static integer inmc;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *,
            integer *);
    static integer iscn, nfev, iycn;
    static doublereal ftol;
    static integer nfun, ispt, iypt, i, bound;
    static doublereal gnorm;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *,
            integer *, doublereal *, integer *);
    static integer point;
    static doublereal xnorm;
    static integer cp;
    static doublereal sq, yr, ys;
    extern /* Subroutine */ int mcsrch_(integer *, doublereal *, doublereal *,
             doublereal *, doublereal *, doublereal *, doublereal *,
            doublereal *, integer *, integer *, integer *, doublereal *);
    static logical finish;
    static doublereal yy;
    static integer maxfev;
/*
//Subroutine 
    extern int lb1_(integer *, integer *, integer *,
            doublereal *, integer *, integer *, doublereal *, doublereal *,
            doublereal *, doublereal *, logical *);
*/
    static integer npt;
    static doublereal stp, stp1;

    /* Fortran I/O blocks */
/*
    static cilist io___4 = { 0, 0, 0, fmt_245, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_235, 0 };
    static cilist io___32 = { 0, 0, 0, fmt_240, 0 };
*/


/*        LIMITED MEMORY BFGS METHOD FOR LARGE SCALE OPTIMIZATION */
/*                          JORGE NOCEDAL */
/*                        *** July 1990 *** */


/*     This subroutine solves the unconstrained minimization problem */

/*                      min F(x),    x= (x1,x2,...,xN), */

/*      using the limited memory BFGS method. The routine is especially */
/*      effective on problems involving a large number of variables. In */
/*      a typical iteration of this method an approximation Hk to the */
/*      inverse of the Hessian is obtained by applying M BFGS updates to
*/
/*     a diagonal matrix Hk0, using information from the previous M steps.
*/
/*      The user specifies the number M, which determines the amount of */
/*      storage required by the routine. The user may also provide the */
/*      diagonal matrices Hk0 if not satisfied with the default choice. */
/*      The algorithm is described in "On the limited memory BFGS method
*/
/*      for large scale optimization", by D. Liu and J. Nocedal, */
/*      Mathematical Programming B 45 (1989) 503-528. */

/*      The user is required to calculate the function value F and its */
/*      gradient G. In order to allow the user complete control over */
/*      these computations, reverse  communication is used. The routine */
/*      must be called repeatedly under the control of the parameter */
/*      IFLAG. */

/*      The steplength is determined at each iteration by means of the */
/*      line search routine MCVSRCH, which is a slight modification of */
/*      the routine CSRCH written by More' and Thuente. */

/*      The calling statement is */

/*          CALL LBFGS(N,M,X,F,G,DIAGCO,DIAG,IPRINT,EPS,XTOL,W,IFLAG) */

/*      where */

/*     N       is an INTEGER variable that must be set by the user to the
*/
/*             number of variables. It is not altered by the routine. */
/*             Restriction: N>0. */

/*     M       is an INTEGER variable that must be set by the user to */
/*             the number of corrections used in the BFGS update. It */
/*             is not altered by the routine. Values of M less than 3 are
*/
/*             not recommended; large values of M will result in excessive
 */
/*             computing time. 3<= M <=7 is recommended. Restriction: M>0.
 */

/*     X       is a DOUBLE PRECISION array of length N. On initial entry
*/
/*             it must be set by the user to the values of the initial */
/*             estimate of the solution vector. On exit with IFLAG=0, it
*/
/*             contains the values of the variables at the best point */
/*             found (usually a solution). */

/*     F       is a DOUBLE PRECISION variable. Before initial entry and on
 */
/*             a re-entry with IFLAG=1, it must be set by the user to */
/*             contain the value of the function F at the point X. */

/*     G       is a DOUBLE PRECISION array of length N. Before initial */
/*             entry and on a re-entry with IFLAG=1, it must be set by */
/*             the user to contain the components of the gradient G at */
/*             the point X. */

/*     DIAGCO  is a LOGICAL variable that must be set to .TRUE. if the */
/*             user  wishes to provide the diagonal matrix Hk0 at each */
/*             iteration. Otherwise it should be set to .FALSE., in which
*/
/*             case  LBFGS will use a default value described below. If */
/*             DIAGCO is set to .TRUE. the routine will return at each */
/*             iteration of the algorithm with IFLAG=2, and the diagonal
*/
/*              matrix Hk0  must be provided in the array DIAG. */


/*     DIAG    is a DOUBLE PRECISION array of length N. If DIAGCO=.TRUE.,
*/
/*             then on initial entry or on re-entry with IFLAG=2, DIAG */
/*             it must be set by the user to contain the values of the */
/*             diagonal matrix Hk0.  Restriction: all elements of DIAG */
/*             must be positive. */

/*     IPRINT  is an INTEGER array of length two which must be set by the
*/
/*             user. */

/*             IPRINT(1) specifies the frequency of the output: */
/*                IPRINT(1) < 0 : no output is generated, */
/*                IPRINT(1) = 0 : output only at first and last iteration,
 */
/*                IPRINT(1) > 0 : output every IPRINT(1) iterations. */

/*             IPRINT(2) specifies the type of output generated: */
/*                IPRINT(2) = 0 : iteration count, number of function */
/*                                evaluations, function value, norm of the
 */
/*                                gradient, and steplength, */
/*                IPRINT(2) = 1 : same as IPRINT(2)=0, plus vector of */
/*                                variables and  gradient vector at the */
/*                                initial point, */
/*                IPRINT(2) = 2 : same as IPRINT(2)=1, plus vector of */
/*                                variables, */
/*               IPRINT(2) = 3 : same as IPRINT(2)=2, plus gradient vector
.*/


/*     EPS     is a positive DOUBLE PRECISION variable that must be set by
 */
/*            the user, and determines the accuracy with which the solutio
n*/
/*             is to be found. The subroutine terminates when */

/*                         ||G|| < EPS max(1,||X||), */

/*             where ||.|| denotes the Euclidean norm. */

/*    XTOL    is a  positive DOUBLE PRECISION variable that must be set by
*/
/*             the user to an estimate of the machine precision (e.g. */
/*            10**(-16) on a SUN station 3/60). The line search routine wi
ll*/
/*            terminate if the relative width of the interval of uncertain
ty*/
/*             is less than XTOL. */

/*     W       is a DOUBLE PRECISION array of length N(2M+1)+2M used as */
/*             workspace for LBFGS. This array must not be altered by the
*/
/*             user. */

/*    IFLAG   is an INTEGER variable that must be set to 0 on initial entr
y*/
/*            to the subroutine. A return with IFLAG<0 indicates an error,
*/
/*            and IFLAG=0 indicates that the routine has terminated withou
t*/
/*             detecting errors. On a return with IFLAG=1, the user must
*/
/*             evaluate the function F and gradient G. On a return with */
/*             IFLAG=2, the user must provide the diagonal matrix Hk0. */

/*             The following negative values of IFLAG, detecting an error,
 */
/*             are possible: */

/*              IFLAG=-1  The line search routine MCSRCH failed. The */
/*                       parameter INFO provides more detailed information
*/
/*                        (see also the documentation of MCSRCH): */

/*                       INFO = 0  IMPROPER INPUT PARAMETERS. */

/*                       INFO = 2  RELATIVE WIDTH OF THE INTERVAL OF */
/*                                 UNCERTAINTY IS AT MOST XTOL. */

/*                       INFO = 3  MORE THAN 20 FUNCTION EVALUATIONS WERE
*/
/*                                 REQUIRED AT THE PRESENT ITERATION. */

/*                       INFO = 4  THE STEP IS TOO SMALL. */

/*                       INFO = 5  THE STEP IS TOO LARGE. */

/*                      INFO = 6  ROUNDING ERRORS PREVENT FURTHER PROGRESS
.*/
/*                                 THERE MAY NOT BE A STEP WHICH SATISFIES
 */
/*                                 THE SUFFICIENT DECREASE AND CURVATURE
*/
/*                                CONDITIONS. TOLERANCES MAY BE TOO SMALL.
*/


/*             IFLAG=-2  The i-th diagonal element of the diagonal inverse
*/
/*                        Hessian approximation, given in DIAG, is not */
/*                        positive. */

/*              IFLAG=-3  Improper input parameters for LBFGS (N or M are
*/
/*                        not positive). */



/*    ON THE DRIVER: */

/*    The program that calls LBFGS must contain the declaration: */

/*                       EXTERNAL LB2 */

/*    LB2 is a BLOCK DATA that defines the default values of several */
/*    parameters described in the COMMON section. */



/*    COMMON: */

/*     The subroutine contains one common area, which the user may wish to
 */
/*    reference: */


/*    MP  is an INTEGER variable with default value 6. It is used as the
*/
/*        unit number for the printing of the monitoring information */
/*        controlled by IPRINT. */

/*    LP  is an INTEGER variable with default value 6. It is used as the
*/
/*        unit number for the printing of error messages. This printing */
/*        may be suppressed by setting LP to a non-positive value. */

/*    GTOL is a DOUBLE PRECISION variable with default value 0.9, which */
/*        controls the accuracy of the line search routine MCSRCH. If the
*/
/*        function and gradient evaluations are inexpensive with respect
*/
/*        to the cost of the iteration (which is sometimes the case when
*/
/*        solving very large problems) it may be advantageous to set GTOL
*/
/*        to a small value. A typical small value is 0.1.  Restriction: */
/*        GTOL should be greater than 1.D-04. */

/*    STPMIN and STPMAX are non-negative DOUBLE PRECISION variables which
*/
/*        specify lower and uper bounds for the step in the line search.
*/
/*        Their default values are 1.D-20 and 1.D+20, respectively. These
*/
/*        values need not be modified unless the exponents are too large
*/
/*        for the machine being used, or unless the problem is extremely
*/
/*        badly scaled (in which case the exponents should be increased).
*/


/*  MACHINE DEPENDENCIES */

/*        The only variables that are machine-dependent are XTOL, */
/*        STPMIN and STPMAX. */


/*  GENERAL INFORMATION */

/*    Other routines called directly:  DAXPY, DDOT, LB1, MCSRCH */

/*    Input/Output  :  No input; diagnostic messages on unit MP and */
/*                     error messages on unit LP. */


/*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-*/


    /* Parameter adjustments */
    --diag;
    --g;
    --x;
    --w;
    --iprint;

    /* Function Body */

/*     INITIALIZE */
/*     ---------- */

    if (*iflag == 0) {
        goto L10;
    }
    switch (*iflag) {
        case 1:  goto L172;
        case 2:  goto L100;
    }
L10:
    //iter = 0;
    if (*n <= 0 || *m <= 0) {
        goto L196;
    }
    if (lb3_1.gtol <= 1e-4) {
        if (lb3_1.lp > 0) {
            //io___4.ciunit = lb3_1.lp;
            //s_wsfe(&io___4);
            //e_wsfe();
        }
        lb3_1.gtol = .9;
    }
    nfun = 1;
    point = 0;
    finish = FALSE_;
    if (*diagco) {
        i__1 = *n;
        for (i = 1; i <= i__1; ++i) {
/* L30: */
            if (diag[i] <= zero) {
                goto L195;
            }
        }
    } else {
        i__1 = *n;
        for (i = 1; i <= i__1; ++i) {
/* L40: */
            diag[i] = 1.;
        }
    }

/*     THE WORK VECTOR W IS DIVIDED AS FOLLOWS: */
/*     --------------------------------------- */
/*     THE FIRST N LOCATIONS ARE USED TO STORE THE GRADIENT AND */
/*         OTHER TEMPORARY INFORMATION. */
/*     LOCATIONS (N+1)...(N+M) STORE THE SCALARS RHO. */
/*     LOCATIONS (N+M+1)...(N+2M) STORE THE NUMBERS ALPHA USED */
/*         IN THE FORMULA THAT COMPUTES H*G. */
/*     LOCATIONS (N+2M+1)...(N+2M+NM) STORE THE LAST M SEARCH */
/*         STEPS. */
/*     LOCATIONS (N+2M+NM+1)...(N+2M+2NM) STORE THE LAST M */
/*         GRADIENT DIFFERENCES. */

/*     THE SEARCH STEPS AND GRADIENT DIFFERENCES ARE STORED IN A */
/*     CIRCULAR ORDER CONTROLLED BY THE PARAMETER POINT. */

    ispt = *n + (*m << 1);
    iypt = ispt + *n * *m;
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
/* L50: */
        w[ispt + i] = -g[i] * diag[i];
    }
    gnorm = sqrt(ddot_(n, &g[1], &c__1, &g[1], &c__1));
    stp1 = one / gnorm;

/*     PARAMETERS FOR LINE SEARCH ROUTINE */

    ftol = 1e-4;
    maxfev = 20;

   /*
    if (iprint[1] >= 0) {
        lb1_(&iprint[1], &iter, &nfun, &gnorm, n, m, &x[1], f, &g[1], &stp, &
                finish);
    }
    */

/*    -------------------- */
/*     MAIN ITERATION LOOP */
/*    -------------------- */

L80:
    ++(*iter);
    *info = 0;
    bound = *iter - 1;
    if (*iter == 1) {
        goto L165;
    }
    if (*iter > *m) {
        bound = *m;
    }

    ys = ddot_(n, &w[iypt + npt + 1], &c__1, &w[ispt + npt + 1], &c__1);
    if (ys==0.0)
        ys=1.e-10;
    if (! (*diagco)) {
        yy = ddot_(n, &w[iypt + npt + 1], &c__1, &w[iypt + npt + 1], &c__1);
        i__1 = *n;
        for (i = 1; i <= i__1; ++i) {
/* L90: */
            diag[i] = ys / yy;
        }
    } else {
        *iflag = 2;
        return 0;
    }
L100:
    if (*diagco) {
        i__1 = *n;
        for (i = 1; i <= i__1; ++i) {
/* L110: */
            if (diag[i] <= zero) {
                goto L195;
            }
        }
    }

/*     COMPUTE -H*G USING THE FORMULA GIVEN IN: Nocedal, J. 1980, */
/*     "Updating quasi-Newton matrices with limited storage", */
/*     Mathematics of Computation, Vol.24, No.151, pp. 773-782. */
/*     --------------------------------------------------------- */

    cp = point;
    if (point == 0) {
        cp = *m;
    }
    w[*n + cp] = one / ys;
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
/* L112: */
        w[i] = -g[i];
    }
    cp = point;
    i__1 = bound;
    for (i = 1; i <= i__1; ++i) {
        --cp;
        if (cp == -1) {
            cp = *m - 1;
        }
        sq = ddot_(n, &w[ispt + cp * *n + 1], &c__1, &w[1], &c__1);
        inmc = *n + *m + cp + 1;
        iycn = iypt + cp * *n;
        w[inmc] = w[*n + cp + 1] * sq;
        d__1 = -w[inmc];
        daxpy_(n, &d__1, &w[iycn + 1], &c__1, &w[1], &c__1);
/* L125: */
    }

    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
/* L130: */
        w[i] = diag[i] * w[i];
    }

    i__1 = bound;
    for (i = 1; i <= i__1; ++i) {
        yr = ddot_(n, &w[iypt + cp * *n + 1], &c__1, &w[1], &c__1);
        beta = w[*n + cp + 1] * yr;
        inmc = *n + *m + cp + 1;
        beta = w[inmc] - beta;
        iscn = ispt + cp * *n;
        daxpy_(n, &beta, &w[iscn + 1], &c__1, &w[1], &c__1);
        ++cp;
        if (cp == *m) {
            cp = 0;
        }
/* L145: */
    }

/*     STORE THE NEW SEARCH DIRECTION */
/*     ------------------------------ */

    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
/* L160: */
        w[ispt + point * *n + i] = w[i];
    }

/*     OBTAIN THE ONE-DIMENSIONAL MINIMIZER OF THE FUNCTION */
/*     BY USING THE LINE SEARCH ROUTINE MCSRCH */
/*     ---------------------------------------------------- */
L165:
    nfev = 0;
    stp = one;
    if (*iter == 1) {
        stp = stp1;
    }
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
/* L170: */
        w[i] = g[i];
    }
L172:
    mcsrch_(n, &x[1], f, &g[1], &w[ispt + point * *n + 1], &stp, &ftol, xtol,
            &maxfev, info, &nfev, &diag[1]);
    if (*info == -1) {
        *iflag = 1;
        return 0;
    }
    if (*info != 1) {
        goto L190;
    }
    nfun += nfev;

/*     COMPUTE THE NEW STEP AND GRADIENT CHANGE */
/*     ----------------------------------------- */

    npt = point * *n;
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
        w[ispt + npt + i] = stp * w[ispt + npt + i];
/* L175: */
        w[iypt + npt + i] = g[i] - w[i];
    }
    ++point;
    if (point == *m) {
        point = 0;
    }

/*     TERMINATION TEST */
/*     ---------------- */

    gnorm = sqrt(ddot_(n, &g[1], &c__1, &g[1], &c__1));
    xnorm = sqrt(ddot_(n, &x[1], &c__1, &x[1], &c__1));
    xnorm = max(1.,xnorm);
    if (gnorm / xnorm <= *eps) {
        finish = TRUE_;
    }

   /*
    if (iprint[1] >= 0) {
        lb1_(&iprint[1], &iter, &nfun, &gnorm, n, m, &x[1], f, &g[1], &stp, &
                finish);
    }
    */
    if (finish) {
        *iflag = 0;
        return 0;
    }
    goto L80;

/*     ------------------------------------------------------------ */
/*     END OF MAIN ITERATION LOOP. ERROR EXITS. */
/*     ------------------------------------------------------------ */

L190:
    *iflag = -1;
    if (lb3_1.lp > 0) {
        //io___30.ciunit = lb3_1.lp;
        //s_wsfe(&io___30);
        //// do_fio(&c__1, (char *)&info, (ftnlen)sizeof(integer));
        //e_wsfe();
    }
    return 0;
L195:
    *iflag = -2;
    if (lb3_1.lp > 0) {
        //io___31.ciunit = lb3_1.lp;
        //s_wsfe(&io___31);
        //// do_fio(&c__1, (char *)&i, (ftnlen)sizeof(integer));
        //e_wsfe();
    }
    return 0;
L196:
    *iflag = -3;
    if (lb3_1.lp > 0) {
        //io___32.ciunit = lb3_1.lp;
        //s_wsfe(&io___32);
        //e_wsfe();
    }

/*     FORMATS */
/*     ------- */

    return 0;
} /* lbfgs_ */


/*     LAST LINE OF SUBROUTINE LBFGS */


/* 
//Subroutine 
int lb1_(integer *iprint, integer *iter, integer *nfun,
        doublereal *gnorm, integer *n, integer *m, doublereal *x, doublereal *
        f, doublereal *g, doublereal *stp, logical *finish)
{
    // Format strings
    static char fmt_10[] = "(\002*******************************************\
******\002)";
    static char fmt_20[] = "(\002  N=\002,i5,\002   NUMBER OF CORRECTIONS\
=\002,i2,/,\002       INITIAL VALUES\002)";
    static char fmt_30[] = "(\002 F= \002,1pd10.3,\002   GNORM= \002,1pd10.3)"
            ;
    static char fmt_40[] = "(\002 VECTOR X= \002)";
    static char fmt_50[] = "(6(2x,1pd10.3))";
    static char fmt_60[] = "(\002 GRADIENT VECTOR G= \002)";
    static char fmt_70[] = "(/\002   I   NFN\002,4x,\002FUNC\002,8x,\002GN\
ORM\002,7x,\002STEPLENGTH\002/)";
    static char fmt_80[] = "(2(i4,1x),3x,3(1pd10.3,2x))";
    static char fmt_90[] = "(\002 FINAL POINT X= \002)";
    static char fmt_100[] = "(/\002 THE MINIMIZATION TERMINATED WITHOUT DETE\
CTING ERRORS.\002,/\002 IFLAG = 0\002)";

    // System generated locals
    integer i__1;

    // Builtin functions
   //integer //s_wsfe(cilist *), e_wsfe(), // do_fio(integer *, char *, ftnlen);

    // Local variables
    static integer i;

    // Fortran I/O blocks
    static cilist io___33 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___34 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___37 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___39 = { 0, 0, 0, fmt_60, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___41 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___42 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___44 = { 0, 0, 0, fmt_80, 0 };
    static cilist io___45 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___46 = { 0, 0, 0, fmt_80, 0 };
    static cilist io___47 = { 0, 0, 0, fmt_90, 0 };
    static cilist io___48 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___49 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___50 = { 0, 0, 0, fmt_60, 0 };
    static cilist io___51 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___52 = { 0, 0, 0, fmt_100, 0 };



//     -------------------------------------------------------------
//     THIS ROUTINE PRINTS MONITORING INFORMATION. THE FREQUENCY AND
//     AMOUNT OF OUTPUT ARE CONTROLLED BY IPRINT.
//     -------------------------------------------------------------


    // Parameter adjustments
    --iprint;
    --g;
    --x;

    // Function Body
    if (*iter == 0) {
        io___33.ciunit = lb3_1.mp;
        // s_wsfe(&io___33);
        // e_wsfe();
        io___34.ciunit = lb3_1.mp;
        // s_wsfe(&io___34);
        // do_fio(&c__1, (char *)&(*n), (ftnlen)sizeof(integer));
        // do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
        // e_wsfe();
        io___35.ciunit = lb3_1.mp;
        // s_wsfe(&io___35);
        // do_fio(&c__1, (char *)&(*f), (ftnlen)sizeof(doublereal));
        // do_fio(&c__1, (char *)&(*gnorm), (ftnlen)sizeof(doublereal));
        // e_wsfe();
        if (iprint[2] >= 1) {
            io___36.ciunit = lb3_1.mp;
            //s_wsfe(&io___36);
            // e_wsfe();
            io___37.ciunit = lb3_1.mp;
            //s_wsfe(&io___37);
            i__1 = *n;
            for (i = 1; i <= i__1; ++i) {
                // do_fio(&c__1, (char *)&x[i], (ftnlen)sizeof(doublereal));
            }
            // e_wsfe();
            io___39.ciunit = lb3_1.mp;
            //s_wsfe(&io___39);
            // e_wsfe();
            io___40.ciunit = lb3_1.mp;
            //s_wsfe(&io___40);
            i__1 = *n;
            for (i = 1; i <= i__1; ++i) {
                // do_fio(&c__1, (char *)&g[i], (ftnlen)sizeof(doublereal));
            }
            // e_wsfe();
        }
        io___41.ciunit = lb3_1.mp;
        // s_wsfe(&io___41);
        // e_wsfe();
        io___42.ciunit = lb3_1.mp;
        // s_wsfe(&io___42);
        // e_wsfe();
    } else {
        if (iprint[1] == 0 && (*iter != 1 && ! (*finish))) {
            return 0;
        }
        if (iprint[1] != 0) {
            if ((*iter - 1) % iprint[1] == 0 || *finish) {
                if (iprint[2] > 1 && *iter > 1) {
                    io___43.ciunit = lb3_1.mp;
                    //s_wsfe(&io___43);
                    // e_wsfe();
                }
                io___44.ciunit = lb3_1.mp;
                // s_wsfe(&io___44);
                // do_fio(&c__1, (char *)&(*iter), (ftnlen)sizeof(integer));
                // do_fio(&c__1, (char *)&(*nfun), (ftnlen)sizeof(integer));
                // do_fio(&c__1, (char *)&(*f), (ftnlen)sizeof(doublereal));
                // do_fio(&c__1, (char *)&(*gnorm), (ftnlen)sizeof(doublereal));
                // do_fio(&c__1, (char *)&(*stp), (ftnlen)sizeof(doublereal));
                // e_wsfe();
            } else {
                return 0;
            }
        } else {
            if (iprint[2] > 1 && *finish) {
                io___45.ciunit = lb3_1.mp;
                // s_wsfe(&io___45);
                // e_wsfe();
            }
            io___46.ciunit = lb3_1.mp;
            //s_wsfe(&io___46);
            // do_fio(&c__1, (char *)&(*iter), (ftnlen)sizeof(integer));
            // do_fio(&c__1, (char *)&(*nfun), (ftnlen)sizeof(integer));
            // do_fio(&c__1, (char *)&(*f), (ftnlen)sizeof(doublereal));
            // do_fio(&c__1, (char *)&(*gnorm), (ftnlen)sizeof(doublereal));
            // do_fio(&c__1, (char *)&(*stp), (ftnlen)sizeof(doublereal));
            // e_wsfe();
        }
        if (iprint[2] == 2 || iprint[2] == 3) {
            if (*finish) {
                io___47.ciunit = lb3_1.mp;
                // s_wsfe(&io___47);
                // e_wsfe();
            } else {
                io___48.ciunit = lb3_1.mp;
                // s_wsfe(&io___48);
                // e_wsfe();
            }
            io___49.ciunit = lb3_1.mp;
            //s_wsfe(&io___49);
            i__1 = *n;
            for (i = 1; i <= i__1; ++i) {
                // do_fio(&c__1, (char *)&x[i], (ftnlen)sizeof(doublereal));
            }
            // e_wsfe();
            if (iprint[2] == 3) {
                io___50.ciunit = lb3_1.mp;
                // s_wsfe(&io___50);
                // e_wsfe();
                io___51.ciunit = lb3_1.mp;
                // s_wsfe(&io___51);
                i__1 = *n;
                for (i = 1; i <= i__1; ++i) {
                    // do_fio(&c__1, (char *)&g[i], (ftnlen)sizeof(doublereal));
                }
                // e_wsfe();
            }
        }
        if (*finish) {
            io___52.ciunit = lb3_1.mp;
            //s_wsfe(&io___52);
            // e_wsfe();
        }
    }


    return 0;
}
*/

/*     ****** */


/*   ---------------------------------------------------------- */
/*     DATA */
/*   ---------------------------------------------------------- */




/*   ---------------------------------------------------------- */

/* Subroutine */ int daxpy_(integer *n, doublereal *da, doublereal *dx,
        integer *incx, doublereal *dy, integer *incy)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i, m, ix, iy, mp1;


/*     constant times a vector plus a vector. */
/*     uses unrolled loops for increments equal to one. */
/*     jack dongarra, linpack, 3/11/78. */


    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
        return 0;
    }
    if (*da == 0.) {
        return 0;
    }
    if (*incx == 1 && *incy == 1) {
        goto L20;
    }

/*        code for unequal increments or equal increments */
/*          not equal to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
        ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
        iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
        dy[iy] += *da * dx[ix];
        ix += *incx;
        iy += *incy;
/* L10: */
    }
    return 0;

/*        code for both increments equal to 1 */


/*        clean-up loop */

L20:
    m = *n % 4;
    if (m == 0) {
        goto L40;
    }
    i__1 = m;
    for (i = 1; i <= i__1; ++i) {
        dy[i] += *da * dx[i];
/* L30: */
    }
    if (*n < 4) {
        return 0;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i = mp1; i <= i__1; i += 4) {
        dy[i] += *da * dx[i];
        dy[i + 1] += *da * dx[i + 1];
        dy[i + 2] += *da * dx[i + 2];
        dy[i + 3] += *da * dx[i + 3];
/* L50: */
    }
    return 0;
} /* daxpy_ */



/*   ---------------------------------------------------------- */

doublereal ddot_(integer *n, doublereal *dx, integer *incx, doublereal *dy,
        integer *incy)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static integer i, m;
    static doublereal dtemp;
    static integer ix, iy, mp1;


/*     forms the dot product of two vectors. */
/*     uses unrolled loops for increments equal to one. */
/*     jack dongarra, linpack, 3/11/78. */


    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    ret_val = 0.;
    dtemp = 0.;
    if (*n <= 0) {
        return ret_val;
    }
    if (*incx == 1 && *incy == 1) {
        goto L20;
    }

/*        code for unequal increments or equal increments */
/*          not equal to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
        ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
        iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
        dtemp += dx[ix] * dy[iy];
        ix += *incx;
        iy += *incy;
/* L10: */
    }
    ret_val = dtemp;
    return ret_val;

/*        code for both increments equal to 1 */


/*        clean-up loop */

L20:
    m = *n % 5;
    if (m == 0) {
        goto L40;
    }
    i__1 = m;
    for (i = 1; i <= i__1; ++i) {
        dtemp += dx[i] * dy[i];
/* L30: */
    }
    if (*n < 5) {
        goto L60;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i = mp1; i <= i__1; i += 5) {
        dtemp = dtemp + dx[i] * dy[i] + dx[i + 1] * dy[i + 1] + dx[i + 2] *
                dy[i + 2] + dx[i + 3] * dy[i + 3] + dx[i + 4] * dy[i + 4];
/* L50: */
    }
L60:
    ret_val = dtemp;
    return ret_val;
} /* ddot_ */

/*    ------------------------------------------------------------------ */

/*     ************************** */
/*     LINE SEARCH ROUTINE MCSRCH */
/*     ************************** */

/* Subroutine */ int mcsrch_(integer *n, doublereal *x, doublereal *f,
        doublereal *g, doublereal *s, doublereal *stp, doublereal *ftol,
        doublereal *xtol, integer *maxfev, integer *info, integer *nfev,
        doublereal *wa)
{
    /* Initialized data */

    static doublereal p5 = .5;
    static doublereal p66 = .66;
    static doublereal xtrapf = 4.;
    static doublereal zero = 0.;

    /* Format strings */
/*
    static char fmt_15[] = "(/\002  THE SEARCH DIRECTION IS NOT A DESCENT DI\
RECTION\002)";
*/

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    //integer //s_wsfe(cilist *), e_wsfe();

    /* Local variables */
    static doublereal dgxm, dgym;
    static integer j, infoc;
    static doublereal finit, width, stmin, stmax;
    static logical stage1;
    static doublereal width1, ftest1, dg, fm, fx, fy;
    static logical brackt;
    static doublereal dginit, dgtest;
    extern /* Subroutine */ int mcstep_(doublereal *, doublereal *,
            doublereal *, doublereal *, doublereal *, doublereal *,
            doublereal *, doublereal *, doublereal *, logical *, doublereal *,
             doublereal *, integer *);
    static doublereal dgm, dgx, dgy, fxm, fym, stx, sty;

    /* Fortran I/O blocks */
    //static cilist io___71 = { 0, 0, 0, fmt_15, 0 };



/*                     SUBROUTINE MCSRCH */

/*     A slight modification of the subroutine CSRCH of More' and Thuente.
 */
/*     The changes are to allow reverse communication, and do not affect
*/
/*       NFEV IS AN INTEGER OUTPUT VARIABLE SET TO THE NUMBER OF */
/*         CALLS TO FCN. */

/*       WA IS A WORK ARRAY OF LENGTH N. */

/*     SUBPROGRAMS CALLED */

/*       MCSTEP */

/*       FORTRAN-SUPPLIED...ABS,MAX,MIN */

/*     ARGONNE NATIONAL LABORATORY. MINPACK PROJECT. JUNE 1983 */
/*     JORGE J. MORE', DAVID J. THUENTE */

/*     ********** */
    /* Parameter adjustments */
    --wa;
    --s;
    --g;
    --x;

    /* Function Body */
    if (*info == -1) {
        goto L45;
    }
    infoc = 1;

/*     CHECK THE INPUT PARAMETERS FOR ERRORS. */

    if (*n <= 0 || *stp <= zero || *ftol < zero || lb3_1.gtol < zero || *xtol
            < zero || lb3_1.stpmin < zero || lb3_1.stpmax < lb3_1.stpmin || *
            maxfev <= 0) {
        return 0;
    }

/*     COMPUTE THE INITIAL GRADIENT IN THE SEARCH DIRECTION */
/*     AND CHECK THAT S IS A DESCENT DIRECTION. */

    dginit = zero;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
        dginit += g[j] * s[j];
/* L10: */
    }
    if (dginit >= zero) {
        //io___71.ciunit = lb3_1.lp;
        // s_wsfe(&io___71);
        // e_wsfe();
        return 0;
    }

/*     INITIALIZE LOCAL VARIABLES. */

    brackt = FALSE_;
    stage1 = TRUE_;
    *nfev = 0;
    finit = *f;
    dgtest = *ftol * dginit;
    width = lb3_1.stpmax - lb3_1.stpmin;
    width1 = width / p5;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
        wa[j] = x[j];
/* L20: */
    }

/*     THE VARIABLES STX, FX, DGX CONTAIN THE VALUES OF THE STEP, */
/*     FUNCTION, AND DIRECTIONAL DERIVATIVE AT THE BEST STEP. */
/*     THE VARIABLES STY, FY, DGY CONTAIN THE VALUE OF THE STEP, */
/*     FUNCTION, AND DERIVATIVE AT THE OTHER ENDPOINT OF */
/*     THE INTERVAL OF UNCERTAINTY. */
/*     THE VARIABLES STP, F, DG CONTAIN THE VALUES OF THE STEP, */
/*     FUNCTION, AND DERIVATIVE AT THE CURRENT STEP. */

    stx = zero;
    fx = finit;
    dgx = dginit;
    sty = zero;
    fy = finit;
    dgy = dginit;

/*     START OF ITERATION. */

L30:

/*        SET THE MINIMUM AND MAXIMUM STEPS TO CORRESPOND */
/*        TO THE PRESENT INTERVAL OF UNCERTAINTY. */

    if (brackt) {
        stmin = min(stx,sty);
        stmax = max(stx,sty);
    } else {
        stmin = stx;
        stmax = *stp + xtrapf * (*stp - stx);
    }

/*        FORCE THE STEP TO BE WITHIN THE BOUNDS STPMAX AND STPMIN. */

    *stp = max(*stp,lb3_1.stpmin);
    *stp = min(*stp,lb3_1.stpmax);

/*        IF AN UNUSUAL TERMINATION IS TO OCCUR THEN LET */
/*        STP BE THE LOWEST POINT OBTAINED SO FAR. */

  if ( ( brackt && (*stp <= stmin || *stp >= stmax) ) || *nfev >= *maxfev - 1 ||
            infoc == 0 || (brackt && stmax - stmin <= *xtol * stmax) ) {
        *stp = stx;
    }

/*        EVALUATE THE FUNCTION AND GRADIENT AT STP */
/*        AND COMPUTE THE DIRECTIONAL DERIVATIVE. */
/*        We return to main program to obtain F and G. */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
        x[j] = wa[j] + *stp * s[j];
/* L40: */
    }
    *info = -1;
    return 0;

L45:
    *info = 0;
    ++(*nfev);
    dg = zero;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
        dg += g[j] * s[j];
/* L50: */
    }
    ftest1 = finit + *stp * dgtest;

/*        TEST FOR CONVERGENCE. */

    if ( (brackt && (*stp <= stmin || *stp >= stmax)) || infoc == 0) {
        *info = 6;
    }
    if (*stp == lb3_1.stpmax && *f <= ftest1 && dg <= dgtest) {
        *info = 5;
    }
    if (*stp == lb3_1.stpmin && (*f > ftest1 || dg >= dgtest)) {
        *info = 4;
    }
    if (*nfev >= *maxfev) {
        *info = 3;
    }
    if (brackt && stmax - stmin <= *xtol * stmax) {
        *info = 2;
    }
    if (*f <= ftest1 && abs(dg) <= lb3_1.gtol * (-dginit)) {
        *info = 1;
    }

/*        CHECK FOR TERMINATION. */

    if (*info != 0) {
        return 0;
    }

/*        IN THE FIRST STAGE WE SEEK A STEP FOR WHICH THE MODIFIED */
/*        FUNCTION HAS A NONPOSITIVE VALUE AND NONNEGATIVE DERIVATIVE. */

    if (stage1 && *f <= ftest1 && dg >= min(*ftol,lb3_1.gtol) * dginit) {
        stage1 = FALSE_;
    }

/*        A MODIFIED FUNCTION IS USED TO PREDICT THE STEP ONLY IF */
/*        WE HAVE NOT OBTAINED A STEP FOR WHICH THE MODIFIED */
/*        FUNCTION HAS A NONPOSITIVE FUNCTION VALUE AND NONNEGATIVE */
/*        DERIVATIVE, AND IF A LOWER FUNCTION VALUE HAS BEEN */
/*        OBTAINED BUT THE DECREASE IS NOT SUFFICIENT. */

    if (stage1 && *f <= fx && *f > ftest1) {
/*           DEFINE THE MODIFIED FUNCTION AND DERIVATIVE VALUES. */

        fm = *f - *stp * dgtest;
        fxm = fx - stx * dgtest;
        fym = fy - sty * dgtest;
        dgm = dg - dgtest;
        dgxm = dgx - dgtest;
        dgym = dgy - dgtest;

/*           CALL CSTEP TO UPDATE THE INTERVAL OF UNCERTAINTY */
/*           AND TO COMPUTE THE NEW STEP. */

        mcstep_(&stx, &fxm, &dgxm, &sty, &fym, &dgym, stp, &fm, &dgm, &brackt,
                 &stmin, &stmax, &infoc);

/*           RESET THE FUNCTION AND GRADIENT VALUES FOR F. */

        fx = fxm + stx * dgtest;
        fy = fym + sty * dgtest;
        dgx = dgxm + dgtest;
        dgy = dgym + dgtest;
    } else {
/*           CALL MCSTEP TO UPDATE THE INTERVAL OF UNCERTAINTY */
/*           AND TO COMPUTE THE NEW STEP. */

        mcstep_(&stx, &fx, &dgx, &sty, &fy, &dgy, stp, f, &dg, &brackt, &
                stmin, &stmax, &infoc);
    }

/*        FORCE A SUFFICIENT DECREASE IN THE SIZE OF THE */
/*        INTERVAL OF UNCERTAINTY. */

    if (brackt) {
        if ((d__1 = sty - stx, abs(d__1)) >= p66 * width1) {
            *stp = stx + p5 * (sty - stx);
        }
        width1 = width;
        width = (d__1 = sty - stx, abs(d__1));
    }

/*        END OF ITERATION. */

    goto L30;

/*     LAST LINE OF SUBROUTINE MCSRCH. */
} /* mcsrch_ */

/* Subroutine */ int mcstep_(doublereal *stx, doublereal *fx, doublereal *dx,
        doublereal *sty, doublereal *fy, doublereal *dy, doublereal *stp,
        doublereal *fp, doublereal *dp, logical *brackt, doublereal *stpmin,
        doublereal *stpmax, integer *info)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal sgnd, stpc, stpf, stpq, p, q, gamma, r, s, theta;
    static logical bound;


/*     SUBROUTINE MCSTEP */

/*     THE PURPOSE OF MCSTEP IS TO COMPUTE A SAFEGUARDED STEP FOR */
/*     A LINESEARCH AND TO UPDATE AN INTERVAL OF UNCERTAINTY FOR */
/*     A MINIMIZER OF THE FUNCTION. */

/*     THE PARAMETER STX CONTAINS THE STEP WITH THE LEAST FUNCTION */
/*     VALUE. THE PARAMETER STP CONTAINS THE CURRENT STEP. IT IS */
/*     ASSUMED THAT THE DERIVATIVE AT STX IS NEGATIVE IN THE */
/*     DIRECTION OF THE STEP. IF BRACKT IS SET TRUE THEN A */
/*     MINIMIZER HAS BEEN BRACKETED IN AN INTERVAL OF UNCERTAINTY */
/*     WITH ENDPOINTS STX AND STY. */

/*     THE SUBROUTINE STATEMENT IS */

/*       SUBROUTINE MCSTEP(STX,FX,DX,STY,FY,DY,STP,FP,DP,BRACKT, */
/*                        STPMIN,STPMAX,INFO) */

/*     WHERE */

/*       STX, FX, AND DX ARE VARIABLES WHICH SPECIFY THE STEP, */
/*         THE FUNCTION, AND THE DERIVATIVE AT THE BEST STEP OBTAINED */
/*         SO FAR. THE DERIVATIVE MUST BE NEGATIVE IN THE DIRECTION */
/*         OF THE STEP, THAT IS, DX AND STP-STX MUST HAVE OPPOSITE */
/*         SIGNS. ON OUTPUT THESE PARAMETERS ARE UPDATED APPROPRIATELY. */

/*       STY, FY, AND DY ARE VARIABLES WHICH SPECIFY THE STEP, */
/*         THE FUNCTION, AND THE DERIVATIVE AT THE OTHER ENDPOINT OF */
/*         THE INTERVAL OF UNCERTAINTY. ON OUTPUT THESE PARAMETERS ARE */
/*         UPDATED APPROPRIATELY. */

/*       STP, FP, AND DP ARE VARIABLES WHICH SPECIFY THE STEP, */
/*         THE FUNCTION, AND THE DERIVATIVE AT THE CURRENT STEP. */
/*         IF BRACKT IS SET TRUE THEN ON INPUT STP MUST BE */
/*         BETWEEN STX AND STY. ON OUTPUT STP IS SET TO THE NEW STEP. */

/*       BRACKT IS A LOGICAL VARIABLE WHICH SPECIFIES IF A MINIMIZER */
/*         HAS BEEN BRACKETED. IF THE MINIMIZER HAS NOT BEEN BRACKETED */
/*         THEN ON INPUT BRACKT MUST BE SET FALSE. IF THE MINIMIZER */
/*         IS BRACKETED THEN ON OUTPUT BRACKT IS SET TRUE. */

/*       STPMIN AND STPMAX ARE INPUT VARIABLES WHICH SPECIFY LOWER */
/*         AND UPPER BOUNDS FOR THE STEP. */

/*       INFO IS AN INTEGER OUTPUT VARIABLE SET AS FOLLOWS: */
/*         IF INFO = 1,2,3,4,5, THEN THE STEP HAS BEEN COMPUTED */
/*         ACCORDING TO ONE OF THE FIVE CASES BELOW. OTHERWISE */
/*         INFO = 0, AND THIS INDICATES IMPROPER INPUT PARAMETERS. */

/*     SUBPROGRAMS CALLED */

/*       FORTRAN-SUPPLIED ... ABS,MAX,MIN,SQRT */

/*     ARGONNE NATIONAL LABORATORY. MINPACK PROJECT. JUNE 1983 */
/*     JORGE J. MORE', DAVID J. THUENTE */

    *info = 0;

/*     CHECK THE INPUT PARAMETERS FOR ERRORS. */

    if ((*brackt && (*stp <= min(*stx,*sty) || *stp >= max(*stx,*sty))) || *dx *
             (*stp - *stx) >= (float)0. || *stpmax < *stpmin) {
        return 0;
    }

/*     DETERMINE IF THE DERIVATIVES HAVE OPPOSITE SIGN. */

    sgnd = *dp * (*dx / abs(*dx));

/*     FIRST CASE. A HIGHER FUNCTION VALUE. */
/*     THE MINIMUM IS BRACKETED. IF THE CUBIC STEP IS CLOSER */
/*     TO STX THAN THE QUADRATIC STEP, THE CUBIC STEP IS TAKEN, */
/*     ELSE THE AVERAGE OF THE CUBIC AND QUADRATIC STEPS IS TAKEN. */

    if (*fp > *fx) {
        *info = 1;
        bound = TRUE_;
        theta = (*fx - *fp) * 3 / (*stp - *stx) + *dx + *dp;
/* Computing MAX */
        d__1 = abs(theta), d__2 = abs(*dx), d__1 = max(d__1,d__2), d__2 = abs(
                *dp);
        s = max(d__1,d__2);
/* Computing 2nd power */
        d__1 = theta / s;
        gamma = s * sqrt(d__1 * d__1 - *dx / s * (*dp / s));
        if (*stp < *stx) {
            gamma = -gamma;
        }
        p = gamma - *dx + theta;
        q = gamma - *dx + gamma + *dp;
        r = p / q;
        stpc = *stx + r * (*stp - *stx);
        stpq = *stx + *dx / ((*fx - *fp) / (*stp - *stx) + *dx) / 2 * (*stp -
                *stx);
        if ((d__1 = stpc - *stx, abs(d__1)) < (d__2 = stpq - *stx, abs(d__2)))
                 {
            stpf = stpc;
        } else {
            stpf = stpc + (stpq - stpc) / 2;
        }
        *brackt = TRUE_;

/*     SECOND CASE. A LOWER FUNCTION VALUE AND DERIVATIVES OF */
/*     OPPOSITE SIGN. THE MINIMUM IS BRACKETED. IF THE CUBIC */
/*     STEP IS CLOSER TO STX THAN THE QUADRATIC (SECANT) STEP, */
/*     THE CUBIC STEP IS TAKEN, ELSE THE QUADRATIC STEP IS TAKEN. */

    } else if (sgnd < (float)0.) {
        *info = 2;
        bound = FALSE_;
        theta = (*fx - *fp) * 3 / (*stp - *stx) + *dx + *dp;
/* Computing MAX */
        d__1 = abs(theta), d__2 = abs(*dx), d__1 = max(d__1,d__2), d__2 = abs(
                *dp);
        s = max(d__1,d__2);
/* Computing 2nd power */
        d__1 = theta / s;
        gamma = s * sqrt(d__1 * d__1 - *dx / s * (*dp / s));
        if (*stp > *stx) {
            gamma = -gamma;
        }
        p = gamma - *dp + theta;
        q = gamma - *dp + gamma + *dx;
        r = p / q;
        stpc = *stp + r * (*stx - *stp);
        stpq = *stp + *dp / (*dp - *dx) * (*stx - *stp);
        if ((d__1 = stpc - *stp, abs(d__1)) > (d__2 = stpq - *stp, abs(d__2)))
                 {
            stpf = stpc;
        } else {
            stpf = stpq;
        }
        *brackt = TRUE_;

/*     THIRD CASE. A LOWER FUNCTION VALUE, DERIVATIVES OF THE */
/*     SAME SIGN, AND THE MAGNITUDE OF THE DERIVATIVE DECREASES. */
/*     THE CUBIC STEP IS ONLY USED IF THE CUBIC TENDS TO INFINITY */
/*     IN THE DIRECTION OF THE STEP OR IF THE MINIMUM OF THE CUBIC */
/*     IS BEYOND STP. OTHERWISE THE CUBIC STEP IS DEFINED TO BE */
/*     EITHER STPMIN OR STPMAX. THE QUADRATIC (SECANT) STEP IS ALSO */
/*     COMPUTED AND IF THE MINIMUM IS BRACKETED THEN THE THE STEP */
/*     CLOSEST TO STX IS TAKEN, ELSE THE STEP FARTHEST AWAY IS TAKEN.
*/

    } else if (abs(*dp) < abs(*dx)) {
        *info = 3;
        bound = TRUE_;
        theta = (*fx - *fp) * 3 / (*stp - *stx) + *dx + *dp;
/* Computing MAX */
        d__1 = abs(theta), d__2 = abs(*dx), d__1 = max(d__1,d__2), d__2 = abs(
                *dp);
        s = max(d__1,d__2);

/*        THE CASE GAMMA = 0 ONLY ARISES IF THE CUBIC DOES NOT TEND */
/*        TO INFINITY IN THE DIRECTION OF THE STEP. */

/* Computing MAX */
/* Computing 2nd power */
        d__3 = theta / s;
        d__1 = 0., d__2 = d__3 * d__3 - *dx / s * (*dp / s);
        gamma = s * sqrt((max(d__1,d__2)));
        if (*stp > *stx) {
            gamma = -gamma;
        }
        p = gamma - *dp + theta;
        q = gamma + (*dx - *dp) + gamma;
        r = p / q;
        if (r < (float)0. && gamma != (float)0.) {
            stpc = *stp + r * (*stx - *stp);
        } else if (*stp > *stx) {
            stpc = *stpmax;
        } else {
            stpc = *stpmin;
        }
        stpq = *stp + *dp / (*dp - *dx) * (*stx - *stp);
        if (*brackt) {
            if ((d__1 = *stp - stpc, abs(d__1)) < (d__2 = *stp - stpq, abs(
                    d__2))) {
                stpf = stpc;
            } else {
                stpf = stpq;
            }
        } else {
            if ((d__1 = *stp - stpc, abs(d__1)) > (d__2 = *stp - stpq, abs(
                    d__2))) {
                stpf = stpc;
            } else {
                stpf = stpq;
            }
        }

/*     FOURTH CASE. A LOWER FUNCTION VALUE, DERIVATIVES OF THE */
/*     SAME SIGN, AND THE MAGNITUDE OF THE DERIVATIVE DOES */
/*     NOT DECREASE. IF THE MINIMUM IS NOT BRACKETED, THE STEP */
/*     IS EITHER STPMIN OR STPMAX, ELSE THE CUBIC STEP IS TAKEN. */

    } else {
        *info = 4;
        bound = FALSE_;
        if (*brackt) {
            theta = (*fp - *fy) * 3 / (*sty - *stp) + *dy + *dp;
/* Computing MAX */
            d__1 = abs(theta), d__2 = abs(*dy), d__1 = max(d__1,d__2), d__2 =
                    abs(*dp);
            s = max(d__1,d__2);
/* Computing 2nd power */
            d__1 = theta / s;
            gamma = s * sqrt(d__1 * d__1 - *dy / s * (*dp / s));
            if (*stp > *sty) {
                gamma = -gamma;
            }
            p = gamma - *dp + theta;
            q = gamma - *dp + gamma + *dy;
            r = p / q;
            stpc = *stp + r * (*sty - *stp);
            stpf = stpc;
        } else if (*stp > *stx) {
            stpf = *stpmax;
        } else {
            stpf = *stpmin;
        }
    }

/*     UPDATE THE INTERVAL OF UNCERTAINTY. THIS UPDATE DOES NOT */
/*     DEPEND ON THE NEW STEP OR THE CASE ANALYSIS ABOVE. */

    if (*fp > *fx) {
        *sty = *stp;
        *fy = *fp;
        *dy = *dp;
    } else {
        if (sgnd < (float)0.) {
            *sty = *stx;
            *fy = *fx;
            *dy = *dx;
        }
        *stx = *stp;
        *fx = *fp;
        *dx = *dp;
    }

/*     COMPUTE THE NEW STEP AND SAFEGUARD IT. */

    stpf = min(*stpmax,stpf);
    stpf = max(*stpmin,stpf);
    *stp = stpf;
    if (*brackt && bound) {
        if (*sty > *stx) {
/* Computing MIN */
            d__1 = *stx + (*sty - *stx) * (float).66;
            *stp = min(d__1,*stp);
        } else {
/* Computing MAX */
            d__1 = *stx + (*sty - *stx) * (float).66;
            *stp = max(d__1,*stp);
        }
    }
    return 0;

/*     LAST LINE OF SUBROUTINE MCSTEP. */
} /* mcstep_ */

#ifdef __cplusplus
        }
#endif
