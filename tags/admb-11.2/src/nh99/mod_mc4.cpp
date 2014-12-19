/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

double better_rand(long int&);

double function_minimizer::get_monte_carlo_value(int nvar, const dvector& x)
{
  //initial_params::xinit(x);
  double f=0.0;
  {
    dvariable vf=0.0;
    vf=initial_params::reset(dvar_vector(x));
    *objective_function_value::pobjfun=0.0;
    userfunction();
    vf+=*objective_function_value::pobjfun;
    f=value(vf);
  }
  return f;
}
