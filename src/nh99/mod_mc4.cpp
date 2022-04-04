/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function function_minimizer::get_monte_carlo_value
*/
#include <admodel.h>

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
