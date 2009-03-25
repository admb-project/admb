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




void bounded_multivariate_normal_mcmc(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& _wght,BOR_CONST dvector& y)
{
  double & wght=(double &) _wght;
  //cout << y << endl;
  const double sqrt_tpi =sqrt(2*3.14159);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  a=a1;
  b=b1;
  wght=0;
  double ah; 
  double bl; 
  double upper;
  double lower; 
  double diff;
  int expflag;
  int in=0;
  int ie=0;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
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

    if (!expflag)
    {
      wght -= .5*y(i)*y(i);
      in++;
    }
    else
    {
      ie++;
      wght += log_density_cauchy(y(i));
    }


    for (int j=i;j<=nvar;j++)
    {
      double tmp=y(i)*ch(j,i);
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
  wght +=  in*log(1./sqrt_tpi);
}


void probing_bounded_multivariate_normal_mcmc(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& _wght,BOR_CONST dvector& y,double pprobe)
{
  double & wght=(double &) _wght;
  //cout << y << endl;
  const double sqrt_tpi =sqrt(2*3.14159);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  a=a1;
  b=b1;
  wght=0;
  double ah; 
  double bl; 
  double upper;
  double lower; 
  double diff;
  double diff1;
  int in=0;
  int ie=0;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
    upper=cumd_norm(bl);
    lower=cumd_norm(ah); 
    diff=upper-lower;
    upper=cumd_cauchy(bl);
    lower=cumd_cauchy(ah);
    diff1=upper-lower;
    if (diff>1.e-5)
    {
      wght+=log((1.0-pprobe)*exp(-.5*y(i)*y(i))/(sqrt_tpi*diff)
         +pprobe*density_cauchy(y(i))/diff1);
    }
    else
    {
      wght += log_density_cauchy(y(i))-log(diff1);
    }

    for (int j=i;j<=nvar;j++)
    {
      double tmp=y(i)*ch(j,i);
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
}


void bounded_multivariate_uniform_mcmc(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& _wght,BOR_CONST dvector& y)
{
  double& wght=(double&) _wght;
  dvector a(1,nvar);
  dvector b(1,nvar);
  a=a1;
  b=b1;
  wght=0;
  double ah; 
  double bl; 
  double upper;
  double lower; 
  double diff;
  for (int i=1;i<=nvar;i++)
  {
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
    lower=ffmax(-1.0,ah);
    upper=ffmin(1.0,bl);
    diff=upper-lower;
    wght-=log(diff);
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y(i)*ch(j,i);
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
}


