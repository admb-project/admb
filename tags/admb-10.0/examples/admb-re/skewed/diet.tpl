// Section 14.2 in Skrondal and Rabe-Hesketh

DATA_SECTION

  init_int n					// Number of observations
  init_ivector D(1,n)				// Bernoulli response (1=disease, 0=not)
  init_matrix X1(1,n,1,3)			// Design matrix for indirect effects (gamma)
  init_matrix X2(1,n,0,3)			// Design matrix for direct effects (beta)

  init_vector fiber1(1,n)			
  init_vector fiber2(1,n)			
 
PARAMETER_SECTION

  init_bounded_vector gamma(1,3,-3.0,3.0,2)     	
  init_bounded_number log_psi(0.0,4.0,2)		

  init_bounded_vector alpha(0,1,0.0,30.0,1)     	
  init_bounded_number log_theta(0.0,4.0,1)	

  init_bounded_number lambda(-0.3,0.3,2)		
  init_bounded_vector beta(0,3,-3.0,3.0,1)     	

  random_effects_vector u(1,n,2)        	// N(0,1) distributed random effects

  objective_function_value g                    // (negative) Log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

GLOBALS_SECTION

  #include <df1b2fun.h>

PROCEDURE_SECTION

  int j;

  g = 0.0;

  for(j=1;j<=n;j++)
    loglik_j(gamma,log_psi,alpha,log_theta,lambda,beta,u(j),j);


SEPARABLE_FUNCTION void loglik_j(const dvar_vector& gamma, const dvariable& log_psi, const dvar_vector& alpha, const dvariable& log_theta, const dvariable& lambda, const dvar_vector& beta, const dvariable& u_j, const  int& j)

  // Exposure model
  g -= -0.9189385 - 0.5*square(u_j);
  dvariable eta_j = X1(j)*gamma + mfexp(0.5*log_psi)*u_j;

  // Measurement error model
  dvariable theta = mfexp(log_theta);
  g -= -0.9189385 - 0.5*log_theta - 0.5*square(fiber1(j) - alpha(0) - eta_j)/theta;

  if(fiber2(j) != -99)
    g -= -0.9189385 - 0.5*log_theta - 0.5*square(fiber2(j) - alpha(0) - alpha(1) - eta_j)/theta;

  // Disease model
  dvariable logit_j = X2(j)*beta + lambda*eta_j;
  g -= D(j)*logit_j - log(1+exp(logit_j));


REPORT_SECTION
  //

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(300000);

