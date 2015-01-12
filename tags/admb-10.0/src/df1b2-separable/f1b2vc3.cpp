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
df1b2matrix outer_prod(const df1b2vector& _MM,const df1b2vector& _NN)
{
  df1b2vector& M = (df1b2vector&)_MM;
  df1b2vector& N = (df1b2vector&)_NN;
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  int cmin=N.indexmin(); 
  int cmax=N.indexmax(); 
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    tmp(i).noallocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=M(i)*N(j);
    }
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector mfexp(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=mfexp(x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator * (const df1b2variable& _v,const dvector& _x)
{
  ADUNCONST(df1b2variable,v)
  ADUNCONST(dvector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v*x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator * (const df1b2vector& _x,const df1b2variable& _v)
{
  ADUNCONST(df1b2variable,v)
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v*x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator * (const df1b2variable& _v,const df1b2vector& _x)
{
  ADUNCONST(df1b2variable,v)
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v*x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator + (const df1b2vector& _x,const df1b2variable& _v)
{
  ADUNCONST(df1b2variable,v)
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v+x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator + (const df1b2variable& _v,const df1b2vector& _x)
{
  ADUNCONST(df1b2variable,v)
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v+x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator + (double v,const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v+x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator + (const df1b2vector& _x,const double v)
{
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v+x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator - (const df1b2vector& _x,const double& v)
{
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v-x(i);
  }
  return tmp;
}

/*
df1b2variable operator * (const df1b2vector& _v,const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,v)
  ADUNCONST(df1b2vector,x)
  df1b2variable tmp=0.0;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    tmp+=v(i)*x(i);
  }
  return tmp;
}
*/

/**
 * Description not yet available.
 * \param
 */
df1b2variable operator * (const dvector& _v,const df1b2vector& _x)
{
  ADUNCONST(dvector,v)
  ADUNCONST(df1b2vector,x)
  df1b2variable tmp=0.0;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    tmp+=v(i)*x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable operator * (const df1b2vector& _v,const dvector& _x)
{
  ADUNCONST(dvector,x)
  ADUNCONST(df1b2vector,v)
  df1b2variable tmp=0.0;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    tmp+=v(i)*x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
int size_count(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  return x.indexmax()-x.indexmin()+1;
}

/**
 * Description not yet available.
 * \param
 */
int size_count(const df1b2matrix& _x)
{
  ADUNCONST(df1b2matrix,x)
  int tmp=0;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    tmp+=size_count(x(i));
  }
  return tmp;
}
  
/**
 * Description not yet available.
 * \param
 */
void df1b2vector::initialize(void)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    //x(i).initialize();
    (*this)(i)=0.0;
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator * (double v,const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  df1b2vector tmp;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v*x(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector operator * (const df1b2vector& _v,double x)
{
  ADUNCONST(df1b2vector,v)
  df1b2vector tmp;
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=v(i)*x;
  }
  return tmp;
}
