/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

dvariable ghk(const dvar_vector& lower,const dvar_vector& upper,
  const dvar_matrix& Sigma, const dmatrix& eps)
{
  RETURN_ARRAYS_INCREMENT();	
  int n=lower.indexmax();
  int m=eps.indexmax();
  dvariable ssum=0.0;
  dvar_matrix ch=choleski_decomp(Sigma);
  dvar_vector l(1,n);
  dvar_vector u(1,n);
  
  for (int k=1;k<=m;k++)
  {
    dvariable weight=1.0;
    l=lower;
    u=upper;
    for (int j=1;j<=n;j++)
    {
      l(j)/=ch(j,j);
      u(j)/=ch(j,j);
      dvariable Phiu=cumd_norm(u(j));
      dvariable Phil=cumd_norm(l(j));
      weight*=Phiu-Phil;
      dvariable eta=inv_cumd_norm((Phiu-Phil)*eps(k,j)+Phil+1.e-30);
      for (int i=j+1;i<=n;i++)
      {
        dvariable tmp=ch(i,j)*eta;
        l(i)-=tmp;
        u(i)-=tmp;
      }
    }
    ssum+=weight;
  }
  RETURN_ARRAYS_DECREMENT();	
  return ssum/m;  
} 

dvariable ghk_m(const dvar_vector& upper,const dvar_matrix& Sigma, const dmatrix& eps)
{
  RETURN_ARRAYS_INCREMENT();	
  int n=upper.indexmax();
  int m=eps.indexmax();
  dvariable ssum=0.0;
  dvar_vector u(1,n);
  dvar_matrix ch=choleski_decomp(Sigma);
  
  for (int k=1;k<=m;k++)
  {
    dvariable weight=1.0;
    u=upper;
    for (int j=1;j<=n;j++)
    {
      u(j)/=ch(j,j);
      dvariable Phiu=cumd_norm(u(j));
      weight*=Phiu;
      dvariable eta=inv_cumd_norm(1.e-30+Phiu*eps(k,j));
      for (int i=j+1;i<=n;i++)
      {
        dvariable tmp=ch(i,j)*eta;
        u(i)-=tmp;
      }
    }
    ssum+=weight;
  }
  RETURN_ARRAYS_DECREMENT();	
  return ssum/m;  
} 

dvariable ghk_choleski(const dvar_vector& lower,const dvar_vector& upper,
  const dvar_matrix& ch, const dmatrix& eps)
{
  RETURN_ARRAYS_INCREMENT();	
  int n=lower.indexmax();
  int m=eps.indexmax();
  dvariable ssum=0.0;
  dvar_vector l(1,n);
  dvar_vector u(1,n);
  
  for (int k=1;k<=m;k++)
  {
    dvariable weight=1.0;
    l=lower;
    u=upper;
    for (int j=1;j<=n;j++)
    {
      l(j)/=ch(j,j);
      u(j)/=ch(j,j);
      dvariable Phiu=cumd_norm(u(j));
      dvariable Phil=cumd_norm(l(j));
      weight*=Phiu-Phil;
      dvariable eta=inv_cumd_norm((Phiu-Phil)*eps(k,j)+Phil);
      for (int i=j+1;i<=n;i++)
      {
        dvariable tmp=ch(i,j)*eta;
        l(i)-=tmp;
        u(i)-=tmp;
      }
    }
    ssum+=weight;
  }
  RETURN_ARRAYS_DECREMENT();	
  return ssum/m;  
} 

dvariable ghk_choleski_m(const dvar_vector& upper,
  const dvar_matrix& ch, const dmatrix& eps)
{
  RETURN_ARRAYS_INCREMENT();	
  int n=upper.indexmax();
  int m=eps.indexmax();
  dvariable ssum=0.0;
  dvar_vector u(1,n);
  
  for (int k=1;k<=m;k++)
  {
    dvariable weight=1.0;
    u=upper;
    for (int j=1;j<=n;j++)
    {
      u(j)/=ch(j,j);
      dvariable Phiu=cumd_norm(u(j));
      weight*=Phiu;
      dvariable eta=inv_cumd_norm(1.e-30+Phiu*eps(k,j));
      for (int i=j+1;i<=n;i++)
      {
        dvariable tmp=ch(i,j)*eta;
        u(i)-=tmp;
      }
    }
    ssum+=weight;
  }
  RETURN_ARRAYS_DECREMENT();	
  return ssum/m;  
} 

void ghk_test(const dmatrix& eps,int i);

dvariable ghk(const dvar_vector& lower,const dvar_vector& upper,
  const dvar_matrix& Sigma, const dmatrix& eps,int i)
{
  RETURN_ARRAYS_INCREMENT();	
  int n=lower.indexmax();
  dvar_matrix ch=choleski_decomp(Sigma);
  dvar_vector l(1,n);
  dvar_vector u(1,n);
  
  ghk_test(eps,i);

  dvariable weight=1.0;
  int k=i;
  {
    l=lower;
    u=upper;
    for (int j=1;j<=n;j++)
    {
      l(j)/=ch(j,j);
      u(j)/=ch(j,j);
      dvariable Phiu=cumd_norm(u(j));
      dvariable Phil=cumd_norm(l(j));
      weight*=Phiu-Phil;
      dvariable eta=inv_cumd_norm((Phiu-Phil)*eps(k,j)+Phil+1.e-30);
      for (int i=j+1;i<=n;i++)
      {
        dvariable tmp=ch(i,j)*eta;
        l(i)-=tmp;
        u(i)-=tmp;
      }
    }
  }
  RETURN_ARRAYS_DECREMENT();	
  return weight;  
} 
dvariable ghk_choleski_m_cauchy(const dvar_vector& upper,
  const dvar_matrix& ch, const dmatrix& eps)
{
  RETURN_ARRAYS_INCREMENT();	
  int n=upper.indexmax();
  int m=eps.indexmax();
  dvariable ssum=0.0;
  dvar_vector u(1,n);
  
  for (int k=1;k<=m;k++)
  {
    dvariable weight=1.0;
    u=upper;
    for (int j=1;j<=n;j++)
    {
      u(j)/=ch(j,j);
      dvariable Phiu=cumd_cauchy(u(j));
      weight*=Phiu;
      dvariable eta=inv_cumd_cauchy(Phiu*eps(k,j));
      for (int i=j+1;i<=n;i++)
      {
        dvariable tmp=ch(i,j)*eta;
        u(i)-=tmp;
      }
    }
    ssum+=weight;
  }
  RETURN_ARRAYS_DECREMENT();	
  return ssum/m;  
} 

dvariable ghk_choleski_m_logistic(const dvar_vector& upper,
  const dvar_matrix& ch, const dmatrix& eps)
{
  RETURN_ARRAYS_INCREMENT();	
  int n=upper.indexmax();
  int m=eps.indexmax();
  dvariable ssum=0.0;
  dvar_vector u(1,n);
  
  for (int k=1;k<=m;k++)
  {
    dvariable weight=1.0;
    u=upper;
    for (int j=1;j<=n;j++)
    {
      u(j)/=ch(j,j);
      dvariable Phiu=cumd_logistic(u(j));
      weight*=Phiu;
      dvariable eta=inv_cumd_logistic(Phiu*eps(k,j));
      for (int i=j+1;i<=n;i++)
      {
        dvariable tmp=ch(i,j)*eta;
        u(i)-=tmp;
      }
    }
    ssum+=weight;
  }
  RETURN_ARRAYS_DECREMENT();	
  return ssum/m;  
} 

