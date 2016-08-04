DATA_SECTION
  init_int N
  init_vector X(1,N)
PARAMETER_SECTION
  init_bounded_number mu(0,2*M_PI)
  init_number logKappa
  sdreport_number kappa
  objective_function_value nll;
PROCEDURE_SECTION
  kappa=exp(logKappa);
  // Von Mises -logL: 
  nll = -kappa*sum(cos(X-mu))+N*log(2*M_PI)+N*log(besselI(kappa,0));
