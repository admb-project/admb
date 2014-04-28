/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>
#include "fvar.hpp"
#define USE_BARD_PEN

/**
 * Description not yet available.
 * \param
 */
void set_value(const prevariable& _x, const dvar_vector& v, const int& _ii)
{
  int& ii = (int&) _ii;
  prevariable& x= (prevariable&)( _x);
  x=v(ii++);
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const prevariable& _x,const dvar_vector& v, const int& _ii,
  double s)
{
  prevariable& x= (prevariable&)( _x);
  int& ii=(int&)(_ii);
  x=v(ii++)/s;
}

/**
 * Description not yet available.
 * \param
 */
void set_value_inv(const prevariable& x,const dvector& _v,const int& _ii,
  double s)
{
  dvector& v=(dvector&)(_v);
  int& ii=(int&)(_ii);
  v(ii++)=s*value(x);
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const prevariable& _x,const dvar_vector& v,const int& _ii,
  double fmin, double fmax,const dvariable& _fpen,double s)
{
  int& ii=(int&)_ii;
  prevariable& x=(prevariable&) _x;
  dvariable& fpen=(dvariable&) _fpen;
  x=boundp(v(ii++),fmin,fmax,fpen,s);
}

/**
 * Description not yet available.
 * \param
 */
void set_value_inv(const prevariable& x,const dvector& _v,const int& _ii,
  double fmin, double fmax,double s)
{
  dvector& v=(dvector&)(_v);
  int& ii=(int&)(_ii);
  v(ii++)=boundpin(x,fmin,fmax,s);
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const prevariable& _u, const dvar_vector& x, const int& _ii,
  const double fmin, const double fmax,const dvariable& _fpen)
{
  int& ii = (int&) _ii;
  prevariable& u= (prevariable&) _u;
  dvariable& fpen= (dvariable&) _fpen;
  if (!initial_params::straight_through_flag)
  {
    u=boundp(x(ii++),fmin,fmax,fpen);
  }
  else
  {
    u=x(ii);
    value(u)=boundp(value(x(ii++)),fmin,fmax);
    double diff=fmax-fmin;
    //t=fmin + diff*ss;
    dvariable ss=(u-fmin)/diff;
#   ifdef USE_BARD_PEN
      const double l4=log(4.0);
      double pen=.000001/diff;
      fpen-=pen*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4);
#   else
          XXXX
#   endif
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_vector& x, const dvar_vector& v, const int& _ii)
{
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      ((dvar_vector&)x)(i)=v(ii++);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_vector& _x,const dvar_vector& v, const int& _ii,
  double s)
{
  dvar_vector& x=(dvar_vector&) _x;
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      x(i)=v(ii++)/s;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_vector& x, const dvar_vector& v, const int& _ii,
  double fmin,double fmax,const dvariable& fpen)
{
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      ((dvar_vector&)(x))(i)=boundp(v(ii++),fmin,fmax,fpen);
    }
  }
}
//dvariable boundp(const prevariable &,double fmin,double fmax,
//  const dvariable& fpen);

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_vector& _x,const dvar_vector& v,const int& _ii,
  double fmin,double fmax,const dvariable& fpen,double s)
{
  dvar_vector& x=(dvar_vector&)(_x);
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      ((dvar_vector&)(x))(i)=boundp(v(ii++)/s,fmin,fmax,fpen);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_vector& _x,const dvar_vector& v,const int& _ii,
  double fmin,double fmax,const dvariable& fpen,double s,const ivector& flags,
  double off_value)
{
  dvar_vector& x=(dvar_vector&)(_x);
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      if (flags(i))
      {
        x(i)=boundp(v(ii++)/s,fmin,fmax,fpen);
      }
      else
      {
        x(i)=off_value;
      }
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_matrix& x, const dvar_vector& v, const int& _ii)
{
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      set_value(x(i),v,ii);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_matrix& x,const dvar_vector& v,const int& _ii,
  double s)
{
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      set_value(x(i),v,ii,s);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_matrix& x, const dvar_vector& v, const int& ii,
  const double fmin, const double fmax,const dvariable& fpen)
{
  if (!(!(x)))
  {
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      set_value(x(i),v,ii,fmin,fmax,fpen);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const dvar_matrix& x,const dvar_vector& v, const int& ii,
  double fmin,double fmax,const dvariable& fpen,double s)
{
  if (!(!(x)))
  {
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      set_value(x(i),v,ii,fmin,fmax,fpen,s);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(dvar3_array& x, const dvar_vector& v, const int& ii,
  const double fmin, const double fmax,const dvariable& fpen)
{
  if (!(!(x)))
  {
    int min=x.slicemin();
    int max=x.slicemax();
    for (int i=min;i<=max;i++)
    {
      set_value(x(i),v,ii,fmin,fmax,fpen);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value_partial(const dvar_matrix& x, const dvar_vector& v,
  const int& _ii, int n)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    set_value_partial(x(i),v,_ii,n);
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value_partial(const dvar_vector& x, const dvar_vector& v,
  const int& _ii, int n)
{
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=min+n-1;
      if (max >x.indexmax())
      {
        cerr <<
          "index out of range in set_value_patial(const dvar_vector&, ... "
          << endl;
      }
    for (int i=min;i<=max;i++)
    {
      ((dvar_vector&)(x))(i)=v(ii++);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value_partial(const dvar_vector& x, const dvar_vector& v,
  const int& _ii, int n, const double fmin, const double fmax,
  const dvariable& fpen)
{
  int& ii = (int&) _ii;
  if (!(!(x)))
  {
    int min=x.indexmin();
    int max=min+n-1;
      if (max >x.indexmax())
      {
        cerr <<
          "index out of range in set_value_patial(const dvar_vector&, ... "
             << endl;
      }
    for (int i=min;i<=max;i++)
    {
      ((dvar_vector&)(x))(i)=boundp(v(ii++),fmin,fmax,fpen);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(dvar3_array& x, const dvar_vector& v, const int& ii)
{
  if (!(!(x)))
  {
    int min=x.slicemin();
    int max=x.slicemax();
    for (int i=min;i<=max;i++)
    {
      set_value(x(i),v,ii);
    }
  }
}
