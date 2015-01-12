/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>
df1b2matrix operator + (const df1b2matrix& _M,const df1b2variable& _x)
{
  ADUNCONST(df1b2matrix,M)
  ADUNCONST(df1b2variable,x)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)+x;
  }
  return tmp;
}

df1b2matrix& df1b2matrix::operator /= (const double x)
{
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++) 
  {
    (*this)(i)/=x;
  }
  return (*this);
}

df1b2matrix& df1b2matrix::operator *= (const double x)
{
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++) 
  {
    (*this)(i)*=x;
  }
  return (*this);
}

df1b2matrix& df1b2matrix::operator /= (const df1b2variable& _x)
{
  ADUNCONST(df1b2variable,x)
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++) 
  {
    (*this)(i)/=x;
  }
  return (*this);
}

df1b2matrix& df1b2matrix::operator *= (const df1b2variable& _x)
{
  ADUNCONST(df1b2variable,x)
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++) 
  {
    (*this)(i)*=x;
  }
  return (*this);
}

df1b2matrix& df1b2matrix::operator += (const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  if (rmin != M.indexmin() || rmax != M.indexmax())
  {
    cerr << "Unequal shapes in" 
      " df1b2matrix& df1b2matrix::operator += (const df1b2matrix& _M)"
      << endl;
    ad_exit(1);
  }
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=(*this)(i).indexmin();
    int cmax=(*this)(i).indexmax();
    for (int j=cmin;j<=cmax;j++) 
      (*this)(i,j)+=M(i,j);
  }
  return (*this);
}


df1b2matrix& df1b2matrix::operator -= (const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  if (rmin != M.indexmin() || rmax != M.indexmax())
  {
    cerr << "Unequal shapes in"
      " df1b2matrix& df1b2matrix::operator -= (const df1b2matrix& _M)"
      << endl;
    ad_exit(1);
  }
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=(*this)(i).indexmin();
    int cmax=(*this)(i).indexmax();
    for (int j=cmin;j<=cmax;j++) 
      (*this)(i,j)-=M(i,j);
  }
  return (*this);
}

df1b2matrix operator + (const df1b2matrix& _M,const double x)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)+x;
  }
  return tmp;
}
df1b2matrix operator + (const df1b2variable& _x,const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  ADUNCONST(df1b2variable,x)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)+x;
  }
  return tmp;
}

df1b2matrix operator + (const double x,const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)+x;
  }
  return tmp;
}

df1b2matrix operator * (const df1b2variable& _x,const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  ADUNCONST(df1b2variable,x)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)*x;
  }
  return tmp;
}

df1b2matrix operator * (const df1b2variable& _x,const dmatrix& _M)
{
  ADUNCONST(dmatrix,M)
  ADUNCONST(df1b2variable,x)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)*x;
  }
  return tmp;
}

df1b2matrix operator * (const df1b2matrix& _M,const df1b2variable& _x)
{
  ADUNCONST(df1b2matrix,M)
  ADUNCONST(df1b2variable,x)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)*x;
  }
  return tmp;
}

df1b2matrix operator * (const dmatrix& _M,const df1b2variable& _x)
{
  ADUNCONST(dmatrix,M)
  ADUNCONST(df1b2variable,x)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)*x;
  }
  return tmp;
}
df1b2matrix operator * (const df1b2matrix& _M,const double x)
{
  return x*_M;
}

df1b2matrix operator * (const double x,const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=M(i,j)*x;
  }
  return tmp;
}


df1b2matrix operator - (const df1b2variable& _x,const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  ADUNCONST(df1b2variable,x)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=x-M(i,j);
  }
  return tmp;
}

df1b2matrix operator - (const double x,const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=x-M(i,j);
  }
  return tmp;
}

df1b2matrix operator +(const df1b2matrix& _MM,const df1b2matrix& _NN)
{
  df1b2matrix& M = (df1b2matrix&)_MM;
  df1b2matrix& N = (df1b2matrix&)_NN;
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin(); 
    int cmax=M(i).indexmax(); 
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=M(i,j)+N(i,j);
    }
  }
  return tmp;
}
df1b2matrix operator +(const df1b2matrix& _M,const dmatrix& N)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin(); 
    int cmax=M(i).indexmax(); 
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=M(i,j)+N(i,j);
    }
  }
  return tmp;
}
df1b2matrix operator +(const dmatrix& M,const df1b2matrix& _NN)
{
  df1b2matrix& N = (df1b2matrix&)_NN;
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin(); 
    int cmax=M(i).indexmax(); 
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=M(i,j)+N(i,j);
    }
  }
  return tmp;
}
df1b2matrix operator -(const df1b2matrix& _MM,const df1b2matrix& _NN)
{
  df1b2matrix& M = (df1b2matrix&)_MM;
  df1b2matrix& N = (df1b2matrix&)_NN;
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin(); 
    int cmax=M(i).indexmax(); 
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=M(i,j)-N(i,j);
    }
  }
  return tmp;
}
df1b2matrix operator -(const df1b2matrix& _M,const dmatrix& N)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin(); 
    int cmax=M(i).indexmax(); 
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=M(i,j)-N(i,j);
    }
  }
  return tmp;
}
df1b2matrix operator -(const dmatrix& M,const df1b2matrix& _NN)
{
  df1b2matrix& N = (df1b2matrix&)_NN;
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin(); 
    int cmax=M(i).indexmax(); 
    tmp(i).allocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=M(i,j)-N(i,j);
    }
  }
  return tmp;
}
