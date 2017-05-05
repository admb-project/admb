/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

 int likeprof_params::num_likeprof_params=0;
 likeprof_params * likeprof_params::likeprofptr[500]; // this should be
                                                 // a resizeable array

  likeprof_params::likeprof_params(void)
  {
    stepsize=0.5;
    stepnumber=8;
  }

  void likeprof_params::add_to_list(void)
  {
    likeprofptr[num_likeprof_params++]= this; // this is the list of
                                         // likelihood profile objects
  }

  param_likeprof_number::param_likeprof_number() : param_stddev_number() ,
    likeprof_params()
  {
    sigma=0.0;
    likeprof_params::add_to_list();
    // stddev_params::add_to_list(); // don't think we need this here
  }

  int param_likeprof_number::size_count(void)
  {
    return 1;
  }

/*
        void param_likeprof_number::set_dependent_variables(void)
        {
                #ifndef __ZTC__
                dvariable(*this) << dvariable(*this);
                #else
                *this << *this;
                #endif
        }
*/

  void param_likeprof_number::allocate(const char * _s)
  {
    named_dvariable::allocate(_s);
    likeprof_params::allocate();
  }

  const char * param_likeprof_number::label(void)
  {
    return model_name_tag::label().mychar();
  }

/**
Assign param_likeprof_number with prevariable var.
\param var prevariable
*/
param_likeprof_number& param_likeprof_number::operator=(const prevariable& var)
{
  this->param_stddev_number::operator=(var);
  return *this;
}
/**
Assign param_likeprof_number with value.
\param value double
*/
param_likeprof_number& param_likeprof_number::operator=(const double value)
{
  this->param_stddev_number::operator=(value);
  return *this;
}

        // for now only do likelihood profiles for numbers
  /*
  int likeprof_params::num_likeprof_calc(void)
  {
    int nvar=0;
    for (int i=0;i<num_likeprof_params;i++)
    {
      nvar+= (likeprofptr[i])->size_count();
    }
    return nvar;
  }

  int param_likeprof_vector::size_count(void)
  {
    return ::size_count(*this);
  }

  param_likeprof_vector::param_likeprof_vector(void) : named_dvar_vector() ,
    likeprof_params()
  {
    add_to_list();
  }

  void param_likeprof_vector::allocate(int imin,int imax,const char * s)
  {
    named_dvar_vector::allocate(imin,imax,s);
    likeprof_params::allocate();
  }

  void param_likeprof_vector::set_dependent_variables(void)
  {
    dvar_vector(*this) << dvar_vector(*this);
  }

  param_likeprof_matrix::param_likeprof_matrix() : named_dvar_matrix() ,
    likeprof_params()
  {
    add_to_list();
  }

  int param_likeprof_matrix::size_count(void)
  {
    return ::size_count(*this);
  }

  void param_likeprof_matrix::allocate(int rmin,int rmax,int cmin,int cmax,
    const char * s)
  {
    named_dvar_matrix::allocate(rmin,rmax,cmin,cmax,s);
    likeprof_params::allocate();
  }

  void param_likeprof_matrix::set_dependent_variables(void)
  {
    dvar_matrix(*this) << dvar_matrix(*this);
  }

  const char * param_likeprof_vector::label(void)
  {
    return model_name_tag::label();
  }

  const char * param_likeprof_matrix::label(void)
  {
    return model_name_tag::label();
  }
*/
