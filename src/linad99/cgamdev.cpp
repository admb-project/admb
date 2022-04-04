/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2012 Regents of the University of California

@brief Functions to compute incomplete gamma.

This file deals with the Incomplete Gamma Functions
of constant types. All supporting mathematical functions
required to compute the Inmomplete Gamma Function
are included. They being: log gamma,
and some polynomial evaluation functions.
*/

#include <fvar.hpp>
#define ITMAX 200
#define EPS 1.e-9
//#define EPS 3.0e-7
#define FPMIN 1.0e-30
void gcf(double& gammcf,double a,double x,double &gln);
void gser(double& gamser,double a,double x,double& gln);

double gammp(double a,double x)
{
  double gamser,gammcf,gln;

  if (x < 0.0 || a <= 0.0)
    cerr << "Invalid arguments in routine gammp" << endl;
  if (x < (a+1.0)) {
    gser(gamser,a,x,gln);
    return gamser;
  } else {
    gcf(gammcf,a,x,gln);
    return 1.0-gammcf;
  }
}

double cumd_gamma(double x,double a)
{
  double gamser,gammcf,gln;

  if (x < 0.0 || a <= 0.0)
    cerr << "Invalid arguments in routine gammp" << endl;
  if (x < (a+1.0)) {
    gser(gamser,a,x,gln);
    return gamser;
  } else {
    gcf(gammcf,a,x,gln);
    return 1.0-gammcf;
  }
}

/** Incomplete gamma function.
    Continued fraction approximation.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6
*/
void gcf(double& gammcf,double a,double x,double &gln)
{
  int i;
  double an,b,c,d,del,h;

  gln=gammln(a);
  b=x+1.0-a;
  c=1.0/FPMIN;
  d=1.0/b;
  h=d;
  for (i=1;i<=ITMAX;i++) {
    an = -i*(i-a);
    b += 2.0;
    d=an*d+b;
    if (fabs(d) < FPMIN) d=FPMIN;
    c=b+an/c;
    if (fabs(c) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(del-1.0) < EPS) break;
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
*/
void gser(double& gamser,double a,double x,double& gln)
{
  int n;
  double sum,del,ap;

  gln=gammln(a);
  if (x <= 0.0) {
    if (x < 0.0)
      cerr << "x less than 0 in routine gser" << endl;
    gamser=0.0;
    return;
  } else {
    ap=a;
    del=sum=1.0/a;
    for (n=1;n<=ITMAX;n++) {
      ++ap;
      del *= x/ap;
      sum += del;
      if (fabs(del) < fabs(sum)*EPS) {
        gamser=sum*exp(-x+a*log(x)-(gln));
        return;
      }
    }
    cerr << "a too large, ITMAX too small in routine gser" << endl;
    return;
  }
}

double get_initial_u(double a,double y);

double Sn(double x,double a);

double inv_cumd_gamma(double y,double a)
{
  if (a<0.05)
  {
    cerr << "a musdt be > 0.1" << endl;
    ad_exit(1);
  }
  double u=get_initial_u(a,y);
  double h;
  do
  {
    double z=gammp(a,a*exp(u));
    double d=y-z;
    //cout << d << endl;
    double log_fprime=a*log(a)+a*(u-exp(u)) -gammln(a);
    double fprime=exp(log_fprime);
    h=d/fprime;
    u+=h;
  }
  while(fabs(h)>1.e-12);
  double x=a*exp(u);
  return x;
}

#undef ITMAX
#undef EPS

double get_initial_u(double a,double y)
{
  const double c=0.57721;
  // note that P = y;
  double logP=log(y);
  double logQ=log(1-y);
  double logB=logQ+gammln(a);
  double x0=1.e+100;
  double log_x0=1.e+100;

  if (a<1.0)
  {
    if ( logB>log(.6) || (logB > log(.45) && a>=.3) )
    {
      double logu;
      if (logB+logQ > log(1.e-8))
      {
        logu=(logP+gammln(1.0+a))/a;
      }
      else
      {
        logu=-exp(logQ)/a -c;
      }
      double u=exp(logu);
      x0=u/(1-u/(1.0+a));
      double tmp=log(1-u/(1.0+a));
      log_x0=logu;
      log_x0-=tmp;
    }
    else if ( a<.3 && log(.35) <= logB && logB <= log(.6) )
    {
      double t=exp(-c-exp(logB));
      double logt=-c-exp(logB);
      double u=t*exp(t);
      x0=t*exp(u);
      log_x0=logt+u;
    }
    else if ( (log(.15)<=logB && logB <=log(.35)) ||
       ((log(.15)<=logB && logB <=log(.45)) && a>=.3) )
    {
      double y=-logB;
      double v=y-(1-a)*log(y);
      x0=y-(1-a)*log(v)-log(1+(1.0-a)/(1.0+v));
      log_x0=log(x0);
    }
    else if (log(.01)<logB && logB < log(.15))
    {
      double y=-logB;
      double v=y-(1-a)*log(y);
      x0=y-(1-a)*log(v)-log((v*v+2*(3-a)*v+(2-a)*(3-a))/(v*v +(5-a)*v+2));
      log_x0=log(x0);
    }
    else if (logB < log(.01))
    {
      double y=-logB;
      double v=y-(1-a)*log(y);
      x0=y-(1-a)*log(v)-log((v*v+2*(3-a)*v+(2-a)*(3-a))/(v*v +(5-a)*v+2));
      log_x0=log(x0);
    }
    else
    {
      cerr << "this can't happen" << endl;
      ad_exit(1);
    }
  }
  else  if (a>=1.0)
  {
    const double a0 = 3.31125922108741;
    const double b1 = 6.61053765625462;
    const double a1 = 11.6616720288968;
    const double b2 = 6.40691597760039;
    const double a2 = 4.28342155967104;
    const double b3 = 1.27364489782223;
    const double a3 = .213623493715853;
    const double b4 = .03611708101884203;

    int sgn=1;
    double logtau;
    if (logP< log(0.5))
    {
      logtau=logP;
      sgn=-1;
    }
    else
    {
      logtau=logQ;
      sgn=1;
    }

    double t=sqrt(-2.0*logtau);

    double num = (((a3*t+a2)*t+a1)*t)+a0;
    double den = ((((b4*t+b3)*t+b2)*t)+b1)*t+1;
    double s=sgn*(t-num/den);
    double s2=s*s;
    double s3=s2*s;
    double s4=s3*s;
    double s5=s4*s;
    double roota=sqrt(a);
    double w=a+s*roota+(s2-1)/3.0+(s3-7.0*s)/(36.*roota)
      -(3.0*s4+7.0*s2-16)/(810.0*a)
      +(9.0*s5+256.0*s3-433.0*s)/(38880.0*a*roota);
    if (logP< log(0.5))
    {
      if (w>.15*(a+1))
      {
        x0=w;
      }
      else
      {
        double v=logP+gammln(a+1);
        double u1=exp(v+w)/a;
        double S1=1+u1/(a+1);
        double u2=exp((v+u1-log(S1))/a);
        double S2=1+u2/(a+1)+u2*u2/((a+1)*(a+2));
        double u3=exp((v+u2-log(S2))/a);
        double S3=1+u3/(a+1)+u3*u3/((a+1)*(a+2))
         + u3*u3*u3/((a+1)*(a+2)*(a+3));
        double z=exp((v+u3-log(S3))/a);
        if (z<.002*(a+1.0))
        {
          x0=z;
        }
        else
        {
          double sn=Sn(z,a);
          double zbar=exp((v+z-log(sn))/a);
          x0=zbar*(1.0-(a*log(zbar)-zbar-v+log(sn))/(a-zbar));
        }
      }
      log_x0=log(x0);
    }
    else
    {
      double u = -logB +(a-1.0)*log(w)-log(1.0+(1.0-a)/(1+w));
      x0=u;
      log_x0=log(x0);
    }
  }
  if (a==1.0)
  {
    x0=-log(1.0-y);
    log_x0=log(x0);
  }
  return log_x0-log(a);
}
