DATA_SECTION
  init_table obs
  vector X0(1,2)  
  
PARAMETER_SECTION
  init_vector logK(1,3);
  init_number logSigma;

  sdreport_vector k(1,3);
  sdreport_number sigma2;
  number pred;
  matrix A(1,2,1,2);
  objective_function_value nll;

PRELIMINARY_CALCS_SECTION
  X0(1)=0.0; X0(2)=100.0;
  logK=-2.0;
  logSigma=-2.0;

PROCEDURE_SECTION
  k=exp(logK);
  sigma2=exp(2.0*logSigma);

  A(1,1)= -k(1); A(1,2)=  k(2);      
  A(2,1)=  k(1); A(2,2)= -k(2)-k(3); 

  for(int i=1; i<=obs.rowmax(); ++i){
    pred=100.0-sum(expm(A*obs(i,1))*X0);
    nll+=0.5*(log(2.0*M_PI*sigma2)+square(obs(i,2)-pred)/sigma2);
  }
