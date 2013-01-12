//$Id$

DATA_SECTION
  !! ad_comm::change_datafile_name("msimple.dat");
  init_int nobs
  init_int nslaves

  matrix Y(1,nslaves,1,nobs)
  matrix x(1,nslaves,1,nobs)

 LOCAL_CALCS
    double A = 2.0;
    double B = 4.0;
    random_number_generator rng(101);
    dvector err(1,nobs);
    for (int i = 1; i <= nslaves; i++)
    {
       x(i).fill_randu(rng);
       x(i) *= 100.0;
       Y(i) = A*x(i) + B;
       err.fill_randn(rng);
       Y(i) += 5.0*err;
    }

PARAMETER_SECTION
  init_number a   
  init_number b   
  vector ff(1,nslaves)
  matrix pred_Y(1,nslaves,1,nobs)
  objective_function_value f

PRELIMINARY_CALCS_SECTION
  a = 1.0;
  b = 2.0;

PROCEDURE_SECTION
  for (int i=1;i<=nslaves;i++)
  {
      pred_Y(i) = a * x(i) +  b;
      ff(i) = norm2(pred_Y(i)-Y(i)); 
      ff(i) = nobs/2.*log(ff(i));    // make it a likelihood function so that
                                    // covariance matrix is correct
  }
  f = sum(ff);

