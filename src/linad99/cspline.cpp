/**
\file
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include <fvar.hpp>

dvector spline(const dvector &x,const dvector&y,double yp1,double ypn);

double splint(const dvector& xa,const dvector& ya,const dvector& y2a,double x);

cubic_spline_function::cubic_spline_function(const dvector & _x,
  const dvector& _y,double yp1,double ypn) : x(_x) , y(_y)
{
  y2.allocate(x);
  y2=spline(x,y,yp1,ypn);
}

double cubic_spline_function::operator () (double u)
{
  // need to deal with u<x(1) or u>x(2)
  return splint(x,y,y2,u);
}

dvector cubic_spline_function::operator () (const dvector& u)
{
  int mmin=u.indexmin();
  int mmax=u.indexmax();
  dvector z(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    z(i)=splint(x,y,y2,u(i));
  }
  return z;
}

dvector spline(const dvector &_x,const dvector&_y,double yp1,double ypn)
{
  dvector& x=(dvector&) _x;
  dvector& y=(dvector&) _y;
  int orig_min=x.indexmin();
  x.shift(1);
  y.shift(1);
  // need to check that x is monotone increasing;
  if  ( x.indexmax() != y.indexmax() )
  {
    cerr << " Incompatible bounds in input to spline" << endl;
  }
  int n=x.indexmax();
  dvector y2(1,n);
  int i,k;
  double  p,qn,sig,un;

  dvector u(1,n-1);
  if (yp1 > 0.99e30)
  {
    y2[1]=u[1]=0.0;
  }
  else
  {
    y2[1] = -0.5;
    u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
  }
  for (i=2;i<=n-1;i++)
  {
    sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
    p=sig*y2[i-1]+2.0;
    y2[i]=(sig-1.0)/p;
    u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
    u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
  }
  if (ypn > 0.99e30)
  {
    qn=un=0.0;
  }
  else
  {
    qn=0.5;
    un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
  }
  y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
  for (k=n-1;k>=1;k--)
  {
    y2[k]=y2[k]*y2[k+1]+u[k];
  }
  x.shift(orig_min);
  y.shift(orig_min);
  y2.shift(orig_min);
  return y2;
}

double splint(const dvector& _xa,const dvector& _ya,const dvector& _y2a,
  double x)
{
  dvector& xa=(dvector&) _xa;
  dvector& ya=(dvector&) _ya;
  dvector& y2a=(dvector&) _y2a;
  int orig_min=xa.indexmin();
  xa.shift(1);
  ya.shift(1);
  y2a.shift(1);
  double y;
  int n = xa.indexmax();
  int klo,khi,k;
  double h,b,a;

  klo=1;
  khi=n;
  while (khi-klo > 1)
  {
    k=(khi+klo) >> 1;
    if (xa[k] > x) khi=k;
    else klo=k;
  }
  h=xa[khi]-xa[klo];
  a=(xa[khi]-x)/h;
  b=(x-xa[klo])/h;
  y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
  xa.shift(orig_min);
  ya.shift(orig_min);
  y2a.shift(orig_min);
  return y;
}
