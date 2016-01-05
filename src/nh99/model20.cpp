/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
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

param_init_bounded_vector& param_init_bounded_vector::operator=(
  const dvector& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }
param_init_bounded_vector& param_init_bounded_vector::operator=(
  const dvar_vector& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }
param_init_bounded_vector& param_init_bounded_vector::operator=(
  const prevariable& v)
  {
    dvar_vector::operator =(v);
    return *this;
  }
param_init_bounded_vector& param_init_bounded_vector::operator=(const double& v)
  {
    dvar_vector::operator = (v);
    return *this;
  }
/**
Assigment operator for dmatrix.
\param m dmatrix with same dimensions
\return set with assigned values from m
*/
param_init_matrix& param_init_matrix::operator=(const dmatrix& _m)
{
  dvar_matrix::operator=(_m);
  return *this;
}
/**
Assigment operator for dvar_matrix.
\param m dvar_matrix with same dimensions
\return set with assigned values from m
*/
param_init_matrix& param_init_matrix::operator=(const dvar_matrix& _m)
{
  dvar_matrix::operator=(_m);
  return *this;
}
/**
Assigment operator for dvariable.
\param d dvariable
\return set with assigned value from d
*/
param_init_matrix& param_init_matrix::operator=(const dvariable& d)
{
  dvar_matrix::operator=(d);
  return *this;
}
/**
Assigment operator for dvariable.
\param d dvariable
\return set with assigned value from d
*/
param_init_matrix& param_init_matrix::operator=(const double& d)
{
  dvar_matrix::operator=(d);
  return *this;
}
