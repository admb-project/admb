// Biomial with random effects

DATA_SECTION

 init_int n					
 init_vector y(1,n)		

PARAMETER_SECTION
  init_bounded_number mu(-5.0,5.0)     	
  init_bounded_number sigma(.001,5,2)	

  random_effects_vector u(1,n,2)

  objective_function_value g    

PROCEDURE_SECTION

  int i;

  for (i=1;i<=n;i++)
    f1(i,mu, sigma,u(i));

SEPARABLE_FUNCTION void f1(const int& i, const prevariable & mu, const prevariable & sigma, const prevariable& ui)
  #ifdef PI
  g -= -0.5*log(2.0*PI) - 0.5*square(ui);
  #else
  g -= -0.5*log(2.0*3.14) - 0.5*square(ui);
  #endif


  dvariable  eta = mu + sigma*ui;
  dvariable  p = mfexp(eta)/(1.0 + mfexp(eta));

  //for (int j=0;j<=2;j++)
  //  if(y(i)==j)
  //    g -= j*log(p) + (2.0-j)*log(1-p); 

  g -= y(i)*eta + 2.0*log(1.0 - p + .0000001); 


TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(100000);


