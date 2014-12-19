/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
/* eval_extern.f -- translated by f2c (version 19950110).
   You must link the resultinumberv object file with the libraries:
     -lf2c -lm   (in that order)
*/
#include <admodel.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"

#include "constructors.h"

int ef_(independent_variables& x,doublereal * f);
int ef_and_gradf(independent_variables& x,doublereal * f,doublereal * _g);
int egradf_(independent_variables& x, doublereal * _g);
int eh_(long int * i,independent_variables& x, doublereal * f);
int egradh_(long int * i,independent_variables& x, doublereal * _g);
int eg_(long int * i,independent_variables& x, doublereal * f);
int egradg_(long int * i,independent_variables& x, doublereal * _g);
int eh_and_jacobian_h(independent_variables& x, dvector& h,dmatrix& jacob_h);
int ehg_and_jacobian_hg(independent_variables& x, dvector& h,
  dvector& g,dmatrix& jacob_h);
int ehg(independent_variables& x, dvector& h,dvector& g);

/**
 * Description not yet available.
 * \param
 */
int eval_extern__(integer *mode)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer i, j;
    doublestar gr(nx);


#define gunit_ref(a_1,a_2) gggg00_1->gunit[(a_2)*3 + a_1 - 1]
#define fugrad_ref(a_1,a_2) gggg18_1->fugrad[(a_2)*nx + a_1 - 1]

/*     PARAMETER (NX=35,NRESM=66,MAXIT=4000,NSTEP=40) */
/* ** */
/*   COLNO ALSO USED O8QPSO WITH DOUBLE LENGTH ! */
/***** IF BLOC=.TRUE. THEN IT IS ASSUMED THAT FUNCTIONEVALUATION TAKES PLA
CE*/
/* **** AT ONCE IN AN EXTERNAL ROUTINE AND */
/***** THAT USER_EVAL HAS BEEN CALLED BEFORE CALLING FOR EVALUATION OF FUN
CTIONS*/
/***** THE LATTER THEN SIMPLY CONSISTS IN COPYING DATA FROM COMMON O8FUEXT
*/
/* **** TO DONLP2'S OWN DATA */
/* **** USER_EVAL MUST SET VALID=TRUE, IF FUNCTIONVALUES ARE VALID FOR THE
 */
/* **** CURRENT XTR */
/* **** CORR IS SET TO TRUE BY DONLP2, IF THE INITIAL X DOES NOT SATISFY
*/
/* **** THE BOUND CONSTRAINTS. X IS MODIFIED IN THIS CASE */
/* **** DIFFTYPE=1,2,3 NUMERICAL DIFFERENTIATION BY THE ORDINARY FORWARD
*/
/* **** DIFFERENCES, BY CENTRAL DIFFERENCES OR BY RICHARDSON-EXTRAPOLATION
 */
/* **** OF ORDER 6, REQUIRING N, 2N , 6N ADDITIONAL FUNCTION EVALUATIONS
*/
/* **** RESPECTIVELY */
/* **** EPSFCN IS THE ASSUMED PRECISION OF THE FUNCTION EVALUATION, TO BE
*/
/* **** SET BY THE USER */
/* **** TAUBND: AMOUNT BY WHICH BOUND CONSTRAINTS MAY BE VIOLATED DURING
*/
/* **** FINITE DIFFERENCING, SET BY THE USER */
/* ***** THIS IS A MODEL OF EVAL_EXTERN, SIMPLY CALLING THE */
/* ***** STANDARD EVALUATION FUNCTIONS OF THE OPTIMIZATION PACKAGE */
    if (*mode == 0) {
        i__1 = gggg05_1->nres;
        for (i = 1; i <= i__1; ++i) {
            if (gunit_ref(1, i) == 1) {
                if (i <= gggg05_1->numberw) {
                    eh_(&i, gggg18_1->xtr, &gggg18_1->fu[i]);
                }
                if (i > gggg05_1->numberw) {
                    i__2 = i - gggg05_1->numberw;
                    eg_(&i__2, gggg18_1->xtr, &gggg18_1->fu[i]);
                }
            }
        }
        return 0;
    }
    if ( !(gunit_ref(1, 0) != 1 && *mode == 2))
    {
      ef_(gggg18_1->xtr, gggg18_1->fu);
    }
    else
    {
      ef_and_gradf(gggg18_1->xtr, gggg18_1->fu,gr);
      i__1 = gggg05_1->n;
      for (i = 1; i <= i__1; ++i) {
        fugrad_ref(i, 0) = gr[i - 1];
      }
    }
   /*
    ef_(gggg18_1->xtr, gggg18_1->fu);
    if (gunit_ref(1, 0) != 1 && *mode == 2) {
        if (gggg01_1->wwuq3) {
            egradf_(gggg18_1->xtr, gr);
            i__1 = gggg05_1->n;
            for (i = 1; i <= i__1; ++i) {
                fugrad_ref(i, 0) = gr[i - 1];
            }
        }
    }
    */

    if (*mode == 2) {
      dvector h(1,gggg05_1->numberw);
      dvector g(1,gggg05_1->numberv);
      dmatrix jacob_hg(1,gggg05_1->numberw+gggg05_1->numberv,1,gggg05_1->n);
      ehg_and_jacobian_hg(gggg18_1->xtr,h,g,jacob_hg);

      i__1 = gggg05_1->numberw;
      for (j = 1; j <= i__1; ++j) {
        gggg18_1->fu[j]=h(j);
        if (gunit_ref(1, j) != 1 && *mode == 2) {
            if (gggg01_1->wwuq3) {
                i__2 = gggg05_1->n;
                for (i = 1; i <= i__2; ++i) {
                    fugrad_ref(i, j) = jacob_hg(j,i);
                }
            }
        }
      }
      i__1 = gggg05_1->numberv;
      for (j = 1; j <= i__1; ++j) {
        //eg_(&j, gggg18_1->xtr, &gggg18_1->fu[gggg05_1->numberw + j]);
        gggg18_1->fu[gggg05_1->numberw + j]=g(j);
        if (gunit_ref(1, j + gggg05_1->numberw) != 1 && *mode == 2) {
            if (gggg01_1->wwuq3) {
                i__2 = gggg05_1->n;
                for (i = 1; i <= i__2; ++i) {
                    fugrad_ref(i, j + gggg05_1->numberw)
                        = jacob_hg(j+ gggg05_1->numberw,i);
                }
            }
        }
      }
    }
    else
    {
      dvector h(1,gggg05_1->numberw);
      dvector g(1,gggg05_1->numberv);
      ehg(gggg18_1->xtr,h,g);

      i__1 = gggg05_1->numberw;
      for (j = 1; j <= i__1; ++j) {
        gggg18_1->fu[j]=h(j);
      }
      i__1 = gggg05_1->numberv;
      for (j = 1; j <= i__1; ++j) {
        gggg18_1->fu[gggg05_1->numberw + j]=g(j);
      }
    }

   /*
    i__1 = gggg05_1->numberw;
    for (j = 1; j <= i__1; ++j) {
        eh_(&j, gggg18_1->xtr, &gggg18_1->fu[j]);
        if (gunit_ref(1, j) != 1 && *mode == 2) {
            if (gggg01_1->wwuq3) {
                egradh_(&j, gggg18_1->xtr, gr);
                i__2 = gggg05_1->n;
                for (i = 1; i <= i__2; ++i) {
                    fugrad_ref(i, j) = gr[i - 1];
                }
            }
        }
    }
    */

    /*
    i__1 = gggg05_1->numberv;
    for (j = 1; j <= i__1; ++j) {
        eg_(&j, gggg18_1->xtr, &gggg18_1->fu[gggg05_1->numberw + j]);
        if (gunit_ref(1, j + gggg05_1->numberw) != 1 && *mode == 2) {
            if (gggg01_1->wwuq3) {
                egradg_(&j, gggg18_1->xtr, gr);
                i__2 = gggg05_1->n;
                for (i = 1; i <= i__2; ++i) {
                    fugrad_ref(i, j + gggg05_1->numberw) = gr[i - 1];
                }
            }
        }
    }
    */
    gggg19_1->wwuq4 = TRUE_;
    return 0;
} /* eval_extern__ */

#undef fugrad_ref
#undef gunit_ref


#ifdef __cplusplus
}
#endif
