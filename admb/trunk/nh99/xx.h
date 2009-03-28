/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
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


#if !defined(__CONSTRUCTORS_H__)
# define __CONSTRUCTORS_H__
 int constrained_minimization(int,int,int,double *);
 extern int nx;
 extern int maxit;
 extern int nresm;
 extern int nresm1;
// 
//const int nx=10;
//const int nresm=31;
//const int nresm1=nresm+1;
//const int maxit=4000;

struct doublestar
{
  int index_max;
  int index_min;
  doublereal * d;
  doublestar(integer);
  doublestar(integer,integer);
  ~doublestar();
  operator doublereal * ();
  doublereal& operator[] (int);
};

struct gggg24 {
  real optite;
  integer itstep, phase;
  real runtim;
  doublereal *accinf;
  gggg24();
};

#define gggg241 gggg24

struct gggg25 {
    doublereal *x, *x0, *x1, *xmin, *resmin, *d, *d0,
	     *dd, *difx, xnorm, x0norm, dnorm, d0norm, sig, sig0,
	     sigmin, dscal, upsi, upsi0, upsi1, upsist, upsim, psi, psi0, 
	    psi1, psist, psimin, phi, phi0, phi1, phimin, fx, fx0, fx1, fxst, 
	    fmin, b2n, b2n0, dirder, cosphi;
gggg25();
};

#define gggg251 gggg25

struct gggg26 {
    //doublereal *gradf, gfn, *qgf, *gres	/* was ** */,
//	     *gresn, *gphi0, *gphi1;
    doublereal *gradf, gfn, *qgf, *gres	/* was ** */,
	     *gresn;
    doublestar gphi0, gphi1;
gggg26();
};

#define gggg261 gggg26

struct gggg27 {
    doublereal *qr	/* was ** */, *betaq, *diag
	    , *cscal, *colle;
    integer *colno, *perm, *perm1, rank;
  gggg27();
};

#define gggg271 gggg27

struct gggg00 {
    logical *val, *gconst;
    integer *gunit	/* was ** */;
    logical *llow, *lup;
  gggg00();
};

#define gggg001 gggg00

struct gggg01 {
    logical intakt, inx, std, te0, te1, te2, te3, singul, ident, eqres, 
	    silent, analyt, cold;
  gggg01(logical _analyt, logical _te0, logical _te1,
    logical _te2, logical _te3, logical _cold);
};

#define gggg011 gggg01

struct gggg02 {
    doublereal *a	/* was ** */, *diag0, scalm, scalm2, 
	    matsc;
  gggg02();
};

#define gggg021 gggg02

struct gggg03 {
    integer *bind, *bind0, *violis, *alist__, *sort;
  gggg03();
};

#define gggg031 gggg03

struct gggg04 {
    doublereal *res, *res0, *res1, *resst, *u, *u0,
	     *w, *w1, *work, *yu, *slack, scf, 
	    scf0, infeas;
  gggg04();
};

#define gggg041 gggg04

struct gggg05 {
    integer n, nh, ng, nr, nres;
    gggg05(int _n,int _nh, int _hg);
};

#define gggg051 gggg05

struct gggg06 {
    doublereal epsmac, tolmac, deldif;
};

#define gggg061 gggg06

struct gggg07 {
    gggg07(int _del0,int _tau0);
    doublereal del0, del01, del, delmin, tau0, tau, smalld, smallw, rho, rho1,
	     eta, ny, epsx, c1d, scfmax, tauqp, taufac, taumax, updmy0;
    integer iterma, ifill1;
};

#define gggg071 gggg07

struct gggg08 {
    doublereal alpha, beta, theta, sigsm, sigla, delta, stptrm, delta1, 
	    stmaxl;
};

#define gggg081 gggg08

struct gggg09 {
    integer icf, icgf, cfincr, *cres, *cgres;
  gggg09();
};

#define gggg091 gggg09

struct gggg10 {
    logical ffuerr, *cfuerr;
  gggg10();
};

#define gggg101 gggg10

struct gggg11 {
    doublereal level;
    integer clow, lastdw, lastup, lastch;
};

#define gggg111 gggg11

struct gggg12 {
    char *name;
  gggg12();
};

#define gggg121 gggg12

struct gggg13 {
    doublereal epsdif;
};

#define gggg131 gggg13

struct gggg14 {
    integer prou, meu;
};

#define gggg141 gggg14

struct gggg15 {
    doublereal *ug, *og, *delfac;
  gggg15();
};

#define gggg151 gggg15

struct gggg16 {
    integer nreset;
};

#define gggg161 gggg16

struct gggg17 {
    doublereal *xst;
  gggg17();
};

#define gggg171 gggg17

struct gggg18 {
    independent_variables xtr;
    doublereal *xsc, *fu, *fugrad	/* was *[
    //doublereal *xtr, *xsc, *fu, *fugrad	/* was *[
	    nresm+1] */, *fud	/* was ** */, epsfcn, taubnd;
  gggg18(int nvar,doublereal _epsfcn, doublereal _taubnd);
};

#define gggg181 gggg18

struct gggg19 {
    logical bloc, valid, corr;
    integer difftype;
    gggg19(logical _bloc,logical _valid, integer _difftype);
};

#define gggg191 gggg19

struct gggg20 {
    integer qpterm, fcount;
};

#define gggg201 gggg20

struct gggg21 {
    doublereal sstr, riitr;
    integer iptr, iqtr, *aitr;
  gggg21();
};

#define gggg211 gggg21

struct gggg22 {
    doublereal rnorm, rlow;
    integer ndual, mi, me, iq;
};

#define gggg221 gggg22

struct gggg23 {
    doublereal *xj,*ddual,*r,*np,*ud,*ud1;
  gggg23();
};

extern integer c__9;
extern integer c__1;
extern integer c__3;
extern integer c__2;
extern integer c__0;
extern integer c__13;
extern integer c__110;
extern logical c_false;
extern integer c__5;
extern integer c__1800;
extern integer c__11;
extern integer c__12;
extern integer c__21;
extern integer c__23;
extern integer c__22;
extern integer c__4;
extern integer c_n1;
extern integer c__6;
extern integer c__7;
extern integer c__10;
extern integer c__17;
extern integer c__14;
extern integer c__15;
extern integer c__18;
extern integer c__16;
extern integer c__20;
extern integer c__8;
extern integer c__24;
extern integer c__25;
extern integer c__1910;
extern integer c__19;
extern doublereal c_b1099;
extern doublereal c_b1100;

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


struct intstar
{
  int index_max;
  integer * d;
  intstar(integer);
  ~intstar();
  integer& operator[] (int);
  operator integer * () { return d;}
};

#endif
