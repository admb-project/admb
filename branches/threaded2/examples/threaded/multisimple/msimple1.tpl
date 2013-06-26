//$Id: msimple1.tpl 742M 2013-06-02 00:06:06Z (local) $

DATA_SECTION
  !! ad_comm::change_datafile_name("msimple.dat");
  init_int nobs
  init_int nrow
  matrix Y(1,nrow,1,nobs)
  matrix x(1,nrow,1,nobs)
  number A
  number B

 LOCAL_CALCS
    A = 2.0;
    B = 4.0;
    random_number_generator rng(101);
    dvector err(1,nobs);
    for (int i = 1; i <= nrow; i++)
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
  vector ff(1,nrow)
  matrix pred_Y(1,nrow,1,nobs)
  objective_function_value f

PRELIMINARY_CALCS_SECTION
  a = 1.0;
  b = 2.0;

PROCEDURE_SECTION
  for (int i=1;i<=nrow;i++)
  {
      pred_Y(i) = a * x(i) +  b;
      ff(i) = norm2(pred_Y(i)-Y(i)); 
  }
  f = sum(ff);
  f = (nrow*nobs)/2.*log(f);    // make it a likelihood function so that
                                // covariance matrix is correct
REPORT_SECTION
  report << "A = " << A << "; B = " << B <<endl;
  report << "a = " << a << "; b = " << b <<endl;


