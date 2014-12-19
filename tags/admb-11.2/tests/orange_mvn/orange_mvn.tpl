// Orange data used in Ch. 8.2, Pinheiro & Bates (2000)

DATA_SECTION

  init_int n			// Number of data points
  init_vector y(1,n)		// Response vector
  init_vector t(1,n)		// Primary covariate
  init_int M			// Number of groups		
  init_vector ngroup(1,M)	// Group indicator
  init_int m			// Number of parameters in nonlinear regression model		

PARAMETER_SECTION

  init_bounded_vector beta(1,3,-50,200,1)		// Fixed effects parameters
  init_bounded_number log_sigma(-6.0,5.0,1)	// log(residual variance)
  init_bounded_number log_sigma_u(-10,5,2)		// 0.5*log(variance component)

  random_effects_vector u(1,M,2)			// Unscaled random effects

  objective_function_value g

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);
 

PROCEDURE_SECTION

  int i,ii;

  g = 0.0;

  ii = 0;
  for(i=1;i<=(int) M;i++)
  {
    fit_individual_tree(beta(1),beta(2),beta(3),u(i),i,ii,log_sigma,log_sigma_u);
  }

SEPARABLE_FUNCTION void fit_individual_tree(const dvariable& beta1, const dvariable& beta2, const dvariable& beta3, const dvariable& u1,  int i, int& ii, const dvariable& log_sigma,const dvariable& log_sigma_u)
    int j;

    dvar_vector a(1,3);	
	  		// Basic model function parameters

    a(1) = 192.0 + beta1 + u1;			
    a(2) = 726.0 + beta2;
    a(3) = 356.0 + beta3;

    int ni = ngroup(i);
    dvar_vector res(1,ni); //residuals conditional on random effect
    dvar_vector f(1,ni); // mean condtional on random effect
    dvariable sigma = mfexp(log_sigma);

    // Random effects contribution
    g -= -(log_sigma_u);
    g -= -.5*(square(u1/mfexp(log_sigma_u)));

    for(j=1;j<=ngroup(i);j++)
    {
      ii++;

      f(j) = a(1)/(1+mfexp(-(t(ii)-a(2))/a(3)));
      res(j) = y(ii) - f(j);
    }
    
    // Create covariance matrix for i^th individual
    dvar_matrix Vi(1,ni,1,ni);
    for(int k=1; k<=ni; k++)
       {
         Vi(k,k)= sigma*sigma;
       }

    //calculate contribution of observed data to log-likelihood using multivariate normal form   
    dvariable ld;
    dvariable sgn;
    //df1b2vector tmp=solve(Vi,res,ld,sgn);
    dvar_vector tmp=solve(Vi,res,ld,sgn);
    g+=0.5*(ni*log(2*M_PI)+ld+tmp*res);

REPORT_SECTION

  //report << beta0+beta << endl;
  report << exp(log_sigma) << endl;
  report << exp(log_sigma_u) << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 40000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(10000);

GLOBALS_SECTION

  /*
  #include<admodel.h>
  #include<df1b2fun.h>
  #include<adrndeff.h>

  df1b2vector solve(const df1b2matrix& aa,const df1b2vector& z,
    const df1b2variable& ld, double& sign);

  df1b2vector solve(const df1b2matrix& aa,const df1b2vector& z,
    const df1b2variable& ld, df1b2variable& sign)
  {
   double sgn;
   return solve(aa,z,ld,sgn);
  } 
  */
