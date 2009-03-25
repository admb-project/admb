/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"

void set_value_inv( CGNU_DOUBLE x,const dvector& _v, const int& _ii)
{
  dvector& v=(dvector&) _v;
  int& ii=(int&) _ii;
  v(ii++)=x;
}

void set_value_inv( CGNU_DOUBLE u,const dvector& _x,const int& _ii, CGNU_DOUBLE fmin,
  CGNU_DOUBLE fmax)
{
  int& ii=(int&) _ii;
  dvector& x=(dvector&) _x;
  x(ii++)=boundpin(u,fmin,fmax);
}

void set_value_inv(_CONST prevariable& u,const dvector& _x,const int& _ii,CGNU_DOUBLE fmin,
  CGNU_DOUBLE fmax)
{
  dvector& x=(dvector&) _x;
  int& ii=(int&) _ii;
  x(ii++)=boundpin(u,fmin,fmax);
}

void set_value_inv(_CONST dvector& x,const dvector& _v, const int& _ii)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    v(ii++)=x(i);
  }
}

void set_value_inv(const dvector& x,const dvector& _v, const int& _ii,double s)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    v(ii++)=x(i)*s;
  }
}

void set_value_inv(_CONST dvector& x,const dvector& _v, const int& _ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    v(ii++)=boundpin(x(i),fmin,fmax);
  }
}

void set_value_inv(_CONST dvar_vector& x,const dvector& _v, const int& _ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    v(ii++)=boundpin(x(i),fmin,fmax);
  }
}

void set_value_inv(_CONST dmatrix& x,const dvector& v, const int& ii)
{
  int min=x.rowmin();
  int max=x.rowmax();
  if (allocated(x))
  {
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii);
    }
  }
}

void set_value_inv(_CONST dmatrix& x,const dvector& v, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  int min=x.rowmin();
  int max=x.rowmax();
  if (allocated(x))
  {
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii,fmin,fmax);
    }
  }
}

void set_value_inv(_CONST d3_array& x,const dvector& v, const int& ii)
{
  int min=x.slicemin();
  int max=x.slicemax();
  if (allocated(x))
  {
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii);
    }
  }
}

void set_value_inv(_CONST d3_array& x,const dvector& v, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  int min=x.slicemin();
  int max=x.slicemax();
  if (allocated(x))
  {
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii,fmin,fmax);
    }
  }
}

void set_value_inv_partial(_CONST dvector& x,const dvector& _v, const int& _ii, int n)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=min+n-1;
  #ifdef SAFE_ARRAYS
    if (max >x.indexmax())
    {
      cerr << "index out of range in set_value_patial(_CONST dvar_vector&, ... "
	   << endl;
    }
  #endif
  for (int i=min;i<=max;i++)
  {
    v(ii++)=x(i);
  }
}

void set_value_inv_partial(_CONST dvector& x,const dvector& _v, const int& _ii, int n,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=min+n-1;
  #ifdef SAFE_ARRAYS
    if (max >x.indexmax())
    {
      cerr << "index out of range in set_value_patial(_CONST dvar_vector&, ... "
	   << endl;
    }
  #endif
  for (int i=min;i<=max;i++)
  {
    v(ii++)=boundpin(x(i),fmin,fmax);
  }
}

void set_value_inv_partial(_CONST dvar_matrix& x,const dvector& _v, 
  const int& _ii, int n)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    set_value_inv_partial(x(i),_v,_ii,n); 
  }
}

void set_value_inv_partial(_CONST dvar_vector& x,const dvector& _v, 
  const int& _ii, int n)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=min+n-1;
  #ifdef SAFE_ARRAYS
    if (max >x.indexmax())
    {
      cerr << "index out of range in set_value_patial(_CONST dvar_vector&, ... "
	   << endl;
    }
  #endif
  for (int i=min;i<=max;i++)
  {
    v(ii++)=value(x(i));
  }
}

void set_value_inv_partial(_CONST dvar_vector& x,const dvector& _v, const int& _ii, int n,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  int& ii=(int&) _ii;
  int min=x.indexmin();
  int max=min+n-1;
  dvector& v=(dvector&) _v;
  #ifdef SAFE_ARRAYS
    if (max >x.indexmax())
    {
      cerr << "index out of range in set_value_patial(_CONST dvar_vector&, ... "
	   << endl;
    }
  #endif
  for (int i=min;i<=max;i++)
  {
    v(ii++)=boundpin(x(i),fmin,fmax);
  }
}

void set_value_inv(_CONST prevariable& x,const dvector& _v, const int& _ii)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  v(ii++)=value(x);
}

void set_value_inv(_CONST dvariable& u,const dvector& _x,const int& _ii,CGNU_DOUBLE fmin,
  CGNU_DOUBLE fmax)
{
  int& ii=(int&) _ii;
  dvector& x=(dvector&) _x;
  x(ii++)=boundpin(value(u),fmin,fmax);
}

void set_value_inv(_CONST dvar_vector& x,const dvector& _v,const int& _ii)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      v(ii++)=value(x(i));
    }
  }
}

void set_value_inv(const dvar_vector& x,const dvector& _v,const int& _ii,
  double fmin,double fmax,double s)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    v(ii++)=boundpin(x(i),fmin,fmax)*s;
  }
}

void set_value_inv(const dvar_vector& x,const dvector& _v,const int& _ii,
  double fmin,double fmax,double s,const ivector& flags)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    if (flags(i))
    {
      v(ii++)=boundpin(x(i),fmin,fmax)*s;
    }
  }
}

void set_value_inv(const dvar_vector& x,const dvector& _v,const int& _ii,double s)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      v(ii++)=value(x(i))*s;
    }
  }
}

void set_value_inv(_CONST dvar_matrix& x,const dvector& v, const int& ii)
{
  if (!(!(x)))
  {
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii);
    }
  }
}

void set_value_inv(const dvar_matrix& x,const dvector& v, const int& ii,
  double s)
{
  if (!(!(x)))
  {
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii,s);
    }
  }
}

void set_value_inv(_CONST dvar_matrix& x,const dvector& v, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  if (allocated(x))
  {
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii,fmin,fmax);
    }
  }
}

void set_value_inv(const dvar_matrix& x,const dvector& v, const int& ii,
  double fmin,double fmax,double s)
{
  if (allocated(x))
  {
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii,fmin,fmax,s);
    }
  }
}

void set_value_inv(_CONST dvar3_array& x,const dvector& v, const int& ii)
{
  if (!(!(x)))
  {
    int min=x.slicemin();
    int max=x.slicemax();
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii);
    }
  }
}

void set_value_inv(_CONST dvar3_array& x,const dvector& v, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax)
{
  if (!(!(x)))
  {
    int min=x.slicemin();
    int max=x.slicemax();
    for (int i=min;i<=max;i++)
    {
      if (allocated(x(i)))
        set_value_inv(x(i),v,ii,fmin,fmax);
    }
  }
}

