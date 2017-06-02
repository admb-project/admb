/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <admodel.h>

/**
Set maximum bounds value for param_init_bounded_number.

\param val double
*/
void param_init_bounded_number::set_maxb(double val)
{
  maxb = val;
}
/**
Returns maximum bounds value for param_init_bounded_number.
*/
double param_init_bounded_number::get_maxb() const
{
  return maxb;
}
/**
Set maximum bounds value for param_init_bounded_vector.

\param val double
*/
void param_init_bounded_vector::set_maxb(double val)
{
  maxb = val;
}
/**
Returns maximum bounds value for param_init_bounded_vector.
*/
double param_init_bounded_vector::get_maxb() const
{
  return maxb;
}
/**
Set maximum bounds value for param_init_bounded_matrix.

\param val double
*/
void param_init_bounded_matrix::set_maxb(double val)
{
  maxb = val;
}
/**
Returns maximum bounds value for param_init_bounded_matrix.
*/
double param_init_bounded_matrix::get_maxb() const
{
  return maxb;
}
