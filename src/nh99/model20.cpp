/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

/**
Assigns values from vec to param_init_vector.

\param vec dvector with same dimensions as param_init_vector.
\return param_init_vector with same element values as vec.
*/
param_init_vector& param_init_vector::operator=(const dvector& vec)
{
  dvar_vector::operator=(vec);
  return *this;
}
/**
Assigns values from varvec to param_init_vector.

\param varvec dvar_vector with same dimensions as param_init_vector.
\return param_init_vector with same element values as varvec.
*/
param_init_vector& param_init_vector::operator=(const dvar_vector& varvec)
{
  dvar_vector::operator=(varvec);
  return *this;
}
/**
Assigns value var to param_init_vector.

\param varvec dvar_vector with same dimensions as param_init_vector.
\return param_init_vector with same element values as varvec.
*/
param_init_vector& param_init_vector::operator=(const prevariable& var)
{
  dvar_vector::operator=(var);
  return *this;
}
/**
Assigns value val to param_init_vector.

\param varvec dvar_vector with same dimensions as param_init_vector.
\return param_init_vector with same element values as varvec.
*/
param_init_vector& param_init_vector::operator=(const double& val)
{
  dvar_vector::operator=(val);
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
Assigns values from _m to param_init_matrix.

\param m dmatrix with same dimensions
\return set with assigned values from m
*/
param_init_matrix& param_init_matrix::operator=(const dmatrix& _m)
{
  dvar_matrix::operator=(_m);
  return *this;
}
/**
Assigns values from _m to param_init_matrix.

\param m dvar_matrix with same dimensions
\return set with assigned values from m
*/
param_init_matrix& param_init_matrix::operator=(const dvar_matrix& _m)
{
  dvar_matrix::operator=(_m);
  return *this;
}
/**
Assigns value d to all elements of param_init_matrix.

\param d dvariable
\return set with assigned value from d
*/
param_init_matrix& param_init_matrix::operator=(const dvariable& d)
{
  dvar_matrix::operator=(d);
  return *this;
}
/**
Assigns value d to all elements of param_init_matrix.

\param d dvariable
\return set with assigned value from d
*/
param_init_matrix& param_init_matrix::operator=(const double& d)
{
  dvar_matrix::operator=(d);
  return *this;
}
