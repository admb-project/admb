/*
 * $Id$
 * 
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>
#include <math.h>
#define EPS 1.0e-9
#define FPMIN 1.0e-30

/** Incomplete beta function for constant objects.
    \param a \f$a\f$
    \param b \f$b\f$
    \param x \f$x\f$
    Evaluates the continued fraction approximation for imcomplete beta function.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2

    \deprecated Scheduled for replacement by 2010.
*/
double betacf(_CONST double& a,_CONST double& b,_CONST double& x, int MAXIT)
{
  int m,m2;
  double aa,c,d,del,h,qab,qam,qap;

  qab=a+b;
  qap=a+1.0;
  qam=a-1.0;
  c=1.0;
  d=1.0-qab*x/qap;
  if (fabs(d) < FPMIN) d=FPMIN;
  d=1.0/d;
  h=d;
  for (m=1;m<=MAXIT;m++) {
    m2=2*m;
    aa=m*(b-m)*x/((qam+m2)*(a+m2));
    d=1.0+aa*d;
    if (fabs(d) < FPMIN) d=FPMIN;
    c=1.0+aa/c;
    if (fabs(c) < FPMIN) c=FPMIN;
    d=1.0/d;
    h *= d*c;
    aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
    d=1.0+aa*d;
    if (fabs(d) < FPMIN) d=FPMIN;
    c=1.0+aa/c;
    if (fabs(c) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(del-1.0) < EPS) break;
  }
  if (m > MAXIT) cerr << "a or b too big, or MAXIT too small in betacf"
         << endl;
  return h;
}
#undef MAXIT
#undef EPS
#undef FPMIN
