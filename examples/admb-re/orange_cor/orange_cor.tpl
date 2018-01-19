// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

// Extended version of: Orange data used in Ch. 8.2, Pinheiro & Bates (2000)
// Correlated random effects

DATA_SECTION

  init_int n			// Number of data points
  init_vector y(1,n)		// Response vector
  init_vector t(1,n)		// Primary covariate
  init_int M			// Number of groups		
  init_vector ngroup(1,M)	// Group indicator
  init_int m			// Number of parameters in nonlinear regression model		

  vector ofset(1,3);


PARAMETER_SECTION

  init_bounded_vector beta(1,3,-50,200,1)		// Fixed effects parameters
  init_bounded_number log_sigma(-6.0,5.0,2)	        // log(residual variance)
  init_bounded_vector log_sigma_u(1,3,-5.,5.,2)	// 0.5*log(variance component)
  init_bounded_vector off_diag(1,3,-5.,5.,-1) 		// Off-diagonal elements in Cholesky factor

  random_effects_matrix u(1,M,1,3,2) 

  objective_function_value g

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

  ofset(1) = 192.0; ofset(2) = 726.0; ofset(3) = 356.0;
 
GLOBALS_SECTION

  #include <df1b2fun.h>
  //#include <fvar.hpp>

PROCEDURE_SECTION

  int i,ii;

  g = 0.0;

  ii = 0;
  for(i=1;i<=(int) M;i++)
  {
    fit_individual_tree(beta,u(i),i,ii,log_sigma,log_sigma_u,off_diag);
  }

SEPARABLE_FUNCTION void fit_individual_tree(const dvar_vector& beta, const dvar_vector& u, const int& i, int& ii, const dvariable& log_sigma, const dvar_vector& log_sigma_u, const dvar_vector& off_diag)

  int j;

  dvar_matrix L(1,3,1,3);

  #ifdef OPT_LIB
  L.initialize();
  #endif

  L(1,1) = 1.0;
  int k = 1;
  for(int i1=2;i1<=3;i1++)
  {
    L(i1,i1) = 1.0;
    for(j=1;j<=i1-1;j++)
      L(i1,j) = off_diag(k++);
    L(i1)(1,i1) /= norm(L(i1)(1,i1));
  }

  //dvector offset("{192.0,726.0,356.0}");		// This does not appear to work. Why?

 
  dvar_vector a(1,3);
  //a = beta + ofset + elem_prod(mfexp(log_sigma_u),L*u);
  a = beta + elem_prod(mfexp(log_sigma_u),L*u);
  a(1) += 192.0;
  a(2) += 726.0;
  a(3) += 356.0;

  // Random effects contribution
  g -= -3*0.91893853 - .5*norm2(u);

  dvariable tmp, f;
  for(j=1;j<=ngroup(i);j++)
  {
    ii++;

    f = a(1)/(1+mfexp(-(t(ii)-a(2))/a(3)));

    tmp = y(ii) - f;
    tmp /= mfexp(log_sigma);
    g -= -0.91893853 - log_sigma - 0.5*square(tmp);
  }

REPORT_SECTION

  report << beta + ofset << endl;
  report << exp(log_sigma) << endl;
  report << exp(log_sigma_u) << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 40000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(10000);



