// Phenobarbital kinetics example in Pinheiro & Bates (2000, Ch. 6.4)

DATA_SECTION

  init_int n			// Number of data points
  init_vector y(1,n)		// dose or response
  init_vector t(1,n)		// Time
  init_ivector isdose(1,n)	// 0=conc, 1=dose
  init_vector Wt(1,n)		// Weight
  init_int M			// Number of groups		
  init_vector ni(1,M)		// Number in each group

PARAMETER_SECTION

  init_bounded_vector beta(1,4,-7,10,1)		// Fixed effects parameters  (lCl, lCl.Wt, lV, lV.Wt)
  init_bounded_number log_sigma(-6.0,5.0,1)	// log(residual variance)
  init_bounded_number log_sigma_lV(-10,5,2)	// 0.5*log(variance component lV)
  init_bounded_number log_sigma_lCl(-10,5,2)	// 0.5*log(variance component lCl)

  random_effects_vector u_lCl(1,M,2)		// Unscaled random effects
  random_effects_vector u_lV(1,M,2)		// Unscaled random effects

  objective_function_value g
	
PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);
 
PROCEDURE_SECTION

  int i,ii;

  g = 0.0;

  ii = 0;
  for(i=1;i<=(int) M;i++)
  {
    fit_individual(beta(1),beta(2),beta(3),beta(4),u_lCl(i),u_lV(i),i,ii,log_sigma,log_sigma_lCl,log_sigma_lV);
  }

SEPARABLE_FUNCTION void fit_individual(const dvariable& beta1, const dvariable& beta2, const dvariable& beta3, const dvariable& beta4, const dvariable& u_lCl, const dvariable& u_lV, int i, int& ii, const dvariable& log_sigma,const dvariable& log_sigma_lCl, const dvariable& log_sigma_lV)
    int j;

    ii++;

    dvariable k, V, Cl, c;	
    Cl = mfexp(beta1+beta2*Wt(ii)+u_lCl);
    V = mfexp(beta3+beta4*Wt(ii)+u_lV);

    k = Cl/V;

    // Random effects contribution
    g -= -log_sigma_lCl - .5*(square(u_lCl/mfexp(log_sigma_lCl)));
    g -= -log_sigma_lV - .5*(square(u_lV/mfexp(log_sigma_lV)));

    // Add first dose
    c = y(ii)/V;					

    for(j=2;j<=ni(i);j++)
    {
      ii++;

      c *= mfexp(-k*(t(ii)-t(ii-1)));	// Time update

      if(isdose(ii)==1)
        c += y(ii)/V;		// Add new dose
      else
        g -= -log_sigma - 0.5*square((y(ii)-c)/mfexp(log_sigma)); 	// Likelihood contribution

    }

REPORT_SECTION

TOP_OF_MAIN_SECTION
  arrmblsize = 40000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(10000);



