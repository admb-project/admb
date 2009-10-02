// Nonparametric estimation of mean and variance applied to the Lidar data.

DATA_SECTION

  // Data
  init_int n	
  init_vector y(1,n)				// Observation vector
  init_vector x(1,n)				// Covariate

  // B-spline for mu
  init_int m1	
  init_matrix X_B1(1,n,1,m1)        		// Design matrix for spline
  init_matrix J1(1,n,1,2)        		// Indexes for start-stop of nonzero elements

  // B-spline for log(sigma)
  init_int m2	
  init_matrix X_B2(1,n,1,m2)        		// Design matrix for spline
  init_matrix J2(1,n,1,2)        		// Indexes for start-stop of nonzero elements
 
PARAMETER_SECTION

  init_bounded_number lambda1(.0001,100,1)            
  init_bounded_number lambda2(.000001,10,2)            

  vector mu(1,n)
  vector sigma(1,n)

  // Nonparametric components
  random_effects_vector u1(1,m1,1)                	// Underying random effect mu
  random_effects_vector u2(1,m2,2) 		// Underying random effect G


  objective_function_value g                    // Log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

GLOBALS_SECTION

PROCEDURE_SECTION
  int j;
  g = 0;

  // Second order difference penalty
  for(j=3;j<=m1;j++)
    g -= -0.5*square(u1(j) - 2*u1(j-1) + u1(j-2));
  //for(j=3;j<=m2;j++)
  //  g -= -0.5*square(u2(j) - 2*u2(j-1) + u2(j-2));
  for(j=2;j<=m2;j++)
    g -= -0.5*square(u2(j) - u2(j-1));

  mu = 0.0;
  dvariable tmps;
  for(int i=1;i<=n;i++)
  {
    tmps = 0.0;
    for(j=(int)J1(i,1);j<=(int)J1(i,2);j++)
      mu(i) +=  X_B1(i,j)*u1(j);
    mu(i) *=  lambda1;

    for(j=(int)J2(i,1);j<=(int)J2(i,2);j++)
      tmps  +=  X_B2(i,j)*u2(j);
    sigma(i) = mfexp(lambda2*tmps);
  }

  g -= -sum(log(sigma)) - 0.5*norm2(elem_div(y-mu,sigma));
  

REPORT_SECTION

  report << mu << endl;
  report << sigma << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(130000);

