/**
 * $Id: df1b2bet.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California
 */
#include <df1b2fun.h>
//#define EPS double(3.0e-7)
#define EPS double(1.0e-9)
#define FPMIN double(1.0e-30)
df1b2variable betacf(const df1b2variable& a,const df1b2variable& b, double x, int MAXIT);
df1b2variable betacf(const df1b2variable& a,const df1b2variable& b, const df1b2variable& x, int MAXIT);

//df1b2variable betai(const df1b2variable& a,const df1b2variable& b,
 // double x, int maxit=100);

/** Incomplete beta function for df1b2variable objects.
    \param a \f$a\f$
    \param b \f$b\f$
    \param x \f$x\f$
    \param maxit Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
df1b2variable betai(const df1b2variable & a,const df1b2variable & b,double x, int maxit)
{
  df1b2variable bt;

  if (x < 0.0 || x > 1.0) cerr << "Bad x in routine betai" << endl;
  if (x == 0.0 || x == 1.0) bt=double(0.0);
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (x < (value(a)+1.0)/(value(a)+value(b)+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}

/** beta distribution function for df1b2variable objects (alias of betai).
    \param x \f$x\f$
    \param a \f$a\f$
    \param b \f$b\f$
    \param maxit Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
df1b2variable pbeta(double x, const df1b2variable & a,const df1b2variable & b, int maxit){
  return betai(a,b,x,maxit);
}

/** Incomplete beta function for df1b2variable objects.
    Evaluates the continued fraction for imcomplete beta function.
    \param _a \f$a\f$
    \param _b \f$b\f$
    \param _x \f$x\f$
    \param MAXIT Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
df1b2variable betacf(const df1b2variable& a,const df1b2variable& b,
  double x, int MAXIT)
{
  int m,m2;
  df1b2variable aa,c,d,del,h,qab,qam,qap;

  qab=a+b;
  qap=a+double(1.0);
  qam=a-double(1.0);
  c=double(1.0);
  d=double(1.0)-qab*x/qap;
  if (fabs(value(d)) < FPMIN) d=FPMIN;
  d=double(1.0)/d;
  h=d;
  for (m=1;m<=MAXIT;m++) {
    m2=2*m;
    aa=double(m)*(b-double(m))*x/((qam+double(m2))*(a+double(m2)));
    d=double(1.0)+aa*d;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    c=double(1.0)+aa/c;
    if (fabs(value(c)) < FPMIN) c=FPMIN;
    d=double(1.0)/d;
    h *= d*c;
    aa = -(a+double(m))*(qab+double(m))*x/((a+double(m2))*(qap+double(m2)));
    d=double(1.0)+aa*d;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    c=double(1.0)+aa/c;
    if (fabs(value(c)) < FPMIN) c=FPMIN;
    d=double(1.0)/d;
    del=d*c;
    h *= del;
    if (fabs(value(del)-double(1.0)) < EPS) break;
  }
  if (m > MAXIT) cerr << "a or b too big, or MAXIT too small in betacf"
         << endl;
  return h;
}






df1b2variable pbeta(const df1b2variable & x, const df1b2variable & a, const df1b2variable & b, int maxit)
{
  df1b2variable bt;

  if (value(x) < 0.0 || value(x) > 1.0) cerr << "Bad x in routine betai" << endl;
  if (value(x) == 0.0 || value(x) == 1.0) bt=double(0.0);
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (value(x) < (value(a)+1.0)/(value(a)+value(b)+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}

df1b2variable betacf(const df1b2variable& a,const df1b2variable& b, const df1b2variable& x, int MAXIT)
{
  int m,m2;
  df1b2variable aa,c,d,del,h,qab,qam,qap;

  qab=a+b;
  qap=a+double(1.0);
  qam=a-double(1.0);
  c=double(1.0);
  d=double(1.0)-qab*x/qap;
  if (fabs(value(d)) < FPMIN) d=FPMIN;
  d=double(1.0)/d;
  h=d;
  for (m=1;m<=MAXIT;m++) {
    m2=2*m;
    aa=double(m)*(b-double(m))*x/((qam+double(m2))*(a+double(m2)));
    d=double(1.0)+aa*d;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    c=double(1.0)+aa/c;
    if (fabs(value(c)) < FPMIN) c=FPMIN;
    d=double(1.0)/d;
    h *= d*c;
    aa = -(a+double(m))*(qab+double(m))*x/((a+double(m2))*(qap+double(m2)));
    d=double(1.0)+aa*d;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    c=double(1.0)+aa/c;
    if (fabs(value(c)) < FPMIN) c=FPMIN;
    d=double(1.0)/d;
    del=d*c;
    h *= del;
    if (fabs(value(del)-double(1.0)) < EPS) break;
  }
  if (m > MAXIT) cerr << "a or b too big, or MAXIT too small in betacf"
         << endl;
  return h;
}



#undef MAXIT
#undef EPS
#undef FPMIN
