/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Functions betai(const dvariable, const dvariable, const dvariable, int) and wrapper pbeta(const dvariable, const dvariable, const dvariable, int)
*/

#include <fvar.hpp>
#include <math.h>

/** Incomplete beta function for variable objects.
    \param a \f$a\f$
    \param b \f$b\f$
    \param x \f$x\f$
    \param maxit Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
dvariable betai(const dvariable a, const dvariable b, const dvariable x, int maxit)
{
  dvariable bt;

  if (x < 0.0 || x > 1.0) cerr << "Bad x in routine betai" << endl;
  if (x == 0.0 || x == 1.0) bt=0.0;
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (x < (a+1.0)/(a+b+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}

/** beta distribution function for variable objects (alias of ibeta function with same arguments order as in R).
    \param x \f$x\f$
    \param a \f$a\f$
    \param b \f$b\f$
    \param maxit Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
dvariable pbeta(const dvariable x, const dvariable a, const dvariable b, int maxit){
  return betai(a, b, x, maxit);
}
