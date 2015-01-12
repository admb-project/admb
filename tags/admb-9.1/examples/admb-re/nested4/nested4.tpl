// Logistic regression with 4 levels of nested random effects

DATA_SECTION

  init_int N					// Parameter in binomial distribution
  init_ivector m(1,4)				// Number of random effects at each nesting levels
  int mm				
  !! mm = 1+m(2)*(1+m(3)*(1+m(4)));		// Total number of random effects under each top level
  int m1				
  !! m1 = m(1);		
  int m2m3m4				
  !! m2m3m4 = m(2)*m(3)*m(4);		

  init_imatrix y(1,m1,1,m2m3m4)			// Observation vector
  init_ivector indI(1,3)			// Index for use in scaling up random effects
  init_imatrix I(1,m2m3m4,1,3)			// For indexing random effects vector
 
PARAMETER_SECTION

  init_bounded_vector b(1,1,-10,10,1)     	// Fixed effects
  init_bounded_vector log_sigma(1,4,-6,5,2)	// Log-variance components

  random_effects_matrix u(1,m1,1,mm,2)        	// Random effects

  objective_function_value g                    // Log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

GLOBALS_SECTION

  #include <df1b2fun.h>

PROCEDURE_SECTION

  int i;

  g = 0.0;

  for(i=1;i<=m(1);i++)
    fit_group_i(b,log_sigma,u(i),i);


SEPARABLE_FUNCTION void fit_group_i(const dvar_vector& b, const dvar_vector& ls, const dvar_vector& U,const  int& i)
    int j;

    // Likelihood contribution from unscaled random effects
    g -= -0.5*norm2(U);

    dvar_vector sigma(1,4);
    sigma = exp(ls);

    // Scaling up the random effects by multiplication with SD
    dvar_vector uu(1,mm);		
    uu(1) = sigma(1)*U(1);
    for(j=2;j<=indI(1);j++)
      uu(j) = sigma(2)*U(j);
    for(j=indI(1)+1;j<=indI(2);j++)
      uu(j) = sigma(3)*U(j);
    for(j=indI(2)+1;j<=indI(3);j++)
      uu(j) = sigma(4)*U(j);

    dvariable eta;			// Linear predictor

    for(j=1;j<=m2m3m4;j++)
    {
      eta = b(1) + uu(1) + uu(I(j,1)) + uu(I(j,2)) + uu(I(j,3));  // That is: u_i + u_ij + u_ijk + u_ijkl
      g -= y(i,j)*eta - N*log(1+exp(eta));
    }


REPORT_SECTION
  //report << "b =" << b << "sigma=" << sigma << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(20000);

