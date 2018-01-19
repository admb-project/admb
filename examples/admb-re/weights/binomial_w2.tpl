// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

// Example to illustrate the use of weights: Biomial with random effects

DATA_SECTION

 init_vector w(1,3)		

PARAMETER_SECTION
  init_bounded_number mu(-5.0,5.0)     	
  init_bounded_number sigma(.001,5,2)	

  random_effects_vector u(0,2,2)

  objective_function_value g    
 !! set_multinomial_weights(w);

PROCEDURE_SECTION

  int y;

  for (y=0;y<=2;y++)
    f1(y,mu, sigma,u(y));

SEPARABLE_FUNCTION void f1(const int& y, const prevariable & mu, const prevariable & sigma, const prevariable& ui)

  dvariable f;

  f = -0.5*log(2*PI) - 0.5*square(ui);

  dvariable  eta = mu + sigma*ui;
  dvariable  p = mfexp(eta)/(1.0 + mfexp(eta));

  f += y*eta + 2.0*log(1.0 - p + .0000001); 

  g -= w(y+1)*f;					// Where the weights are applied.


TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(100000);


