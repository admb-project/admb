// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

// Stochastic volatitliy model of Stroud, Muller and Stoffer (2003)

DATA_SECTION

  init_int n			// Length of time series
  init_vector y(1,n)		// Time series

PARAMETER_SECTION

  init_bounded_number b(-.9999,.9999,2)			// Correlation coefficient
  init_bounded_number log_sigma(-3.0,3.0,2)	// 0.5*log(variance component)
  init_bounded_number mu(-10,10,-1)		// Regression parameters 
  init_bounded_number mu_x(-10,3,1)		// Regression parameters 

  random_effects_vector x(1,n,2)			// Random effects

  objective_function_value g

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

GLOBALS_SECTION

  //#include <df1b2fun.h>
  
PROCEDURE_SECTION

  int i;	

  sf1(log_sigma,b,x(1));
  for (i=2;i<=n;i++)
  {
    sf2(log_sigma,b,x(i),x(i-1));
  }
  for (i=1;i<=n;i++)
  {
    sf3(x(i),mu,mu_x,i);
  }

SEPARABLE_FUNCTION void sf1(const dvariable& ls,const dvariable& bb,const dvariable& x_1)
  g -= -ls + 0.5*log(1-square(bb))  - 0.5*square(x_1/mfexp(ls))*(1-square(bb));

SEPARABLE_FUNCTION void sf2(const dvariable& ls,const dvariable& bb,const dvariable& x_i,const dvariable& x_i1)
  g -= -ls - .5*square((x_i-bb*x_i1)/mfexp(ls));

SEPARABLE_FUNCTION void sf3(const dvariable& x_i ,const dvariable& mu ,const dvariable& mu_x ,int i)
  dvariable log_sigma_y = 0.5*(mu_x + x_i);
  dvariable sigma_y = mfexp(log_sigma_y);
  g -= -log_sigma_y - .5*square((y(i)-mu)/sigma_y);


REPORT_SECTION

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(50850);


