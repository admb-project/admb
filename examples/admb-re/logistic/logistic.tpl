// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

// Logistic regression: Example 1 in Skaug and Fournier (2003)

DATA_SECTION

  init_int n					// Number of observations
  init_vector y(1,n)				// Observation vector
  init_int p					// Number of fixed effects
  init_matrix X(1,n,1,p)			// Covariate matrix for fixed effects
  init_int q					// Number of fixed effects
  init_matrix Z(1,n,1,q)			// Covariate matrix for random effects
 
PARAMETER_SECTION

  init_bounded_vector b(1,p,-10,10,1)     	// Fixed effects
  init_bounded_number log_sigma(-6,5,2)       
  sdreport_number sigma                       	// sqrt(variance component)

  random_effects_vector u(1,q,2)                // Random effects

  objective_function_value g                    // Log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

GLOBALS_SECTION

  #include <df1b2fun.h>

PROCEDURE_SECTION

  int i;

  sigma = exp(log_sigma);
  dvariable eta;
							
  g = -q*log(sigma) - .5*norm2(u/sigma);  // log[h(u)]

  for(i=1;i<=n;i++)
  {
    eta = X(i)*b + Z(i)*u;            	  // X(i) is i'th row of X (similar for Z)
    g += y(i)*eta - log(1+exp(eta));      // log[f(y(i)|u)] 
  }


  g *= -1;                                // ADMB does miminization!


REPORT_SECTION
  report << "b =" << b << "sigma=" << sigma << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(2000);

