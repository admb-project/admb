/*
 * $Id$
 * 
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>

static double eps=3.0e-14;
static double pim=0.7511255444649427;
static int maxit=50;

/** Gauss-Hermite quadature.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 4

    \deprecated Scheduled for replacement by 2010.
*/
void gauss_hermite(BOR_CONST dvector& _x,BOR_CONST dvector& _w)
{
  dvector x=(dvector&) _x;
  dvector w=(dvector&) _w;
  int ximin=x.indexmin();
  int ximax=x.indexmax();
  int wimin=w.indexmin();
  int wimax=w.indexmax();
  if (ximin != wimin || ximax != wimax) 
  {
    cerr << " Vector size mismatch in Gauss_hermite routine" << endl;
    ad_exit(1);
  }
    
  x.shift(1);
  w.shift(1);
  int n=x.size();
  int i,its,j,m;
  double p1,p2,p3,pp,z,z1;

  m=(n+1)/2;
  for (i=1;i<=m;i++) 
  {
    if (i == 1) 
    {
      z=sqrt((double)(2*n+1))-1.85575*pow((double)(2*n+1),-0.16667);
    } 
    else if (i == 2) 
    {
      z -= 1.14*pow((double)n,0.426)/z;
    } 
    else if (i == 3) 
    {
      z=1.86*z-0.86*x[1];
    } 
    else if (i == 4) 
    {
      z=1.91*z-0.91*x[2];
    } 
    else 
    {
      z=2.0*z-x[i-2];
    }
    for (its=1;its<=maxit;its++) 
    {
      p1=pim;
      p2=0.0;
      for (j=1;j<=n;j++) 
      {
        p3=p2;
        p2=p1;
        p1=z*sqrt(2.0/j)*p2-sqrt(((double)(j-1))/j)*p3;
      }
      pp=sqrt((double)2*n)*p2;
      z1=z;
      z=z1-p1/pp;
      if (fabs(z-z1) <= eps) break;
    }
    if (its > maxit) cerr << "too many iterations in gaussher" << endl;
    x[i]=z;
    x[n+1-i] = -z;
    w[i]=2.0/(pp*pp);
    w[n+1-i]=w[i];
  }
  x.shift(ximin);
  w.shift(ximin);
}

/** Gauss-Legendre quadature.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 4

    \deprecated Scheduled for replacement by 2010.
*/
void gauss_legendre(double x1, double x2, const dvector& _x, const dvector& _w)
{
  dvector & x=(dvector&)(_x);
  dvector & w=(dvector&)(_w);
  int ximin=x.indexmin();
  int ximax=x.indexmax();
  int wimin=w.indexmin();
  int wimax=w.indexmax();
  if (ximin != wimin || ximax != wimax) 
  {
    cerr << " Vector size mismatch in Gauss_hermite routine" << endl;
    ad_exit(1);
  }
  x.shift(1);
  w.shift(1);
    
  int m,j,i;
  double z1,z,xm,xl,pp,p3,p2,p1;
  int n=x.size();

  m=(n+1)/2;
  xm=0.5*(x2+x1);
  xl=0.5*(x2-x1);
  for (i=1;i<=m;i++) {
    z=cos(3.141592654*(i-0.25)/(n+0.5));
    do {
      p1=1.0;
      p2=0.0;
      for (j=1;j<=n;j++) {
        p3=p2;
        p2=p1;
        p1=((2.0*j-1.0)*z*p2-(j-1.0)*p3)/j;
      }
      pp=n*(z*p1-p2)/(z*z-1.0);
      z1=z;
      z=z1-p1/pp;
    } while (fabs(z-z1) > eps);
    x[i]=xm-xl*z;
    x[n+1-i]=xm+xl*z;
    w[i]=2.0*xl/((1.0-z*z)*pp*pp);
    w[n+1-i]=w[i];
  }
  x.shift(ximin);
  w.shift(ximin);
}

/** Gauss-Legendre quadature.
*/
void gauss_legendre(const dvector& _x, const dvector& _w)
{
  gauss_legendre(0,1,_x,_w);
}

/** Gauss-Hermite quadature.
 this is normlaized so that standard normal density
 integrates to 1
*/
void normalized_gauss_hermite(const dvector& _x, const dvector& _w)
{
  dvector& x=(dvector&) _x;
  dvector& w=(dvector&) _w;
  gauss_hermite(x,w);
  w=elem_prod(w,exp(square(x)));
  x*=sqrt(2.0);
  w*=sqrt(2.0);
}
  
