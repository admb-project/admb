/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

void generate_actual_multivariate_mixture(int nvar, const dvector& a,
  const dvector& b, dmatrix& ch,long int& iseed, const double& lprob,
  const dvector& w);

double cumd_mixture_02(const double& x);

void generate_actual_multivariate_cauchy(int nvar, const dvector& a,
  const dvector& b, dmatrix& ch,long int& iseed, const double& lprob,
  const dvector& w);
double log_likelihood_mixture_02(const double& x);
double log_likelihood_mixture(const double& x);
double inv_cumd_norm(const double& x);
double inv_cumd_norm_ln(const double& x);
double inv_cumd_norms(const double& x);
double cumd_norm(const double& x);
double ln_normal_tail_right(const double& x);
double ln_normal_tail_left(const double& x);
double ln_normal_tail(const double& x);
double better_rand(long int& iseed);
void get_bounded_mixture(double x1,double x2, const double& y,
  const double& density, long int& iseed);
void get_bounded_cauchy(double x1,double x2, const double& y,
  const double& density, long int& iseed);
void get_bounded_normal(double x1,double x2, const double& y,
  const double& density, long int& iseed);

void get_bounded_normal_virtual(double x1,double x2, const double& _y,
  double& _log_density);

dvector bounded_multivariate_normal(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch,long int& iseed);

void generate_virtual_multivariate(int nvar, const dvector& a,
  const dvector& b, const dmatrix& ch, const double& lprob, const dvector& eps);

void generate_actual_multivariate(int nvar, const dvector& a, const dvector& b,
  const dmatrix& ch, long int& iseed, const double& lprob, const dvector& w);

dvector bounded_robust_multivariate_normal(int nvar, const dvector& a1,
  dvector& b1, const dmatrix& ch, const dmatrix& ch3, const dmatrix& chinv,
  const dmatrix& ch3inv, double contaminant,long int& iseed,
  const double& lprob, const double& _lprob3, double& log_tprob,
  const int& _outflag)
{
  double& lprob3=(double&) _lprob3;
  int& outflag=(int&) _outflag;
  dvector w(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  w.initialize();
  double r = better_rand(iseed);
  if (r>contaminant)
  {
    outflag=0;
    a=a1;
    b=b1;
    generate_actual_multivariate(nvar,a,b,ch,iseed,lprob,w);
    a=a1;
    b=b1;
    generate_virtual_multivariate(nvar,a,b,ch3,lprob3,ch3inv*w);
  }
  else
  {
    outflag=1;
    a=a1;
    b=b1;
    generate_actual_multivariate(nvar,a,b,ch3,iseed,lprob3,w);
    a=a1;
    b=b1;
    generate_virtual_multivariate(nvar,a,b,ch,lprob,chinv*w);
  }
  double tmpa=(lprob+.5*nvar);
  double tmpb=(lprob3-nvar*log(3.0)+.5*nvar);
  lprob3=lprob3-nvar*log(3.0);
  //tprob=(1.-contaminant)*exp(tmpa)+contaminant*exp(tmpb);
  if (tmpa>tmpb)
  {
    //tprob=exp(tmpa)*
      //( (1.-contaminant)+contaminant*exp(tmpb-tmpa) );
    log_tprob=tmpa+log((1.-contaminant)+contaminant*exp(tmpb-tmpa));
  }
  else
  {
    log_tprob=tmpb+log((1.-contaminant)*exp(tmpa-tmpb)+contaminant);
  }
  return w;
}

dvector bounded_multivariate_cauchy(int nvar, const dvector& a1,
  dvector& b1, const dmatrix& _ch,long int& iseed, const double& lprob,
  double& log_tprob, const int& _outflag)
{
  dmatrix& ch=(dmatrix&)_ch;
  int& outflag=(int&) _outflag;
  dvector w(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  w.initialize();
  {
    outflag=0;
    a=a1;
    b=b1;
    generate_actual_multivariate_cauchy(nvar,a,b,ch,iseed,lprob,w);
  }
  double tmpa=(lprob+.5*nvar);
  log_tprob=tmpa;
  return w;
}

void generate_actual_multivariate_cauchy(int nvar, const dvector& _a,
  const dvector& _b, dmatrix& ch,long int& iseed, const double& _lprob,
  const dvector& _w)
{
  double& lprob=(double&) _lprob;
  dvector& a=(dvector&) _a;
  dvector& b=(dvector&) _b;
  dvector& w=(dvector&) _w;
  double ah;
  double bl;
  dvector y(1,nvar);
  lprob=0;
  double log_density=0.0;;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i);
    bl=b(i)/ch(i,i);

    get_bounded_cauchy(ah,bl,y(i),log_density,iseed);
    lprob += log_density;
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y(i)*ch(j,i);
      w(j)+=tmp;
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
}

dvector bounded_multivariate_mixture(int nvar, const dvector& a1,
  dvector& b1, const dmatrix& _ch,long int& iseed, const double& lprob,
  const int& _outflag)
{
  dmatrix& ch=(dmatrix&)_ch;
  int& outflag=(int&) _outflag;
  dvector w(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  w.initialize();
  {
    outflag=0;
    a=a1;
    b=b1;
    generate_actual_multivariate_mixture(nvar,a,b,ch,iseed,lprob,w);
  }
  return w;
}

void generate_actual_multivariate_mixture(int nvar, const dvector& _a,
  const dvector& _b, dmatrix& ch,long int& iseed, const double& _lprob,
  const dvector& _w)
{
  double& lprob=(double&) _lprob;
  dvector& a=(dvector&) _a;
  dvector& b=(dvector&) _b;
  dvector& w=(dvector&) _w;
  double ah;
  double bl;
  dvector y(1,nvar);
  lprob=0;
  double log_density=0.0;;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i);
    bl=b(i)/ch(i,i);

    get_bounded_mixture(ah,bl,y(i),log_density,iseed);
    lprob += log_density;
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y(i)*ch(j,i);
      w(j)+=tmp;
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
}

void generate_actual_multivariate(int nvar, const dvector& _a,
  const dvector& _b, const dmatrix& ch, long int& iseed, const double& _lprob,
  const dvector& _w)
{
  double& lprob=(double&) _lprob;
  dvector& a=(dvector&) _a;
  dvector& b=(dvector&) _b;
  dvector& w=(dvector&) _w;
  double ah;
  double bl;
  dvector y(1,nvar);
  lprob=0;
  double log_density=0.0;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i);
    bl=b(i)/ch(i,i);

    get_bounded_normal(ah,bl,y(i),log_density,iseed);
    lprob += log_density;
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y(i)*ch(j,i);
      w(j)+=tmp;
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
}

void generate_virtual_multivariate(int nvar, const dvector& _a,
  const dvector& _b, const dmatrix& ch, const double& _lprob,
  const dvector& eps)
{
  double& lprob=(double&) _lprob;
  dvector& a=(dvector&) _a;
  dvector& b=(dvector&) _b;
  double ah;
  double bl;
  dvector& y=(dvector&)(eps);
  lprob=0;
  double log_density;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i);
    bl=b(i)/ch(i,i);
    get_bounded_normal_virtual(ah,bl,y(i),log_density);
    lprob -= log_density;
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y(i)*ch(j,i);
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
}

void get_bounded_cauchy(double x1,double x2, const double& _y,
  const double& _log_density, long int& iseed)
{
  double& log_density=(double&) _log_density;
  double& y=(double&) _y;
  //double lp1;
  //double lp2;
  //double v;
  double w;
  double u = better_rand(iseed);
  {
    double lower=cumd_cauchy(x1);
    double upper=cumd_cauchy(x2);
    w=-log(upper-lower);
    u=u*.9998+.0001;
    y = inv_cumd_cauchy(u*(upper-lower)+lower);
  }
  log_density=w-log(1+0.5*y*y);
}

void get_bounded_mixture(double x1,double x2, const double& _y,
  const double& _log_density, long int& iseed)
{
  double& y=(double&) _y;
  double& log_density=(double&) _log_density;
  //double lp1;
  //double lp2;
  //double v;
  double w;
  double u = better_rand(iseed);
  {
    //double lower=cumd_mixture_02(x1);
    //double upper=cumd_mixture_02(x2);
    double lower=cumd_mixture(x1);
    double upper=cumd_mixture(x2);
    w=-log(upper-lower);
    u=u*.9998+.0001;
    //y = inv_cumd_mixture_02(u*(upper-lower)+lower);
    y = inv_cumd_mixture(u*(upper-lower)+lower);
  }
  //log_density=w+log_likelihood_mixture_02(y);
  log_density=w+log_likelihood_mixture(y);
}

void get_bounded_normal(double x1,double x2, const double& _y,
  const double& _log_density, long int& iseed)
{
  double& y=(double&) _y;
  double& log_density=(double&) _log_density;
  double lp1;
  double lp2;
  double v;
  double w;
  double u = better_rand(iseed);
  if (x2<-5.0)
  {
    lp1=ln_normal_tail(x1);
    lp2=ln_normal_tail(x2);
    v=exp(lp1-lp2);
    w=-lp2-log(1.0-v);
    y = inv_cumd_norm_ln( lp2 + log(u*(1.0-v)+v) );
  }
  else if (x1>5.0)
  {
    lp1=ln_normal_tail(x2);
    lp2=ln_normal_tail(x1);
    v=exp(lp1-lp2);
    w=-lp2-log(1.0-v);
    y = inv_cumd_norm_ln( lp2 + log(u*(1.0-v)+v) );
    y = -y;
  }
  else
  {
    double lower=cumd_norm(x1);
    double upper=cumd_norm(x2);
    w=-log(upper-lower);
    u=u*.9998+.0001;
    y = inv_cumd_norm(u*(upper-lower)+lower);
  }
  log_density=w-0.5*y*y;
}

void get_bounded_normal_virtual(double x1,double x2, const double& _y,
  double& _log_density)
{
  double& y=(double&) _y;
  double& log_density=(double&) _log_density;
  double lp1;
  double lp2;
  double v;
  double w;
  if (x2<-5.0)
  {
    lp1=ln_normal_tail(x1);
    lp2=ln_normal_tail(x2);
    v=exp(lp1-lp2);
    w=-lp2-log(1.0-v);
  }
  else if (x1>5.0)
  {
    lp1=ln_normal_tail(x2);
    lp2=ln_normal_tail(x1);
    v=exp(lp1-lp2);
    w=-lp2-log(1.0-v);
  }
  else
  {
    double lower=cumd_norm(x1);
    double upper=cumd_norm(x2);
    w=-log(upper-lower);
  }
  log_density=w-0.5*y*y;
}

double ln_normal_tail(const double& x)
{
  if (x<0) return ln_normal_tail_left(x);
  return ln_normal_tail_right(x);
}

double ln_normal_tail_left(const double& x)
{
  if (x>-2.0)
  {
    cerr << "arugument of ln_normal_tail_left must be < -2.0 you have "
         << x << endl;
    exit(1);
  }
  return ln_normal_tail_right(-x);
}

double ln_normal_tail_right(const double& x)
{
  if (x<2.0)
  {
    cerr << "arugument of ln_normal_tail_right must be > 2.0 you have "
         << x << endl;
    exit(1);
  }
  const double a3=5;
  const double a4=9;
  const double a5=129;
  double x2=x*x;
  double lz=log(0.3989422804)-.5*x2;
  double b1=x2+2;
  double b2=b1*(x2+4);
  double b3=b2*(x2+6);
  double b4=b3*(x2+8);
  double b5=b4*(x2+10);
  double tmp=lz-log(x) +
    log(1.0 -1.0/b1 +1.0/b2 - a3/b3 +a4/b4 -a5/b5);
  return tmp;
}

/*
Same as linad99/cumdist.cpp -> double inv_cumd_norm_inner(const double& x)
double inv_cumd_norm(const double& x)
{
  const double c0=2.515517;
  const double c1=0.802853;
  const double c2=0.010328;
  const double d1=1.432788;
  const double d2=0.189269;
  const double d3=0.001308;
  if (x<=0 || x>=1.0)
  {
    cerr << "Illegal argument to inv_cumd_norm = " << x << endl;
    return 0;
  }

  if (x<0.5)
  {
    double t = sqrt(-2.*log(x));
    double p=((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1)-t;
    return p;
  }
  else if (x==0.5)
  {
    return 0.0;
  }
  else
  {
    double y=1.-x;
    double t = sqrt(-2.*log(y));
    double p=t-((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1);
    return p;
  }
}
*/

double inv_cumd_norm_ln(const double& x)
{
  const double c0=2.515517;
  const double c1=0.802853;
  const double c2=0.010328;
  const double d1=1.432788;
  const double d2=0.189269;
  const double d3=0.001308;
  if (x>=0)
  {
    cerr << "Illegal argument to inv_cumd_norm = " << x << endl;
    return 0;
  }

  if (x<log(0.5))
  {
    double t = sqrt(-2.*x);
    double p=((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1)-t;
    return p;
  }
  else
  {
    double y;
    if (x<-1.e-10)
    {
      y=log(1.-exp(x));
    }
    else
    {
      y=log(-x)*log(1.0+x*(0.5+0.1666666666667*x));
    }
    double t = sqrt(-2.*y);
    double p=t-((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1);
    return p;
  }
}

/*
Same as in linad99/cumdist.cpp
double cumd_norm(const double& x)
{
  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double p=.2316419;
  if (x>30.0)
  {
    return 1.0;
  }
  else if (x<-30.0)
  {
    return 0.0;
  }
  else if (x>=0)
  {
    double u=1./(1+p*x);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double z=1.0-0.3989422804*exp(-.5*x*x)*y;
    return z;
  }
  else
  {
    double w=-x;
    double u=1./(1+p*w);
    double y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    double z=0.3989422804*exp(-.5*x*x)*y;
    return z;
  }
}
*/

double cumd_mixture_02(const double& x)
{
  double w=0.0;
  double w1=0.0;
  double w2=0.0;
  w1=cumd_norm(x);
  w2=cumd_cauchy(x);
  w=0.98*w1+.02*w2;
  return w;
}


double cumd_mixture(const double& x)
{
  double w=0.0;
  double w1=0.0;
  double w2=0.0;
  w1=cumd_norm(x);
  w2=cumd_cauchy(x);
  w=0.95*w1+.05*w2;
  return w;
}

double log_likelihood_mixture(const double& x)
{
  double y=0.5*x*x;
  double w=log(0.379*exp(-y)+0.01254/(1.+y));
  return w;
}


double log_likelihood_mixture_02(const double& x)
{
  double y=0.5*x*x;
  double w=log(0.391*exp(-y)+0.004502/(1.+y));
  return w;
}


double inv_cumd_mixture(const double& zz)
{
  if (zz<=0.5)
  {
    if (zz> 0.030328178)  // 2.02
    {
      const double beta=0.2000006361;
      const double a1= -1.20100758;
      const double a2=  0.705759703;
      const double a3= -0.3969207118;
      const double a4=  0.1013877547;
      const double b1=  0.4064582431;
      const double b2= -1.313226944;
      const double b3= -0.4745760236;
      const double b4=  0.8704844718;
      double t=2*zz;
      double x=-log(t);
      if (x>0) x=pow(x,beta);
      double pred=inv_cumd_cauchy(zz);
      double u=(((a4*x+a3)*x+a2)*x+a1)*x+1.0;
      double v=(((b4*x+b3)*x+b2)*x+b1)*x+1.0;
      return u/v*pred;
    }
    else if (zz>0.002235963385) // -10.0
    {
      const double beta=1.391943399;
      const double a1=-0.3960836641;
      const double a2=0.06458378977;
      const double a3=-0.005347047973;
      const double a4=0.0001938683488;
      const double b1=0.1252881802;
      const double b2=0.01855936157;
      const double b3=-0.01768441436;
      const double b4=0.001537604957;
      double t=2*zz;
      double x=-log(t);
      if (x>0) x=pow(x,beta);
      double pred=inv_cumd_cauchy(zz);
      double u=(((a4*x+a3)*x+a2)*x+a1)*x+1.0;
      double v=(((b4*x+b3)*x+b2)*x+b1)*x+1.0;
      return u/v*pred;
    }
    else
    {
      return inv_cumd_cauchy(20.*zz);
    }
  }
  else
  {
    return -inv_cumd_mixture(1-zz);
  }
}

double inv_cumd_mixture_02(const double& zz)
{
  if (zz<=0.5)
  {
    if (zz> 0.030328178)  // 2.02
    {
      const double beta=0.20000048;
      const double a1=-2.1053015;
      const double a2=2.4746767;
      const double a3=-1.7449831;
      const double a4=0.49304616;
      const double b1=-0.27804868;
      const double b2=-1.391687;
      const double b3=1.0477872;
      const double b4=-0.09850461;
      double t=2*zz;
      double x=-log(t);
      if (x>0) x=pow(x,beta);
      double pred=inv_cumd_cauchy(zz);
      double u=(((a4*x+a3)*x+a2)*x+a1)*x+1.0;
      double v=(((b4*x+b3)*x+b2)*x+b1)*x+1.0;
      return u/v*pred;
    }
    else if (zz>0.002235963385) // -10.0
    {
      const double beta=1.2392131;
      const double a1=-0.42498166;
      const double a2=0.07016042;
      const double a3=-0.0053910956;
      const double a4=0.0001646762;
      const double b1=0.18071484;
      const double b2=0.00029307283;
      const double b3=-0.014820049;
      const double b4=0.0013084549;
      double t=2*zz;
      double x=-log(t);
      if (x>0) x=pow(x,beta);
      double pred=inv_cumd_cauchy(zz);
      double u=(((a4*x+a3)*x+a2)*x+a1)*x+1.0;
      double v=(((b4*x+b3)*x+b2)*x+b1)*x+1.0;
      return u/v*pred;
    }
    else
    {
      return inv_cumd_cauchy(50.*zz);
    }
  }
  else
  {
    return -inv_cumd_mixture_02(1-zz);
  }
}

/*
dvariable inv_cumd_norm(const prevariable& x)
{
  const double c0=2.515517;
  const double c1=0.802853;
  const double c2=0.010328;
  const double d1=1.432788;
  const double d2=0.189269;
  const double d3=0.001308;
  if (x<=0 || x>=1.0)
  {
    cerr << "Illegal argument to inv_cumd_norm = " << x << endl;
    return 0;
  }

  if (x<0.5)
  {
    dvariable t = sqrt(-2.*log(x));
    dvariable p=((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1)-t;
    return p;
  }
  else if (x==0.5)
  {
    return 0.0;
  }
  else
  {
    dvariable y=1.-x;
    dvariable t = sqrt(-2.*log(y));
    dvariable p=t-((c2*t+c1)*t+c0)/((((d3*t+d2)*t+d1)*t)+1);
    return p;
  }
}
*/
