DATA_SECTION
  vector x(1,200)
  !! x.fill_seqadd(0,.005);
  vector y(1,200)
  !! y=pbeta(x,0.3,0.4);

PARAMETER_SECTION
  init_number loga
  init_number logb
  random_effects_vector u(1,2);
  sdreport_number a
  sdreport_number b
  objective_function_value nll

PROCEDURE_SECTION
  nll=0;
  a=exp(loga);
  b=exp(logb);
  
  dvar_vector pred=pbeta((dvar_vector)x,a+u(1),b+u(2));
  nll=sum(square(y-pred))+sum(square(u));
  