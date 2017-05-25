/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

void dll_data_int::allocate(int *_pi,const char * _s)
{
  model_name_tag::allocate(_s);
  pi=_pi;
  val=*_pi;
}

void dll_data_number::allocate(double *_pd,const char * _s)
{
  model_name_tag::allocate(_s);
  pd=_pd;
  val=*_pd;
}

dll_data_number& dll_data_number::operator=(const double& v)
{
  data_number::operator =(v);
  return *this;
}
dll_param_number& dll_param_number::operator=(const prevariable& m)
{
  dvariable::operator = (m);
  return *this;
}

dll_param_number& dll_param_number::operator=(const double m)
{
  dvariable::operator = (m);
  return *this;
}

/**
Allocate param_init_number and sets pd = _pd.

\param _pd pointer to double
\param _phase_start
\param _s id
*/
void dll_param_init_number::allocate
  (double * _pd,int _phase_start,const char *_s)
{
  named_dvariable::allocate(_s);
  initial_params::allocate(_phase_start);
  pd=_pd;
  value(*this)=*_pd;
}

void dll_param_number::allocate
  (double * _pd,const char *_s)
{
  named_dvariable::allocate(_s);
  pd=_pd;
  value(*this)=*_pd;
}
/**
Allocate param_init_number and sets pd = _pd.
Uses 1 as default phase_start.

\param _pd pointer to double
\param _s id
*/
void dll_param_init_number::allocate(
  double* _pd,
  const char* _s)
{
  allocate(_pd, 1, _s);
}
/**
Assigns val to parameter value.

\param val double
*/
dll_param_init_number& dll_param_init_number::operator=(const double val)
{
  dvariable::operator=(val);
  return *this;
}
/**
Assigns var to parameter value.

\param var prevariable
*/
dll_param_init_number& dll_param_init_number::operator=(const prevariable& var)
{
  dvariable::operator=(var);
  return *this;
}

dll_param_init_vector& dll_param_init_vector::operator = (const dvector& x)
{
  param_init_vector::operator = (x);
  return (*this);
}

dll_param_init_vector& dll_param_init_vector::operator = (const dvar_vector& x)
{
  param_init_vector::operator = (x);
  return (*this);
}

dll_param_init_vector& dll_param_init_vector::operator =
  (const prevariable& x)
{
  param_init_vector::operator = (x);
  return (*this);
}

dll_param_init_vector& dll_param_init_vector::operator = (const double& x)
{
  param_init_vector::operator = (x);
  return (*this);
}

void dll_param_init_vector::allocate(double * _pd,int imin,int imax,
  int _phase_start,const char * _s)
{
  pd=_pd;
  named_dvar_vector::allocate(imin,imax,_s);
  if (pd && allocated(*this))
  {
    initial_params::allocate(_phase_start);
    double * tmp=_pd;
    for (int i=imin;i<=imax;i++)
    {
      (*this)[i]=*tmp++;
    }
  }
}

dll_param_vector& dll_param_vector::operator=(const dvar_vector& m)
{
  dvar_vector::operator = (m);
  return *this;
}

dll_param_vector& dll_param_vector::operator=(const dvector& m)
{
  dvar_vector::operator = (m);
  return *this;
}

dll_param_vector& dll_param_vector::operator=(const double m)
{
  dvar_vector::operator = (m);
  return *this;
}

dll_param_vector& dll_param_vector::operator=(const prevariable& m)
{
  dvar_vector::operator = (m);
  return *this;
}

void dll_param_vector::allocate(double *_pd,int imin,int imax,
  const char * _s)
{
  pd=_pd;
  named_dvar_vector::allocate(imin,imax,_s);
  if (pd && allocated(*this))
  {
    double * tmp=_pd;
    for (int i=imin;i<=imax;i++)
    {
      (*this)[i]=*tmp++;
    }
  }
}
void dll_param_init_vector::allocate(double * _pd,int imin,int imax,
  const char * _s)
{
  allocate(_pd,imin,imax,1,_s);
}

void dll_data_vector::allocate(double * _pd,int imin,int imax,const char * _s)
{
  pd=_pd;
  named_dvector::allocate(imin,imax,_s);
  if (pd && allocated())
  {
    double * tmp=_pd;
    for (int i=imin;i<=imax;i++)
    {
      (*this)[i]=*tmp++;
    }
  }
}
dll_data_vector& dll_data_vector::operator = (const dvector& x)
{
  data_vector::operator = (x);
  return (*this);
}

dll_data_vector& dll_data_vector::operator = (const double& x)
{
  data_vector::operator = (x);
  return (*this);
}

void dll_data_matrix::allocate(double * _d,int rmin,int rmax,
  int cmin,int cmax,const char * _s)
{
  d=_d;
  named_dmatrix::allocate(rmin,rmax,cmin,cmax,_s);
  if (d && allocated(*this))
  {
    double * tmp=_d;
    if (!AD_gaussflag)
    {
      for (int j=cmin;j<=cmax;j++)
      {
        for (int i=rmin;i<=rmax;i++)
        {
          (*this)(i,j)=*tmp++;
        }
      }
    }
    else
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int j=cmin;j<=cmax;j++)
        {
          (*this)(i,j)=*tmp++;
        }
      }
    }
  }
}

/**
Assign values from mat to elements of dll_data_matrix.
\param mat dmatrix
*/
dll_data_matrix& dll_data_matrix::operator=(const dmatrix& mat)
{
  data_matrix::operator=(mat);
  return *this;
}
/**
Assign value to all elements of dll_data_matrix.
\param value double
*/
dll_data_matrix& dll_data_matrix::operator=(const double& value)
{
  data_matrix::operator=(value);
  return *this;
}

void dll_param_init_matrix::allocate(double* _d,int rmin,int rmax,
  int cmin,int cmax,const char *_s )
{
  allocate(_d,rmin,rmax,cmin,cmax,1,_s );
}


void dll_param_init_matrix::allocate(double* _d,int rmin,int rmax,
  int cmin,int cmax,int _phase_start,const char *_s )
{
  d=_d;
  named_dvar_matrix::allocate(rmin,rmax,cmin,cmax,_s);
  initial_params::allocate(_phase_start);
  if (d && allocated(*this))
  {
    double * tmp=_d;
    if (!AD_gaussflag)
    {
      for (int j=cmin;j<=cmax;j++)
      {
        for (int i=rmin;i<=rmax;i++)
        {
          (*this)(i,j)=*tmp++;
        }
      }
    }
    else
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int j=cmin;j<=cmax;j++)
        {
          (*this)(i,j)=*tmp++;
        }
      }
    }
  }
}

void dll_param_matrix::allocate(double* _pd,int rmin,int rmax,
  int cmin,int cmax,const char *_s )
{
  pd=_pd;
  named_dvar_matrix::allocate(rmin,rmax,cmin,cmax,_s);
  if (pd && allocated(*this))
  {
    double * tmp=_pd;
    if (!AD_gaussflag)
    {
      for (int j=cmin;j<=cmax;j++)
      {
        for (int i=rmin;i<=rmax;i++)
        {
          (*this)(i,j)=*tmp++;
        }
      }
    }
    else
    {
      for (int i=rmin;i<=rmax;i++)
      {
        for (int j=cmin;j<=cmax;j++)
        {
          (*this)(i,j)=*tmp++;
        }
      }
    }
  }
}

void dll_param_init_bounded_number::allocate(double *_pd,double _minb,
  double _maxb,const char * _s)
{
  allocate(_pd,_minb,_maxb,1,_s);
}

void dll_param_init_bounded_number::allocate(double *_pd,double _minb,
  double _maxb,int _phase_start,const char * _s)
{
  pd=_pd;
  minb=_minb;
  maxb=_maxb;
  named_dvariable::allocate(_s);
  initial_params::allocate(_phase_start);
  {
    if (!pd)
      prevariable::operator=((minb+maxb)/2.);
    else
    {
      double iv=*pd;
      if ( iv <=minb || iv >= maxb)
      {
        prevariable::operator=((minb+maxb)/2.);
      }
      else
      {
        prevariable::operator=(iv);
      }
    }
  }
}

/**
Allocates dll_param_init_bounded_vector.
\param imin lower index value
\param imax upper index value
\param minb elements lower value bound
\param maxb elements upper value bound
\param phase_start
\param s id name
*/
void dll_param_init_bounded_vector::allocate(double* _pd,
  int imin, int imax, double _minb, double _maxb,
  int _phase_start, const char* s)
{
  pd=_pd;
  minb=_minb;
  maxb=_maxb;
  named_dvar_vector::allocate(imin,imax,s);
  initial_params::allocate(_phase_start);
  if (pd && allocated(*this))
  {
    double * tmp=_pd;
    for (int i=imin;i<=imax;i++)
    {
      double td=*tmp++;
      if (td<minb || td>maxb) td=(minb+maxb)/2.;
      (*this)[i]=td;
    }
  }
}

void dll_param_init_bounded_vector::allocate(double* _pd,int imin,int imax,
  double _minb,double _maxb,const char * s)
{
  allocate(_pd,imin,imax,_minb,_maxb,1,s);
}

dll_param_matrix& dll_param_matrix::operator=(const dvar_matrix& varmat)
{
  param_matrix::operator=(varmat);
  return *this;
}
dll_param_matrix& dll_param_matrix::operator=(const double value)
{
  param_matrix::operator=(value);
  return *this;
}
dll_param_matrix& dll_param_matrix::operator=(const dvariable& var)
{
  param_matrix::operator=(var);
  return *this;
}
dll_param_matrix& dll_param_matrix::operator=(const dmatrix& mat)
{
  param_matrix::operator=(mat);
  return *this;
}
dll_param_init_matrix& dll_param_init_matrix::operator=(const dmatrix& mat)
{
  param_init_matrix::operator=(mat);
  return *this;
}
dll_param_init_matrix& dll_param_init_matrix::operator=(
  const dvar_matrix& varmat)
{
  param_init_matrix::operator=(varmat);
  return *this;
}
dll_param_init_matrix& dll_param_init_matrix::operator=(const dvariable& value)
{
  param_init_matrix::operator=(value);
  return *this;
}
dll_param_init_matrix& dll_param_init_matrix::operator=(const double& value)
{
  param_init_matrix::operator=(value);
  return *this;
}
