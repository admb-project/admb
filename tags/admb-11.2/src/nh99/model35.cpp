/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

dll_data_3array::~dll_data_3array()
{
  if (d && allocated(*this))
  {
    double * tmp=d;
    int rmin=rowmin();
    int rmax=rowmax();
    int cmin=colmin();
    int cmax=colmax();
    int hmin=indexmin();
    int hmax=indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int k=hmin;k<=hmax;k++)
        {
          *tmp++=(*this)(k,i,j);
        }
      }
    }
  }
}

dll_param_d3array::~dll_param_d3array()
{
  if (d && allocated(*this))
  {
    double * tmp=d;
    int rmin=rowmin();
    int rmax=rowmax();
    int cmin=colmin();
    int cmax=colmax();
    int hmin=indexmin();
    int hmax=indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int k=hmin;k<=hmax;k++)
        {
          *tmp++=::value((*this)(k,i,j));
        }
      }
    }
  }
}

void dll_param_d3array::allocate(double * _d,int hmin,int hmax,
  int rmin,int rmax, int cmin,int cmax,const char * _s)
{
  d=_d;
  named_dvar3_array::allocate(hmin,hmax,rmin,rmax,cmin,cmax,_s);
  double * tmp=_d;
  if (d && allocated(*this))
  {
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int k=hmin;k<=hmax;k++)
        {
          (*this)(k,i,j)=*tmp++;
        }
      }
    }
  }
}


void dll_data_3array::allocate(double * _d,int hmin,int hmax,
  int rmin,int rmax, int cmin,int cmax,const char * _s)
{
  d=_d;
  named_d3_array::allocate(hmin,hmax,rmin,rmax,cmin,cmax,_s);
  if (d && allocated(*this))
  {
    double * tmp=_d;
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int k=hmin;k<=hmax;k++)
        {
          (*this)(k,i,j)=*tmp++;
        }
      }
    }
  }
}


dll_param_init_d3array::~dll_param_init_d3array()
{
  double * tmp=d;
  if (d && allocated(*this))
  {
    int hmin=indexmin();
    int hmax=indexmax();
    int rmin=rowmin();
    int rmax=rowmax();
    int cmin=colmin();
    int cmax=colmax();
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int k=hmin;k<=hmax;k++)
        {
          *tmp++=::value((*this)(k,i,j));
        }
      }
    }
  }
}


void dll_param_init_d3array::allocate(double* _d,int hmin,int hmax,
  int rmin,int rmax,int cmin,int cmax,int _phase_start,const char *_s )
{
  d=_d;
  named_dvar3_array::allocate(hmin,hmax,rmin,rmax,cmin,cmax,_s);
  initial_params::allocate(_phase_start);
  if (d && allocated(*this))
  {
    double * tmp=_d;
    for (int j=cmin;j<=cmax;j++)
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int k=hmin;k<=hmax;k++)
        {
          (*this)(k,i,j)=*tmp++;
        }
      }
    }
  }
}

void dll_param_init_d3array::allocate(double* _d,int hmin,int hmax,
  int rmin,int rmax,int cmin,int cmax,const char *_s )
{
  dll_param_init_d3array::allocate(_d,hmin,hmax,rmin,rmax,
    cmin,cmax,1,_s);
}

dll_data_3array& dll_data_3array::operator=(const d3_array &m)
{
  d3_array::operator = (m);
  return *this;
}

dll_param_d3array& dll_param_d3array::operator=(const dvar3_array &m)
{
  dvar3_array::operator = (m);
  return *this;
}

dll_param_d3array& dll_param_d3array::operator=(const d3_array &m)
{
  dvar3_array::operator = (m);
  return *this;
}

dll_param_init_d3array& dll_param_init_d3array::operator=(const dvar3_array &m)
{
  dvar3_array::operator = (m);
  return *this;
}


dll_param_init_d3array& dll_param_init_d3array::operator=(const d3_array &m)
{
  dvar3_array::operator = (m);
  return *this;
}
