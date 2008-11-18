DATA_SECTION
  init_int nobs
  init_int m
  init_int trunc_flag
  init_matrix data(1,nobs,1,m+1)
  vector Y(1,nobs)
  matrix X(1,nobs,1,m)
 LOC_CALCS
  Y=column(data,1);
  for (int i=1;i<=nobs;i++)
  {
    X(i)=data(i)(2,m+1).shift(1);
  }
PARAMETER_SECTION
  sdreport_number sigma
  number vhat
  init_bounded_number log_a(-5.0,5.0);
  sdreport_number a
  init_vector u(1,m)
  objective_function_value f
PROCEDURE_SECTION
  a=exp(log_a);
  dvar_vector pred=X*u;
  dvar_vector res=Y-pred;
  dvariable r2=norm2(res); 
  vhat=r2/nobs; 
  dvariable v=a*vhat;
  sigma=sqrt(v);

  dvar_vector spred=pred/sigma;
  f=0.0;
  switch (trunc_flag)
  {
  case -1:  // left_truncated
    {
      for (int i=1;i<=nobs;i++)
      {
        f+=log(1.00001-cumd_norm(-spred(i)));
      }
    }
    break;
  case 1:   // right truncated
    {
      for (int i=1;i<=nobs;i++)
      {
        f+=log(0.99999*cumd_norm(-spred(i)));
      }
    }
    break;
  case 0:   // no truncation
    break;
  default:
    cerr << "Illegal value for truncation flag" << endl;
    ad_exit(1);
  }
  f+=0.5*nobs*log(v)+0.5*r2/v;


REPORT_SECTION
  report << "#u " << endl << u << endl;
  report << "#sigma " << endl << sigma << endl;
  report << "#a " << endl << a << endl;
  report << "#vhat " << endl << vhat << endl;
  report << "#shat " << endl << sqrt(vhat) << endl;
