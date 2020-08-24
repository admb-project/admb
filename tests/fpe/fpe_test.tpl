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
  yhat=b0+b1*x;
  f=regression(y,yhat);
  fpe_invalid();
  fpe_divbyzero();
  fpe_overflow();
  double* x = nullptr;
  cout << x[1] << endl;
FUNCTION fpe_invalid
  cout << std::sqrt(-1) << endl;
FUNCTION fpe_divbyzero
  double z = 0.0;
  double ret = 5.0 / z;
  cout << ret << endl;
FUNCTION fpe_overflow
  double ret = DBL_MAX * 2.0;
  cout << ret << endl;
