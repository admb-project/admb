// Weibull regression with random effects in the BUGS manual: Example 3 in Skaug and Fournier (2003)

DATA_SECTION

  init_int n			// Number of inidviduals
  init_matrix age(1,n,1,2)	// Age
  init_ivector sex(1,n)		// Sex
  init_ivector disease(1,n)	// Disease type
  init_matrix t(1,n,1,2)	// Survival time
  matrix logt(1,n,1,2)		// Log-survival time
  init_matrix delta(1,n,1,2)	// Cencoring indicator

PARAMETER_SECTION

  // Parameters in related to covariates
  init_bounded_number b0(-8,2)			// Intercept
  init_bounded_number b_age(-.1,.1)		// Age effect
  init_bounded_vector b_disease(1,3,-3,3) 	// Contrast for codes 2,3,4
  init_bounded_number b_sex(-3,3)		// Sex effect

  init_bounded_number r(.5,2)			// Shape parameter in Weibull distribution
  init_bounded_number log_sigma(-6.0,1.0)	// 0.5*log-variance component

  random_effects_vector u(1,n)			// Random effect

  objective_function_value g			// Joint log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);
  logt = log(t);

PROCEDURE_SECTION

  int i, j;

  dvariable sigma, eta, h0t, ht, Ht;                      // Local variables 

  sigma = exp(log_sigma);

  g = -n*log(sigma)-0.5*norm2(u/sigma); // log[h(u)]

  for(i=1;i<=n;i++)                     
  {
    for(j=1;j<=2;j++)                     
    {
      eta = b0 + b_age*age(i,j) + b_sex*sex(i) + u(i);
      if(disease(i)>1)
        eta += b_disease(disease(i)-1);

      h0t = r*exp(logt(i,j)*(r-1));     // Baseline hazard
      ht = h0t * mfexp(eta);            // Hazard function    
      Ht = ht*t(i,j)/r;                 // Cumulative hazard
 
      g += delta(i,j)*log(ht) - Ht;     // log[f(y|u)] 
    }
  }

  g *= -1;

REPORT_SECTION

TOP_OF_MAIN_SECTION
  arrmblsize = 400000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(2000);



