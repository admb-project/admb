/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>

  param_init_vector& param_init_vector::operator = (const dvector& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }
  param_init_vector& param_init_vector::operator = (const dvar_vector& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }
  param_init_vector& param_init_vector::operator = (const prevariable& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }

  param_init_vector& param_init_vector::operator = (const double& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }

  param_init_bounded_vector& param_init_bounded_vector::operator = (const dvector& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }
  param_init_bounded_vector& param_init_bounded_vector::operator = (const dvar_vector& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }
  param_init_bounded_vector& param_init_bounded_vector::operator = (const prevariable& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }
  param_init_bounded_vector& param_init_bounded_vector::operator = (const double& v)
  {
    dvar_vector::operator = (v);
    return *this;
  }

  param_init_matrix& param_init_matrix::operator = (const dmatrix& m)
  {
    dvar_matrix::operator = (m);
    return *this;
  }

  param_init_matrix& param_init_matrix::operator = (const dvar_matrix& m)
  {
    dvar_matrix::operator = (m);
    return *this;
  }

  param_init_matrix& param_init_matrix::operator = (const dvariable& m)
  {
    dvar_matrix::operator = (m);
    return *this;
  }

  param_init_matrix& param_init_matrix::operator = (const double& m)
  {
    dvar_matrix::operator = (m);
    return *this;
  }

