/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

//Destructor
dll_data_int::~dll_data_int()
{
  *pi = val;
}
//Destructor
dll_data_number::~dll_data_number()
{
  *pd = val;
}
//Destructor
dll_param_init_number::~dll_param_init_number()
{
  if (pd)
  {
    *pd = value(*this);
  }
}
/// Destructor
dll_param_init_bounded_number::~dll_param_init_bounded_number()
{
  *pd = value(*this);
}
/// Destructor
dll_param_number::~dll_param_number()
{
  *pd = value(*this);
}
/// Destructor
dll_param_vector::~dll_param_vector()
{
  int imin=indexmin();
  int imax=indexmax();
  double* tmp=pd;
  for (int i=imin;i<=imax;i++)
  {
    *tmp++=value((*this)[i]);
  }
}
/// Destructor
dll_param_init_bounded_vector::~dll_param_init_bounded_vector()
{
  int imin=indexmin();
  int imax=indexmax();
  double* tmp = pd;
  for (int i=imin;i<=imax;i++)
  {
    *tmp++=value((*this)[i]);
  }
}
/// Destructor
dll_param_init_vector::~dll_param_init_vector()
{
  int imin=indexmin();
  int imax=indexmax();
  double* tmp=pd;
  for (int i=imin;i<=imax;i++)
  {
    *tmp++=value((*this)[i]);
  }
}
/// Destructor
dll_data_vector::~dll_data_vector()
{
  int imin=indexmin();
  int imax=indexmax();
  double* tmp=pd;
  for (int i=imin;i<=imax;i++)
  {
    *tmp++=(*this)[i];
  }
}
/// Destructor
dll_data_matrix::~dll_data_matrix()
{
  double* tmp=d;
  int rmin=rowmin();
  int rmax=rowmax();
  int cmin=colmin();
  int cmax=colmax();
  if (!AD_gaussflag)
  {
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        *tmp++=(*this)(i,j);
      }
    }
  }
  else
  {
    for (int i=rmin;i<=rmax;i++)
    {
      for (int j=cmin;j<=cmax;j++)
      {
        *tmp++=(*this)(i,j);
      }
    }
  }
}
/// Destructor
dll_param_init_matrix::~dll_param_init_matrix()
{
  double* tmp=d;
  int rmin=rowmin();
  int rmax=rowmax();
  int cmin=colmin();
  int cmax=colmax();
  if (!AD_gaussflag)
  {
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        *tmp++=value((*this)(i,j));
      }
    }
  }
  else
  {
    for (int i=rmin;i<=rmax;i++)
    {
      for (int j=cmin;j<=cmax;j++)
      {
        *tmp++=value((*this)(i,j));
      }
    }
  }
}
/// Destructor
dll_param_matrix::~dll_param_matrix()
{
  double* tmp=pd;
  int rmin=rowmin();
  int rmax=rowmax();
  int cmin=colmin();
  int cmax=colmax();
  if (!AD_gaussflag)
  {
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        *tmp++=value((*this)(i,j));
      }
    }
  }
  else
  {
    for (int i=rmin;i<=rmax;i++)
    {
      for (int j=cmin;j<=cmax;j++)
      {
        *tmp++=value((*this)(i,j));
      }
    }
  }
}
