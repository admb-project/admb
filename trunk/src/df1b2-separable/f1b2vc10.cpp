/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const df1b2vector& _v,double x)
{
  ADUNCONST(df1b2vector,v);
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=pow(v(i),x);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const  df1b2vector& _x,const df1b2vector& _v)
{
  ADUNCONST(df1b2vector,x);
  ADUNCONST(df1b2vector,v);
  //check_shape(x,M,"operator *");
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=pow(x(i),v(i));
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const df1b2vector& _v,const df1b2variable & _x)
{
  ADUNCONST(df1b2vector,v);
  ADUNCONST(df1b2variable,x);
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v(i),x);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const df1b2variable & _v,const df1b2vector& _x)
{
  ADUNCONST(df1b2variable,v);
  ADUNCONST(df1b2vector,x);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v,x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const double v,const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v,x(i));
  }
  return tmp;
}
