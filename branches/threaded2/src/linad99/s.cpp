#include <df1b2fun.h>
#include <df12fun.h>
//#define EPS double(3.0e-7)
#define EPS double(1.0e-9)
#define FPMIN double(1.0e-30
prevariable betacf(_CONST prevariable& a,_CONST prevariable& b,
  double x, int MAXIT=100);


//prevariable betai(_CONST prevariable& a,_CONST prevariable& b,
 // double x, int maxit=100);
df1_two_variable betacf(df1_two_variable& a, df1_two_variable& b, 
  double x,int MAXIT=100);

dvariable betai(const prevariable & a,const prevariable & b,double x,
  int maxit)
{
  dvariable bt;

  if (x < 0.0 || x > 1.0) cerr << "Bad x in routine betai" << endl;
  if (x == 0.0 || x == 1.0) bt=double(0.0);
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (x < (value(a)+1.0)/(value(a)+value(b)+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}


  df1_two_variable betacf(df1_two_variable& a, df1_two_variable& b, 
    double x,int MAXIT)
  {
    int m,m2;
    df1_two_variable aa,c,d,del,h,qab,qam,qap;
     
    qab=a+b;
    qap=a+1.0;
    qam=a-1.0;
    c=1.0;
    d=1.0-qab*x/qap;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    d=1.0/d;
    h=d;
    for (m=1;m<=MAXIT;m++) 
    {
      m2=2*m;
      aa=m*(b-m)*x/((qam+m2)*(a+m2));
      d=1.0+aa*d;
      if (fabs(value(d)) < FPMIN) d=FPMIN;
      c=1.0+aa/c;
      if (fabs(value(c)) < FPMIN) c=FPMIN;
      d=1.0/d;
      h *= d*c;
      aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
      d=1.0+aa*d;
      if (fabs(value(d)) < FPMIN) d=FPMIN;
      c=1.0+aa/c;
      if (fabs(value(c)) < FPMIN) c=FPMIN;
      d=1.0/d;
  
      del=d*c;
      h *= del;
      if (fabs(value(del)-1.0) < EPS) break;
    }
    if (m > MAXIT) 
    {
      cerr << "a or b too big, or MAXIT too small in betacf"
         << endl;
      ad_exit(1);
    }
    return h;
  }
  

prevariable betacf(const prevariable& _xa,const prevariable& _xb, 
    double x,int MAXIT)
{
  ADUNCONST(prevariable,xa)
  ADUNCONST(prevariable,xb) 
  init_df1_two_variable a(xa);
  init_df1_two_variable b(xb);
  df1_two_variable z=betacf(a,b,x,MAXIT);
  dvariable tmp;
  tmp=z;
  return tmp;
}

#undef MAXIT
#undef EPS
#undef FPMIN
