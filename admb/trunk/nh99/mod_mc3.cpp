/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>

#ifdef __GNUDOS__
  #include <gccmanip.h>
#endif

double better_rand(long int&);

void initial_params::add_random_vector(BOR_CONST dvector& y,BOR_CONST dvector& x,BOR_CONST double& ll,
  BOR_CONST dvector& diag)
{
  int ii=1;
  for (int i=0;i<num_initial_params;i++)
  {
    if (withinbound(0,(varsptr[i])->phase_start,current_phase))
    {
      (varsptr[i])->add_value(y,x,ii,ll,diag);
    }
  }
}
void initial_params::get_jacobian_value(BOR_CONST dvector& y,BOR_CONST dvector& jac)
{
  int ii=1;
  for (int i=0;i<num_initial_params;i++)
  {
    if (withinbound(0,(varsptr[i])->phase_start,current_phase))
    {
      (varsptr[i])->get_jacobian(y,jac,ii);
    }
  }
}


void multivariate_mixture(BOR_CONST dvector& _mix,int nvar,long int& iseed,
  BOR_CONST double& _log_density_normal,BOR_CONST double& _log_density_cauchy,
  BOR_CONST double& _log_density_small_normal,int is)
{
  dvector& mix=(dvector&) _mix;
  double& log_density_cauchy=(double&) _log_density_cauchy;
  double& log_density_normal=(double&) _log_density_normal;
  double& log_density_small_normal=(double&) _log_density_small_normal;
  const double r2=sqrt(2.0);
  const double l2p=0.5*log(2*3.1415927);
  const double l3p=0.5*log(2*3.1415927)-log(3.0);
  const double pr2=log(3.1415927*r2);
  log_density_normal=0.0;
  log_density_cauchy=0.0;
  
 
  if (is==0)
  {
    for (int i=1;i<=nvar;i++)
    {
      double u;
      do
      {
        u = better_rand(iseed);
      }
      while (u<.0001 || u>.9999);
      mix(i) = inv_cumd_norm(u); 
      log_density_normal-= l2p +.5*mix(i)*mix(i);
      log_density_small_normal-= l3p +4.5*mix(i)*mix(i);
      log_density_cauchy+= -pr2 + 1./(1.+mix(i)*mix(i)); 
    }
  }
  else if (is==2)
  {
    for (int i=1;i<=nvar;i++)
    {
      double u;
      do
      {
        u = better_rand(iseed);
      }
      while (u<.0001 || u>.9999);
      mix(i) = inv_cumd_norm(u); 
      mix(i)/=3;
      log_density_normal-= l2p +.5*mix(i)*mix(i);
      log_density_cauchy+= -pr2 + 1./(1.+mix(i)*mix(i)); 
      log_density_small_normal-= l3p +4.5*mix(i)*mix(i);
    }
  }
  else if (is==1)
  {
    for (int i=1;i<=nvar;i++)
    {
      double u;
      do
      {
        u = better_rand(iseed);
      }
      while (u<.0001 || u>.9999);
      mix(i) = inv_cumd_cauchy(u); 
      log_density_normal-= l2p +.5*mix(i)*mix(i);
      log_density_small_normal-= l3p +4.5*mix(i)*mix(i);
      log_density_cauchy+= -pr2 + 1./(1.+mix(i)*mix(i)); 
    }
  }
  else
  {
    for (int i=1;i<=nvar;i++)
    {
      double u=0.5;
      while (u<.0001 || u>.9999);
      mix(i) = inv_cumd_cauchy(u); 
      log_density_normal-= l2p +.5*mix(i)*mix(i);
      log_density_small_normal-= l3p +4.5*mix(i)*mix(i);
      log_density_cauchy+= -pr2 + 1./(1.+mix(i)*mix(i)); 
    }
  }  
}

double set_value_inv_mc(const prevariable& z,double min, double max)
{
  return tan(3.1415927*( (value(z)-min)/(max-min)-0.5 ));
}

double set_value_inv_mc(double z,double min, double max)
{
  return tan(3.1415927*( (z-min)/(max-min)-0.5 ));
}

dvariable set_value_mc(const prevariable& z,double min,double max)
{
  const double pinv=1./3.1415927;
  dvariable y=atan(z)*pinv+0.5;
  return min+(max-min)*y;
}

double set_value_mc(double z,double min,double max)
{
  const double pinv=1./3.1415927;
  double y=atan(z)*pinv+0.5;
  return min+(max-min)*y;
}

void set_value_inv_mc(_CONST dvar_vector& x,BOR_CONST dvector& _v, BOR_CONST int& _ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  dvector& v=(dvector&) _v;
  int& ii=(int&) _ii;
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    v(ii++)=set_value_inv_mc(x(i),fmin,fmax);
  }
}

void set_value_mc(BOR_CONST dvar_vector& _x,_CONST dvar_vector& v, BOR_CONST int& _ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  ADUNCONST(dvar_vector,x)
  int& ii=(int&) _ii;
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    x(i)=set_value_mc(v(ii++),fmin,fmax);
  }
}



