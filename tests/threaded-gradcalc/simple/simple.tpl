// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_int n
  init_vector x(1,n)
  init_vector y(1,n)
PARAMETER_SECTION
  init_number b0
  init_number b1
  vector yhat(1,n)
  objective_function_value f
PROCEDURE_SECTION
  //yhat=b0+b1*x;
  yhat = compute_yhat(b0, b1, x);
  //f=regression(y,yhat);
  f = compute_regression(y,yhat);
GLOBALS_SECTION
  #include <fvar.hpp>
  dvar_vector compute_yhat(dvariable& b0, dvariable& b1, dvector& x);
  dvariable compute_regression(const dvector& obs, const dvar_vector& pred);
