/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#include <df1b2fun.h>
//#define EPS double(3.0e-7)
#define EPS double(1.0e-9)
#define FPMIN double(1.0e-30)
df1b2variable betacf(_CONST df1b2variable& a,_CONST df1b2variable& b,
  double x, int MAXIT);


//df1b2variable betai(_CONST df1b2variable& a,_CONST df1b2variable& b,
 // double x, int maxit=100);

df1b2variable betai(_CONST df1b2variable & a,_CONST df1b2variable & b,double x,
  int maxit)
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

df1b2variable betacf(_CONST df1b2variable& a,_CONST df1b2variable& b,
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
#undef MAXIT
#undef EPS
#undef FPMIN
