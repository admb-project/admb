DATA_SECTION
  init_int nobs
  init_vector Y(1,nobs)
  init_vector X(1,nobs)
PARAMETER_SECTION
  init_number a   
  init_number b   
  init_number mu
  vector pred_Y(1,nobs)
  init_bounded_number sigma_Y(0.0000001,10)
  init_bounded_number sigma_x(0.0000001,10)
  random_effects_vector x(1,nobs)
  sdreport_number sa
  sdreport_number sb
  sdreport_number smu
  objective_function_value f
PROCEDURE_SECTION
  f = 0;
  pred_Y=a*x+b;

  f += nobs*log(sigma_x) + 0.5*norm2((x-mu)/sigma_x);

  f += nobs*log(sigma_Y) + 0.5*norm2((pred_Y-Y)/sigma_Y);

  f += 0.5*norm2((X-x)/0.5);

  sa = a;
  sb = b;
  smu = mu;
