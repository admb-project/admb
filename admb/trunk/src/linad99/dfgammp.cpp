/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#else
#  include <fvar.hpp>
#endif
#define ITMAX 100
#define EPS 1.0e-9
//#define EPS 3.0e-7
#define FPMIN 1.0e-30
double get_values(double x,double y,int print_switch);

/** Incomplete gamma function.
    Continued fraction approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
void gcf(const dvariable& _gammcf,const dvariable& a,
  const dvariable& x,const dvariable& _gln)
{
  ADUNCONST(dvariable,gln)
  ADUNCONST(dvariable,gammcf)
  int i;
  dvariable an,b,c,d,del,h;

  gln=gammln(a);
  b=x+1.0-a;
  c=1.0/FPMIN;
  d=1.0/b;
  h=d;
  for (i=1;i<=ITMAX;i++) {
    an = -i*(i-a);
    b += 2.0;
    d=an*d+b;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    c=b+an/c;
    if (fabs(value(c)) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(value(del)-1.0) < EPS) break;
  }
  if (i > ITMAX) 
    cerr << "a too large, ITMAX too small in gcf" << endl;
  gammcf=exp(-x+a*log(x)-(gln))*h;
}

/** Incomplete gamma function.
    Series approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
void gser(const dvariable& _gamser,const dvariable& a,
  const dvariable& x,const dvariable& _gln)
{
  ADUNCONST(dvariable,gln)
  ADUNCONST(dvariable,gamser)
  int n;
  dvariable sum,del,ap;

  gln=gammln(a);

  if (value(x) <= 0.0) {
    if (value(x) < 0.0) 
      cerr << "x less than 0 in routine gser" << endl;
    gamser=0.0;
    return;
  } 
  else 
  {
    ap=a;
    del=sum=1.0/a;
    for (n=1;n<=ITMAX;n++) {
      ap+=1.0;
      del *= x/ap;
      sum += del;
      if (fabs(value(del)) < fabs(value(sum))*EPS) {
        gamser=sum*exp(-x+a*log(x)-(gln));
        return;
      }
    }
    cerr << "a too large, ITMAX too small in routine gser" << endl;
    return;
  }
}


dvariable cumd_gamma(const dvariable& x, const dvariable& a)
{
  dvariable gamser,gammcf,gln;

  if (value(x) < 0.0 || value(a) <= 0.0) 
    cerr << "Invalid arguments in routine gammp" << endl;
  if (value(x) < (value(a)+1.0)) {
    gser(gamser,a,x,gln);
    return gamser;
  } else {
    gcf(gammcf,a,x,gln);
    return 1.0-gammcf;
  }
}
