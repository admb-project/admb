/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

int adkdelta(int i,int j)
{
  return i == j ? 1 : 0;
}

void param_init_number::dev_correction(const dmatrix& H, const int& _ii)
{
  int& ii=(int&) _ii;
  ii++;
}

void param_init_matrix::dev_correction(const dmatrix& H, const int& _ii)
{
  int& ii=(int&) _ii;
  ii+=size_count();
}

void param_init_d3array::dev_correction(const dmatrix& H, const int& _ii)
{
  int& ii=(int&) _ii;
  ii+=size_count();
}

void param_init_vector::dev_correction(const dmatrix& H, const int& _ii)
{
  int& ii=(int&) _ii;
  ii+=size_count();
}

void param_init_bounded_vector::dev_correction(const dmatrix& H, const int& _ii)
{
  int& ii=(int&) _ii;
  ii+=size_count();
}

void param_init_bounded_dev_vector::dev_correction(const dmatrix& _H,
  const int& _ii)
{
  dmatrix& H=(dmatrix&) _H;
  int& ii=(int&) _ii;
  int lmin=ii;
  int n=size();
  int lmax=lmin+n-1;
  dmatrix Htmp(lmin,lmax,lmin,lmax);
  double ninv=1.0/double(n);
  int i,j,k,l;
  for (i=lmin;i<=lmax;i++)
  {
    for (j=lmin;j<=lmax;j++)
    {
      double tmp=0.0;
      for (k=lmin;k<=lmax;k++)
      {
        for (l=lmin;l<=lmax;l++)
        {
          tmp+=(adkdelta(i,k)-ninv)*(adkdelta(j,l)-ninv)*H(k,l);
        }
      }
      Htmp(i,j)=tmp;
    }
  }
  for (i=lmin;i<=lmax;i++)
  {
    for (j=lmin;j<=lmax;j++)
    {
      H(i,j)=Htmp(i,j);
    }
  }
  ii+=n;
}
