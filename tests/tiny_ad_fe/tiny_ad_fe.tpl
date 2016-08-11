DATA_SECTION
  vector x(1,20000)
  !! x.fill_seqadd(0,.00005);
  vector y(1,20000)
  !! y=pbeta(x,0.3,0.4);

PARAMETER_SECTION
  init_number loga
  init_number logb
  sdreport_number a
  sdreport_number b
  objective_function_value nll

PROCEDURE_SECTION
  nll=0;
  a=exp(loga);
  b=exp(logb);
  dvar_vector pred=pbeta((dvar_vector)x,a,b);
  nll=sum(square(y-pred));
  