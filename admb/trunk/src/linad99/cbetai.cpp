/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>
#include <math.h>

/** Incomplete beta function for constant objects.
    \param a \f$a\f$
    \param b \f$b\f$
    \param x \f$x\f$
    \param maxit Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$
`
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2

    \deprecated Scheduled for replacement by 2010.
*/
double betai(const double a,const double b,const double x,int maxit)
{
  double bt;

  if (x < 0.0 || x > 1.0) cerr << "Bad x in routine betai" << endl;
  if (x == 0.0 || x == 1.0) bt=0.0;
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (x < (a+1.0)/(a+b+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}

