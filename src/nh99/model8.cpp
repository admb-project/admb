/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

objective_function_value* objective_function_value::pobjfun = NULL;
double objective_function_value::gmax = 0;

/**
Default constructor
*/
objective_function_value::objective_function_value()
{
  pobjfun = this;
}
/**
Assigment operator for prevariable.
*/
objective_function_value& objective_function_value::operator=
  (const prevariable& _v)
{
  prevariable::operator=(_v);
  return *this;
}
/**
Assigment operator for double.
*/
objective_function_value& objective_function_value::operator=
  (const double _v)
{
  prevariable::operator=(_v);
  return *this;
}
