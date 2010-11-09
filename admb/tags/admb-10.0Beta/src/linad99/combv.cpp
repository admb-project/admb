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
