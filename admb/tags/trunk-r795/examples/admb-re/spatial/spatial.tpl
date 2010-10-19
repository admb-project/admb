// Poisson regression with spatially smoothed mean.

DATA_SECTION
  init_int n			// Number of observations
  init_vector y(1,n)		// Poisson counts
  init_int p			// Number of fixed effects (b's)
  init_matrix X(1,n,1,p)	// Covariate matrix
  init_matrix Z(1,n,1,2)	// Locations (xy-coordinates)

  // Makes columns of X orthogonal to improve stability
  number ncol1
  number ncol2
  matrix dd(1,n,1,n);		// Distance matrix
 LOC_CALCS
  int i, j;
  // make the columns of X orthonormal
  dmatrix tX=trans(X);
  ncol1=norm(tX(1));
  tX(1)/=ncol1; 
  tX(2)-= tX(1)*tX(2)*tX(1);
  cout << tX(1)*tX(2) << endl;
  ncol2=norm(tX(2));
  tX(2)/=ncol2; 
  X=trans(tX);
  cout << norm(column(X,1)) << endl;
  cout << norm(column(X,2)) << endl;
  cout << column(X,1)*column(X,2) << endl;

  dd.initialize();
  for(i=1;i<=n;i++)
  {
    for ( j=1;j<i;j++)
    {
      dd(i,j)=sqrt(square(Z(i,1)-Z(j,1))+square(Z(i,2)-Z(j,2)));
      dd(j,i)=dd(i,j);
    }
  }
 END_CALCS

PARAMETER_SECTION

  init_bounded_vector b(1,p,-100,100) 
  init_bounded_number a(0.01,3.0,2)
  init_bounded_number log_sigma(-3.0,3.0,2)

  random_effects_vector u(1,n,2)
  normal_prior M(u);

  objective_function_value l

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);
  
PROCEDURE_SECTION

  int i;

  //get_M(a);						// Calculate covariate matrix

  for (i=1;i<=n;i++)
    pois_loglik(i,u(i),b,log_sigma);			// Likelilhood contribution from i'th point

SEPARABLE_FUNCTION void pois_loglik(int i,const dvariable& ui,const dvar_vector& _b,const dvariable& _log_sigma)
    dvariable eta = X(i)*_b + exp(_log_sigma)*ui;	// Linear predictor
    dvariable lambda = mfexp(eta);			// Mean in Poisson distribution
    l += lambda-y(i)*eta;

NORMAL_PRIOR_FUNCTION void get_M(const dvariable& _a)
  int i,j;
  dvar_matrix tmpM(1,n,1,n);

  for (i=1;i<=n;i++)
  {
    tmpM(i,i)=1.0;
    for ( j=1;j<i;j++)
    {
      tmpM(i,j)=exp(-_a*dd(i,j));			// Exponentially decaying correlation
      tmpM(j,i)=tmpM(i,j);
    }
  }
  M=tmpM;

FUNCTION void evaluate_M(void)

  get_M(a);

REPORT_SECTION
  cout << "b =" << b << "sigma=" << exp(log_sigma) << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 40000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(460404);




  
