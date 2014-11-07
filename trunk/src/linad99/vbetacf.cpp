/**
 * $Id: vbetacf.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2009, 2010 ADMB Foundation
 */
#include <fvar.hpp>
#include <math.h>
#define EPS 1.0e-9
#define FPMIN 1.0e-30

/** Incomplete beta function for variable objects.
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
dvariable betacf(const dvariable& _a, const dvariable& _b, const dvariable& _x,
  int MAXIT)
{
  double qab,qam,qap;
  double a=value(_a);
  double b=value(_b);
  double x=value(_x);

  qab=a+b;
  qap=a+1.0;
  qam=a-1.0;
  dvector c1(0,MAXIT);
  dvector c(1,MAXIT);
  dvector d1(0,MAXIT);
  dvector d(1,MAXIT);
  dvector del(1,MAXIT);
  dvector h1(0,MAXIT);
  dvector h(1,MAXIT);
  dvector aa(1,MAXIT);
  dvector aa1(1,MAXIT);
  c1(0)=1.0;
  d1(0)=1.0/(1.0-qab*x/qap);
  h1(0)=d1(0);

  int m = 1;
  for (; m <= MAXIT; m++)
  {
    int i=m;
    int m2=2*m;
    aa(i)=m*(b-m)*x/((qam+m2)*(a+m2));
    d(i)=1.0/(1.0+aa(i)*d1(i-1));
    c(i)=1.0+aa(i)/c1(i-1);
    h(i) = h1(i-1)*d(i)*c(i);
    aa1(i) = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
    d1(i)=1.0/(1.0+aa1(i)*d(i));
    c1(i)=1.0+aa1(i)/c(i);
    del(i)=d1(i)*c1(i);
    h1(i) = h(i)*del(i);
    if (fabs(del(i)-1.0) < EPS) break;
  }
  if (m > MAXIT)
  {
    cerr << "a or b too big, or MAXIT too small in cumulative beta function"
      " routine" << endl;
    m=MAXIT;
  }
  int mmax=m;
  dvariable hh;
  value(hh)=h1(mmax);


  dvector dfc1(0,MAXIT);
  dvector dfc(1,MAXIT);
  dvector dfd1(0,MAXIT);
  dvector dfd(1,MAXIT);
  dvector dfh1(0,MAXIT);
  dvector dfh(1,MAXIT);
  dvector dfaa(1,MAXIT);
  dvector dfaa1(1,MAXIT);
  dvector dfdel(1,MAXIT);

  dfc1.initialize();
  dfc.initialize();
  dfaa1.initialize();
  dfaa.initialize();
  dfd1.initialize();
  dfd.initialize();
  dfh1.initialize();
  dfh.initialize();
  dfdel.initialize();
  dfh1(mmax)=1.0;
  double dfqab=0.0;
  double dfqam=0.0;
  double dfqap=0.0;
  double dfa=0.0;
  double dfb=0.0;
  double dfx=0.0;

  for (m=mmax;m>=1;m--)
  {
   /*
    int i=m;
    m2=2*m;
    aa(i)=m*(b-m)*x/((qam+m2)*(a+m2));
    d(i)=1.0/(1.0+aa(i)*d1(i-1));
    c(i)=1.0+aa(i)/c1(i-1);
    h(i) = h1(i-1)*d(i)*c(i);
    aa1(i) = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
    d1(i)=1.0/(1.0+aa1(i)*d(i));
    c1(i)=1.0+aa1(i)/c(i);
    del(i)=d1(i)*c1(i);
    h1(i) = h(i)*del(i);
   */

    int i=m;
    int m2=2*m;

    //h1(i) = h(i)*del(i);

    dfh(i)+=dfh1(i)*del(i);
    dfdel(i)+=dfh1(i)*h(i);
    dfh1(i)=0.0;

    //del(i)=d1(i)*c1(i);

    dfd1(i)+=dfdel(i)*c1(i);
    dfc1(i)+=dfdel(i)*d1(i);
    dfdel(i)=0.0;

    //c1(i)=1.0+aa1(i)/c(i);

    dfaa1(i)+=dfc1(i)/c(i);
    dfc(i)-=dfc1(i)*aa1(i)/(c(i)*c(i));
    dfc1(i)=0.0;

    //d1(i)=1.0/(1.0+aa1(i)*d(i));
    double sq=square(d1(i));
    dfaa1(i)-=dfd1(i)*sq*d(i);
    dfd(i)-=dfd1(i)*sq*aa1(i);
    dfd1(i)=0.0;

    //aa1(i) = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
    dfx -= dfaa1(i) *
     (a+m)*(qab+m)/((a+m2)*(qap+m2));

    dfa += dfaa1(i) * aa1(i)* (1.0/(a+m) - 1.0/(a+m2));
    dfqab += dfaa1(i) * aa1(i)/(qab+m);
    dfqap += dfaa1(i) * aa1(i)* (-1.0/(qap+m2));
    dfaa1(i)=0.0;


    //h(i) = h1(i-1)*d(i)*c(i);
    dfh1(i-1)+=dfh(i)*d(i)*c(i);
    dfd(i)+=dfh(i)*h1(i-1)*c(i);
    dfc(i)+=dfh(i)*h1(i-1)*d(i);
    dfh(i)=0.0;

    //c(i)=1.0+aa(i)/c1(i-1);
    dfaa(i)+=dfc(i)/c1(i-1);
    dfc1(i-1)-=dfc(i)*aa(i)/square(c1(i-1));
    dfc(i)=0.0;


    //d(i)=1.0/(1.0+aa(i)*d1(i-1));
    dfaa(i)-=dfd(i)*square(d(i))*d1(i-1);
    dfd1(i-1)-=dfd(i)*square(d(i))*aa(i);
    dfd(i)=0.0;

    //aa(i)=m*(b-m)*x/((qam+m2)*(a+m2));
    dfx+=dfaa(i)*
      m*(b-m)/((qam+m2)*(a+m2));

    dfb+=dfaa(i)*
      m*x/((qam+m2)*(a+m2));


    dfa-=dfaa(i)*aa(i)/(a+m2);
    dfqam-=dfaa(i)*aa(i)/(qam+m2);
    dfaa(i)=0.0;
  }
  /*
  c1(0)=1.0;
  d1(0)=1.0/(1.0-qab*x/qap);
  h1(0)=d1(0);
 */

  //h1(0)=d1(0);
  dfd1(0)+=dfh1(0);
  dfh1(0)=0.0;

  //d1(0)=1.0/(1.0-qab*x/qap);
  double sq1=square(d1(0))/qap;
  dfx+=dfd1(0)*sq1*qab;
  dfqab+=dfd1(0)*sq1*x;
  dfqap-=dfd1(0)*sq1*qab*x/qap;
  dfd1(0)=0.0;

  /*
  qab=a+b;
  qap=a+1.0;
  qam=a-1.0;
 */

  //qam=a-1.0;
  dfa+=dfqam;

  //qap=a+1.0;
  dfa+=dfqap;

  //qab=a+b;
  dfa+=dfqab;
  dfb+=dfqab;


  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3ind,
    &(value(hh)) ,&(value(_a)),dfa ,&(value(_b)),dfb ,&(value(_x)),dfx);


  return hh;
}

#undef MAXIT
#undef EPS
#undef FPMIN
