////////////////////////////////////////////////////////
// ADMB code for the theta logistic population model.
//
// This model should be compiled with -r flag for random effects,
// I.e. admb -r admbmodel
// and should be executed with the -noinit flag,
// I.e. admbmodel -noinit
//
// Author: Casper W. Berg, 13-07-2010
////////////////////////////////////////////////////////
DATA_SECTION
  init_vector initPars(1,5);
  init_number N;
  init_vector y(1,N)
PARAMETER_SECTION
  init_number logSdU;
  init_number logSdy;
  init_number logr0;
  init_number logTheta;
  init_bounded_number K(100.0,2000.0);
  random_effects_vector U(1,N);
  objective_function_value jnll;
  
  // do delta method to find confidence intervals for the following untransformed parameters
  sdreport_number r0;
  sdreport_number theta;
  sdreport_number SdU;
  sdreport_number Sdy;

PRELIMINARY_CALCS_SECTION
  //initialize parameters 
  logr0 = log(initPars(1)); 
  K = initPars(2);
  logSdU = log(initPars(3)); 
  logSdy = log(initPars(4)); 
  logTheta = log(initPars(5));
  
PROCEDURE_SECTION
  jnll=0.0; // joint negative log-likelihood to be minimized.
  r0 = exp(logr0);
  theta=exp(logTheta);
  SdU = exp(logSdU);
  Sdy = exp(logSdy);
  
  // transition equation (Eq. 3)
  for(int i=2; i<=N; ++i){
    step(U(i-1),U(i),logSdU,logr0,K,i-1,logTheta);
  }
  // observation equation (Eq. 4)
  for(int i=1; i<=N; ++i){
    obs( logSdy, U(i), i);
  }
  
SEPARABLE_FUNCTION void step(const dvariable& U1, const dvariable& U2, const dvariable& logSdU, const dvariable& logr0, const dvariable& K, int i, const dvariable& logTheta)
  dvariable var2=exp(2.0*logSdU);
  dvariable r0 = exp(logr0);
  dvariable theta = exp(logTheta);
  dvariable pred = U1 + r0*(1.0-pow( exp(U1)/K,theta ));
  jnll+=0.5*(log(2.0*M_PI*var2)+square(pred-U2)/var2);

SEPARABLE_FUNCTION void obs(const dvariable& logSdy, const dvariable& x, int i)
  dvariable var=exp(2.0*logSdy);
  jnll+=0.5*(log(2.0*M_PI*var)+square(x-y(i))/var);

TOP_OF_MAIN_SECTION
  // Set maximum number of independent variables to 1000 and increase memory.
  gradient_structure::set_MAX_NVAR_OFFSET(1000);
  arrmblsize=2000000;
