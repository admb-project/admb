/*
 * $Id$
 * Author: Unknown
 */
#include <fvar.hpp>

dvariable gammln(_CONST dvariable& xx);
dvariable factln(_CONST dvariable& n);
double factln(double n);

dvariable log_comb(_CONST dvariable& n,double k)
{
  return factln(n)-factln(k)-factln(n-k);
}

dvariable log_comb(_CONST dvariable& n,_CONST dvariable& k)
{
  return factln(n)-factln(k)-factln(n-k);
}

dvariable log_comb(double n,_CONST dvariable& k)
{
  return factln(n)-factln(k)-factln(n-k);
}

dvariable factln(_CONST dvariable& n)
{
  return gammln(n+1.0);
}


  dvar_vector log_comb(_CONST dvar_vector& n,_CONST dvar_vector& r)
  {
    RETURN_ARRAYS_INCREMENT();
    int mmin=n.indexmin();
    int mmax=n.indexmax();
    if (mmin != r.indexmin() || mmax != r.indexmax()) 
    {
      cerr << "Incompatible array bounds in function "
        "dvar_vector log_comb(BOR_CONST dvar_vector& n, BOR_CONST dvector& r)" << endl;
      ad_exit(1);
    } 
    dvar_vector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=log_comb(n(i),r(i));
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
  } 

  dvar_vector log_comb(_CONST dvector& n,_CONST dvar_vector& r)
  {
    RETURN_ARRAYS_INCREMENT();
    int mmin=n.indexmin();
    int mmax=n.indexmax();
    if (mmin != r.indexmin() || mmax != r.indexmax()) 
    {
      cerr << "Incompatible array bounds in function "
        "dvar_vector log_comb(BOR_CONST dvar_vector& n, BOR_CONST dvector& r)" << endl;
      ad_exit(1);
    } 
    dvar_vector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=log_comb(n(i),r(i));
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
  } 



  dvar_vector log_comb(_CONST dvar_vector& n,_CONST dvector& r)
  {
    RETURN_ARRAYS_INCREMENT();
    int mmin=n.indexmin();
    int mmax=n.indexmax();
    if (mmin != r.indexmin() || mmax != r.indexmax()) 
    {
      cerr << "Incompatible array bounds in function "
        "dvar_vector log_comb(BOR_CONST dvar_vector& n, BOR_CONST dvector& r)" << endl;
      ad_exit(1);
    } 
    dvar_vector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=log_comb(n(i),r(i));
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
  } 

  dvar_vector log_comb(_CONST dvariable& n,_CONST dvector& r)
  {
    RETURN_ARRAYS_INCREMENT();
    int mmin=r.indexmin();
    int mmax=r.indexmax();
    dvar_vector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=log_comb(n,r(i));
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
  } 

  dvar_vector log_comb(_CONST dvariable& n,_CONST dvar_vector& r)
  {
    RETURN_ARRAYS_INCREMENT();
    int mmin=r.indexmin();
    int mmax=r.indexmax();
    dvar_vector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=log_comb(n,r(i));
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
  } 

dvar_vector factln(_CONST dvar_vector& r)
{
    RETURN_ARRAYS_INCREMENT();
    int mmin=r.indexmin();
    int mmax=r.indexmax();
    dvar_vector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=gammln(r(i)+1.0);
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
}

  dvar_vector log_comb(double n,_CONST dvar_vector& r)
  {
    RETURN_ARRAYS_INCREMENT();
    int mmin=r.indexmin();
    int mmax=r.indexmax();
    dvar_vector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=log_comb(n,r(i));
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
  } 


dvar_vector gammln(_CONST dvar_vector& v)
{
  RETURN_ARRAYS_INCREMENT();
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  dvar_vector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=gammln(v(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

  
static dvariable gammlnguts(const prevariable _z)
{
  double  z = value(_z);
  double zdot=1.0;
  const double lpi =1.1447298858494001741434272;
  const double pi =3.1415926535897932384626432;
  const double lpp =0.9189385332046727417803297;
  int n=7;
  const double c[9]={0.99999999999980993, 
    676.5203681218851, 
    -1259.1392167224028,
     771.32342877765313, 
    -176.61502916214059, 
    12.507343278686905,
     -0.13857109526572012, 
    9.9843695780195716e-6, 
    1.5056327351493116e-7};
  z-=1.0;
  double x=c[0];
  double xdot=0.0;
  for (int i=1;i<=n+1;i++)
  {
    double zinv=1.0/(z+i);
    x+=c[i]*zinv;
    //xdot-=c[i]/square(z+i)*zdot;  since zdot=1.0
    xdot-=c[i]*square(zinv);
  }    
  double t=z+n+0.5;
  double tdot=zdot;
  //return lpp + (z+0.5)*log(t) -t + log(x);
  double ans= lpp + (z+0.5)*log(t) -t + log(x);
  //double ansdot=zdot*log(t) + (z+0.5)/t*tdot -tdot +xdot/x;
  // since tdot=1.0
  // since zdot=1.0
  double ansdot=log(t) + (z+0.5)/t -1.0 +xdot/x;
  dvariable u;
  u.v->x=ans;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
    &(u.v->x), &(_z.v->x), ansdot );
  return(u);
}

dvariable gammln(const prevariable& z)
{
  const double lpi =1.1447298858494001741434272;
  const double pi =3.1415926535897932384626432;
  if (z<0.5)
  {
    return lpi - log(sin(pi*z)) - gammlnguts(1.0-z);
  }
  else
  {
    return gammlnguts(z);
  }
}

