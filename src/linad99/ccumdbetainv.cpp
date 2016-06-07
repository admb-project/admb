/**
 * $Id: ccumdbetainv.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: Unknown
 */
#include <admodel.h>

static double lnbeta(double a,double b)
{
  return gammln(a)+gammln(b)-gammln(a+b);
}

/*
static int sgn(double z)
{
  if (z>=0)
    return 1;
  else
    return -1;
}
*/

double old_inv_cumd_beta_stable(double a,double b,double y,double eps)
{
  double eps1=1.0-eps;

  int icount=0;
  if (y<0.0 || y>1.0 || a<=0.0 || b<=0.0 )
  {
    cerr << "Illegal value in inv_cumd_beta" << endl;
    ad_exit(1);
  }

  double mu=a/(a+b);
  double x=mu;
  if (x<=eps)
    x=1.1*eps;

  if(x>=eps1)
    x=eps1-0.1*eps;

  double s=log(x/(1.0-x));
  double lower=log(eps/eps1);
  double upper=-lower; // bracket the minimum

  double bet=exp(lnbeta(a,b)); // normalizing constant
  double denom=1.0/(betai(a,b,eps1)-betai(a,b,eps));
  double finit=betai(a,b,x)-betai(a,b,eps)*denom;

  if (finit>y)
  {
    upper=s;
  }
  else if (finit<y)
  {
    lower=s;
  }

  double d=0.0;
  do
  {
    double f,dx; // der of x wrt s
    x=1.0/(1.0+exp(-s));  //transform from s to x

    f=(betai(a,b,x)-betai(a,b,eps))*denom;

    dx=exp(-s)/square(1+exp(-s)); // der of x wrt s

    d=y-f;

    if (d<0)   // x is too large
    {
       if (s<upper)
         upper=s;
    }
    else if (d>0) // x is too small
    {
      if (s>lower)
      {
        lower=s;
      }
    }

    double xa1=pow(x,a-1);
    double xb1;
    xb1=pow(1-x,b-1);

    double fp=(xa1*xb1/bet)*dx*denom; // derivative of cumulative dist fun
                           // wrt x
    double h=d/fp;

    double stry=s+h;
    if (h<0.0)
    {
      if (stry<lower)
        s=lower+0.5*(s-lower);
      else
        s=stry;
    }
    else
    if (h>0.0)
    {
      if (stry>upper)
        s=s+0.5*(upper-x);
      else
        s=stry;
    }
    icount++;
    if (icount>15) break;
  }
  while(fabs(d)>1.e-12);

  return x;
}


double inv_cumd_beta_stable(double a,double b,double y,double eps)
{
  //double eps1=1.0-eps;

  int icount=0;
  if (y<0.0 || y>1.0 || a<=0.0 || b<=0.0 )
  {
    cerr << "Illegal value in inv_cumd_beta" << endl;
    ad_exit(1);
  }

  double mu=a/(a+b);
  double x=mu;
  //if (x<=eps)
  //  x=1.1*eps;

  //if(x>=eps1)
  //  x=eps1-0.1*eps;

  double lower=0.0;
  double upper=1.0; // bracket the minimum

  double bet=exp(lnbeta(a,b)); // normalizing constant
  double finit=betai(a,b,x);

  if (finit>y)
  {
    upper=x;
  }
  else if (finit<y)
  {
    lower=x;
  }

  double d=0.0;
  do
  {
    double f; // der of x wrt s
    f=betai(a,b,x);
    d=y-f;
    if (d<0)   // x is too large
    {
       if (x<upper)
         upper=x;
    }
    else if (d>0) // x is too small
    {
      if (x>lower)
      {
        lower=x;
      }
    }
    double xa1=pow(x,a-1);
    double xb1;
    xb1=pow(1-x,b-1);

    double fp=(xa1*xb1/bet); // derivative of cumulative dist fun
                           // wrt x
     
    double h=d/fp;
    double stry=x+h;
    if (h<0.0)
    {
      if (stry<lower)
        x=lower+0.5*(x-lower);
      else
        x=stry;
    }
    else
    if (h>0.0)
    {
      if (stry>upper)
        x=x+0.5*(upper-x);
      else
        x=stry;
    }
    icount++;
    if (icount>50) break;
  }
  while(fabs(d)>1.e-16);
  return x;
}


double qbeta(double x, double a, double b, double eps){
  return inv_cumd_beta_stable(a,b,x,eps);
}



/*
main()
{
  double eps=0.000001;
  do
  {
    double a,b,y;
    cin >> a;
    cin >> b;
    cin >> y;
    double x1=inv_cumd_beta(a,b,y);
    double x2=inv_cumd_beta_stable(a,b,y,eps);
    cout << x1 << " " << x2 << endl;
  }
  while(1);
}
*/
