/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
#include <df1b2fun.h>

df1b2vector operator + (const df1b2variable& _x,const dvector& _v)
{
  ADUNCONST(dvector,v)
  ADUNCONST(df1b2variable,x)
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=x+v(i);
  return tmp;
}


df1b2vector operator - (const df1b2vector& _v,const df1b2variable& _x)
{
  ADUNCONST(df1b2vector,v)
  ADUNCONST(df1b2variable,x)
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=v(i)-x;
  return tmp;
}

df1b2vector operator - (const df1b2variable& _x,const df1b2vector& _v)
{
  ADUNCONST(df1b2vector,v)
  ADUNCONST(df1b2variable,x)
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=x-v(i);
  return tmp;
}

df1b2vector operator - (const df1b2variable& _x,const dvector& _v)
{
  ADUNCONST(dvector,v)
  ADUNCONST(df1b2variable,x)
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=x-v(i);
  return tmp;
}

df1b2vector operator - (const dvector& _v,const df1b2variable& _x)
{
  ADUNCONST(dvector,v)
  ADUNCONST(df1b2variable,x)
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=v(i)-x;
  return tmp;
}

df1b2vector operator + (const dvector& _v,const df1b2variable& _x)
{
  ADUNCONST(dvector,v)
  ADUNCONST(df1b2variable,x)
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=v(i)+x;
  return tmp;
}


df1b2vector operator * (const dvector& _v,const df1b2variable& _x)
{
  ADUNCONST(dvector,v)
  ADUNCONST(df1b2variable,x)
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=v(i)*x;
  return tmp;
}

