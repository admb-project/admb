/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

double inv_cumd_norm(_CONST double& x);
double cumd_norm(_CONST double& x);
double myran1(long int&);
//double better_rand(long int&);

dvector new_probing_bounded_multivariate_normal(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,BOR_CONST double& _wght,double pprobe, random_number_generator& rng)
{
  double& wght=(double&) _wght;
  const double rob1=0.95;
  const double sqrt_tpi =sqrt(2*3.14159);
  dvector w(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  a=a1;
  b=b1;
  wght=0;
  double rwght=0;
  double nwght=0;
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
  //int in=0;
  //int ie=0;
  double u = rng.better_rand();
  int rflag;
  if (u>rob1)
  {
    rflag=1;
  }
  else
  {
    rflag=0;
  }
  if (!rflag)
  {
    for (int i=1;i<=nvar;i++)
    {
      ah=a(i)/ch(i,i); 
      bl=b(i)/ch(i,i); 
      double u = rng.better_rand();
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
        y = inv_cumd_norm(u*(upper-lower)+lower);
      }
      else
      {
        y = inv_cumd_cauchy(u*(upper1-lower1)+lower1);
      }
      if (diff>1.e-5)
      {
        nwght+=-.5*y*y -log(sqrt_tpi*diff);
      }
      else
      {
        nwght += log_density_cauchy(y)-log(diff1);
      }
      for (int j=i;j<=nvar;j++)
      {
        double tmp=y*ch(j,i);
        w(j)+=tmp;
        a(j)-=tmp;
        b(j)-=tmp;
      }
    }
    wght = nwght;
  }
  else
  {
    a=a1;
    b=b1;
    for (int i=1;i<=nvar;i++)
    {
      ah=a(i)/ch(i,i); 
      bl=b(i)/ch(i,i); 
      double u = rng.better_rand();
      double pp = rng.better_rand();
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
        rwght+=log((1.0-pprobe)*exp(-.5*y*y)/(sqrt_tpi*diff)
         +pprobe*density_cauchy(y)/diff1);
      }
      else
      {
        rwght += log_density_cauchy(y)-log(diff1);
      }
      for (int j=i;j<=nvar;j++)
      {
        double tmp=y*ch(j,i);
        w(j)+=tmp;
        a(j)-=tmp;
        b(j)-=tmp;
      }
    }
    double dd=rob1*(exp(nwght-rwght))+1.0-rob1;
    if (dd<=0)
    {
      cerr << "dd <=0" << endl;
    }
    wght = log(dd)+rwght;
  }
  return w; 
}


void new_probing_bounded_multivariate_normal_mcmc(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch, BOR_CONST double& _wght,BOR_CONST dvector& _y,double pprobe, random_number_generator& rng)
{
  double& wght=(double&) _wght;
  const double rob1=0.95;
  const double sqrt_tpi =sqrt(2*3.14159);
  dvector w(1,nvar);
  dvector a(1,nvar);
  dvector b(1,nvar);
  dvector alpha(1,nvar);
  dvector beta(1,nvar);
  wght=0;
  double rwght=0;
  double nwght=0;
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
  //int in=0;
  //int ie=0;

  a=a1;
  b=b1;
  int i;
  for (i=1;i<=nvar;i++)
  {
    y=_y(i);
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
    /*double u = */rng.better_rand();
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
  
    if (diff>1.e-5)
    {
      nwght+=-.5*y*y -log(sqrt_tpi*diff);
    }
    else
    {
      nwght+= log_density_cauchy(y)-log(diff1);
    }
    for (int j=i;j<=nvar;j++)
    {
      double tmp=y*ch(j,i);
      w(j)+=tmp;
      a(j)-=tmp;
      b(j)-=tmp;
    }
  }
  a=a1;
  b=b1;
  w.initialize();
  for (i=1;i<=nvar;i++)
  {
    y=_y(i);
    ah=a(i)/ch(i,i); 
    bl=b(i)/ch(i,i); 
    double u = rng.better_rand();
    double pp = rng.better_rand();
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
      rwght+=log((1.0-pprobe)*exp(-.5*y*y)/(sqrt_tpi*diff)
       +pprobe*density_cauchy(y)/diff1);
    }
    else
    {
      rwght += log_density_cauchy(y)-log(diff1);
    }
  }
  wght = log(rob1*(exp(nwght-rwght))+(1.0-rob1))+rwght;
  for (int j=i;j<=nvar;j++)
  {
    double tmp=y*ch(j,i);
    w(j)+=tmp;
    a(j)-=tmp;
    b(j)-=tmp;
  }
}

void sobseq(int*,BOR_CONST dvector&);

