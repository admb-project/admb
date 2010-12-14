/*
  * $Id$
  *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <df1b2fun.h>
#define ITMAX 100
#define EPS 1.0e-9
//#define EPS 3.0e-7
#define FPMIN 1.0e-30
double get_values(double x,double y,int print_switch);


df1b2variable log_negbinomial_density(double x,const df1b2variable& _xmu, 
  const df1b2variable& _xtau)
{
  ADUNCONST(df1b2variable,xmu)
  ADUNCONST(df1b2variable,xtau)
  init_df3_two_variable mu(xmu);
  init_df3_two_variable tau(xtau);
  *mu.get_u_x()=1.0;
  *tau.get_u_y()=1.0;
  if (value(tau)-1.0<0.0)
  {
    cerr << "tau <=1 in log_negbinomial_density " << endl;
    ad_exit(1);
  }
  df3_two_variable r=mu/(1.e-120+(tau-1.0));
  df3_two_variable tmp;
  tmp=gammln(x+r)-gammln(r) -gammln(x+1)
    +r*log(r)+x*log(mu)-(r+x)*log(r+mu);
  df1b2variable tmp1;
  tmp1=tmp;
  return tmp1;
}

/** Log gamma function.
    \param xx \f$x\f$
    \return \f$\ln\bigr(\Gamma(x)\bigl)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
df3_two_variable gammln(const df3_two_variable& xx)
{
  df3_two_variable x,tmp,ser,tmp1;
  static double cof[6]={76.18009173,-86.50532033,24.01409822,
    -1.231739516,0.120858003e-2,-0.536382e-5};
  int j;
  x=xx-1.0;
  tmp=x+5.5;
  tmp -= (x+0.5)*log(tmp);
  ser=1.0;
  for (j=0;j<=5;j++) 
  {
    x += 1.0;
    ser += cof[j]/x;
  }
  return -tmp+log(2.50662827465*ser);
}


/** Incomplete gamma function.
    Continued fraction approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
void gcf(const df3_two_variable& _gammcf,const df3_two_variable& a,
  const df3_two_variable& x,const df3_two_variable& _gln)
{
  ADUNCONST(df3_two_variable,gln)
  ADUNCONST(df3_two_variable,gammcf)
  int i;
  df3_two_variable an,b,c,d,del,h;

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
    Continued fraction approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
void gser(const df3_two_variable& _gamser,const df3_two_variable& a,
  const df3_two_variable& x,const df3_two_variable& _gln)
{
  int n;
  ADUNCONST(df3_two_variable,gln)
  ADUNCONST(df3_two_variable,gamser)
  df3_two_variable sum,del,ap;

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


df3_two_variable cumd_gamma(const df3_two_variable& x,
  const df3_two_variable& a)
{
  df3_two_variable gamser,gammcf,gln;

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
df3_two_variable cumd_exponential(const df3_two_variable& x,
  const df3_two_variable& a)
{
  df3_two_variable tmp;
  if (value(x)<=0)
    return 0.5*exp(x);
  else
    return 1.0-0.5*exp(-x);
}
df3_two_variable cumd_cauchy(const df3_two_variable& x,const df3_two_variable& a)
{
  return atan(x/a);
}
