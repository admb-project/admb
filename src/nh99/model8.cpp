/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
  #include <admodel.h>

  objective_function_value * objective_function_value::pobjfun=NULL;
  double objective_function_value::gmax=0;

  objective_function_value::objective_function_value() {pobjfun=this;}
  objective_function_value& objective_function_value::operator =
    (const prevariable& v)
  {
    prevariable::operator = (v);
    return *this;
  }
objective_function_value& objective_function_value::operator=(const double v)
  {
    prevariable::operator = (v);
    return *this;
  }
