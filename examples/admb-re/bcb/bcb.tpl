// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

// ADMB-RE implementation of from Zeh and Punt (2004) SC/56/BRG1

DATA_SECTION

  init_int n					// Number of years with data
  init_matrix D(1,n,1,7)			// year, N4, SE(N4), indicator, P4, SE(N4), indicator
  vector cv_N4(1,n) 				// CV of N4
  vector cv_P4(1,n) 				// CV of P4
  ivector indN4(1,n)				// Indicator for whether there are N4 data in a particular year
  ivector indP4(1,n)				// Indicator for whether there are P4 data in a particular year

PARAMETER_SECTION

  init_bounded_number log_s_eta(-10,10)		// log(sigma_eta)

  vector log_p(1,n)				// log(p)
  sdreport_vector Py(1,n)			// Abundance
  
  random_effects_vector log_pi(1,1)		// log(pi) 
  random_effects_vector a(0,1)			// Intercept and Rate of increase (alternative model)

  random_effects_vector eta(1,n)	

  objective_function_value g

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);
  
  // Punt's cv's
  cv_N4 = sqrt(log(square(elem_div(column(D,3),column(D,2)))+1.0));
  cv_P4 = sqrt(log(square(elem_div(column(D,6),column(D,5)))+1.0));

  indN4 = (ivector) column(D,4);
  indP4 = (ivector) column(D,7);

  
PROCEDURE_SECTION


  int i;

  // Contribution from random effects distribution
  g = -n*log_s_eta - .5*norm2(eta)/mfexp(2*log_s_eta);

  log_p  = log_pi(1) + eta;

  for(i=1;i<=n;i++)
  {
    if(indN4(i))
      g += -0.5*square((log(D(i,2)) - log_p(i) - a(0) - a(1)*(D(i,1)-1980))/cv_N4(i));		// Rate of increase verison

    if(indP4(i))
      g += -0.5*square((log(D(i,5))-log_p(i))/cv_P4(i));
  }

  g *= -1.0;				// ADMB does minimization !!!

  Py = exp(a(0) + a(1)*(column(D,1)-1980.0));
      
REPORT_SECTION
  report << "s_eta = " << exp(log_s_eta) << endl;
  report << "pi = " << exp(log_pi) << endl;
  report << "Py(1978-1983,1985-1988,1993,2001) = " << Py << endl;
  
     
TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(50850);


