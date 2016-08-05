GLOBALS_SECTION
  extern double CHECK_HESSIAN_PENALTY;

DATA_SECTION

PARAMETER_SECTION
  init_number dummy
  random_effects_vector u(1,3);
  objective_function_value nll

PROCEDURE_SECTION
  CHECK_HESSIAN_PENALTY=10;
  ad_comm::print_hess_and_exit_flag=true;  
  dvariable q=0.1+u(1), a=0.2+u(2), b=0.3+u(3); 
  dvariable fun=pbeta(q,a,b);
  nll=fun+(CHECK_HESSIAN_PENALTY)*sum(square(u));

