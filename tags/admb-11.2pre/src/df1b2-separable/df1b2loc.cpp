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
#include <df1b2fun.h>
#include <df1b2loc.h>

/**
 * Description not yet available.
 * \param
 */
  int operator >= (const double& x,const df1b2variable& y)
  {
    if (x>=value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator >= (double x,const df1b2variable& y)
  {
    if (value(x)>=value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator >= (const df1b2variable& x,double y)
  {
    if (value(x)>=y)
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator > (const double& x,const df1b2variable& y)
  {
    if (x>value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator > (double x,const df1b2variable& y)
  {
    if (value(x)>value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator > (const df1b2variable& x,double y)
  {
    if (value(x)>y)
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator <= (const double& x,const df1b2variable& y)
  {
    if (x<=value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator <= (double x,const df1b2variable& y)
  {
    if (value(x)<=value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator <= (const df1b2variable& x,double y)
  {
    if (value(x)<=y)
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator < (const double& x,const df1b2variable& y)
  {
    if (x<value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator < (double x,const df1b2variable& y)
  {
    if (value(x)<value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator < (const df1b2variable& x,double y)
  {
    if (value(x)<y)
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator == (const double& x,const df1b2variable& y)
  {
    if (x==value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator == (double x,const df1b2variable& y)
  {
    if (value(x)==value(y))
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
  int operator == (const df1b2variable& x,double y)
  {
    if (value(x)==y)
      return 1;
    else
      return 0;
  }

/**
 * Description not yet available.
 * \param
 */
df1b2vector posfun(const df1b2vector& x,double eps,
  const df1b2variable& _pen)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=posfun(x(i),eps,_pen);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable posfun(const df1b2variable&x,const double eps,
  const df1b2variable& _pen)
{
  df1b2variable& pen= (df1b2variable&) _pen;
  if (x>=eps)
  {
    return x;
  }
  else
  {
    pen+=.01*square(x-eps);
    return eps/(2-x/eps);
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable dfposfun(const df1b2variable&x,const double eps)
{
  if (x>=eps)
  {
    return 1;
  }
  else
  {
    //double z=eps/(2-x/eps);
    df1b2variable dfx=1.0/square(2-x/eps);
    return dfx;
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable posfun(const df1b2variable&x,const double eps)
{
  if (x>=eps)
  {
    return x;
  }
  else
  {
    return eps/(2-x/eps);
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable posfun2(const df1b2variable&x,const double eps,
  const df1b2variable& _pen)
{
  df1b2variable& pen= (df1b2variable&) _pen;
  if (x>=eps)
  {
    return x;
  }
  else
  {
    df1b2variable y=eps-x;
    df1b2variable  tmp=y/eps;
    df1b2variable  tmp2=tmp*tmp;
    df1b2variable  tmp3=tmp2*tmp;
    pen+=.01*tmp3;
    return eps/(1.0+tmp+tmp2+tmp3);
  }
}
