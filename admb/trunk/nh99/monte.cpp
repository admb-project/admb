/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>

double inv_cumd_norm(_CONST double& x);
double cumd_norm(_CONST double& x);
double myran1(long int&);
double better_rand(long int&);
double ffmax(double a,double b)
{
  if (a>=b) return a;
  return b;
}
double ffmin(double a,double b)
{
  if (a<=b) return a;
  return b;
}
    


void bull(double y) {;}

double inv_cumd_exp(double x)
{
  if (x>.5)
  {
    return -log(2.*(x-1.));
  }
  else
  {
    return -log(2.*x);
  }
} 

double cumd_exp(double x)
{
  if (x<=0.0)
  {
    return 0.5*exp(-x);
  }
  else
  {
    return 1.0-0.5*exp(-x);
  }                  
}

dvector bounded_multivariate_normal(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& _wght)
{
  double& wght= (double&) _wght;
  const double sqrt_tpi =sqrt(2*3.14159);
  dvector w(1,nvar);
  //dvector ty(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  a=a1;
  b=b1;
  wght=0;
  w.initialize();
  double ah; 
  double bl; 
  double upper;
  double lower; 
  double diff;
  int expflag;
  double y;
  int in=0;
  int ie=0;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
    double u = better_rand(iseed);
    upper=cumd_norm(bl);
    lower=cumd_norm(ah); 
    diff=upper-lower;
    if (diff>1.e-5)
    {
      wght-=log(diff);
      expflag=0;
    }
    else
    {
      upper=cumd_cauchy(bl);
      lower=cumd_cauchy(ah);
      diff=upper-lower;
      wght-=log(diff);
      expflag=1;
    }

    u=u*.9998+.0001;
    if (!expflag)
    {
      y = inv_cumd_norm(u*(upper-lower)+lower);
      wght -= .5*y*y;
      in++;
    }
    else
    {
      y = inv_cumd_cauchy(u*(upper-lower)+lower);
      ie++;
      wght += log_density_cauchy(y);
    }
    //ty(i)=y;
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y*ch(j,i);
      w(j)+=tmp;
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
  //cout << ty << endl;
  wght +=  in*log(1./sqrt_tpi);
  return w; 
}

dvector probing_bounded_multivariate_normal(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& _wght,double pprobe)
{
  double& wght= (double&) _wght;
  const double sqrt_tpi =sqrt(2*3.14159);
  dvector w(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  a=a1;
  b=b1;
  wght=0;
  w.initialize();
  double ah; 
  double bl; 
  double upper;
  double lower; 
  double upper1;
  double lower1; 
  double diff;
  double diff1;
  int expflag;
  double y;
  int in=0;
  int ie=0;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
    double u = better_rand(iseed);
    double pp = better_rand(iseed);
    upper=cumd_norm(bl);
    lower=cumd_norm(ah); 
    diff=upper-lower;
    if (diff>1.e-5)
    {
      expflag=0;
    }
    else
    {
      expflag=1;
    }
    upper1=cumd_cauchy(bl);
    lower1=cumd_cauchy(ah);
    diff1=upper1-lower1;

    u=u*.9998+.0001;
    if (!expflag)
    {
      if (pp>pprobe)
        y = inv_cumd_norm(u*(upper-lower)+lower);
      else
        y = inv_cumd_cauchy(u*(upper1-lower1)+lower1);
    }
    else
    {
      y = inv_cumd_cauchy(u*(upper1-lower1)+lower1);
    }
    if (diff>1.e-5)
    {
      wght+=log((1.0-pprobe)*exp(-.5*y*y)/(sqrt_tpi*diff)
       +pprobe*density_cauchy(y)/diff1);
    }
    else
    {
      wght += log_density_cauchy(y)-log(diff1);
    }

    for (int j=i;j<=nvar;j++)
    {
      double tmp=y*ch(j,i);
      w(j)+=tmp;
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
  return w; 
}

dvector bounded_multivariate_uniform(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& _wght)
{
  double& wght= (double&) _wght;
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector w(1,nvar);
  w.initialize();
  a=a1;
  b=b1;
  wght=0;
  double ah; 
  double bl; 
  double upper;
  double lower; 
  double diff;
  double y;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
    double u = better_rand(iseed);
    lower=ffmax(-1.0,ah);
    upper=ffmin(1.0,bl);
    diff=upper-lower;
    wght-=log(diff);

    y=lower+u*diff;
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y*ch(j,i);
      w(j)+=tmp;
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
  return w;
}

dvector bounded_robust_multivariate_normal(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,BOR_CONST dmatrix& ch3, double contaminant, long int& iseed,BOR_CONST double& _wght)
{
  double& wght= (double&) _wght;
  dvector w(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  a=a1;
  b=b1;
  wght=1;
  w.initialize();
  double ah; 
  double bl; 
  double r = better_rand(iseed);
  if (r>contaminant)
  {
    for (int i=1;i<=nvar;i++)
    {
      ah=a(i)/ch(i,i); 
      bl=b(i)/ch(i,i); 
      double u = better_rand(iseed);
      double upper=cumd_norm(bl);
      double lower=cumd_norm(ah); 
      wght *= upper-lower;
      u=u*.9998+.0001;
      double y = inv_cumd_norm(u*(upper-lower)+lower); 
      if (y>3.5)
      {
        bull(y);
      }
      for (int j=i;j<=nvar;j++)
      {
        double tmp=y*ch(j,i);
        w(j)+=tmp;
        a(j)-=tmp;
        b(j)-=tmp;
      }
    }
  }
  else
  {
    // use the bigger variance normal
    for (int i=1;i<=nvar;i++)
    {
      ah=a(i)/ch3(i,i); 
      bl=b(i)/ch3(i,i); 
      double u = better_rand(iseed);
      double upper=cumd_norm(bl);
      double lower=cumd_norm(ah); 
      wght *= upper-lower;
      u=u*.9998+.0001;
      double y = inv_cumd_norm(u*(upper-lower)+lower); 
      if (y>3.5)
      {
        bull(y);
      }
      for (int j=i;j<=nvar;j++)
      {
        double tmp=y*ch3(j,i);
        w(j)+=tmp;
        a(j)-=tmp;
        b(j)-=tmp;
      }
    }
  }
  return w; 
}
void sobseq(int*,BOR_CONST dvector&);

/*
dvector bounded_multivariate_normal_sobol(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& wght)
{
  const double sqrt_tpi =sqrt(2*3.14159);
  dvector w(1,nvar);
  //dvector ty(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  a=a1;
  b=b1;
  wght=0;
  w.initialize();
  double ah; 
  double bl; 
  double upper;
  double lower; 
  double diff;
  int expflag;
  double y;
  int in=0;
  int ie=0;
  dvector uu(1,nvar);
  sobseq(&nvar,uu);
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
    double u = uu(i);
    upper=cumd_norm(bl);
    lower=cumd_norm(ah); 
    diff=upper-lower;
    if (diff>1.e-5)
    {
      wght-=log(diff);
      expflag=0;
    }
    else
    {
      upper=cumd_cauchy(bl);
      lower=cumd_cauchy(ah);
      diff=upper-lower;
      wght-=log(diff);
      expflag=1;
    }

    u=u*.9998+.0001;
    if (!expflag)
    {
      y = inv_cumd_norm(u*(upper-lower)+lower);
      wght -= .5*y*y;
      in++;
    }
    else
    {
      y = inv_cumd_cauchy(u*(upper-lower)+lower);
      ie++;
      wght += log_density_cauchy(y);
    }
    //ty(i)=y;
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y*ch(j,i);
      w(j)+=tmp;
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
  wght +=  in*log(1./sqrt_tpi);
  return w; 
}
*/

/*
dvector bounded_multivariate_normal(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed)
{
  dvector w(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  a=a1;
  b=b1;
  int badflag=0;
  do
  {
    w.initialize();
    for (int i=1;i<=nvar;i++)
    {
      double u = better_rand(iseed);
      double y = inv_cumd_norm(u); 
      for (int j=i;j<=nvar;j++)
      {
        double tmp=y*ch(j,i);
        w(j)+=tmp;
      }
    }
    badflag=0;
    for (i=1;i<=nvar;i++)
    {
      if ( w(i)<=a(i) )
      {
        //cout << "a " << i << "  " << w(i) << "  " << a(i) << endl;
        badflag=1;
        break;
      } 
      if ( w(i)>=b(i) )
      {
        //cout << "b "<< i << "  " << w(i) << "  " << b(i) << endl;
        badflag=1;
        break;
      } 
    }
  }
  while (badflag);
  return w; 
}
*/


