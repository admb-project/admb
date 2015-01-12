// Poisson regression with autocorrelated random effects
DATA_SECTION

  !!USER_CODE ad_comm::change_datafile_name("polio.dat");
  init_int n			// Length of time series
  init_vector y(1,n)		// Time series
  init_int fakep;			// Length of time series
  int p			// Number of regression parameters
 !! p=6;
  init_matrix X(1,n,1,p)	// Covariate matrix

  !!USER_CODE ad_comm::change_pinfile_name("polio.pin");

PARAMETER_SECTION

  init_bounded_vector b(1,p,-100,100,1)		// Regression parameters 
  init_bounded_number a(-1,1,2)			// Correlation coefficient
  init_bounded_number log_sigma(-3.0,3.0,2)	// 0.5*log(variance component)
  
  //init_bounded_vector b(1,p,-100,100)		// Regression parameters 
  //init_bounded_number a(-1,1)			// Correlation coefficient
  //init_bounded_number log_sigma(-3.0,3.0)	// 0.5*log(variance component)

  random_effects_vector u(1,n,2)		// Random effects

  objective_function_value g

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

GLOBALS_SECTION

  //#include <df1b2fun.h>
  
PROCEDURE_SECTION

  int i;	

  sf1(log_sigma,a,u(1));

  for (i=2;i<=n;i++)
  {
    sf2(log_sigma,a,u(i),u(i-1),i);
  //  sf2(log_sigma,a,u,i);
  }
  for (i=1;i<=n;i++)
  {
    sf3(u(i),b,i);
  }

SEPARABLE_FUNCTION void sf1(const dvariable& ls,const dvariable& aa,const dvariable& u_1)
  g += ls - 0.5*log(1-square(aa)) +0.5*square(u_1/mfexp(ls))*(1-square(aa));


SEPARABLE_FUNCTION void sf2(const dvariable& ls, const dvariable& aa,const dvariable& u_i,const dvariable& u_i1,int i)
    if (i<=10000)
      g += ls +.5*square((u_i-aa*u_i1)/mfexp(ls));
    else
      g += ls +.5*square((u_i-0.2*u_i1)/mfexp(ls));



SEPARABLE_FUNCTION void sf3(const dvariable& u_i ,const dvar_vector& bb, int i)
    dvariable eta = X(i)*bb + u_i;
    dvariable lambda = mfexp(eta);
    g -= y(i)*eta - lambda;


REPORT_SECTION
  //cout << "b =" << b << "sigma=" << sigma << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(50850);


