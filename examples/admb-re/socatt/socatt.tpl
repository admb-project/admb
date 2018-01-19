// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

// Ordinal response model with random effects. 
// The SOCATT data used in the software comparison http://multilevel.ioe.ac.uk/softrev/index.html

DATA_SECTION

  init_int n			// Number of observations
  init_ivector y(1,n)		// Response vector
  init_int S			// Number of response categories
  int S1			// For variable allocation
  !! S1=S-1;			
  init_int p			// Number of fixed effects
  init_matrix X(1,n,1,p)	// Fixed effects design matrix
  init_int M			// Number of random effects
  init_ivector ngroup(1,M)      // Group indicator
 

PARAMETER_SECTION

  init_bounded_vector b(1,p,-5,5) 		// Fixed effects
  init_bounded_number logsigma(-3.0,2.0)	// 0.5*log-variance component

  init_bounded_vector tmpk(1,S1,-3,1)		// Variables underlying kappa

  random_effects_vector u(1,M)			// Random effects

  objective_function_value g

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

GLOBALS_SECTION

  #include <df1b2fun.h>

PROCEDURE_SECTION

  int i,ii;
  ii = 1;

  // Likelihood contribution for the i'th cluster
  for(i=1;i<=(int) M;i++)
    sep_fun(ii,ngroup(i),u(i),b,logsigma,tmpk);


SEPARABLE_FUNCTION void sep_fun(int& ii, int& ni, const dvariable& u,const dvar_vector& b,const dvariable& logsigma,const dvar_vector& tmpk)
  int j;

  dvariable sigma = exp(logsigma);

  // Sets up kappa from underlying variable tmpk
  dvar_vector kappa(1,S1);
  kappa(1) = tmpk(1);
  for(int s=2;s<=S-1;s++)
    kappa(s) = kappa(s-1) + mfexp(tmpk(s));
  kappa *= sigma;

  dvariable P,eta;                      	// Variable allocation 

  g -= -log(sigma)-0.5*square(u/sigma);// log[h(u)]

  for(j=1;j<=ni;j++)
  {
    eta = X(ii)*b + u;             		// X(i) is i'th row of X
    if(y(ii)==S)				
      P = 1.0;
    else
      P = 1/(1+exp(-(kappa(y(ii))-eta)));
    if(y(ii) > 1)
      P -= 1/(1+exp(-(kappa(y(ii)-1)-eta)));
    g -= log(1.e-20+P);                   		// log[f(y|u)] for i'th super individuals

    ii++;
  }

REPORT_SECTION

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(2000);



