/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

  void param_init_bounded_matrix::set_value(const dvar_vector& x,
    BOR_CONST int& ii,BOR_CONST dvariable& pen)
  {
    if (allocated(*this))
    {
      if (!scalefactor)
        ::set_value(*this,x,ii,minb,maxb,pen);
      else
        ::set_value(*this,x,ii,minb,maxb,pen,scalefactor);
    }
  }


  void param_init_bounded_matrix::set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    if (allocated(*this))
    {
      if (!scalefactor)
        ::set_value_inv(*this,x,ii,minb,maxb);
      else
        ::set_value_inv(*this,x,ii,minb,maxb,scalefactor);
    }
  }

  param_init_bounded_matrix::param_init_bounded_matrix() :
    param_init_matrix()
  {;}

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
              //cerr << "Initial value out of bounds -- using halfway value" << endl;
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
              //cerr << "Initial value out of bounds -- using halfway value" << endl;
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
    const ad_integer& rmax,_CONST index_type& cmin,
    _CONST index_type& cmax, double _minb,double _maxb,
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
              //cerr << "Initial value out of bounds -- using halfway value" << endl;
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
    const ad_integer& rmax,_CONST index_type& cmin,
    _CONST index_type& cmax, double _minb,double _maxb,
    const char * s)
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
              //cerr << "Initial value out of bounds -- using halfway value" << endl;
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
