/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California
 * 
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 *
 * License:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * \file
 * Description not yet available.
 */
#if !defined(__CONSTRUCTORS_H__)
# define __CONSTRUCTORS_H__
 int constrained_munimxization(int,int,int,double *);
 extern int nx;
 extern int inumber1;
 extern int number3;
 extern int number31;
// 
//const int nx=10;
//const int number3=31;
//const int number31=number3+1;
//const int inumber1=4000;

/**
 * Description not yet available.
 * \param
 */
struct doublestar
{
  int index_max;
  int index_min;
  doublereal * d;
  doublestar(integer);
  doublestar(integer,integer);
  ~doublestar();
  operator doublereal * ();
  doublereal& operator[] (int i){ return *(d+i);}
  doublereal& operator[] (long int i){ return *(d+i);}
};

/**
 * Description not yet available.
 * \param
 */
struct gggg24 {
  doublereal uertte;
  integer itstep, phase;
  doublereal runtim;
  doublereal *accinf;
  gggg24();
};

#define gggg241 gggg24

/**
 * Description not yet available.
 * \param
 */
struct gggg25 {
    doublereal *x, *x0, *x1, *xmin, *resmin, *d, *d0,
	     *dd, *difx, xnorm, x0norm, dnorm, d0norm, sig, sig0,
	     sigmin, dscal, upsi, upsi0, upsi1, upsist, upsim, psi, psi0, 
	    psi1, psist, psimin, phi, phi0, phi1, phimin, fx, fx0, fx1, fxst, 
	    fmin, b2n, b2n0, dirder, cosphi;
gggg25();
};

#define gggg251 gggg25

/**
 * Description not yet available.
 * \param
 */
struct gggg26 {
    //doublereal *gradf, gfn, *qgf, *gres	/* was ** */,
//	     *gresn, *gphi0, *gphi1;
    doublereal *gradf, gfn, *qgf, *gres	/* was ** */,
	     *gresn;
    doublestar gphi0, gphi1;
gggg26();
};

#define gggg261 gggg26

/**
 * Description not yet available.
 * \param
 */
struct gggg27 {
    doublereal *qr	/* was ** */, *betaq, *diag
	    , *cscal, *colle;
    integer *colno, *perm, *perm1, rank;
  gggg27();
};

#define gggg271 gggg27

/**
 * Description not yet available.
 * \param
 */
struct gggg00 {
    logical *val, *gconst;
    integer *gunit	/* was ** */;
    logical *llow, *lup;
  gggg00();
};

#define gggg001 gggg00

/**
 * Description not yet available.
 * \param
 */
struct gggg01 {
    logical intakt, inx, std, te0, te1, te2, te3, sinumbervul, ident, eqres, 
	    silent, wwuq3, cold;
  gggg01(logical _wwuq3, logical _te0, logical _te1,
    logical _te2, logical _te3, logical _cold);
};

#define gggg011 gggg01

/**
 * Description not yet available.
 * \param
 */
struct gggg02 {
    doublereal *a	/* was ** */, *diag0, scalm, scalm2, 
	    matsc;
  gggg02();
};

#define gggg021 gggg02

/**
 * Description not yet available.
 * \param
 */
struct gggg03 {
    integer *bind, *bind0, *violis, *alist__, *sort;
  gggg03();
};

#define gggg031 gggg03

/**
 * Description not yet available.
 * \param
 */
struct gggg04 {
    doublereal *res, *res0, *res1, *resst, *u, *u0,
	     *w, *w1, *work, *yu, *slack, scf, 
	    scf0, infeas;
  gggg04();
};

#define gggg041 gggg04

/**
 * Description not yet available.
 * \param
 */
struct gggg05 {
    integer n, numberw, numberv, nr, nres;
    gggg05(int _n,int _numberw, int _hg);
};

#define gggg051 gggg05

/**
 * Description not yet available.
 * \param
 */
struct gggg06 {
    doublereal epsmac, tolmac, deldif;
};

#define gggg061 gggg06

/**
 * Description not yet available.
 * \param
 */
struct gggg07 {
    gggg07(doublereal _jgh4,doublereal _jgh5);
    doublereal jgh4, jgh41, del, delmin, jgh5, wdg5, wdg9, wdg10, wdg11, wdg111,
	     eta, ny, wdg7, c1d, scfmax, wdg5qp, wdg5fac, wdg5max, updmy0;
    integer wdg6, ifill1;
};

#define gggg071 gggg07

/**
 * Description not yet available.
 * \param
 */
struct gggg08 {
    doublereal alpha, beta, theta, wdg8, sigla, delta, stptrm, delta1, 
	    stmaxl;
};

#define gggg081 gggg08

/**
 * Description not yet available.
 * \param
 */
struct gggg09 {
    integer icf, icgf, cfincr, *cres, *cgres;
  gggg09();
};

#define gggg091 gggg09

/**
 * Description not yet available.
 * \param
 */
struct gggg10 {
    logical ffuerr, *cfuerr;
  gggg10();
};

#define gggg101 gggg10

/**
 * Description not yet available.
 * \param
 */
struct gggg11 {
    doublereal wdg4;
    integer clow, lwdg2, wdg3, wdg1;
};

#define gggg111 gggg11

/**
 * Description not yet available.
 * \param
 */
struct gggg12 {
    char *name;
  gggg12();
};

#define gggg121 gggg12

/**
 * Description not yet available.
 * \param
 */
struct gggg13 {
    doublereal epsdif;
};

#define gggg131 gggg13

/**
 * Description not yet available.
 * \param
 */
struct gggg14 {
    integer jgh1, jgh2;
};

#define gggg141 gggg14

/**
 * Description not yet available.
 * \param
 */
struct gggg15 {
    doublereal *ug, *og, *delfac;
  gggg15();
};

#define gggg151 gggg15

/**
 * Description not yet available.
 * \param
 */
struct gggg16 {
    integer jgh3;
};

#define gggg161 gggg16

/**
 * Description not yet available.
 * \param
 */
struct gggg17 {
    doublereal *xst;
  gggg17();
};

#define gggg171 gggg17

/**
 * Description not yet available.
 * \param
 */
struct gggg18 {
    independent_variables xtr;
    doublereal *xsc, *fu, *fugrad	/* was *[
    //doublereal *xtr, *xsc, *fu, *fugrad	/ * was *[
	    number3+1] */, *fud	/* was ** */, wwuq5, wdg5bnd;
  gggg18(int nvar,doublereal _wwuq5, doublereal _wdg5bnd);
};

#define gggg181 gggg18

/**
 * Description not yet available.
 * \param
 */
struct gggg19 {
    logical wwuq2, wwuq4, corr;
    integer wwuq6;
    gggg19(logical _wwuq2,logical _wwuq4, integer _wwuq6);
};

#define gggg191 gggg19

/**
 * Description not yet available.
 * \param
 */
struct gggg20 {
    integer qpterm, fcount;
};

#define gggg201 gggg20

/**
 * Description not yet available.
 * \param
 */
struct gggg21 {
    doublereal sstr, riitr;
    integer iptr, iqtr, *aitr;
  gggg21();
};

#define gggg211 gggg21

/**
 * Description not yet available.
 * \param
 */
struct gggg22 {
    doublereal rnorm, rlow;
    integer ndual, mi, me, iq;
};

#define gggg221 gggg22

/**
 * Description not yet available.
 * \param
 */
struct gggg23 {
    doublereal *xj,*ddual,*r,*np,*ud,*ud1;
  gggg23();
};

extern integer stj1;
extern integer stj2;
extern integer stj3;
extern integer stj4;
extern integer stj5;
extern integer stj23;
extern integer stj210;
extern logical stj8;
extern integer stj9;
extern integer stj2800;
extern integer stj21;
extern integer stj22;
extern integer stj41;
extern integer stj43;
extern integer stj42;
extern integer stj17;
extern integer stj18;
extern integer stj19;
extern integer stj110;
extern integer stj20;
extern integer stj27;
extern integer stj24;
extern integer stj25;
extern integer stj28;
extern integer stj26;
extern integer stj40;
extern integer stj118;
extern integer stj44;
extern integer stj45;
extern integer stj2910;
extern integer stj29;
extern doublereal stj123;
extern doublereal stj124;

extern gggg23 *gggg23_1;
extern gggg24 *gggg24_1;
extern gggg25 *gggg25_1;
extern gggg26 *gggg26_1;
extern gggg27 *gggg27_1;
extern gggg00 *gggg00_1;
extern gggg01 *gggg01_1;
extern gggg02 *gggg02_1;
extern gggg03 *gggg03_1;
extern gggg04 *gggg04_1;
extern gggg05 *gggg05_1;
extern gggg06 *gggg06_1;
extern gggg07 *gggg07_1;
extern gggg08 *gggg08_1;
extern gggg09 *gggg09_1;
extern gggg10 *gggg10_1;
extern gggg11 *gggg11_1;
extern gggg12 *gggg12_1;
extern gggg13 *gggg13_1;
extern gggg14 *gggg14_1;
extern gggg15 *gggg15_1;
extern gggg16 *gggg16_1;
extern gggg17 *gggg17_1;
extern gggg18 *gggg18_1;
extern gggg19 *gggg19_1;
extern gggg20 *gggg20_1;
extern gggg21 *gggg21_1;
extern gggg22 *gggg22_1;

#ifdef __cplusplus
extern "C" {
#endif
  void make_all_classes(int,int,int);
#ifdef __cplusplus
	}
#endif

/**
 * Description not yet available.
 * \param
 */
struct intstar
{
  int index_max;
  integer * d;
  intstar(integer);
  ~intstar();
  integer& operator[] (int i){return *(d+i);}
  integer& operator[] (long int i){return *(d+i);}
  operator integer * () { return d;}
};

#endif
