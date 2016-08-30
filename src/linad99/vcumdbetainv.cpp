/**
 * $Id: vcumdbetainv.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: Unknown
 */

#include <admodel.h>
#include "df12fun.h"

//#define ADUNCONST(type,obj) type & obj = (type&) _##obj;

static double lnbeta(double a,double b)
{
  return gammln(a)+gammln(b)-gammln(a+b);
}

df1_two_variable betai(const df1_two_variable& a,
  const df1_two_variable& b,double x,int maxit=100);

dvariable inv_cumd_beta_stable(const prevariable& _a,const prevariable& _b,
  const prevariable& _y,double eps)
{
  ADUNCONST(prevariable,a);
  ADUNCONST(prevariable,b);
  ADUNCONST(prevariable,y);

  double eps1=1.0-eps;
  // this gets the inverse without derivatives
  double ca=value(a);
  double cb=value(b);
  double cx=inv_cumd_beta_stable(ca,cb,value(y),eps);

  init_df1_two_variable va(_a);
  init_df1_two_variable vb(_b);

  // this gets the derivatives for the function itself

  df1_two_variable z=(betai(va,vb,cx)-betai(va,vb,eps))/
    (betai(va,vb,eps1)-betai(va,vb,eps));

  double dga=*z.get_u_x();
  double dgb=*z.get_u_y();

  double denom=1.0/(betai(ca,cb,eps1)-betai(ca,cb,eps));
  double dgx=pow(cx,value(a)-1.0)*pow(1.0-cx,value(b)-1.0)/
    exp(lnbeta(value(a),value(b)))*denom;

  // now solve for the derivatves of the inverse function

  double dfx=1.0/dgx;
  double dfa=-dfx*dga;
  double dfb=-dfx*dgb;

  dvariable tmp;
  value(tmp)=cx;

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3ind,
    &(value(tmp)) ,&(value(_a)),dfa ,&(value(_b)),dfb ,&(value(_y)),dfx);

  return tmp;
}

df1_two_variable betacf(const df1_two_variable& a,const df1_two_variable& b,
  double x);


df1_two_variable betai(const df1_two_variable& a,
  const df1_two_variable& b,double x,int maxit)
{
  df1_two_variable bt;

  if (x < 0.0 || x > 1.0) cerr << "Bad x in routine betai" << endl;
  double z=1.0-x;
  if (x == 0.0 || x==1.0)
    bt=0.0;
  else
  {
    bt=exp(gammln(a+b) -gammln(a) -gammln(b) +a*log(x) +b*log(z));
  }
  if (x < (value(a)+1.0)/(value(a)+value(b)+2.0))
    return bt*betacf(a,b,x)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x)/b;
}

/*
main()
{
  double a,b,x;

  a=2.0;
  b=3.0;
  x=.80;
  do
  {
    cin >> a;
    cin >> b;
    cin >> x;
    if (x<0 ) exit(1);
    independent_variables xx(1,3);
    dvector g(1,3);
    dvector gg(1,3);
    xx(1)=a;
    xx(2)=b;
    xx(3)=x;
    gradient_structure gs(10000);
    {
      dvar_vector vx=dvar_vector(xx);
      dvariable y=inv_cumd_beta(vx(1),vx(2),vx(3));
      cout << y << endl;
      gradcalc(3,g);
      double h=1.e-6;
      gg(1)=(inv_cumd_beta(a+h,b,x)-inv_cumd_beta(a-h,b,x))/(2.0*h);
      gg(2)=(inv_cumd_beta(a,b+h,x)-inv_cumd_beta(a,b-h,x))/(2.0*h);
      gg(3)=(inv_cumd_beta(a,b,x+h)-inv_cumd_beta(a,b,x-h))/(2.0*h);
      cout << g << endl  << gg << " " << endl << g-gg << endl;
    }
    {
      dvar_vector vx=dvar_vector(xx);
      dvariable y=inv_cumd_beta_stable(vx(1),vx(2),vx(3),1.e-7);
      cout << y << endl;
      gradcalc(3,g);
      double h=1.e-6;
      gg(1)=(inv_cumd_beta_stable(a+h,b,x,1.e-7)-inv_cumd_beta_stable(a-h,b,x,1.e-7))/
        (2.0*h);
      gg(2)=(inv_cumd_beta_stable(a,b+h,x,1.e-7)-inv_cumd_beta_stable(a,b-h,x,1.e-7))/
        (2.0*h);
      gg(3)=(inv_cumd_beta_stable(a,b,x+h,1.e-7)-inv_cumd_beta_stable(a,b,x-h,1.e-7))/
        (2.0*h);
      cout << g << endl  << gg << " " << endl << g-gg << endl;
    }
  }
  while(1);
}
*/

const double tiny=1.0e-8;
const double maxn=150;
const double lowerbd=1.0e-40;

df1_two_variable betacf(const df1_two_variable& a, const df1_two_variable& b,
  double x)
{
  df1_two_variable v;
  df1_two_variable aa;
  df1_two_variable h;
  df1_two_variable up;
  df1_two_variable yy;
  df1_two_variable um;
  df1_two_variable d;
  df1_two_variable ssum;

  up=a+1.0;
  um=a-1.0;
  v=1.0;
  ssum=a+b;
  d=1.0-ssum*x/up;
  if (fabs(value(d)) < lowerbd) d=lowerbd;
  d=1.0/d;
  h=d;
  int m;
  for (m=1;m<=maxn;m++)
  {
    int m2=2*m;
    aa=m*(b-m)*x/((um+m2)*(a+m2));
    d=1.0+aa*d;
    if (fabs(value(d)) < lowerbd) d=lowerbd;
    v=1.0+aa/v;
    if (fabs(value(v)) < lowerbd) v=lowerbd;
    d=1.0/d;
    h *= d*v;
    aa = -(a+m)*(ssum+m)*x/((a+m2)*(up+m2));
    d=1.0+aa*d;
    if (fabs(value(d)) < lowerbd) d=lowerbd;
    v=1.0+aa/v;
    if (fabs(value(v)) < lowerbd) v=lowerbd;
    d=1.0/d;

    yy=d*v;
    h *= yy;
    if (fabs(value(yy)-1.0) < tiny) break;
  }
  if (m > maxn)
  {
    cerr << "num interations exceeded " << endl;
    ad_exit(1);
  }
  return h;
}

/*

df1_two_variable gammln(const df1_two_variable& xx)
{
  df1_two_variable x,tmp,ser;
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
*/


static df1_two_variable gammlnguts(const df1_two_variable& _z)
{
  df1_two_variable x;
  const double lpp =0.9189385332046727417803297;
  int n=7;
  const double c[9]={0.99999999999980993,
    676.5203681218851,
    -1259.1392167224028,
     771.32342877765313,
    -176.61502916214059,
    12.507343278686905,
     -0.13857109526572012,
    9.9843695780195716e-6,
    1.5056327351493116e-7};
  df1_two_variable z=_z-1.0;
  x=c[0];
  for (int i=1;i<=n+1;i++)
  {
    df1_two_variable zinv=1.0/(z+i);
    x+=c[i]*zinv;
  }
  df1_two_variable t=z+n+0.5;
  df1_two_variable ans= lpp + (z+0.5)*log(t) -t + log(x);
  return(ans);
}

df1_two_variable gammln(const df1_two_variable& z)
{
  const double lpi =1.1447298858494001741434272;
  const double pi =3.1415926535897932384626432;
  if (value(z)<0.5)
  {
    return lpi - log(sin(pi*z)) - gammlnguts(1.0-z);
  }
  else
  {
    return gammlnguts(z);
  }
}

dvariable qbeta(dvariable x, dvariable a, dvariable b, double eps){
  return inv_cumd_beta_stable(a,b,x,eps);
}
