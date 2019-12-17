/**
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB Foundation
 */
/**
 * \file
 * Contains routines for numerical integration
 */

#include <admodel.h>
//#define EPS 1.0e-4
#define JMAX 50
//#define JMAXP JMAX+1
//#define K 5

class model_parameters;

dvariable trapzd(_func func, double a, double b, int n);
dvariable trapzd(_func func, double a, const dvariable& b, int n);
dvariable trapzd(_func func, const dvariable& a, const dvariable& b, int n);
dvariable trapzd(_func func, const dvariable& a, double b, int n);

void polint(const dvector& xa, const dvar_vector& ya,int n,double x,
  const dvariable& y, const dvariable& dy);

/** Romberg integration.
  \param func Pointer to a member function of class model_parameters.
  \param a Lower limit of integration.
  \param b Upper limit of inegration.
  \param ns
  \return The integral of the function from a to b using Romberg's method
*/
dvariable function_minimizer::adromb(_func func, double a, double b, int ns)
{
  const double base = 4;
  int MAXN = min(JMAX, ns);
  dvar_vector s(1,MAXN+1);

  for(int j=1; j<=MAXN+1; j++)
  {
    s[j] = trapzd(func,a,b,j);
  }

  for(int iter=1; iter<=MAXN+1; iter++)
  {
    for(int j=1; j<=MAXN+1-iter; j++)
    {
      s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
    }
  }

  return s[1];
}

/** Romberg integration.
  \param func Pointer to a member function of class model_parameters.
  \param a Lower limit of integration.
  \param b Upper limit of inegration.
  \param ns
  \return The integral of the function from a to b using Romberg's method
*/
dvariable function_minimizer::adromb(_func func, const dvariable& a, double b, int ns)
{
  const double base = 4;
  int MAXN = min(JMAX, ns);
  dvar_vector s(1,MAXN+1);

  for(int j=1; j<=MAXN+1; j++)
  {
    s[j] = trapzd(func,a,b,j);
  }

  for(int iter=1; iter<=MAXN+1; iter++)
  {
    for(int j=1; j<=MAXN+1-iter; j++)
    {
      s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
    }
  }

  return s[1];
}

/** Romberg integration.
  \param func Pointer to a member function of class model_parameters.
  \param a Lower limit of integration.
  \param b Upper limit of inegration.
  \param ns
  \return The integral of the function from a to b using Romberg's method
*/
dvariable function_minimizer::adromb(_func func, double a, const dvariable& b, int ns)
{
  const double base = 4;
  int MAXN = min(JMAX, ns);
  dvar_vector s(1,MAXN+1);

  for(int j=1; j<=MAXN+1; j++)
  {
    s[j] = trapzd(func,a,b,j);
  }

  for(int iter=1; iter<=MAXN+1; iter++)
  {
    for(int j=1; j<=MAXN+1-iter; j++)
    {
      s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
    }
  }

  return s[1];
}

/** Romberg integration.
  \param func Pointer to a member function of class model_parameters.
  \param a Lower limit of integration.
  \param b Upper limit of inegration.
  \param ns
  \return The integral of the function from a to b using Romberg's method
*/
dvariable function_minimizer::adromb(_func func, const dvariable& a, const dvariable& b, int ns)
{
  const double base = 4;
  int MAXN = min(JMAX, ns);
  dvar_vector s(1,MAXN+1);

  for(int j=1; j<=MAXN+1; j++)
  {
    s[j] = trapzd(func,a,b,j);
  }

  for(int iter=1; iter<=MAXN+1; iter++)
  {
    for(int j=1; j<=MAXN+1-iter; j++)
    {
      s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
    }
  }

  return s[1];
}

/** Extended trapezoid rule.
 *
 * This algorithm was adapted from function trapzd in
 * "Numerical Recipes in C", 2nd edition,
 * Press, Teukolsky, Vetterling, Flannery, chapter 4.2
 *
 */
dvariable function_minimizer::trapzd(_func func, double a, double b, int n)
{
  double x,num_interval,hn;
  dvariable sum;
  static dvariable s;
  static int interval;
  int j;
  if (n == 1) {
    interval=1;
    return (s=0.5*(b-a)*(func(a)+func(b)));
  } else {
    num_interval=interval;
    hn=(b-a)/num_interval;
    x=a+0.5*hn;
    for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += func(x);
    interval *= 2;
    s=0.5*(s+(b-a)*sum/num_interval);
    return s;
  }
}

/** Extended trapezoid rule.
 *
 * This algorithm was adapted from function trapzd in
 * "Numerical Recipes in C", 2nd edition,
 * Press, Teukolsky, Vetterling, Flannery, chapter 4.2
 *
 */
dvariable function_minimizer::trapzd(_func func, const dvariable& a, double b, int n)
{
  double num_interval;
  dvariable x,sum,hn;
  static dvariable s;
  static int interval;
  int j;
  if (n == 1) {
    interval=1;
    return (s=0.5*(b-a)*(func(a)+func(b)));
  } else {
    num_interval=interval;
    hn=(b-a)/num_interval;
    x=a+0.5*hn;
    for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += func(x);
    interval *= 2;
    s=0.5*(s+(b-a)*sum/num_interval);
    return s;
  }
}

/** Extended trapezoid rule.
 *
 * This algorithm was adapted from function trapzd in
 * "Numerical Recipes in C", 2nd edition,
 * Press, Teukolsky, Vetterling, Flannery, chapter 4.2
 */
dvariable function_minimizer::trapzd(_func func, double a, const dvariable& b, int n)
{
  double num_interval;
  dvariable sum,hn,x;
  static dvariable s;

  static int interval;
  int j;

  if (n == 1) {
    interval=1;
    return (s=0.5*(b-a)*(func(a)+func(b)));
  } else {
    num_interval=interval;
    hn=(b-a)/num_interval;
    x=a+0.5*hn;
    for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += func(x);
    interval *= 2;
    s=0.5*(s+(b-a)*sum/num_interval);
    return s;
  }
}

/** Extended trapezoid rule.
 *
 * This algorithm was adapted from function trapzd in
 * "Numerical Recipes in C", 2nd edition,
 * Press, Teukolsky, Vetterling, Flannery, chapter 4.2
 */
dvariable function_minimizer::trapzd(_func func, const dvariable& a, const dvariable& b, int n)
{
  double num_interval;
  dvariable sum,hn,x;
  static dvariable s;
  static int interval;
  int j;

  if (n == 1) {
    interval=1;
    return (s=0.5*(b-a)*(func(a)+func(b)));
  } else {
    num_interval=interval;
    hn=(b-a)/num_interval;
    x=a+0.5*hn;
    for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += func(x);
    interval *= 2;
    s=0.5*(s+(b-a)*sum/num_interval);
    return s;
  }
}
//#undef EPS
#undef JMAX
//#undef JMAXP
//#undef K

 //Not used elsewhere
void polint(const dvector& xa, const dvar_vector& ya,int n,double x,
  const dvariable& _y, const dvariable& _dy)
{
  dvariable& y=(dvariable&) _y;
  dvariable& dy=(dvariable&) _dy;
  int i,m,ns=1;
  double dif,dift,ho,hp;
  dvariable den,w;

  dif=fabs(x-xa[1]);
  dvar_vector c(1,n);
  dvar_vector d(1,n);
  for (i=1;i<=n;i++) {
    if ( (dift=fabs(x-xa[i])) < dif) {
      ns=i;
      dif=dift;
    }
    c[i]=ya[i];
    d[i]=ya[i];
  }
  y=ya[ns--];
  for (m=1;m<n;m++) {
    for (i=1;i<=n-m;i++) {
      ho=xa[i]-x;
      hp=xa[i+m]-x;
      w=c[i+1]-d[i];
      if ( (den=ho-hp) == 0.0)
      {
        cerr << "Error in routine POLINT" << endl;
        exit(1);
      }
      den=w/den;
      d[i]=hp*den;
      c[i]=ho*den;
    }
    y += (dy=(2*ns < (n-m) ? c[ns+1] : d[ns--]));
  }
}
