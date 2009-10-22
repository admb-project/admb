/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */

#include <admodel.h>
#define EPS 1.0e-4
#define JMAX 50
#define JMAXP JMAX+1
#define K 5

class model_parameters;

dvariable trapzd(dvariable (model_parameters::*func)(const dvariable&),double a,double b,int n);
dvariable trapzd(dvariable (model_parameters::*func)(const dvariable&),double a,BOR_CONST dvariable& b,int n);
dvariable trapzd(dvariable (model_parameters::*func)(const dvariable&),BOR_CONST dvariable& a,BOR_CONST dvariable& b,int n);
dvariable trapzd(dvariable (model_parameters::*func)(const dvariable&),BOR_CONST dvariable& a,double b,int n);

void polint(BOR_CONST dvector& xa,BOR_CONST dvar_vector& ya,int n,double x,
  BOR_CONST dvariable& y,BOR_CONST dvariable& dy);


/** Romberg integration.
  \param func Pointer to a member function of class model_parameters.
  \param a Lower limit of integration.
  \param b Upper limit of inegration.
  \param ns
  \return The integral of the function from a to b

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 7

   \deprecated Scheduled for replacement by 2010.
*/
dvariable function_minimizer::adromb(dvariable (model_parameters::*func)(const dvariable&),double a,
  double b,int ns)
{
  dvariable ss,dss;
  //double s[JMAXP+1],h[JMAXP+1];
  dvar_vector s(0,JMAXP+1);
  dvector h(0,JMAXP+1);
  int j;

  h[1]=1.0;
  for (j=1;j<=JMAX;j++) 
  {
    s[j]=trapzd(func,a,b,j);
    if (j >= K) 
    {
      polint(h(j-K,JMAXP+1).shift(0),s(j-K,JMAXP+1).shift(0),K,0.0,ss,dss);
      //if (fabs(value(dss)) < EPS*fabs(value(ss))) return ss;
      if (j==ns) return ss;
    }
    s[j+1]=s[j];
    h[j+1]=0.25*h[j];
  }
  cerr << "Too many steps in routine QROMB" << endl;
  return 0.0;
}


/** Romberg integration.
  \param func Pointer to a member function of class model_parameters.
  \param a Lower limit of integration.
  \param b Upper limit of inegration.
  \param ns
  \return The integral of the function from a to b

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 7

    \deprecated Scheduled for replacement by 2010.
*/
dvariable function_minimizer::adromb(dvariable (model_parameters::*func)(const dvariable&),BOR_CONST dvariable& a,
  double b,int ns)
{
  dvariable ss,dss;
  //double s[JMAXP+1],h[JMAXP+1];
  dvar_vector s(0,JMAXP+1);
  dvector h(0,JMAXP+1);
  int j;

  h[1]=1.0;
  for (j=1;j<=JMAX;j++) 
  {
    s[j]=trapzd(func,a,b,j);
    if (j >= K) 
    {
      polint(h(j-K,JMAXP+1).shift(0),s(j-K,JMAXP+1).shift(1),K,0.0,ss,dss);
      //if (fabs(value(dss)) < EPS*fabs(value(ss))) return ss;
      if (j==ns) return ss;
    }
    s[j+1]=s[j];
    h[j+1]=0.25*h[j];
  }
  cerr << "Too many steps in routine QROMB" << endl;
  return 0.0;
}

/** Romberg integration.
  \param func Pointer to a member function of class model_parameters.
  \param a Lower limit of integration.
  \param b Upper limit of inegration.
  \param ns
  \return The integral of the function from a to b

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 7

    \deprecated Scheduled for replacement by 2010.
*/
dvariable function_minimizer::adromb(dvariable (model_parameters::*func)(const dvariable&),double a,
  BOR_CONST dvariable& b,int ns)
{
  dvariable ss,dss;
  //double s[JMAXP+1],h[JMAXP+1];
  dvar_vector s(0,JMAXP+1);
  dvector h(0,JMAXP+1);
  int j;

  h[1]=1.0;
  for (j=1;j<=JMAX;j++) 
  {
    s[j]=trapzd(func,a,b,j);
    if (j >= K) 
    {
      polint(h(j-K,JMAXP+1).shift(0),s(j-K,JMAXP+1).shift(1),K,0.0,ss,dss);
      //if (fabs(value(dss)) < EPS*fabs(value(ss)))
      if (j==ns) return ss;
    }
    s[j+1]=s[j];
    h[j+1]=0.25*h[j];
  }
  cerr << "Too many steps in routine QROMB" << endl;
  return 0.0;
}


/** Romberg integration.
  \param func Pointer to a member function of class model_parameters.
  \param a Lower limit of integration.
  \param b Upper limit of inegration.
  \param ns
  \return The integral of the function from a to b

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 7

    \deprecated Scheduled for replacement by 2010.
*/
dvariable function_minimizer::adromb(dvariable (model_parameters::*func)(const dvariable&),
  BOR_CONST dvariable& a,BOR_CONST dvariable& b, int ns)
{
  dvariable ss,dss;
  //double s[JMAXP+1],h[JMAXP+1];
  dvar_vector s(0,JMAXP+1);
  dvector h(0,JMAXP+1);
  int j;

  h[1]=1.0;
  for (j=1;j<=JMAX;j++) 
  {
    s[j]=trapzd(func,a,b,j);
    if (j >= K) 
    {
      polint(h(j-K,JMAXP+1).shift(0),s(j-K,JMAXP+1).shift(1),K,0.0,ss,dss);
      //if (fabs(value(dss)) < EPS*fabs(value(ss))) return ss;
      if (j==ns) return ss;
    }
    s[j+1]=s[j];
    h[j+1]=0.25*h[j];
  }
  cerr << "Too many steps in routine QROMB" << endl;
  return 0.0;
}


/** Extended trapezoid rule.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 7

    \deprecated Scheduled for replacement by 2010.
*/
dvariable function_minimizer::trapzd(dvariable (model_parameters::*func)(const dvariable&),double a,double b,int n)
{
  double x,tnm,del;
  dvariable sum;
  static dvariable s;
  static int it;
  int j;
  model_parameters * ptr= (model_parameters *) mycast();

  if (n == 1) {
    it=1;
    return (s=0.5*(b-a)*((ptr->*func)(a)+(ptr->*func)(b)));
  } else {
    tnm=it;
    del=(b-a)/tnm;
    x=a+0.5*del;
    for (sum=0.0,j=1;j<=it;j++,x+=del) sum += (ptr->*func)(x);
    it *= 2;
    s=0.5*(s+(b-a)*sum/tnm);
    return s;
  }
}


dvariable function_minimizer::trapzd(dvariable (model_parameters::*func)(const dvariable&),BOR_CONST dvariable& a,double b,int n)
{
  double tnm;
  dvariable x,sum,del;
  static dvariable s;
  static int it;
  int j;
  model_parameters * ptr= (model_parameters *) mycast();
  if (n == 1) {
    it=1;
    return (s=0.5*(b-a)*((ptr->*func)(a)+(ptr->*func)(b)));
  } else {
    tnm=it;
    del=(b-a)/tnm;
    x=a+0.5*del;
    for (sum=0.0,j=1;j<=it;j++,x+=del) sum += (ptr->*func)(x);
    it *= 2;
    s=0.5*(s+(b-a)*sum/tnm);
    return s;
  }
}


dvariable function_minimizer::trapzd(dvariable (model_parameters::*func)(const dvariable&),double a,BOR_CONST dvariable& b,int n)
{
  double tnm;
  dvariable sum,del,x;
  static dvariable s;
  
  static int it;
  int j;

  model_parameters * ptr= (model_parameters *) mycast();
  if (n == 1) {
    it=1;
    return (s=0.5*(b-a)*((ptr->*func)(a)+(ptr->*func)(b)));
  } else {
    tnm=it;
    del=(b-a)/tnm;
    x=a+0.5*del;
    for (sum=0.0,j=1;j<=it;j++,x+=del) sum += (ptr->*func)(x);
    it *= 2;
    s=0.5*(s+(b-a)*sum/tnm);
    return s;
  }
}

dvariable function_minimizer::trapzd(dvariable (model_parameters::*func)(const dvariable&),BOR_CONST dvariable& a,BOR_CONST dvariable& b,int n)
{
  double tnm;
  dvariable sum,del,x;
  static dvariable s;
  static int it;
  int j;

  model_parameters * ptr= (model_parameters *) mycast();
  if (n == 1) {
    it=1;
    return (s=0.5*(b-a)*((ptr->*func)(a)+(ptr->*func)(b)));
  } else {
    tnm=it;
    del=(b-a)/tnm;
    x=a+0.5*del;
    for (sum=0.0,j=1;j<=it;j++,x+=del) sum += (ptr->*func)(x);
    it *= 2;
    s=0.5*(s+(b-a)*sum/tnm);
    return s;
  }
}
#undef EPS
#undef JMAX
#undef JMAXP
#undef K

void polint(BOR_CONST dvector& xa,BOR_CONST dvar_vector& ya,int n,double x,BOR_CONST dvariable& _y,BOR_CONST dvariable& _dy)
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


