/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>


double factln(double n);
double gammln(double xx);

double log_comb(double n, double k)
{
  return factln(n)-factln(k)-factln(n-k);
}

double factln(double n)
{
  return gammln(n+1.0);
}

/** Log gamma function.
    \param xx \f$x\f$
    \return \f$\ln\bigr(\Gamma(x)\bigl)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 6

    \deprecated Scheduled for replacement by 2010.
*/
double gammln(double xx)
{
  double x,tmp,ser;
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


  dvector log_comb(_CONST dvector& n,_CONST dvector& r)
  {
    int mmin=n.indexmin();
    int mmax=n.indexmax();
    if (mmin != r.indexmin() || mmax != r.indexmax()) 
    {
      cerr << "Incompatible array bounds in function "
        "dvector log_comb(_CONST dvector& n, _CONST dvector& r)" << endl;
      ad_exit(1);
    } 
    dvector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=log_comb(n(i),r(i));
    }
    return tmp;
  } 

  dvector log_comb(double n,_CONST dvector& r)
  {
    int mmin=r.indexmin();
    int mmax=r.indexmax();
    dvector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=log_comb(n,r(i));
    }
    return tmp;
  } 

dvector gammln(_CONST dvector& v)
{
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  dvector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=gammln(v(i));
  }
  return tmp;
}
dvector factln(_CONST dvector& r)
{
    int mmin=r.indexmin();
    int mmax=r.indexmax();
    dvector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=gammln(r(i)+1.0);
    }
    return tmp;
}
