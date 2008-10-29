#include <fvar.hpp>
#include <math.h>

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
