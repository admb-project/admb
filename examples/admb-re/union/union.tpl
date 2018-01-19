// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

// Generalized additive model fitted to the Wage-union data

DATA_SECTION

  // Data
  init_int n					// Number of observations
  init_vector y(1,n)				// The responses: 0 or 1
  init_ivector race(1,n)			// Covariate
  init_ivector sex(1,n)				// Covariate
  init_ivector south(1,n)			// Covariate

  // B-spline for wages
  init_int m1					// Number of collumns in the desing matrix X
  init_matrix X_B1(1,n,1,m1)        		// Design matrix for spline
  init_matrix J1(1,n,1,2)        		// Indexes for start-stop of nonzero elements in X

  // B-spline for age
  init_int m2					// Number of collumns in the desing matrix X
  init_matrix X_B2(1,n,1,m2)        		// Design matrix for spline
  init_matrix J2(1,n,1,2)        		// Indexes for start-stop of nonzero elements in X

  // B-spline for education
  init_int m3					// Number of collumns in the desing matrix X
  init_matrix X_B3(1,n,1,m3)        		// Design matrix for spline
  init_matrix J3(1,n,1,2)        		// Indexes for start-stop of nonzero elements in X
 
PARAMETER_SECTION

  // Ordinary regression parameters
  init_bounded_vector b_race(1,3,-3,3,1)            
  init_bounded_number b_sex(-3,3,1)            
  init_bounded_number b_south(-3,3,1)            

  // Smothing parameters
  init_bounded_number lambda1(.0001,10,2)            
  init_bounded_number lambda2(.0001,40,2)            
  init_bounded_number lambda3(.0001,10,2)            

  // Spline functions
  vector f_wages(1,n)
  vector f_age(1,n)
  vector f_ed(1,n)

  // Nonparametric components
  random_effects_vector u1(1,m1,2)              // Underying random effect for wages
  random_effects_vector u2(1,m2,2) 		// Underying random effect for age
  random_effects_vector u3(1,m3,2) 		// Underying random effect for ed

  objective_function_value g                    // Penalized log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

GLOBALS_SECTION

PROCEDURE_SECTION

  int i,j;

  g = 0;

  // Add 1rst order difference penalties 
  // Note that the smothing parameter lambda enters below
  for(j=2;j<=m1;j++)
    g -= -0.5*square(u1(j) - u1(j-1));
  for(j=2;j<=m2;j++)
    g -= -0.5*square(u2(j) - u2(j-1));
  for(j=2;j<=m3;j++)
    g -= -0.5*square(u3(j) - u3(j-1));

  // Center the splines at zero to make the model identifiable.
  g -= -0.5*(square(mean(u1)) + square(mean(u2)) + square(mean(u3)));

  f_wages = 0;
  f_age = 0;
  f_ed = 0;

  // Calculate the spline functions from the B-spline bases.
  for(i=1;i<=n;i++)
  {
    for(j=J1(i,1);j<=J1(i,2);j++)
      f_wages(i) +=  X_B1(i,j)*u1(j);
  
    for(j=J2(i,1);j<=J2(i,2);j++)
      f_age(i)   +=  X_B2(i,j)*u2(j);

    for(j=J3(i,1);j<=J3(i,2);j++)
      f_ed(i)    +=  X_B3(i,j)*u3(j);
  }

  // Scale up the splines
  f_wages /= lambda1;
  f_age /= lambda2;
  f_ed /= lambda3;

  // Bernoulli likelhood
  for(i=1;i<=n;i++)
  {
    dvariable eta = b_race(race(i)) + b_sex*sex(i) + b_south*south(i) + f_wages(i) + f_age(i) + f_ed(i); 
    g -= y(i)*eta - log(1+mfexp(eta));      
  }
  
REPORT_SECTION

  report << f_wages << endl;
  report << f_age << endl;
  report << f_ed << "\n\n" << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(130000);

