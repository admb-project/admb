// GLMM with negative binomial response
// Example 2 in Booth, Casella, Friedl, Hobert (2003) Statistical Modelling, vol. 3, no. 3, pp. 179-191
// Numerical results meant to match rightmost column in Table 2 of Booth et al.

DATA_SECTION

  init_int n					// Number of observations
  init_vector y(1,n)				// Observation vector
  init_int p					// Number of fixed effects
  init_matrix X(1,n,1,p)				// Covariate matrix for fixed effects
  init_int q					// Number of Clusters
  init_int m					// Number of random effects within clusters
  init_matrix Z(1,n,1,m)				// Covariate matrix for random effects
  init_vector I(1,n)				// Grouping variable

PARAMETER_SECTION

  
  init_bounded_vector b(1,p,-10,10,1)     	// Fixed effects
  !! int mm = (m*(m+1))/2;
  init_vector tmpL(1,mm,3)			// Elements of cholesky-factor L of correlation matrix
  init_bounded_number log_alpha(-6,5,2)	// phase 2 by dave       

  //sdreport_number sigma                       	// sqrt(variance component)
  sdreport_number alpha                       	// sqrt(variance component)
  vector lambda(1,n)  
  random_effects_matrix u(1,q,1,m,3)            // Random effects
  objective_function_value g                    // Log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);


PROCEDURE_SECTION

  int i;
  for (i=1;i<=q;i++)
  {
    fu(u(i));
  }

  for (i=1;i<=n;i++)
  {
    f1(i,tmpL,u((int) I(i)),b,log_alpha);
  }

  if (sd_phase())
  {
    alpha=exp(log_alpha);
  }

  f0(tmpL,m);

SEPARABLE_FUNCTION void f0(const dvar_vector& tmpL,int m)

  // Small penalty so that the Hessian is not singiular when 
  // the variance of some compnent is 0.
  int mm=m*(m+1)/2;
  for (int i=m+1;i<=mm;i++)
  {
    g+=1.e-2*square(tmpL(i));
  }
  
SEPARABLE_FUNCTION void fu(const dvar_vector& ui)
  g+=0.5*norm2(ui);


SEPARABLE_FUNCTION void f1(int _i,const dvar_vector& tmpL,const dvar_vector& ui,const dvar_vector& b,const prevariable& log_alpha)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-30;
    e2=1.e-30;
  }
  else
  {
    e1=1.e-6;
    e2=1.e-4;
  }
  
  dvar_matrix L(1,m,1,m);
  L.initialize();
  int i,j;

  if (tmpL.indexmax() != m*(m+1)/2)
  {
    cerr << "size error in get_choleski" << endl;
  }
  L(1,1)=1.0;
  int ii=m+1;
  for (i=2;i<=m;i++)
  {
    dvar_vector alpha(1,i-1);
    for (j=1;j<=i-1;j++)
    {
      alpha(j)=tmpL(ii++);
    }
    dvariable d=sqrt(1.0+norm2(alpha));
    L(i,i)=1/d;
    L(i)(1,i-1)=alpha/d;
  }
  for (i=1;i<=m;i++)
  {
    L(i)*=exp(tmpL(i));
  }

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  
  dvariable alpha = e2+exp(log_alpha);
  dvariable tau = 1.0+e1+lambda/alpha;
  g-=log(e2+exp(log_negbinomial_density(y(_i),lambda,tau)));

REPORT_SECTION
  
TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(2000000);
  gradient_structure::set_MAX_NVAR_OFFSET(50000);

GLOBALS_SECTION
  #include <windows.h>
  #include <admodel.h>
  #include <float.h>
   int controlword=0;
   BOOL DllMain(HANDLE hinstDLL,
      DWORD reason,
      LPVOID res)
   {
     // for floating point so that R doesn't complain
     controlword=control87(0,0);
     return TRUE;
   }
  #if defined(PRINT_DEBUG)
    #include <admodel.h>
    ofstream ofs("model.out");
  #endif
  

FINAL_SECTION
   control87(controlword,0xfffff);
