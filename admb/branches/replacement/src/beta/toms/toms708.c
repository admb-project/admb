/* toms708.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static integer c__4 = 4;
static integer c__5 = 5;
static integer c__6 = 6;
static integer c__7 = 7;
static doublereal c_b188 = 1.;
static integer c__3 = 3;

/*      ALGORITHM 708, COLLECTED ALGORITHMS FROM ACM. */
/*      THIS WORK PUBLISHED IN TRANSACTIONS ON MATHEMATICAL SOFTWARE, */
/*      VOL. 18, NO. 3, SEPTEMBER, 1992, PP. 360-373z. */
/*     PROGRAM BTST (OUTPUT, TAPE6=OUTPUT) */
/* ----------------------------------------------------------------------- */

/*     SAMPLE PROGRAM USING BRATIO. GIVEN THE NONNEGATIVE VALUES */
/*     A, B, X, Y WHERE A AND B ARE NOT BOTH 0 AND X + Y = 1. THEN */

/*              CALL BRATIO (A, B, X, Y, W, W1, IERR) */

/*     COMPUTES THE VALUES */

/*                W = I (A,B)  AND W1 = 1 - I (A,B). */
/*                     X                     X */

/*     IERR IS A VARIABLE THAT REPORTS THE STATUS OF THE RESULTS. */
/*     IF NO INPUT ERRORS ARE DETECTED THEN IERR IS SET TO 0 AND */
/*     W AND W1 ARE COMPUTED. FOR MORE DETAILS SEE THE IN-LINE */
/*     DOCUMENTATION OF BRATIO. */

/*     THE LAST FUNCTION IN THIS PACKAGE, IPMPAR, MUST BE DEFINED */
/*     FOR THE PARTICULAR COMPUTER BEING USED. FOR DETAILS SEE THE */
/*     IN-LINE DOCUMENTATION OF IPMPAR. */

/*     NO DATA IS READ. THE OUTPUT FOR THE PROGRAM IS WRITTEN ON */
/*     UNIT 6. THE FIRST STATMENT OF THIS TEXT MAY BE USED TO */
/*     BEGIN THE PROGRAM FOR THE CDC 6000-7000 SERIES COMPUTERS. */
/* ----------------------------------------------------------------------- */
/* Main program */ int MAIN__()
{
    /* Format strings */
    static char fmt_1[] = "(\0021   X     Y\002,11x,\002W\002,14x,\002W1\002\
/)";
    static char fmt_2[] = "(2f6.2,2e16.6)";

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe();
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer do_fio(integer *, char *, ftnlen);

    /* Local variables */
    doublereal a, b;
    integer l;
    doublereal w, x, y, w1;
    integer ierr;
    extern /* Subroutine */ int bratio_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    ;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, fmt_1, 0 };
    static cilist io___10 = { 0, 6, 0, fmt_2, 0 };


    s_wsfe(&io___1);
    e_wsfe();
/* L2: */

    a = 5.3;
    b = 10.1;
    x = .01;
    for (l = 1; l <= 50; ++l) {
	y = .5 - x + .5;
	bratio_(&a, &b, &x, &y, &w, &w1, &ierr);
	if (ierr != 0) {
	    s_stop("", (ftnlen)0);
	}
	s_wsfe(&io___10);
	do_fio(&c__1, (char *)&x, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&w, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&w1, (ftnlen)sizeof(doublereal));
	e_wsfe();
	x += .01;
/* L10: */
    }
    s_stop("", (ftnlen)0);
    return 0;
} /* MAIN__ */

/* Subroutine */ int bratio_(doublereal *a, doublereal *b, doublereal *x, 
	doublereal *y, doublereal *w, doublereal *w1, integer *ierr)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    integer n;
    doublereal t, z__, a0, b0, x0, y0;
    integer ind;
    extern doublereal bup_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *);
    doublereal eps;
    integer ierr1;
    extern doublereal bfrac_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    extern /* Subroutine */ int bgrat_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, integer *);
    extern doublereal apser_(doublereal *, doublereal *, doublereal *, 
	    doublereal *), bpser_(doublereal *, doublereal *, doublereal *, 
	    doublereal *), basym_(doublereal *, doublereal *, doublereal *, 
	    doublereal *), fpser_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    doublereal lambda;
    extern doublereal spmpar_(integer *);

/* ----------------------------------------------------------------------- */

/*            EVALUATION OF THE INCOMPLETE BETA FUNCTION IX(A,B) */

/*                     -------------------- */

/*     IT IS ASSUMED THAT A AND B ARE NONNEGATIVE, AND THAT X .LE. 1 */
/*     AND Y = 1 - X.  BRATIO ASSIGNS W AND W1 THE VALUES */

/*                      W  = IX(A,B) */
/*                      W1 = 1 - IX(A,B) */

/*     IERR IS A VARIABLE THAT REPORTS THE STATUS OF THE RESULTS. */
/*     IF NO INPUT ERRORS ARE DETECTED THEN IERR IS SET TO 0 AND */
/*     W AND W1 ARE COMPUTED. OTHERWISE, IF AN ERROR IS DETECTED, */
/*     THEN W AND W1 ARE ASSIGNED THE VALUE 0 AND IERR IS SET TO */
/*     ONE OF THE FOLLOWING VALUES ... */

/*        IERR = 1  IF A OR B IS NEGATIVE */
/*        IERR = 2  IF A = B = 0 */
/*        IERR = 3  IF X .LT. 0 OR X .GT. 1 */
/*        IERR = 4  IF Y .LT. 0 OR Y .GT. 1 */
/*        IERR = 5  IF X + Y .NE. 1 */
/*        IERR = 6  IF X = A = 0 */
/*        IERR = 7  IF Y = B = 0 */

/* -------------------- */
/*     WRITTEN BY ALFRED H. MORRIS, JR. */
/*        NAVAL SURFACE WARFARE CENTER */
/*        DAHLGREN, VIRGINIA */
/*     REVISED ... NOV 1991 */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */

/*     ****** EPS IS A MACHINE DEPENDENT CONSTANT. EPS IS THE SMALLEST */
/*            FLOATING POINT NUMBER FOR WHICH 1.0 + EPS .GT. 1.0 */

    eps = spmpar_(&c__1);

/* ----------------------------------------------------------------------- */
    *w = 0.;
    *w1 = 0.;
    if (*a < 0. || *b < 0.) {
	goto L300;
    }
    if (*a == 0. && *b == 0.) {
	goto L310;
    }
    if (*x < 0. || *x > 1.) {
	goto L320;
    }
    if (*y < 0. || *y > 1.) {
	goto L330;
    }
    z__ = *x + *y - .5 - .5;
    if (abs(z__) > eps * 3.) {
	goto L340;
    }

    *ierr = 0;
    if (*x == 0.) {
	goto L200;
    }
    if (*y == 0.) {
	goto L210;
    }
    if (*a == 0.) {
	goto L211;
    }
    if (*b == 0.) {
	goto L201;
    }

    eps = max(eps,1e-15);
    if (max(*a,*b) < eps * .001) {
	goto L230;
    }

    ind = 0;
    a0 = *a;
    b0 = *b;
    x0 = *x;
    y0 = *y;
    if (min(a0,b0) > 1.) {
	goto L30;
    }

/*             PROCEDURE FOR A0 .LE. 1 OR B0 .LE. 1 */

    if (*x <= .5) {
	goto L10;
    }
    ind = 1;
    a0 = *b;
    b0 = *a;
    x0 = *y;
    y0 = *x;

L10:
/* Computing MIN */
    d__1 = eps, d__2 = eps * a0;
    if (b0 < min(d__1,d__2)) {
	goto L80;
    }
/* Computing MIN */
    d__1 = eps, d__2 = eps * b0;
    if (a0 < min(d__1,d__2) && b0 * x0 <= 1.) {
	goto L90;
    }
    if (max(a0,b0) > 1.) {
	goto L20;
    }
    if (a0 >= min(.2,b0)) {
	goto L100;
    }
    if (pow_dd(&x0, &a0) <= .9) {
	goto L100;
    }
    if (x0 >= .3) {
	goto L110;
    }
    n = 20;
    goto L130;

L20:
    if (b0 <= 1.) {
	goto L100;
    }
    if (x0 >= .3) {
	goto L110;
    }
    if (x0 >= .1) {
	goto L21;
    }
    d__1 = x0 * b0;
    if (pow_dd(&d__1, &a0) <= .7) {
	goto L100;
    }
L21:
    if (b0 > 15.) {
	goto L131;
    }
    n = 20;
    goto L130;

/*             PROCEDURE FOR A0 .GT. 1 AND B0 .GT. 1 */

L30:
    if (*a > *b) {
	goto L31;
    }
    lambda = *a - (*a + *b) * *x;
    goto L32;
L31:
    lambda = (*a + *b) * *y - *b;
L32:
    if (lambda >= 0.) {
	goto L40;
    }
    ind = 1;
    a0 = *b;
    b0 = *a;
    x0 = *y;
    y0 = *x;
    lambda = abs(lambda);

L40:
    if (b0 < 40. && b0 * x0 <= .7) {
	goto L100;
    }
    if (b0 < 40.) {
	goto L140;
    }
    if (a0 > b0) {
	goto L50;
    }
    if (a0 <= 100.) {
	goto L120;
    }
    if (lambda > a0 * .03) {
	goto L120;
    }
    goto L180;
L50:
    if (b0 <= 100.) {
	goto L120;
    }
    if (lambda > b0 * .03) {
	goto L120;
    }
    goto L180;

/*            EVALUATION OF THE APPROPRIATE ALGORITHM */

L80:
    *w = fpser_(&a0, &b0, &x0, &eps);
    *w1 = .5 - *w + .5;
    goto L220;

L90:
    *w1 = apser_(&a0, &b0, &x0, &eps);
    *w = .5 - *w1 + .5;
    goto L220;

L100:
    *w = bpser_(&a0, &b0, &x0, &eps);
    *w1 = .5 - *w + .5;
    goto L220;

L110:
    *w1 = bpser_(&b0, &a0, &y0, &eps);
    *w = .5 - *w1 + .5;
    goto L220;

L120:
    d__1 = eps * 15.;
    *w = bfrac_(&a0, &b0, &x0, &y0, &lambda, &d__1);
    *w1 = .5 - *w + .5;
    goto L220;

L130:
    *w1 = bup_(&b0, &a0, &y0, &x0, &n, &eps);
    b0 += n;
L131:
    d__1 = eps * 15.;
    bgrat_(&b0, &a0, &y0, &x0, w1, &d__1, &ierr1);
    *w = .5 - *w1 + .5;
    goto L220;

L140:
    n = (integer) b0;
    b0 -= n;
    if (b0 != 0.) {
	goto L141;
    }
    --n;
    b0 = 1.;
L141:
    *w = bup_(&b0, &a0, &y0, &x0, &n, &eps);
    if (x0 > .7) {
	goto L150;
    }
    *w += bpser_(&a0, &b0, &x0, &eps);
    *w1 = .5 - *w + .5;
    goto L220;

L150:
    if (a0 > 15.) {
	goto L151;
    }
    n = 20;
    *w += bup_(&a0, &b0, &x0, &y0, &n, &eps);
    a0 += n;
L151:
    d__1 = eps * 15.;
    bgrat_(&a0, &b0, &x0, &y0, w, &d__1, &ierr1);
    *w1 = .5 - *w + .5;
    goto L220;

L180:
    d__1 = eps * 100.;
    *w = basym_(&a0, &b0, &lambda, &d__1);
    *w1 = .5 - *w + .5;
    goto L220;

/*               TERMINATION OF THE PROCEDURE */

L200:
    if (*a == 0.) {
	goto L350;
    }
L201:
    *w = 0.;
    *w1 = 1.;
    return 0;

L210:
    if (*b == 0.) {
	goto L360;
    }
L211:
    *w = 1.;
    *w1 = 0.;
    return 0;

L220:
    if (ind == 0) {
	return 0;
    }
    t = *w;
    *w = *w1;
    *w1 = t;
    return 0;

/*           PROCEDURE FOR A AND B .LT. 1.E-3*EPS */

L230:
    *w = *b / (*a + *b);
    *w1 = *a / (*a + *b);
    return 0;

/*                       ERROR RETURN */

L300:
    *ierr = 1;
    return 0;
L310:
    *ierr = 2;
    return 0;
L320:
    *ierr = 3;
    return 0;
L330:
    *ierr = 4;
    return 0;
L340:
    *ierr = 5;
    return 0;
L350:
    *ierr = 6;
    return 0;
L360:
    *ierr = 7;
    return 0;
} /* bratio_ */

doublereal fpser_(doublereal *a, doublereal *b, doublereal *x, doublereal *
	eps)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double log(doublereal), exp(doublereal);

    /* Local variables */
    doublereal c__, s, t, an, tol;
    extern doublereal exparg_(integer *);

/* ----------------------------------------------------------------------- */

/*                 EVALUATION OF I (A,B) */
/*                                X */

/*          FOR B .LT. MIN(EPS,EPS*A) AND X .LE. 0.5. */

/* ----------------------------------------------------------------------- */

/*                  SET  FPSER = X**A */

    ret_val = 1.;
    if (*a <= *eps * .001) {
	goto L10;
    }
    ret_val = 0.;
    t = *a * log(*x);
    if (t < exparg_(&c__1)) {
	return ret_val;
    }
    ret_val = exp(t);

/*                NOTE THAT 1/B(A,B) = B */

L10:
    ret_val = *b / *a * ret_val;
    tol = *eps / *a;
    an = *a + 1.;
    t = *x;
    s = t / an;
L20:
    an += 1.;
    t = *x * t;
    c__ = t / an;
    s += c__;
    if (abs(c__) > tol) {
	goto L20;
    }

    ret_val *= *a * s + 1.;
    return ret_val;
} /* fpser_ */

doublereal apser_(doublereal *a, doublereal *b, doublereal *x, doublereal *
	eps)
{
    /* Initialized data */

    static doublereal g = .577215664901533;

    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    doublereal c__, j, s, t, aj, bx;
    extern doublereal psi_(doublereal *);
    doublereal tol;

/* ----------------------------------------------------------------------- */
/*     APSER YIELDS THE INCOMPLETE BETA RATIO I(SUB(1-X))(B,A) FOR */
/*     A .LE. MIN(EPS,EPS*B), B*X .LE. 1, AND X .LE. 0.5. USED WHEN */
/*     A IS VERY SMALL. USE ONLY IF ABOVE INEQUALITIES ARE SATISFIED. */
/* ----------------------------------------------------------------------- */
/* -------------------- */
/* -------------------- */
    bx = *b * *x;
    t = *x - bx;
    if (*b * *eps > .02) {
	goto L10;
    }
    c__ = log(*x) + psi_(b) + g + t;
    goto L20;
L10:
    c__ = log(bx) + g + t;

L20:
    tol = *eps * 5. * abs(c__);
    j = 1.;
    s = 0.;
L30:
    j += 1.;
    t *= *x - bx / j;
    aj = t / j;
    s += aj;
    if (abs(aj) > tol) {
	goto L30;
    }

    ret_val = -(*a) * (c__ + s);
    return ret_val;
} /* apser_ */

doublereal bpser_(doublereal *a, doublereal *b, doublereal *x, doublereal *
	eps)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Builtin functions */
    double log(doublereal), exp(doublereal), pow_dd(doublereal *, doublereal *
	    );

    /* Local variables */
    doublereal c__;
    integer i__, m;
    doublereal n, t, u, w, z__, a0, b0, apb, tol, sum;
    extern doublereal gam1_(doublereal *), gamln1_(doublereal *), betaln_(
	    doublereal *, doublereal *), algdiv_(doublereal *, doublereal *);

/* ----------------------------------------------------------------------- */
/*     POWER SERIES EXPANSION FOR EVALUATING IX(A,B) WHEN B .LE. 1 */
/*     OR B*X .LE. 0.7.  EPS IS THE TOLERANCE USED. */
/* ----------------------------------------------------------------------- */

    ret_val = 0.;
    if (*x == 0.) {
	return ret_val;
    }
/* ----------------------------------------------------------------------- */
/*            COMPUTE THE FACTOR X**A/(A*BETA(A,B)) */
/* ----------------------------------------------------------------------- */
    a0 = min(*a,*b);
    if (a0 < 1.) {
	goto L10;
    }
    z__ = *a * log(*x) - betaln_(a, b);
    ret_val = exp(z__) / *a;
    goto L70;
L10:
    b0 = max(*a,*b);
    if (b0 >= 8.) {
	goto L60;
    }
    if (b0 > 1.) {
	goto L40;
    }

/*            PROCEDURE FOR A0 .LT. 1 AND B0 .LE. 1 */

    ret_val = pow_dd(x, a);
    if (ret_val == 0.) {
	return ret_val;
    }

    apb = *a + *b;
    if (apb > 1.) {
	goto L20;
    }
    z__ = gam1_(&apb) + 1.;
    goto L30;
L20:
    u = *a + *b - 1.;
    z__ = (gam1_(&u) + 1.) / apb;

L30:
    c__ = (gam1_(a) + 1.) * (gam1_(b) + 1.) / z__;
    ret_val = ret_val * c__ * (*b / apb);
    goto L70;

/*         PROCEDURE FOR A0 .LT. 1 AND 1 .LT. B0 .LT. 8 */

L40:
    u = gamln1_(&a0);
    m = (integer) (b0 - 1.);
    if (m < 1) {
	goto L50;
    }
    c__ = 1.;
    i__1 = m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b0 += -1.;
/* L41: */
	c__ *= b0 / (a0 + b0);
    }
    u = log(c__) + u;

L50:
    z__ = *a * log(*x) - u;
    b0 += -1.;
    apb = a0 + b0;
    if (apb > 1.) {
	goto L51;
    }
    t = gam1_(&apb) + 1.;
    goto L52;
L51:
    u = a0 + b0 - 1.;
    t = (gam1_(&u) + 1.) / apb;
L52:
    ret_val = exp(z__) * (a0 / *a) * (gam1_(&b0) + 1.) / t;
    goto L70;

/*            PROCEDURE FOR A0 .LT. 1 AND B0 .GE. 8 */

L60:
    u = gamln1_(&a0) + algdiv_(&a0, &b0);
    z__ = *a * log(*x) - u;
    ret_val = a0 / *a * exp(z__);
L70:
    if (ret_val == 0. || *a <= *eps * .1) {
	return ret_val;
    }
/* ----------------------------------------------------------------------- */
/*                     COMPUTE THE SERIES */
/* ----------------------------------------------------------------------- */
    sum = 0.;
    n = 0.;
    c__ = 1.;
    tol = *eps / *a;
L100:
    n += 1.;
    c__ = c__ * (.5 - *b / n + .5) * *x;
    w = c__ / (*a + n);
    sum += w;
    if (abs(w) > tol) {
	goto L100;
    }
    ret_val *= *a * sum + 1.;
    return ret_val;
} /* bpser_ */

doublereal bup_(doublereal *a, doublereal *b, doublereal *x, doublereal *y, 
	integer *n, doublereal *eps)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    doublereal d__;
    integer i__, k;
    doublereal l, r__, t, w;
    integer mu;
    doublereal ap1;
    integer nm1, kp1;
    doublereal apb;
    extern doublereal brcmp1_(integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), exparg_(integer *);

/* ----------------------------------------------------------------------- */
/*     EVALUATION OF IX(A,B) - IX(A+N,B) WHERE N IS A POSITIVE INTEGER. */
/*     EPS IS THE TOLERANCE USED. */
/* ----------------------------------------------------------------------- */

/*          OBTAIN THE SCALING FACTOR EXP(-MU) AND */
/*             EXP(MU)*(X**A*Y**B/BETA(A,B))/A */

    apb = *a + *b;
    ap1 = *a + 1.;
    mu = 0;
    d__ = 1.;
    if (*n == 1 || *a < 1.) {
	goto L10;
    }
    if (apb < ap1 * 1.1) {
	goto L10;
    }
    mu = (d__1 = exparg_(&c__1), (integer) abs(d__1));
    k = (integer) exparg_(&c__0);
    if (k < mu) {
	mu = k;
    }
    t = (doublereal) mu;
    d__ = exp(-t);

L10:
    ret_val = brcmp1_(&mu, a, b, x, y) / *a;
    if (*n == 1 || ret_val == 0.) {
	return ret_val;
    }
    nm1 = *n - 1;
    w = d__;

/*          LET K BE THE INDEX OF THE MAXIMUM TERM */

    k = 0;
    if (*b <= 1.) {
	goto L40;
    }
    if (*y > 1e-4) {
	goto L20;
    }
    k = nm1;
    goto L30;
L20:
    r__ = (*b - 1.) * *x / *y - *a;
    if (r__ < 1.) {
	goto L40;
    }
    k = nm1;
    t = (doublereal) nm1;
    if (r__ < t) {
	k = (integer) r__;
    }

/*          ADD THE INCREASING TERMS OF THE SERIES */

L30:
    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {
	l = (doublereal) (i__ - 1);
	d__ = (apb + l) / (ap1 + l) * *x * d__;
	w += d__;
/* L31: */
    }
    if (k == nm1) {
	goto L50;
    }

/*          ADD THE REMAINING TERMS OF THE SERIES */

L40:
    kp1 = k + 1;
    i__1 = nm1;
    for (i__ = kp1; i__ <= i__1; ++i__) {
	l = (doublereal) (i__ - 1);
	d__ = (apb + l) / (ap1 + l) * *x * d__;
	w += d__;
	if (d__ <= *eps * w) {
	    goto L50;
	}
/* L41: */
    }

/*               TERMINATE THE PROCEDURE */

L50:
    ret_val *= w;
    return ret_val;
} /* bup_ */

doublereal bfrac_(doublereal *a, doublereal *b, doublereal *x, doublereal *y, 
	doublereal *lambda, doublereal *eps)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    doublereal c__, e, n, p, r__, s, t, w, c0, c1, r0, an, bn, yp1, anp1, 
	    bnp1, beta, alpha;
    extern doublereal brcomp_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* ----------------------------------------------------------------------- */
/*     CONTINUED FRACTION EXPANSION FOR IX(A,B) WHEN A,B .GT. 1. */
/*     IT IS ASSUMED THAT  LAMBDA = (A + B)*Y - B. */
/* ----------------------------------------------------------------------- */
/* -------------------- */
    ret_val = brcomp_(a, b, x, y);
    if (ret_val == 0.) {
	return ret_val;
    }

    c__ = *lambda + 1.;
    c0 = *b / *a;
    c1 = 1. / *a + 1.;
    yp1 = *y + 1.;

    n = 0.;
    p = 1.;
    s = *a + 1.;
    an = 0.;
    bn = 1.;
    anp1 = 1.;
    bnp1 = c__ / c1;
    r__ = c1 / c__;

/*        CONTINUED FRACTION CALCULATION */

L10:
    n += 1.;
    t = n / *a;
    w = n * (*b - n) * *x;
    e = *a / s;
    alpha = p * (p + c0) * e * e * (w * *x);
    e = (t + 1.) / (c1 + t + t);
    beta = n + w / s + e * (c__ + n * yp1);
    p = t + 1.;
    s += 2.;

/*        UPDATE AN, BN, ANP1, AND BNP1 */

    t = alpha * an + beta * anp1;
    an = anp1;
    anp1 = t;
    t = alpha * bn + beta * bnp1;
    bn = bnp1;
    bnp1 = t;

    r0 = r__;
    r__ = anp1 / bnp1;
    if ((d__1 = r__ - r0, abs(d__1)) <= *eps * r__) {
	goto L20;
    }

/*        RESCALE AN, BN, ANP1, AND BNP1 */

    an /= bnp1;
    bn /= bnp1;
    anp1 = r__;
    bnp1 = 1.;
    goto L10;

/*                 TERMINATION */

L20:
    ret_val *= r__;
    return ret_val;
} /* bfrac_ */

doublereal brcomp_(doublereal *a, doublereal *b, doublereal *x, doublereal *y)
{
    /* Initialized data */

    static doublereal const__ = .398942280401433;

    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(doublereal), exp(doublereal), sqrt(doublereal);

    /* Local variables */
    doublereal c__, e, h__;
    integer i__, n;
    doublereal t, u, v, z__, a0, b0, x0, y0, apb, lnx, lny;
    extern doublereal gam1_(doublereal *), rlog1_(doublereal *), bcorr_(
	    doublereal *, doublereal *), gamln1_(doublereal *);
    doublereal lambda;
    extern doublereal betaln_(doublereal *, doublereal *), algdiv_(doublereal 
	    *, doublereal *), alnrel_(doublereal *);

/* ----------------------------------------------------------------------- */
/*               EVALUATION OF X**A*Y**B/BETA(A,B) */
/* ----------------------------------------------------------------------- */
/* ----------------- */
/*     CONST = 1/SQRT(2*PI) */
/* ----------------- */

    ret_val = 0.;
    if (*x == 0. || *y == 0.) {
	return ret_val;
    }
    a0 = min(*a,*b);
    if (a0 >= 8.) {
	goto L100;
    }

    if (*x > .375) {
	goto L10;
    }
    lnx = log(*x);
    d__1 = -(*x);
    lny = alnrel_(&d__1);
    goto L20;
L10:
    if (*y > .375) {
	goto L11;
    }
    d__1 = -(*y);
    lnx = alnrel_(&d__1);
    lny = log(*y);
    goto L20;
L11:
    lnx = log(*x);
    lny = log(*y);

L20:
    z__ = *a * lnx + *b * lny;
    if (a0 < 1.) {
	goto L30;
    }
    z__ -= betaln_(a, b);
    ret_val = exp(z__);
    return ret_val;
/* ----------------------------------------------------------------------- */
/*              PROCEDURE FOR A .LT. 1 OR B .LT. 1 */
/* ----------------------------------------------------------------------- */
L30:
    b0 = max(*a,*b);
    if (b0 >= 8.) {
	goto L80;
    }
    if (b0 > 1.) {
	goto L60;
    }

/*                   ALGORITHM FOR B0 .LE. 1 */

    ret_val = exp(z__);
    if (ret_val == 0.) {
	return ret_val;
    }

    apb = *a + *b;
    if (apb > 1.) {
	goto L40;
    }
    z__ = gam1_(&apb) + 1.;
    goto L50;
L40:
    u = *a + *b - 1.;
    z__ = (gam1_(&u) + 1.) / apb;

L50:
    c__ = (gam1_(a) + 1.) * (gam1_(b) + 1.) / z__;
    ret_val = ret_val * (a0 * c__) / (a0 / b0 + 1.);
    return ret_val;

/*                ALGORITHM FOR 1 .LT. B0 .LT. 8 */

L60:
    u = gamln1_(&a0);
    n = (integer) (b0 - 1.);
    if (n < 1) {
	goto L70;
    }
    c__ = 1.;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b0 += -1.;
	c__ *= b0 / (a0 + b0);
/* L61: */
    }
    u = log(c__) + u;

L70:
    z__ -= u;
    b0 += -1.;
    apb = a0 + b0;
    if (apb > 1.) {
	goto L71;
    }
    t = gam1_(&apb) + 1.;
    goto L72;
L71:
    u = a0 + b0 - 1.;
    t = (gam1_(&u) + 1.) / apb;
L72:
    ret_val = a0 * exp(z__) * (gam1_(&b0) + 1.) / t;
    return ret_val;

/*                   ALGORITHM FOR B0 .GE. 8 */

L80:
    u = gamln1_(&a0) + algdiv_(&a0, &b0);
    ret_val = a0 * exp(z__ - u);
    return ret_val;
/* ----------------------------------------------------------------------- */
/*              PROCEDURE FOR A .GE. 8 AND B .GE. 8 */
/* ----------------------------------------------------------------------- */
L100:
    if (*a > *b) {
	goto L101;
    }
    h__ = *a / *b;
    x0 = h__ / (h__ + 1.);
    y0 = 1. / (h__ + 1.);
    lambda = *a - (*a + *b) * *x;
    goto L110;
L101:
    h__ = *b / *a;
    x0 = 1. / (h__ + 1.);
    y0 = h__ / (h__ + 1.);
    lambda = (*a + *b) * *y - *b;

L110:
    e = -lambda / *a;
    if (abs(e) > .6) {
	goto L111;
    }
    u = rlog1_(&e);
    goto L120;
L111:
    u = e - log(*x / x0);

L120:
    e = lambda / *b;
    if (abs(e) > .6) {
	goto L121;
    }
    v = rlog1_(&e);
    goto L130;
L121:
    v = e - log(*y / y0);

L130:
    z__ = exp(-(*a * u + *b * v));
    ret_val = const__ * sqrt(*b * x0) * z__ * exp(-bcorr_(a, b));
    return ret_val;
} /* brcomp_ */

doublereal brcmp1_(integer *mu, doublereal *a, doublereal *b, doublereal *x, 
	doublereal *y)
{
    /* Initialized data */

    static doublereal const__ = .398942280401433;

    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(doublereal), sqrt(doublereal), exp(doublereal);

    /* Local variables */
    doublereal c__, e, h__;
    integer i__, n;
    doublereal t, u, v, z__, a0, b0, x0, y0, apb, lnx, lny;
    extern doublereal gam1_(doublereal *), esum_(integer *, doublereal *), 
	    rlog1_(doublereal *), bcorr_(doublereal *, doublereal *), gamln1_(
	    doublereal *);
    doublereal lambda;
    extern doublereal betaln_(doublereal *, doublereal *), algdiv_(doublereal 
	    *, doublereal *), alnrel_(doublereal *);

/* ----------------------------------------------------------------------- */
/*          EVALUATION OF  EXP(MU) * (X**A*Y**B/BETA(A,B)) */
/* ----------------------------------------------------------------------- */
/* ----------------- */
/*     CONST = 1/SQRT(2*PI) */
/* ----------------- */

    a0 = min(*a,*b);
    if (a0 >= 8.) {
	goto L100;
    }

    if (*x > .375) {
	goto L10;
    }
    lnx = log(*x);
    d__1 = -(*x);
    lny = alnrel_(&d__1);
    goto L20;
L10:
    if (*y > .375) {
	goto L11;
    }
    d__1 = -(*y);
    lnx = alnrel_(&d__1);
    lny = log(*y);
    goto L20;
L11:
    lnx = log(*x);
    lny = log(*y);

L20:
    z__ = *a * lnx + *b * lny;
    if (a0 < 1.) {
	goto L30;
    }
    z__ -= betaln_(a, b);
    ret_val = esum_(mu, &z__);
    return ret_val;
/* ----------------------------------------------------------------------- */
/*              PROCEDURE FOR A .LT. 1 OR B .LT. 1 */
/* ----------------------------------------------------------------------- */
L30:
    b0 = max(*a,*b);
    if (b0 >= 8.) {
	goto L80;
    }
    if (b0 > 1.) {
	goto L60;
    }

/*                   ALGORITHM FOR B0 .LE. 1 */

    ret_val = esum_(mu, &z__);
    if (ret_val == 0.) {
	return ret_val;
    }

    apb = *a + *b;
    if (apb > 1.) {
	goto L40;
    }
    z__ = gam1_(&apb) + 1.;
    goto L50;
L40:
    u = *a + *b - 1.;
    z__ = (gam1_(&u) + 1.) / apb;

L50:
    c__ = (gam1_(a) + 1.) * (gam1_(b) + 1.) / z__;
    ret_val = ret_val * (a0 * c__) / (a0 / b0 + 1.);
    return ret_val;

/*                ALGORITHM FOR 1 .LT. B0 .LT. 8 */

L60:
    u = gamln1_(&a0);
    n = (integer) (b0 - 1.);
    if (n < 1) {
	goto L70;
    }
    c__ = 1.;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b0 += -1.;
	c__ *= b0 / (a0 + b0);
/* L61: */
    }
    u = log(c__) + u;

L70:
    z__ -= u;
    b0 += -1.;
    apb = a0 + b0;
    if (apb > 1.) {
	goto L71;
    }
    t = gam1_(&apb) + 1.;
    goto L72;
L71:
    u = a0 + b0 - 1.;
    t = (gam1_(&u) + 1.) / apb;
L72:
    ret_val = a0 * esum_(mu, &z__) * (gam1_(&b0) + 1.) / t;
    return ret_val;

/*                   ALGORITHM FOR B0 .GE. 8 */

L80:
    u = gamln1_(&a0) + algdiv_(&a0, &b0);
    d__1 = z__ - u;
    ret_val = a0 * esum_(mu, &d__1);
    return ret_val;
/* ----------------------------------------------------------------------- */
/*              PROCEDURE FOR A .GE. 8 AND B .GE. 8 */
/* ----------------------------------------------------------------------- */
L100:
    if (*a > *b) {
	goto L101;
    }
    h__ = *a / *b;
    x0 = h__ / (h__ + 1.);
    y0 = 1. / (h__ + 1.);
    lambda = *a - (*a + *b) * *x;
    goto L110;
L101:
    h__ = *b / *a;
    x0 = 1. / (h__ + 1.);
    y0 = h__ / (h__ + 1.);
    lambda = (*a + *b) * *y - *b;

L110:
    e = -lambda / *a;
    if (abs(e) > .6) {
	goto L111;
    }
    u = rlog1_(&e);
    goto L120;
L111:
    u = e - log(*x / x0);

L120:
    e = lambda / *b;
    if (abs(e) > .6) {
	goto L121;
    }
    v = rlog1_(&e);
    goto L130;
L121:
    v = e - log(*y / y0);

L130:
    d__1 = -(*a * u + *b * v);
    z__ = esum_(mu, &d__1);
    ret_val = const__ * sqrt(*b * x0) * z__ * exp(-bcorr_(a, b));
    return ret_val;
} /* brcmp1_ */

/* Subroutine */ int bgrat_(doublereal *a, doublereal *b, doublereal *x, 
	doublereal *y, doublereal *w, doublereal *eps, integer *ierr)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal), exp(doublereal);

    /* Local variables */
    doublereal c__[30], d__[30];
    integer i__;
    doublereal j, l;
    integer n;
    doublereal p, q, r__, s, t, u, v, z__, n2, t2, dj, cn, nu, bm1;
    integer nm1;
    doublereal lnx, sum;
    extern doublereal gam1_(doublereal *);
    doublereal bp2n, coef;
    extern /* Subroutine */ int grat1_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *);
    extern doublereal algdiv_(doublereal *, doublereal *), alnrel_(doublereal 
	    *);

/* ----------------------------------------------------------------------- */
/*     ASYMPTOTIC EXPANSION FOR IX(A,B) WHEN A IS LARGER THAN B. */
/*     THE RESULT OF THE EXPANSION IS ADDED TO W. IT IS ASSUMED */
/*     THAT A .GE. 15 AND B .LE. 1.  EPS IS THE TOLERANCE USED. */
/*     IERR IS A VARIABLE THAT REPORTS THE STATUS OF THE RESULTS. */
/* ----------------------------------------------------------------------- */

    bm1 = *b - .5 - .5;
    nu = *a + bm1 * .5;
    if (*y > .375) {
	goto L10;
    }
    d__1 = -(*y);
    lnx = alnrel_(&d__1);
    goto L11;
L10:
    lnx = log(*x);
L11:
    z__ = -nu * lnx;
    if (*b * z__ == 0.) {
	goto L100;
    }

/*                 COMPUTATION OF THE EXPANSION */
/*                 SET R = EXP(-Z)*Z**B/GAMMA(B) */

    r__ = *b * (gam1_(b) + 1.) * exp(*b * log(z__));
    r__ = r__ * exp(*a * lnx) * exp(bm1 * .5 * lnx);
    u = algdiv_(b, a) + *b * log(nu);
    u = r__ * exp(-u);
    if (u == 0.) {
	goto L100;
    }
    grat1_(b, &z__, &r__, &p, &q, eps);

/* Computing 2nd power */
    d__1 = 1. / nu;
    v = d__1 * d__1 * .25;
    t2 = lnx * .25 * lnx;
    l = *w / u;
    j = q / r__;
    sum = j;
    t = 1.;
    cn = 1.;
    n2 = 0.;
    for (n = 1; n <= 30; ++n) {
	bp2n = *b + n2;
	j = (bp2n * (bp2n + 1.) * j + (z__ + bp2n + 1.) * t) * v;
	n2 += 2.;
	t *= t2;
	cn /= n2 * (n2 + 1.);
	c__[n - 1] = cn;
	s = 0.;
	if (n == 1) {
	    goto L21;
	}
	nm1 = n - 1;
	coef = *b - n;
	i__1 = nm1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    s += coef * c__[i__ - 1] * d__[n - i__ - 1];
/* L20: */
	    coef += *b;
	}
L21:
	d__[n - 1] = bm1 * cn + s / n;
	dj = d__[n - 1] * j;
	sum += dj;
	if (sum <= 0.) {
	    goto L100;
	}
	if (abs(dj) <= *eps * (sum + l)) {
	    goto L30;
	}
/* L22: */
    }

/*                    ADD THE RESULTS TO W */

L30:
    *ierr = 0;
    *w += u * sum;
    return 0;

/*               THE EXPANSION CANNOT BE COMPUTED */

L100:
    *ierr = 1;
    return 0;
} /* bgrat_ */

/* Subroutine */ int grat1_(doublereal *a, doublereal *x, doublereal *r__, 
	doublereal *p, doublereal *q, doublereal *eps)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal), exp(doublereal), sqrt(doublereal);

    /* Local variables */
    doublereal c__, g, h__, j, l, t, w, z__, an, am0, an0, a2n, b2n, cma;
    extern doublereal erf_(doublereal *);
    doublereal tol, sum;
    extern doublereal gam1_(doublereal *);
    doublereal a2nm1, b2nm1;
    extern doublereal rexp_(doublereal *), erfc1_(integer *, doublereal *);

/* ----------------------------------------------------------------------- */
/*        EVALUATION OF THE INCOMPLETE GAMMA RATIO FUNCTIONS */
/*                      P(A,X) AND Q(A,X) */

/*     IT IS ASSUMED THAT A .LE. 1.  EPS IS THE TOLERANCE TO BE USED. */
/*     THE INPUT ARGUMENT R HAS THE VALUE E**(-X)*X**A/GAMMA(A). */
/* ----------------------------------------------------------------------- */
    if (*a * *x == 0.) {
	goto L130;
    }
    if (*a == .5) {
	goto L120;
    }
    if (*x < 1.1) {
	goto L10;
    }
    goto L50;

/*             TAYLOR SERIES FOR P(A,X)/X**A */

L10:
    an = 3.;
    c__ = *x;
    sum = *x / (*a + 3.);
    tol = *eps * .1 / (*a + 1.);
L11:
    an += 1.;
    c__ = -c__ * (*x / an);
    t = c__ / (*a + an);
    sum += t;
    if (abs(t) > tol) {
	goto L11;
    }
    j = *a * *x * ((sum / 6. - .5 / (*a + 2.)) * *x + 1. / (*a + 1.));

    z__ = *a * log(*x);
    h__ = gam1_(a);
    g = h__ + 1.;
    if (*x < .25) {
	goto L20;
    }
    if (*a < *x / 2.59) {
	goto L40;
    }
    goto L30;
L20:
    if (z__ > -.13394) {
	goto L40;
    }

L30:
    w = exp(z__);
    *p = w * g * (.5 - j + .5);
    *q = .5 - *p + .5;
    return 0;

L40:
    l = rexp_(&z__);
    w = l + .5 + .5;
    *q = (w * j - l) * g - h__;
    if (*q < 0.) {
	goto L110;
    }
    *p = .5 - *q + .5;
    return 0;

/*              CONTINUED FRACTION EXPANSION */

L50:
    a2nm1 = 1.;
    a2n = 1.;
    b2nm1 = *x;
    b2n = *x + (1. - *a);
    c__ = 1.;
L51:
    a2nm1 = *x * a2n + c__ * a2nm1;
    b2nm1 = *x * b2n + c__ * b2nm1;
    am0 = a2nm1 / b2nm1;
    c__ += 1.;
    cma = c__ - *a;
    a2n = a2nm1 + cma * a2n;
    b2n = b2nm1 + cma * b2n;
    an0 = a2n / b2n;
    if ((d__1 = an0 - am0, abs(d__1)) >= *eps * an0) {
	goto L51;
    }
    *q = *r__ * an0;
    *p = .5 - *q + .5;
    return 0;

/*                SPECIAL CASES */

L100:
    *p = 0.;
    *q = 1.;
    return 0;

L110:
    *p = 1.;
    *q = 0.;
    return 0;

L120:
    if (*x >= .25) {
	goto L121;
    }
    d__1 = sqrt(*x);
    *p = erf_(&d__1);
    *q = .5 - *p + .5;
    return 0;
L121:
    d__1 = sqrt(*x);
    *q = erfc1_(&c__0, &d__1);
    *p = .5 - *q + .5;
    return 0;

L130:
    if (*x <= *a) {
	goto L100;
    }
    goto L110;
} /* grat1_ */

doublereal basym_(doublereal *a, doublereal *b, doublereal *lambda, 
	doublereal *eps)
{
    /* Initialized data */

    static integer num = 20;
    static doublereal e0 = 1.12837916709551;
    static doublereal e1 = .353553390593274;

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal ret_val, d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal), exp(doublereal);

    /* Local variables */
    doublereal c__[21], d__[21], f, h__;
    integer i__, j, m, n;
    doublereal r__, s, t, u, w, z__, a0[21], b0[21], j0, j1, h2, r0, r1, t0, 
	    t1, w0, z0, z2, hn, zn;
    integer im1, mm1, np1, imj, mmj;
    doublereal sum, znm1, bsum, dsum;
    extern doublereal erfc1_(integer *, doublereal *), rlog1_(doublereal *), 
	    bcorr_(doublereal *, doublereal *);

/* ----------------------------------------------------------------------- */
/*     ASYMPTOTIC EXPANSION FOR IX(A,B) FOR LARGE A AND B. */
/*     LAMBDA = (A + B)*Y - B  AND EPS IS THE TOLERANCE USED. */
/*     IT IS ASSUMED THAT LAMBDA IS NONNEGATIVE AND THAT */
/*     A AND B ARE GREATER THAN OR EQUAL TO 15. */
/* ----------------------------------------------------------------------- */
/* ------------------------ */
/*     ****** NUM IS THE MAXIMUM VALUE THAT N CAN TAKE IN THE DO LOOP */
/*            ENDING AT STATEMENT 50. IT IS REQUIRED THAT NUM BE EVEN. */
/*            THE ARRAYS A0, B0, C, D HAVE DIMENSION NUM + 1. */

/* ------------------------ */
/*     E0 = 2/SQRT(PI) */
/*     E1 = 2**(-3/2) */
/* ------------------------ */
/* ------------------------ */
    ret_val = 0.;
    if (*a >= *b) {
	goto L10;
    }
    h__ = *a / *b;
    r0 = 1. / (h__ + 1.);
    r1 = (*b - *a) / *b;
    w0 = 1. / sqrt(*a * (h__ + 1.));
    goto L20;
L10:
    h__ = *b / *a;
    r0 = 1. / (h__ + 1.);
    r1 = (*b - *a) / *a;
    w0 = 1. / sqrt(*b * (h__ + 1.));

L20:
    d__1 = -(*lambda) / *a;
    d__2 = *lambda / *b;
    f = *a * rlog1_(&d__1) + *b * rlog1_(&d__2);
    t = exp(-f);
    if (t == 0.) {
	return ret_val;
    }
    z0 = sqrt(f);
    z__ = z0 / e1 * .5;
    z2 = f + f;

    a0[0] = r1 * .66666666666666663;
    c__[0] = a0[0] * -.5;
    d__[0] = -c__[0];
    j0 = .5 / e0 * erfc1_(&c__1, &z0);
    j1 = e1;
    sum = j0 + d__[0] * w0 * j1;

    s = 1.;
    h2 = h__ * h__;
    hn = 1.;
    w = w0;
    znm1 = z__;
    zn = z2;
    i__1 = num;
    for (n = 2; n <= i__1; n += 2) {
	hn = h2 * hn;
	a0[n - 1] = r0 * 2. * (h__ * hn + 1.) / (n + 2.);
	np1 = n + 1;
	s += hn;
	a0[np1 - 1] = r1 * 2. * s / (n + 3.);

	i__2 = np1;
	for (i__ = n; i__ <= i__2; ++i__) {
	    r__ = (i__ + 1.) * -.5;
	    b0[0] = r__ * a0[0];
	    i__3 = i__;
	    for (m = 2; m <= i__3; ++m) {
		bsum = 0.;
		mm1 = m - 1;
		i__4 = mm1;
		for (j = 1; j <= i__4; ++j) {
		    mmj = m - j;
/* L30: */
		    bsum += (j * r__ - mmj) * a0[j - 1] * b0[mmj - 1];
		}
/* L31: */
		b0[m - 1] = r__ * a0[m - 1] + bsum / m;
	    }
	    c__[i__ - 1] = b0[i__ - 1] / (i__ + 1.);

	    dsum = 0.;
	    im1 = i__ - 1;
	    i__3 = im1;
	    for (j = 1; j <= i__3; ++j) {
		imj = i__ - j;
/* L40: */
		dsum += d__[imj - 1] * c__[j - 1];
	    }
/* L41: */
	    d__[i__ - 1] = -(dsum + c__[i__ - 1]);
	}

	j0 = e1 * znm1 + (n - 1.) * j0;
	j1 = e1 * zn + n * j1;
	znm1 = z2 * znm1;
	zn = z2 * zn;
	w = w0 * w;
	t0 = d__[n - 1] * w * j0;
	w = w0 * w;
	t1 = d__[np1 - 1] * w * j1;
	sum += t0 + t1;
	if (abs(t0) + abs(t1) <= *eps * sum) {
	    goto L60;
	}
/* L50: */
    }

L60:
    u = exp(-bcorr_(a, b));
    ret_val = e0 * t * u * sum;
    return ret_val;
} /* basym_ */

doublereal spmpar_(integer *i__)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Builtin functions */
    double pow_di(doublereal *, integer *);

    /* Local variables */
    doublereal b;
    integer m;
    doublereal w, z__, bm1, one;
    integer emin, emax;
    doublereal binv;
    integer ibeta;
    extern integer ipmpar_(integer *);

/* ----------------------------------------------------------------------- */

/*     SPMPAR PROVIDES THE SINGLE PRECISION MACHINE CONSTANTS FOR */
/*     THE COMPUTER BEING USED. IT IS ASSUMED THAT THE ARGUMENT */
/*     I IS AN INTEGER HAVING ONE OF THE VALUES 1, 2, OR 3. IF THE */
/*     SINGLE PRECISION ARITHMETIC BEING USED HAS M BASE B DIGITS AND */
/*     ITS SMALLEST AND LARGEST EXPONENTS ARE EMIN AND EMAX, THEN */

/*        SPMPAR(1) = B**(1 - M), THE MACHINE PRECISION, */

/*        SPMPAR(2) = B**(EMIN - 1), THE SMALLEST MAGNITUDE, */

/*        SPMPAR(3) = B**EMAX*(1 - B**(-M)), THE LARGEST MAGNITUDE. */

/* ----------------------------------------------------------------------- */
/*     WRITTEN BY */
/*        ALFRED H. MORRIS, JR. */
/*        NAVAL SURFACE WARFARE CENTER */
/*        DAHLGREN VIRGINIA */
/* ----------------------------------------------------------------------- */

    if (*i__ > 1) {
	goto L10;
    }
    b = (doublereal) ipmpar_(&c__4);
    m = ipmpar_(&c__5);
    i__1 = 1 - m;
    ret_val = pow_di(&b, &i__1);
    return ret_val;

L10:
    if (*i__ > 2) {
	goto L20;
    }
    b = (doublereal) ipmpar_(&c__4);
    emin = ipmpar_(&c__6);
    one = 1.;
    binv = one / b;
    i__1 = emin + 2;
    w = pow_di(&b, &i__1);
    ret_val = w * binv * binv * binv;
    return ret_val;

L20:
    ibeta = ipmpar_(&c__4);
    m = ipmpar_(&c__5);
    emax = ipmpar_(&c__7);

    b = (doublereal) ibeta;
    bm1 = (doublereal) (ibeta - 1);
    one = 1.;
    i__1 = m - 1;
    z__ = pow_di(&b, &i__1);
    w = ((z__ - one) * b + bm1) / (b * z__);

    i__1 = emax - 2;
    z__ = pow_di(&b, &i__1);
    ret_val = w * z__ * b * b;
    return ret_val;
} /* spmpar_ */

doublereal exparg_(integer *l)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    integer b, m;
    doublereal lnb;
    extern integer ipmpar_(integer *);

/* -------------------------------------------------------------------- */
/*     IF L = 0 THEN  EXPARG(L) = THE LARGEST POSITIVE W FOR WHICH */
/*     EXP(W) CAN BE COMPUTED. */

/*     IF L IS NONZERO THEN  EXPARG(L) = THE LARGEST NEGATIVE W FOR */
/*     WHICH THE COMPUTED VALUE OF EXP(W) IS NONZERO. */

/*     NOTE... ONLY AN APPROXIMATE VALUE FOR EXPARG(L) IS NEEDED. */
/* -------------------------------------------------------------------- */

    b = ipmpar_(&c__4);
    if (b != 2) {
	goto L10;
    }
    lnb = .69314718055995;
    goto L50;
L10:
    if (b != 8) {
	goto L20;
    }
    lnb = 2.0794415416798;
    goto L50;
L20:
    if (b != 16) {
	goto L30;
    }
    lnb = 2.7725887222398;
    goto L50;
L30:
    lnb = log((doublereal) b);

L50:
    if (*l == 0) {
	goto L60;
    }
    m = ipmpar_(&c__6) - 1;
    ret_val = m * lnb * .99999;
    return ret_val;
L60:
    m = ipmpar_(&c__7);
    ret_val = m * lnb * .99999;
    return ret_val;
} /* exparg_ */

doublereal esum_(integer *mu, doublereal *x)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    doublereal w;

/* ----------------------------------------------------------------------- */
/*                    EVALUATION OF EXP(MU + X) */
/* ----------------------------------------------------------------------- */
    if (*x > 0.) {
	goto L10;
    }

    if (*mu < 0) {
	goto L20;
    }
    w = *mu + *x;
    if (w > 0.) {
	goto L20;
    }
    ret_val = exp(w);
    return ret_val;

L10:
    if (*mu > 0) {
	goto L20;
    }
    w = *mu + *x;
    if (w < 0.) {
	goto L20;
    }
    ret_val = exp(w);
    return ret_val;

L20:
    w = (doublereal) (*mu);
    ret_val = exp(w) * exp(*x);
    return ret_val;
} /* esum_ */

doublereal rexp_(doublereal *x)
{
    /* Initialized data */

    static doublereal p1 = 9.14041914819518e-10;
    static doublereal p2 = .0238082361044469;
    static doublereal q1 = -.499999999085958;
    static doublereal q2 = .107141568980644;
    static doublereal q3 = -.0119041179760821;
    static doublereal q4 = 5.95130811860248e-4;

    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    doublereal w;

/* ----------------------------------------------------------------------- */
/*            EVALUATION OF THE FUNCTION EXP(X) - 1 */
/* ----------------------------------------------------------------------- */
/* ----------------------- */
    if (abs(*x) > .15) {
	goto L10;
    }
    ret_val = *x * (((p2 * *x + p1) * *x + 1.) / ((((q4 * *x + q3) * *x + q2) 
	    * *x + q1) * *x + 1.));
    return ret_val;

L10:
    w = exp(*x);
    if (*x > 0.) {
	goto L20;
    }
    ret_val = w - .5 - .5;
    return ret_val;
L20:
    ret_val = w * (.5 - 1. / w + .5);
    return ret_val;
} /* rexp_ */

doublereal alnrel_(doublereal *a)
{
    /* Initialized data */

    static doublereal p1 = -1.29418923021993;
    static doublereal p2 = .405303492862024;
    static doublereal p3 = -.0178874546012214;
    static doublereal q1 = -1.62752256355323;
    static doublereal q2 = .747811014037616;
    static doublereal q3 = -.0845104217945565;

    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    doublereal t, w, x, t2;

/* ----------------------------------------------------------------------- */
/*            EVALUATION OF THE FUNCTION LN(1 + A) */
/* ----------------------------------------------------------------------- */
/* -------------------------- */
    if (abs(*a) > .375) {
	goto L10;
    }
    t = *a / (*a + 2.);
    t2 = t * t;
    w = (((p3 * t2 + p2) * t2 + p1) * t2 + 1.) / (((q3 * t2 + q2) * t2 + q1) *
	     t2 + 1.);
    ret_val = t * 2. * w;
    return ret_val;

L10:
    x = *a + 1.;
    ret_val = log(x);
    return ret_val;
} /* alnrel_ */

doublereal rlog1_(doublereal *x)
{
    /* Initialized data */

    static doublereal a = .0566749439387324;
    static doublereal b = .0456512608815524;
    static doublereal p0 = .333333333333333;
    static doublereal p1 = -.224696413112536;
    static doublereal p2 = .00620886815375787;
    static doublereal q1 = -1.27408923933623;
    static doublereal q2 = .354508718369557;

    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    doublereal h__, r__, t, w, w1;

/* ----------------------------------------------------------------------- */
/*             EVALUATION OF THE FUNCTION X - LN(1 + X) */
/* ----------------------------------------------------------------------- */
/* ------------------------ */
/* ------------------------ */
    if (*x < -.39 || *x > .57) {
	goto L100;
    }
    if (*x < -.18) {
	goto L10;
    }
    if (*x > .18) {
	goto L20;
    }

/*              ARGUMENT REDUCTION */

    h__ = *x;
    w1 = 0.;
    goto L30;

L10:
    h__ = *x + .3;
    h__ /= .7;
    w1 = a - h__ * .3;
    goto L30;

L20:
    h__ = *x * .75 - .25;
    w1 = b + h__ / 3.;

/*               SERIES EXPANSION */

L30:
    r__ = h__ / (h__ + 2.);
    t = r__ * r__;
    w = ((p2 * t + p1) * t + p0) / ((q2 * t + q1) * t + 1.);
    ret_val = t * 2. * (1. / (1. - r__) - r__ * w) + w1;
    return ret_val;


L100:
    w = *x + .5 + .5;
    ret_val = *x - log(w);
    return ret_val;
} /* rlog1_ */

doublereal erf_(doublereal *x)
{
    /* Initialized data */

    static doublereal c__ = .564189583547756;
    static doublereal a[5] = { 7.7105849500132e-5,-.00133733772997339,
	    .0323076579225834,.0479137145607681,.128379167095513 };
    static doublereal b[3] = { .00301048631703895,.0538971687740286,
	    .375795757275549 };
    static doublereal p[8] = { -1.36864857382717e-7,.564195517478974,
	    7.21175825088309,43.1622272220567,152.98928504694,
	    339.320816734344,451.918953711873,300.459261020162 };
    static doublereal q[8] = { 1.,12.7827273196294,77.0001529352295,
	    277.585444743988,638.980264465631,931.35409485061,
	    790.950925327898,300.459260956983 };
    static doublereal r__[5] = { 2.10144126479064,26.2370141675169,
	    21.3688200555087,4.6580782871847,.282094791773523 };
    static doublereal s[4] = { 94.153775055546,187.11481179959,
	    99.0191814623914,18.0124575948747 };

    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal), d_sign(doublereal *, doublereal *);

    /* Local variables */
    doublereal t, x2, ax, bot, top;

/* ----------------------------------------------------------------------- */
/*             EVALUATION OF THE REAL ERROR FUNCTION */
/* ----------------------------------------------------------------------- */
/* ------------------------- */
/* ------------------------- */
/* ------------------------- */
/* ------------------------- */
/* ------------------------- */
    ax = abs(*x);
    if (ax > .5) {
	goto L10;
    }
    t = *x * *x;
    top = (((a[0] * t + a[1]) * t + a[2]) * t + a[3]) * t + a[4] + 1.;
    bot = ((b[0] * t + b[1]) * t + b[2]) * t + 1.;
    ret_val = *x * (top / bot);
    return ret_val;

L10:
    if (ax > 4.) {
	goto L20;
    }
    top = ((((((p[0] * ax + p[1]) * ax + p[2]) * ax + p[3]) * ax + p[4]) * ax 
	    + p[5]) * ax + p[6]) * ax + p[7];
    bot = ((((((q[0] * ax + q[1]) * ax + q[2]) * ax + q[3]) * ax + q[4]) * ax 
	    + q[5]) * ax + q[6]) * ax + q[7];
    ret_val = .5 - exp(-(*x) * *x) * top / bot + .5;
    if (*x < 0.) {
	ret_val = -ret_val;
    }
    return ret_val;

L20:
    if (ax >= 5.8) {
	goto L30;
    }
    x2 = *x * *x;
    t = 1. / x2;
    top = (((r__[0] * t + r__[1]) * t + r__[2]) * t + r__[3]) * t + r__[4];
    bot = (((s[0] * t + s[1]) * t + s[2]) * t + s[3]) * t + 1.;
    ret_val = (c__ - top / (x2 * bot)) / ax;
    ret_val = .5 - exp(-x2) * ret_val + .5;
    if (*x < 0.) {
	ret_val = -ret_val;
    }
    return ret_val;

L30:
    ret_val = d_sign(&c_b188, x);
    return ret_val;
} /* erf_ */

doublereal erfc1_(integer *ind, doublereal *x)
{
    /* Initialized data */

    static doublereal c__ = .564189583547756;
    static doublereal a[5] = { 7.7105849500132e-5,-.00133733772997339,
	    .0323076579225834,.0479137145607681,.128379167095513 };
    static doublereal b[3] = { .00301048631703895,.0538971687740286,
	    .375795757275549 };
    static doublereal p[8] = { -1.36864857382717e-7,.564195517478974,
	    7.21175825088309,43.1622272220567,152.98928504694,
	    339.320816734344,451.918953711873,300.459261020162 };
    static doublereal q[8] = { 1.,12.7827273196294,77.0001529352295,
	    277.585444743988,638.980264465631,931.35409485061,
	    790.950925327898,300.459260956983 };
    static doublereal r__[5] = { 2.10144126479064,26.2370141675169,
	    21.3688200555087,4.6580782871847,.282094791773523 };
    static doublereal s[4] = { 94.153775055546,187.11481179959,
	    99.0191814623914,18.0124575948747 };

    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    doublereal e, t, w, ax, bot, top;
    extern doublereal exparg_(integer *);

/* ----------------------------------------------------------------------- */
/*         EVALUATION OF THE COMPLEMENTARY ERROR FUNCTION */

/*          ERFC1(IND,X) = ERFC(X)            IF IND = 0 */
/*          ERFC1(IND,X) = EXP(X*X)*ERFC(X)   OTHERWISE */
/* ----------------------------------------------------------------------- */
/* ------------------------- */
/* ------------------------- */
/* ------------------------- */
/* ------------------------- */
/* ------------------------- */

/*                     ABS(X) .LE. 0.5 */

    ax = abs(*x);
    if (ax > .5) {
	goto L10;
    }
    t = *x * *x;
    top = (((a[0] * t + a[1]) * t + a[2]) * t + a[3]) * t + a[4] + 1.;
    bot = ((b[0] * t + b[1]) * t + b[2]) * t + 1.;
    ret_val = .5 - *x * (top / bot) + .5;
    if (*ind != 0) {
	ret_val = exp(t) * ret_val;
    }
    return ret_val;

/*                  0.5 .LT. ABS(X) .LE. 4 */

L10:
    if (ax > 4.) {
	goto L20;
    }
    top = ((((((p[0] * ax + p[1]) * ax + p[2]) * ax + p[3]) * ax + p[4]) * ax 
	    + p[5]) * ax + p[6]) * ax + p[7];
    bot = ((((((q[0] * ax + q[1]) * ax + q[2]) * ax + q[3]) * ax + q[4]) * ax 
	    + q[5]) * ax + q[6]) * ax + q[7];
    ret_val = top / bot;
    goto L40;

/*                      ABS(X) .GT. 4 */

L20:
    if (*x <= -5.6) {
	goto L50;
    }
    if (*ind != 0) {
	goto L30;
    }
    if (*x > 100.) {
	goto L60;
    }
    if (*x * *x > -exparg_(&c__1)) {
	goto L60;
    }

L30:
/* Computing 2nd power */
    d__1 = 1. / *x;
    t = d__1 * d__1;
    top = (((r__[0] * t + r__[1]) * t + r__[2]) * t + r__[3]) * t + r__[4];
    bot = (((s[0] * t + s[1]) * t + s[2]) * t + s[3]) * t + 1.;
    ret_val = (c__ - t * top / bot) / ax;

/*                      FINAL ASSEMBLY */

L40:
    if (*ind == 0) {
	goto L41;
    }
    if (*x < 0.) {
	ret_val = exp(*x * *x) * 2. - ret_val;
    }
    return ret_val;
L41:
    w = *x * *x;
    t = w;
    e = w - t;
    ret_val = (.5 - e + .5) * exp(-t) * ret_val;
    if (*x < 0.) {
	ret_val = 2. - ret_val;
    }
    return ret_val;

/*             LIMIT VALUE FOR LARGE NEGATIVE X */

L50:
    ret_val = 2.;
    if (*ind != 0) {
	ret_val = exp(*x * *x) * 2.;
    }
    return ret_val;

/*             LIMIT VALUE FOR LARGE POSITIVE X */
/*                       WHEN IND = 0 */

L60:
    ret_val = 0.;
    return ret_val;
} /* erfc1_ */

doublereal gam1_(doublereal *a)
{
    /* Initialized data */

    static doublereal p[7] = { .577215664901533,-.409078193005776,
	    -.230975380857675,.0597275330452234,.0076696818164949,
	    -.00514889771323592,5.89597428611429e-4 };
    static doublereal q[5] = { 1.,.427569613095214,.158451672430138,
	    .0261132021441447,.00423244297896961 };
    static doublereal r__[9] = { -.422784335098468,-.771330383816272,
	    -.244757765222226,.118378989872749,9.30357293360349e-4,
	    -.0118290993445146,.00223047661158249,2.66505979058923e-4,
	    -1.32674909766242e-4 };
    static doublereal s1 = .273076135303957;
    static doublereal s2 = .0559398236957378;

    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    doublereal d__, t, w, bot, top;

/*     ------------------------------------------------------------------ */
/*     COMPUTATION OF 1/GAMMA(A+1) - 1  FOR -0.5 .LE. A .LE. 1.5 */
/*     ------------------------------------------------------------------ */
/*     ------------------- */
/*     ------------------- */
/*     ------------------- */
/*     ------------------- */
/*     ------------------- */
    t = *a;
    d__ = *a - .5;
    if (d__ > 0.) {
	t = d__ - .5;
    }
    if (t < 0.) {
	goto L30;
    } else if (t == 0) {
	goto L10;
    } else {
	goto L20;
    }

L10:
    ret_val = 0.;
    return ret_val;

L20:
    top = (((((p[6] * t + p[5]) * t + p[4]) * t + p[3]) * t + p[2]) * t + p[1]
	    ) * t + p[0];
    bot = (((q[4] * t + q[3]) * t + q[2]) * t + q[1]) * t + 1.;
    w = top / bot;
    if (d__ > 0.) {
	goto L21;
    }
    ret_val = *a * w;
    return ret_val;
L21:
    ret_val = t / *a * (w - .5 - .5);
    return ret_val;

L30:
    top = (((((((r__[8] * t + r__[7]) * t + r__[6]) * t + r__[5]) * t + r__[4]
	    ) * t + r__[3]) * t + r__[2]) * t + r__[1]) * t + r__[0];
    bot = (s2 * t + s1) * t + 1.;
    w = top / bot;
    if (d__ > 0.) {
	goto L31;
    }
    ret_val = *a * (w + .5 + .5);
    return ret_val;
L31:
    ret_val = t * w / *a;
    return ret_val;
} /* gam1_ */

doublereal gamln1_(doublereal *a)
{
    /* Initialized data */

    static doublereal p0 = .577215664901533;
    static doublereal p1 = .844203922187225;
    static doublereal p2 = -.168860593646662;
    static doublereal p3 = -.780427615533591;
    static doublereal p4 = -.402055799310489;
    static doublereal p5 = -.0673562214325671;
    static doublereal p6 = -.00271935708322958;
    static doublereal q1 = 2.88743195473681;
    static doublereal q2 = 3.12755088914843;
    static doublereal q3 = 1.56875193295039;
    static doublereal q4 = .361951990101499;
    static doublereal q5 = .0325038868253937;
    static doublereal q6 = 6.67465618796164e-4;
    static doublereal r0 = .422784335098467;
    static doublereal r1 = .848044614534529;
    static doublereal r2 = .565221050691933;
    static doublereal r3 = .156513060486551;
    static doublereal r4 = .017050248402265;
    static doublereal r5 = 4.97958207639485e-4;
    static doublereal s1 = 1.24313399877507;
    static doublereal s2 = .548042109832463;
    static doublereal s3 = .10155218743983;
    static doublereal s4 = .00713309612391;
    static doublereal s5 = 1.16165475989616e-4;

    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    doublereal w, x;

/* ----------------------------------------------------------------------- */
/*     EVALUATION OF LN(GAMMA(1 + A)) FOR -0.2 .LE. A .LE. 1.25 */
/* ----------------------------------------------------------------------- */
/* ---------------------- */
/* ---------------------- */
    if (*a >= .6) {
	goto L10;
    }
    w = ((((((p6 * *a + p5) * *a + p4) * *a + p3) * *a + p2) * *a + p1) * *a 
	    + p0) / ((((((q6 * *a + q5) * *a + q4) * *a + q3) * *a + q2) * *a 
	    + q1) * *a + 1.);
    ret_val = -(*a) * w;
    return ret_val;

L10:
    x = *a - .5 - .5;
    w = (((((r5 * x + r4) * x + r3) * x + r2) * x + r1) * x + r0) / (((((s5 * 
	    x + s4) * x + s3) * x + s2) * x + s1) * x + 1.);
    ret_val = x * w;
    return ret_val;
} /* gamln1_ */

doublereal psi_(doublereal *xx)
{
    /* Initialized data */

    static doublereal piov4 = .785398163397448;
    static doublereal dx0 = 1.461632144968362341262659542325721325;
    static doublereal p1[7] = { .0089538502298197,4.77762828042627,
	    142.441585084029,1186.45200713425,3633.51846806499,
	    4138.10161269013,1305.60269827897 };
    static doublereal q1[6] = { 44.8452573429826,520.752771467162,
	    2210.0079924783,3641.27349079381,1908.310765963,
	    6.91091682714533e-6 };
    static doublereal p2[4] = { -2.12940445131011,-7.01677227766759,
	    -4.48616543918019,-.648157123766197 };
    static doublereal q2[4] = { 32.2703493791143,89.2920700481861,
	    54.6117738103215,7.77788548522962 };

    /* System generated locals */
    doublereal ret_val, d__1, d__2;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), log(doublereal);

    /* Local variables */
    integer i__, m, n;
    doublereal w, x, z__;
    integer nq;
    doublereal den, aug, sgn, xmx0, xmax1, upper;
    extern integer ipmpar_(integer *);
    doublereal xsmall;
    extern doublereal spmpar_(integer *);

/* --------------------------------------------------------------------- */

/*                 EVALUATION OF THE DIGAMMA FUNCTION */

/*                           ----------- */

/*     PSI(XX) IS ASSIGNED THE VALUE 0 WHEN THE DIGAMMA FUNCTION CANNOT */
/*     BE COMPUTED. */

/*     THE MAIN COMPUTATION INVOLVES EVALUATION OF RATIONAL CHEBYSHEV */
/*     APPROXIMATIONS PUBLISHED IN MATH. COMP. 27, 123-127(1973) BY */
/*     CODY, STRECOK AND THACHER. */

/* --------------------------------------------------------------------- */
/*     PSI WAS WRITTEN AT ARGONNE NATIONAL LABORATORY FOR THE FUNPACK */
/*     PACKAGE OF SPECIAL FUNCTION SUBROUTINES. PSI WAS MODIFIED BY */
/*     A.H. MORRIS (NSWC). */
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/*     PIOV4 = PI/4 */
/*     DX0 = ZERO OF PSI TO EXTENDED PRECISION */

/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/*     COEFFICIENTS FOR RATIONAL APPROXIMATION OF */
/*     PSI(X) / (X - X0),  0.5 .LE. X .LE. 3.0 */

/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/*     COEFFICIENTS FOR RATIONAL APPROXIMATION OF */
/*     PSI(X) - LN(X) + 1 / (2*X),  X .GT. 3.0 */

/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/*     MACHINE DEPENDENT CONSTANTS ... */

/*        XMAX1  = THE SMALLEST POSITIVE FLOATING POINT CONSTANT */
/*                 WITH ENTIRELY INTEGER REPRESENTATION.  ALSO USED */
/*                 AS NEGATIVE OF LOWER BOUND ON ACCEPTABLE NEGATIVE */
/*                 ARGUMENTS AND AS THE POSITIVE ARGUMENT BEYOND WHICH */
/*                 PSI MAY BE REPRESENTED AS ALOG(X). */

/*        XSMALL = ABSOLUTE ARGUMENT BELOW WHICH PI*COTAN(PI*X) */
/*                 MAY BE REPRESENTED BY 1/X. */

/* --------------------------------------------------------------------- */
    xmax1 = (doublereal) ipmpar_(&c__3);
/* Computing MIN */
    d__1 = xmax1, d__2 = 1. / spmpar_(&c__1);
    xmax1 = min(d__1,d__2);
    xsmall = 1e-9;
/* --------------------------------------------------------------------- */
    x = *xx;
    aug = 0.;
    if (x >= .5) {
	goto L200;
    }
/* --------------------------------------------------------------------- */
/*     X .LT. 0.5,  USE REFLECTION FORMULA */
/*     PSI(1-X) = PSI(X) + PI * COTAN(PI*X) */
/* --------------------------------------------------------------------- */
    if (abs(x) > xsmall) {
	goto L100;
    }
    if (x == 0.) {
	goto L400;
    }
/* --------------------------------------------------------------------- */
/*     0 .LT. ABS(X) .LE. XSMALL.  USE 1/X AS A SUBSTITUTE */
/*     FOR  PI*COTAN(PI*X) */
/* --------------------------------------------------------------------- */
    aug = -1. / x;
    goto L150;
/* --------------------------------------------------------------------- */
/*     REDUCTION OF ARGUMENT FOR COTAN */
/* --------------------------------------------------------------------- */
L100:
    w = -x;
    sgn = piov4;
    if (w > 0.) {
	goto L120;
    }
    w = -w;
    sgn = -sgn;
/* --------------------------------------------------------------------- */
/*     MAKE AN ERROR EXIT IF X .LE. -XMAX1 */
/* --------------------------------------------------------------------- */
L120:
    if (w >= xmax1) {
	goto L400;
    }
    nq = (integer) w;
    w -= (doublereal) nq;
    nq = (integer) (w * 4.);
    w = (w - (doublereal) nq * .25) * 4.;
/* --------------------------------------------------------------------- */
/*     W IS NOW RELATED TO THE FRACTIONAL PART OF  4.0 * X. */
/*     ADJUST ARGUMENT TO CORRESPOND TO VALUES IN FIRST */
/*     QUADRANT AND DETERMINE SIGN */
/* --------------------------------------------------------------------- */
    n = nq / 2;
    if (n + n != nq) {
	w = 1. - w;
    }
    z__ = piov4 * w;
    m = n / 2;
    if (m + m != n) {
	sgn = -sgn;
    }
/* --------------------------------------------------------------------- */
/*     DETERMINE FINAL VALUE FOR  -PI*COTAN(PI*X) */
/* --------------------------------------------------------------------- */
    n = (nq + 1) / 2;
    m = n / 2;
    m += m;
    if (m != n) {
	goto L140;
    }
/* --------------------------------------------------------------------- */
/*     CHECK FOR SINGULARITY */
/* --------------------------------------------------------------------- */
    if (z__ == 0.) {
	goto L400;
    }
/* --------------------------------------------------------------------- */
/*     USE COS/SIN AS A SUBSTITUTE FOR COTAN, AND */
/*     SIN/COS AS A SUBSTITUTE FOR TAN */
/* --------------------------------------------------------------------- */
    aug = sgn * (cos(z__) / sin(z__) * 4.);
    goto L150;
L140:
    aug = sgn * (sin(z__) / cos(z__) * 4.);
L150:
    x = 1. - x;
L200:
    if (x > 3.) {
	goto L300;
    }
/* --------------------------------------------------------------------- */
/*     0.5 .LE. X .LE. 3.0 */
/* --------------------------------------------------------------------- */
    den = x;
    upper = p1[0] * x;

    for (i__ = 1; i__ <= 5; ++i__) {
	den = (den + q1[i__ - 1]) * x;
	upper = (upper + p1[i__]) * x;
/* L210: */
    }

    den = (upper + p1[6]) / (den + q1[5]);
    xmx0 = x - dx0;
    ret_val = den * xmx0 + aug;
    return ret_val;
/* --------------------------------------------------------------------- */
/*     IF X .GE. XMAX1, PSI = LN(X) */
/* --------------------------------------------------------------------- */
L300:
    if (x >= xmax1) {
	goto L350;
    }
/* --------------------------------------------------------------------- */
/*     3.0 .LT. X .LT. XMAX1 */
/* --------------------------------------------------------------------- */
    w = 1. / (x * x);
    den = w;
    upper = p2[0] * w;

    for (i__ = 1; i__ <= 3; ++i__) {
	den = (den + q2[i__ - 1]) * w;
	upper = (upper + p2[i__]) * w;
/* L310: */
    }

    aug = upper / (den + q2[3]) - .5 / x + aug;
L350:
    ret_val = aug + log(x);
    return ret_val;
/* --------------------------------------------------------------------- */
/*     ERROR RETURN */
/* --------------------------------------------------------------------- */
L400:
    ret_val = 0.;
    return ret_val;
} /* psi_ */

doublereal betaln_(doublereal *a0, doublereal *b0)
{
    /* Initialized data */

    static doublereal e = .918938533204673;

    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    doublereal a, b, c__, h__;
    integer i__, n;
    doublereal u, v, w, z__;
    extern doublereal gamln_(doublereal *), bcorr_(doublereal *, doublereal *)
	    , algdiv_(doublereal *, doublereal *), alnrel_(doublereal *), 
	    gsumln_(doublereal *, doublereal *);

/* ----------------------------------------------------------------------- */
/*     EVALUATION OF THE LOGARITHM OF THE BETA FUNCTION */
/* ----------------------------------------------------------------------- */
/*     E = 0.5*LN(2*PI) */
/* -------------------------- */
/* -------------------------- */
    a = min(*a0,*b0);
    b = max(*a0,*b0);
    if (a >= 8.) {
	goto L60;
    }
    if (a >= 1.) {
	goto L20;
    }
/* ----------------------------------------------------------------------- */
/*                   PROCEDURE WHEN A .LT. 1 */
/* ----------------------------------------------------------------------- */
    if (b >= 8.) {
	goto L10;
    }
    d__1 = a + b;
    ret_val = gamln_(&a) + (gamln_(&b) - gamln_(&d__1));
    return ret_val;
L10:
    ret_val = gamln_(&a) + algdiv_(&a, &b);
    return ret_val;
/* ----------------------------------------------------------------------- */
/*                PROCEDURE WHEN 1 .LE. A .LT. 8 */
/* ----------------------------------------------------------------------- */
L20:
    if (a > 2.) {
	goto L30;
    }
    if (b > 2.) {
	goto L21;
    }
    ret_val = gamln_(&a) + gamln_(&b) - gsumln_(&a, &b);
    return ret_val;
L21:
    w = 0.;
    if (b < 8.) {
	goto L40;
    }
    ret_val = gamln_(&a) + algdiv_(&a, &b);
    return ret_val;

/*                REDUCTION OF A WHEN B .LE. 1000 */

L30:
    if (b > 1e3) {
	goto L50;
    }
    n = (integer) (a - 1.);
    w = 1.;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	a += -1.;
	h__ = a / b;
	w *= h__ / (h__ + 1.);
/* L31: */
    }
    w = log(w);
    if (b < 8.) {
	goto L40;
    }
    ret_val = w + gamln_(&a) + algdiv_(&a, &b);
    return ret_val;

/*                 REDUCTION OF B WHEN B .LT. 8 */

L40:
    n = (integer) (b - 1.);
    z__ = 1.;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b += -1.;
	z__ *= b / (a + b);
/* L41: */
    }
    ret_val = w + log(z__) + (gamln_(&a) + (gamln_(&b) - gsumln_(&a, &b)));
    return ret_val;

/*                REDUCTION OF A WHEN B .GT. 1000 */

L50:
    n = (integer) (a - 1.);
    w = 1.;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	a += -1.;
	w *= a / (a / b + 1.);
/* L51: */
    }
    ret_val = log(w) - n * log(b) + (gamln_(&a) + algdiv_(&a, &b));
    return ret_val;
/* ----------------------------------------------------------------------- */
/*                   PROCEDURE WHEN A .GE. 8 */
/* ----------------------------------------------------------------------- */
L60:
    w = bcorr_(&a, &b);
    h__ = a / b;
    c__ = h__ / (h__ + 1.);
    u = -(a - .5) * log(c__);
    v = b * alnrel_(&h__);
    if (u <= v) {
	goto L61;
    }
    ret_val = log(b) * -.5 + e + w - v - u;
    return ret_val;
L61:
    ret_val = log(b) * -.5 + e + w - u - v;
    return ret_val;
} /* betaln_ */

doublereal gsumln_(doublereal *a, doublereal *b)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    doublereal x;
    extern doublereal gamln1_(doublereal *), alnrel_(doublereal *);

/* ----------------------------------------------------------------------- */
/*          EVALUATION OF THE FUNCTION LN(GAMMA(A + B)) */
/*          FOR 1 .LE. A .LE. 2  AND  1 .LE. B .LE. 2 */
/* ----------------------------------------------------------------------- */
    x = *a + *b - 2.;
    if (x > .25) {
	goto L10;
    }
    d__1 = x + 1.;
    ret_val = gamln1_(&d__1);
    return ret_val;
L10:
    if (x > 1.25) {
	goto L20;
    }
    ret_val = gamln1_(&x) + alnrel_(&x);
    return ret_val;
L20:
    d__1 = x - 1.;
    ret_val = gamln1_(&d__1) + log(x * (x + 1.));
    return ret_val;
} /* gsumln_ */

doublereal bcorr_(doublereal *a0, doublereal *b0)
{
    /* Initialized data */

    static doublereal c0 = .0833333333333333;
    static doublereal c1 = -.00277777777760991;
    static doublereal c2 = 7.9365066682539e-4;
    static doublereal c3 = -5.9520293135187e-4;
    static doublereal c4 = 8.37308034031215e-4;
    static doublereal c5 = -.00165322962780713;

    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    doublereal a, b, c__, h__, t, w, x, s3, s5, x2, s7, s9, s11;

/* ----------------------------------------------------------------------- */

/*     EVALUATION OF  DEL(A0) + DEL(B0) - DEL(A0 + B0)  WHERE */
/*     LN(GAMMA(A)) = (A - 0.5)*LN(A) - A + 0.5*LN(2*PI) + DEL(A). */
/*     IT IS ASSUMED THAT A0 .GE. 8 AND B0 .GE. 8. */

/* ----------------------------------------------------------------------- */
/* ------------------------ */
    a = min(*a0,*b0);
    b = max(*a0,*b0);

    h__ = a / b;
    c__ = h__ / (h__ + 1.);
    x = 1. / (h__ + 1.);
    x2 = x * x;

/*                SET SN = (1 - X**N)/(1 - X) */

    s3 = x + x2 + 1.;
    s5 = x + x2 * s3 + 1.;
    s7 = x + x2 * s5 + 1.;
    s9 = x + x2 * s7 + 1.;
    s11 = x + x2 * s9 + 1.;

/*                SET W = DEL(B) - DEL(A + B) */

/* Computing 2nd power */
    d__1 = 1. / b;
    t = d__1 * d__1;
    w = ((((c5 * s11 * t + c4 * s9) * t + c3 * s7) * t + c2 * s5) * t + c1 * 
	    s3) * t + c0;
    w *= c__ / b;

/*                   COMPUTE  DEL(A) + W */

/* Computing 2nd power */
    d__1 = 1. / a;
    t = d__1 * d__1;
    ret_val = (((((c5 * t + c4) * t + c3) * t + c2) * t + c1) * t + c0) / a + 
	    w;
    return ret_val;
} /* bcorr_ */

doublereal algdiv_(doublereal *a, doublereal *b)
{
    /* Initialized data */

    static doublereal c0 = .0833333333333333;
    static doublereal c1 = -.00277777777760991;
    static doublereal c2 = 7.9365066682539e-4;
    static doublereal c3 = -5.9520293135187e-4;
    static doublereal c4 = 8.37308034031215e-4;
    static doublereal c5 = -.00165322962780713;

    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    doublereal c__, d__, h__, t, u, v, w, x, s3, s5, x2, s7, s9, s11;
    extern doublereal alnrel_(doublereal *);

/* ----------------------------------------------------------------------- */

/*     COMPUTATION OF LN(GAMMA(B)/GAMMA(A+B)) WHEN B .GE. 8 */

/*                         -------- */

/*     IN THIS ALGORITHM, DEL(X) IS THE FUNCTION DEFINED BY */
/*     LN(GAMMA(X)) = (X - 0.5)*LN(X) - X + 0.5*LN(2*PI) + DEL(X). */

/* ----------------------------------------------------------------------- */
/* ------------------------ */
    if (*a <= *b) {
	goto L10;
    }
    h__ = *b / *a;
    c__ = 1. / (h__ + 1.);
    x = h__ / (h__ + 1.);
    d__ = *a + (*b - .5);
    goto L20;
L10:
    h__ = *a / *b;
    c__ = h__ / (h__ + 1.);
    x = 1. / (h__ + 1.);
    d__ = *b + (*a - .5);

/*                SET SN = (1 - X**N)/(1 - X) */

L20:
    x2 = x * x;
    s3 = x + x2 + 1.;
    s5 = x + x2 * s3 + 1.;
    s7 = x + x2 * s5 + 1.;
    s9 = x + x2 * s7 + 1.;
    s11 = x + x2 * s9 + 1.;

/*                SET W = DEL(B) - DEL(A + B) */

/* Computing 2nd power */
    d__1 = 1. / *b;
    t = d__1 * d__1;
    w = ((((c5 * s11 * t + c4 * s9) * t + c3 * s7) * t + c2 * s5) * t + c1 * 
	    s3) * t + c0;
    w *= c__ / *b;

/*                    COMBINE THE RESULTS */

    d__1 = *a / *b;
    u = d__ * alnrel_(&d__1);
    v = *a * (log(*b) - 1.);
    if (u <= v) {
	goto L30;
    }
    ret_val = w - v - u;
    return ret_val;
L30:
    ret_val = w - u - v;
    return ret_val;
} /* algdiv_ */

doublereal gamln_(doublereal *a)
{
    /* Initialized data */

    static doublereal d__ = .418938533204673;
    static doublereal c0 = .0833333333333333;
    static doublereal c1 = -.00277777777760991;
    static doublereal c2 = 7.9365066682539e-4;
    static doublereal c3 = -5.9520293135187e-4;
    static doublereal c4 = 8.37308034031215e-4;
    static doublereal c5 = -.00165322962780713;

    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    integer i__, n;
    doublereal t, w;
    extern doublereal gamln1_(doublereal *);

/* ----------------------------------------------------------------------- */
/*            EVALUATION OF LN(GAMMA(A)) FOR POSITIVE A */
/* ----------------------------------------------------------------------- */
/*     WRITTEN BY ALFRED H. MORRIS */
/*          NAVAL SURFACE WARFARE CENTER */
/*          DAHLGREN, VIRGINIA */
/* -------------------------- */
/*     D = 0.5*(LN(2*PI) - 1) */
/* -------------------------- */
/* -------------------------- */
/* ----------------------------------------------------------------------- */
    if (*a > .8) {
	goto L10;
    }
    ret_val = gamln1_(a) - log(*a);
    return ret_val;
L10:
    if (*a > 2.25) {
	goto L20;
    }
    t = *a - .5 - .5;
    ret_val = gamln1_(&t);
    return ret_val;

L20:
    if (*a >= 10.) {
	goto L30;
    }
    n = (integer) (*a - 1.25);
    t = *a;
    w = 1.;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	t += -1.;
/* L21: */
	w = t * w;
    }
    d__1 = t - 1.;
    ret_val = gamln1_(&d__1) + log(w);
    return ret_val;

L30:
/* Computing 2nd power */
    d__1 = 1. / *a;
    t = d__1 * d__1;
    w = (((((c5 * t + c4) * t + c3) * t + c2) * t + c1) * t + c0) / *a;
    ret_val = d__ + w + (*a - .5) * (log(*a) - 1.);
    return ret_val;
} /* gamln_ */

integer ipmpar_(integer *i__)
{
    /* Initialized data */

    static integer imach[10] = { 2,48,281474976710655,2,48,-974,1070,95,-926,
	    1070 };

    /* System generated locals */
    integer ret_val;

/* ----------------------------------------------------------------------- */

/*     IPMPAR PROVIDES THE INTEGER MACHINE CONSTANTS FOR THE COMPUTER */
/*     THAT IS USED. IT IS ASSUMED THAT THE ARGUMENT I IS AN INTEGER */
/*     HAVING ONE OF THE VALUES 1-10. IPMPAR(I) HAS THE VALUE ... */

/*  INTEGERS. */

/*     ASSUME INTEGERS ARE REPRESENTED IN THE N-DIGIT, BASE-A FORM */

/*               SIGN ( X(N-1)*A**(N-1) + ... + X(1)*A + X(0) ) */

/*               WHERE 0 .LE. X(I) .LT. A FOR I=0,...,N-1. */

/*     IPMPAR(1) = A, THE BASE. */

/*     IPMPAR(2) = N, THE NUMBER OF BASE-A DIGITS. */

/*     IPMPAR(3) = A**N - 1, THE LARGEST MAGNITUDE. */

/*  FLOATING-POINT NUMBERS. */

/*     IT IS ASSUMED THAT THE SINGLE AND DOUBLE PRECISION FLOATING */
/*     POINT ARITHMETICS HAVE THE SAME BASE, SAY B, AND THAT THE */
/*     NONZERO NUMBERS ARE REPRESENTED IN THE FORM */

/*               SIGN (B**E) * (X(1)/B + ... + X(M)/B**M) */

/*               WHERE X(I) = 0,1,...,B-1 FOR I=1,...,M, */
/*               X(1) .GE. 1, AND EMIN .LE. E .LE. EMAX. */

/*     IPMPAR(4) = B, THE BASE. */

/*  SINGLE-PRECISION */

/*     IPMPAR(5) = M, THE NUMBER OF BASE-B DIGITS. */

/*     IPMPAR(6) = EMIN, THE SMALLEST EXPONENT E. */

/*     IPMPAR(7) = EMAX, THE LARGEST EXPONENT E. */

/*  DOUBLE-PRECISION */

/*     IPMPAR(8) = M, THE NUMBER OF BASE-B DIGITS. */

/*     IPMPAR(9) = EMIN, THE SMALLEST EXPONENT E. */

/*     IPMPAR(10) = EMAX, THE LARGEST EXPONENT E. */

/* ----------------------------------------------------------------------- */

/*     TO DEFINE THIS FUNCTION FOR THE COMPUTER BEING USED, ACTIVATE */
/*     THE DATA STATMENTS FOR THE COMPUTER BY REMOVING THE C FROM */
/*     COLUMN 1. (ALL THE OTHER DATA STATEMENTS SHOULD HAVE C IN */
/*     COLUMN 1.) */

/* ----------------------------------------------------------------------- */

/*     IPMPAR IS AN ADAPTATION OF THE FUNCTION I1MACH, WRITTEN BY */
/*     P.A. FOX, A.D. HALL, AND N.L. SCHRYER (BELL LABORATORIES). */
/*     IPMPAR WAS FORMED BY A.H. MORRIS (NSWC). THE CONSTANTS ARE */
/*     FROM BELL LABORATORIES, NSWC, AND OTHER SOURCES. */

/* ----------------------------------------------------------------------- */

/*     MACHINE CONSTANTS FOR AMDAHL MACHINES. */

/*     DATA IMACH( 1) /   2 / */
/*     DATA IMACH( 2) /  31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /  16 / */
/*     DATA IMACH( 5) /   6 / */
/*     DATA IMACH( 6) / -64 / */
/*     DATA IMACH( 7) /  63 / */
/*     DATA IMACH( 8) /  14 / */
/*     DATA IMACH( 9) / -64 / */
/*     DATA IMACH(10) /  63 / */

/*     MACHINE CONSTANTS FOR THE AT&T 3B SERIES, AT&T */
/*     PC 7300, AND AT&T 6300. */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    24 / */
/*     DATA IMACH( 6) /  -125 / */
/*     DATA IMACH( 7) /   128 / */
/*     DATA IMACH( 8) /    53 / */
/*     DATA IMACH( 9) / -1021 / */
/*     DATA IMACH(10) /  1024 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 1700 SYSTEM. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   33 / */
/*     DATA IMACH( 3) / 8589934591 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   24 / */
/*     DATA IMACH( 6) / -256 / */
/*     DATA IMACH( 7) /  255 / */
/*     DATA IMACH( 8) /   60 / */
/*     DATA IMACH( 9) / -256 / */
/*     DATA IMACH(10) /  255 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 5700 SYSTEM. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   39 / */
/*     DATA IMACH( 3) / 549755813887 / */
/*     DATA IMACH( 4) /    8 / */
/*     DATA IMACH( 5) /   13 / */
/*     DATA IMACH( 6) /  -50 / */
/*     DATA IMACH( 7) /   76 / */
/*     DATA IMACH( 8) /   26 / */
/*     DATA IMACH( 9) /  -50 / */
/*     DATA IMACH(10) /   76 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 6700/7700 SYSTEMS. */

/*     DATA IMACH( 1) /      2 / */
/*     DATA IMACH( 2) /     39 / */
/*     DATA IMACH( 3) / 549755813887 / */
/*     DATA IMACH( 4) /      8 / */
/*     DATA IMACH( 5) /     13 / */
/*     DATA IMACH( 6) /    -50 / */
/*     DATA IMACH( 7) /     76 / */
/*     DATA IMACH( 8) /     26 / */
/*     DATA IMACH( 9) / -32754 / */
/*     DATA IMACH(10) /  32780 / */

/*     MACHINE CONSTANTS FOR THE CDC 6000/7000 SERIES */
/*     60 BIT ARITHMETIC, AND THE CDC CYBER 995 64 BIT */
/*     ARITHMETIC (NOS OPERATING SYSTEM). */


/*     MACHINE CONSTANTS FOR THE CDC CYBER 995 64 BIT */
/*     ARITHMETIC (NOS/VE OPERATING SYSTEM). */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    63 / */
/*     DATA IMACH( 3) / 9223372036854775807 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    48 / */
/*     DATA IMACH( 6) / -4096 / */
/*     DATA IMACH( 7) /  4095 / */
/*     DATA IMACH( 8) /    96 / */
/*     DATA IMACH( 9) / -4096 / */
/*     DATA IMACH(10) /  4095 / */

/*     MACHINE CONSTANTS FOR THE CRAY 1, XMP, 2, AND 3. */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    63 / */
/*     DATA IMACH( 3) / 9223372036854775807 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    47 / */
/*     DATA IMACH( 6) / -8189 / */
/*     DATA IMACH( 7) /  8190 / */
/*     DATA IMACH( 8) /    94 / */
/*     DATA IMACH( 9) / -8099 / */
/*     DATA IMACH(10) /  8190 / */

/*     MACHINE CONSTANTS FOR THE DATA GENERAL ECLIPSE S/200. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   15 / */
/*     DATA IMACH( 3) / 32767 / */
/*     DATA IMACH( 4) /   16 / */
/*     DATA IMACH( 5) /    6 / */
/*     DATA IMACH( 6) /  -64 / */
/*     DATA IMACH( 7) /   63 / */
/*     DATA IMACH( 8) /   14 / */
/*     DATA IMACH( 9) /  -64 / */
/*     DATA IMACH(10) /   63 / */

/*     MACHINE CONSTANTS FOR THE HARRIS 220. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   23 / */
/*     DATA IMACH( 3) / 8388607 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   23 / */
/*     DATA IMACH( 6) / -127 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   38 / */
/*     DATA IMACH( 9) / -127 / */
/*     DATA IMACH(10) /  127 / */

/*     MACHINE CONSTANTS FOR THE HONEYWELL 600/6000 */
/*     AND DPS 8/70 SERIES. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   35 / */
/*     DATA IMACH( 3) / 34359738367 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   27 / */
/*     DATA IMACH( 6) / -127 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   63 / */
/*     DATA IMACH( 9) / -127 / */
/*     DATA IMACH(10) /  127 / */

/*     MACHINE CONSTANTS FOR THE HP 2100 */
/*     3 WORD DOUBLE PRECISION OPTION WITH FTN4 */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   15 / */
/*     DATA IMACH( 3) / 32767 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   23 / */
/*     DATA IMACH( 6) / -128 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   39 / */
/*     DATA IMACH( 9) / -128 / */
/*     DATA IMACH(10) /  127 / */

/*     MACHINE CONSTANTS FOR THE HP 2100 */
/*     4 WORD DOUBLE PRECISION OPTION WITH FTN4 */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   15 / */
/*     DATA IMACH( 3) / 32767 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   23 / */
/*     DATA IMACH( 6) / -128 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   55 / */
/*     DATA IMACH( 9) / -128 / */
/*     DATA IMACH(10) /  127 / */

/*     MACHINE CONSTANTS FOR THE HP 9000. */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    24 / */
/*     DATA IMACH( 6) /  -126 / */
/*     DATA IMACH( 7) /   128 / */
/*     DATA IMACH( 8) /    53 / */
/*     DATA IMACH( 9) / -1021 / */
/*     DATA IMACH(10) /  1024 / */

/*     MACHINE CONSTANTS FOR THE IBM 360/370 SERIES, */
/*     THE ICL 2900, THE ITEL AS/6, THE XEROX SIGMA */
/*     5/7/9 AND THE SEL SYSTEMS 85/86. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /   16 / */
/*     DATA IMACH( 5) /    6 / */
/*     DATA IMACH( 6) /  -64 / */
/*     DATA IMACH( 7) /   63 / */
/*     DATA IMACH( 8) /   14 / */
/*     DATA IMACH( 9) /  -64 / */
/*     DATA IMACH(10) /   63 / */

/*     MACHINE CONSTANTS FOR THE IBM PC. */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    24 / */
/*     DATA IMACH( 6) /  -125 / */
/*     DATA IMACH( 7) /   128 / */
/*     DATA IMACH( 8) /    53 / */
/*     DATA IMACH( 9) / -1021 / */
/*     DATA IMACH(10) /  1024 / */

/*     MACHINE CONSTANTS FOR THE MACINTOSH II - ABSOFT */
/*     MACFORTRAN II. */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    24 / */
/*     DATA IMACH( 6) /  -125 / */
/*     DATA IMACH( 7) /   128 / */
/*     DATA IMACH( 8) /    53 / */
/*     DATA IMACH( 9) / -1021 / */
/*     DATA IMACH(10) /  1024 / */

/*     MACHINE CONSTANTS FOR THE MICROVAX - VMS FORTRAN. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   24 / */
/*     DATA IMACH( 6) / -127 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   56 / */
/*     DATA IMACH( 9) / -127 / */
/*     DATA IMACH(10) /  127 / */

/*     MACHINE CONSTANTS FOR THE PDP-10 (KA PROCESSOR). */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   35 / */
/*     DATA IMACH( 3) / 34359738367 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   27 / */
/*     DATA IMACH( 6) / -128 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   54 / */
/*     DATA IMACH( 9) / -101 / */
/*     DATA IMACH(10) /  127 / */

/*     MACHINE CONSTANTS FOR THE PDP-10 (KI PROCESSOR). */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   35 / */
/*     DATA IMACH( 3) / 34359738367 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   27 / */
/*     DATA IMACH( 6) / -128 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   62 / */
/*     DATA IMACH( 9) / -128 / */
/*     DATA IMACH(10) /  127 / */

/*     MACHINE CONSTANTS FOR THE PDP-11 FORTRAN SUPPORTING */
/*     32-BIT INTEGER ARITHMETIC. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   24 / */
/*     DATA IMACH( 6) / -127 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   56 / */
/*     DATA IMACH( 9) / -127 / */
/*     DATA IMACH(10) /  127 / */

/*     MACHINE CONSTANTS FOR THE SEQUENT BALANCE 8000. */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    24 / */
/*     DATA IMACH( 6) /  -125 / */
/*     DATA IMACH( 7) /   128 / */
/*     DATA IMACH( 8) /    53 / */
/*     DATA IMACH( 9) / -1021 / */
/*     DATA IMACH(10) /  1024 / */

/*     MACHINE CONSTANTS FOR THE SILICON GRAPHICS IRIS-4D */
/*     SERIES (MIPS R3000 PROCESSOR). */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    24 / */
/*     DATA IMACH( 6) /  -125 / */
/*     DATA IMACH( 7) /   128 / */
/*     DATA IMACH( 8) /    53 / */
/*     DATA IMACH( 9) / -1021 / */
/*     DATA IMACH(10) /  1024 / */

/*     MACHINE CONSTANTS FOR THE SUN 3. */

/*     DATA IMACH( 1) /     2 / */
/*     DATA IMACH( 2) /    31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /     2 / */
/*     DATA IMACH( 5) /    24 / */
/*     DATA IMACH( 6) /  -125 / */
/*     DATA IMACH( 7) /   128 / */
/*     DATA IMACH( 8) /    53 / */
/*     DATA IMACH( 9) / -1021 / */
/*     DATA IMACH(10) /  1024 / */

/*     MACHINE CONSTANTS FOR THE UNIVAC 1100 SERIES. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   35 / */
/*     DATA IMACH( 3) / 34359738367 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   27 / */
/*     DATA IMACH( 6) / -128 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   60 / */
/*     DATA IMACH( 9) /-1024 / */
/*     DATA IMACH(10) / 1023 / */

/*     MACHINE CONSTANTS FOR THE VAX 11/780. */

/*     DATA IMACH( 1) /    2 / */
/*     DATA IMACH( 2) /   31 / */
/*     DATA IMACH( 3) / 2147483647 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   24 / */
/*     DATA IMACH( 6) / -127 / */
/*     DATA IMACH( 7) /  127 / */
/*     DATA IMACH( 8) /   56 / */
/*     DATA IMACH( 9) / -127 / */
/*     DATA IMACH(10) /  127 / */

    ret_val = imach[(0 + (0 + (*i__ - 1 << 2))) / 4];
    return ret_val;
} /* ipmpar_ */

#ifdef __cplusplus
	}
#endif
