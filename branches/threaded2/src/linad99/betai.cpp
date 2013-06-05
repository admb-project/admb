#include <df1b2fun.h>
#include <df12fun.h>
//#define EPS double(3.0e-7)
#define EPS double(1.0e-10)
#define FPMIN double(1.0e-60)

double betacf(double a, double b, 
  double x,int MAXIT=100);


double betai(double a,double b,double x,
  int maxit)
{
  double bt;

  if (x < 0.0 || x > 1.0) cerr << "Bad x in routine betai" << endl;
  if (x == 0.0 || x == 1.0) bt=double(0.0);
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (x < (a+1.0)/(a+b+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}


  double betacf(double a, double b,double x,int MAXIT)
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
    for (m=1;m<=MAXIT;m++) 
    {
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
    if (m > MAXIT) 
    {
      cerr << "a or b too big, or MAXIT too small in betacf"
         << endl;
      ad_exit(1);
    }
    return h;
  }
  
#undef MAXIT
#undef EPS
#undef FPMIN
