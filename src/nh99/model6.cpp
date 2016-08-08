/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

#ifdef ISZERO
  #undef ISZERO
#endif
#define ISZERO(d) ((d)==0.0)

/**
Default constructor
*/
param_init_bounded_matrix::param_init_bounded_matrix():
  param_init_matrix(), minb(0), maxb(0)
{
}

void param_init_bounded_matrix::set_value(const dvar_vector& x,
  const int& ii, const dvariable& pen)
  {
    if (allocated(*this))
    {
      if (ISZERO(scalefactor))
        ::set_value(*this,x,ii,minb,maxb,pen);
      else
        ::set_value(*this,x,ii,minb,maxb,pen,scalefactor);
    }
  }


void param_init_bounded_matrix::set_value_inv(const dvector& x, const int& ii)
  {
    if (allocated(*this))
    {
      if (ISZERO(scalefactor))
        ::set_value_inv(*this,x,ii,minb,maxb);
      else
        ::set_value_inv(*this,x,ii,minb,maxb,scalefactor);
    }
  }

  void param_init_bounded_matrix::allocate(int rmin,int rmax,
    int cmin,int cmax,
    double _minb,double _maxb,int _phase_start,const char * s)
  {
    minb=_minb;
    maxb=_maxb;
    dvar_matrix::allocate(rmin,rmax,cmin,cmax);
    model_name_tag::allocate(s);
    if (allocated(*this))
    {
      initial_params::allocate(_phase_start);
      for (int i=indexmin();i<=indexmax();i++)
      {
        if (allocated((*this)(i)))
        {
          if (ad_comm::global_bparfile)
          {
            *(ad_comm::global_bparfile) >> (*this)(i);
          }
          else if (ad_comm::global_parfile)
          {
            *(ad_comm::global_parfile) >> (*this)(i);
          }
          else
          {
            if ((!initial_value_flag) || initial_value <=minb
                 || initial_value >= maxb)
            {
              //cerr << "Initial value out of bounds -- using halfway value\n.";
              initial_value=(minb+maxb)/2.;
            }
            (*this)(i)=(initial_value);
          }
        }
      }
    }
    else
    {
      initial_params::allocate(-1);
    }
  }

  void param_init_bounded_matrix::allocate(int rmin,int rmax,
    int cmin,int cmax,double _minb,double _maxb,const char * s)
  {
    minb=_minb;
    maxb=_maxb;
    dvar_matrix::allocate(rmin,rmax,cmin,cmax);
    model_name_tag::allocate(s);
    if (allocated(*this))
    {
      initial_params::allocate(1);
      for (int i=indexmin();i<=indexmax();i++)
      {
        if (allocated((*this)(i)))
        {
          if (ad_comm::global_bparfile)
          {
            *(ad_comm::global_bparfile) >> (*this)(i);
          }
          else if (ad_comm::global_parfile)
          {
            *(ad_comm::global_parfile) >> (*this)(i);
          }
          else
          {
            if ((!initial_value_flag) || initial_value <=minb
                 || initial_value >= maxb)
            {
              //cerr << "Initial value out of bounds -- using halfway value\n.";
              initial_value=(minb+maxb)/2.;
            }
            (*this)(i)=(initial_value);
          }
       }
      }
    }
    else
    {
      initial_params::allocate(-1);
    }
  }

void param_init_bounded_matrix::allocate(const ad_integer& rmin,
  const ad_integer& rmax, const index_type& cmin,
  const index_type& cmax, double _minb,double _maxb,
    int _phase_start,const char * s)
  {
    minb=_minb;
    maxb=_maxb;
    dvar_matrix::allocate(rmin,rmax,cmin,cmax);
    model_name_tag::allocate(s);
    if (allocated(*this))
    {
      initial_params::allocate(_phase_start);
      for (int i=indexmin();i<=indexmax();i++)
      {
        if (allocated((*this)(i)))
        {
          if (ad_comm::global_bparfile)
          {
            *(ad_comm::global_bparfile) >> (*this)(i);
          }
          else if (ad_comm::global_parfile)
          {
            *(ad_comm::global_parfile) >> (*this)(i);
          }
          else
          {
            if ((!initial_value_flag) || initial_value <=minb
                 || initial_value >= maxb)
            {
              //cerr << "Initial value out of bounds -- using halfway value\n.";
              initial_value=(minb+maxb)/2.;
            }
            (*this)(i)=(initial_value);
          }
        }
      }
    }
    else
    {
      initial_params::allocate(-1);
    }
  }


void param_init_bounded_matrix::allocate(const ad_integer& rmin,
  const ad_integer& rmax, const index_type& cmin,
  const index_type& cmax, double _minb, double _maxb,
  const char* s)
  {
    minb=_minb;
    maxb=_maxb;
    dvar_matrix::allocate(rmin,rmax,cmin,cmax);
    model_name_tag::allocate(s);
    if (allocated(*this))
    {
      initial_params::allocate(1);
      for (int i=indexmin();i<=indexmax();i++)
      {
        if (allocated((*this)(i)))
        {
          if (ad_comm::global_bparfile)
          {
            *(ad_comm::global_bparfile) >> (*this)(i);
          }
          else if (ad_comm::global_parfile)
          {
            *(ad_comm::global_parfile) >> (*this)(i);
          }
          else
          {
            if ((!initial_value_flag) || initial_value <=minb
                 || initial_value >= maxb)
            {
              //cerr << "Initial value out of bounds -- using halfway value\n.";
              initial_value=(minb+maxb)/2.;
            }
            (*this)(i)=(initial_value);
          }
        }
      }
    }
    else
    {
      initial_params::allocate(-1);
    }
  }
