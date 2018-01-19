// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_int nobs;
  init_matrix data(1,nobs,1,2)
  vector age(1,nobs);
  vector size(1,nobs);
PARAMETER_SECTION
  init_number linf;
  init_number K;
  init_number t0;
  init_bounded_number a(0.,0.71,2);
  vector pred_size(1,nobs)
  objective_function_value f;
PRELIMINARY_CALCS_SECTION
  a=.70;
  // get the data out of the columns of the data matrix 
  age=column(data,1);
  size=column(data,2);
  linf=1.1*max(size);  // set linf to 1.1 times the longest observed length
PROCEDURE_SECTION
  // pred(i)=linf*(1-exp(-K*(age(i)-t0))) without loops
  pred_size=linf*(1.-exp(-K*(age-t0)));
  f=robust_regression(size,pred_size,a);  // use robust regression
