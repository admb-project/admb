This file shows how to convert diet.tpl into diet_sk.tpl,
i.e. how go from normal random effects (re's).

For normally distributed re's the log-likelihood is

   // Exposure model
   g -= -0.9189385 - 0.5*square(u_j);   // prior on the u_j's
   dvariable eta_j = X1(j)*gamma + mfexp(0.5*log_psi)*u_j;

which is converted to the skewed re model by transforming
the u_j to the skewed zeta_j and using zeta_j as the re in the code.

  // Exposure model
   g -= -0.9189385 - 0.5*square(u_j);  // normal prior on the  u_j's
   dvariable a2 = square(a)+square(1-a);
   dvariable zeta_j = 1.0/sqrt(a2)*(a*u_j +
(1-a)*(mfexp(u_j)-exp(.5))/2.161197);
   dvariable eta_j = X1(j)*gamma + mfexp(0.5*log_psi)*zeta_j;

Ths involves the extra parameter a which must be added into the function
call so that

SEPARABLE_FUNCTION void loglik_j(const dvar_vector& gamma, const
dvariable& log_psi, const dvar_vector& alpha, const dvariable&
log_theta, const dvariable& lambda, const dvar_vector& beta, const
dvariable& u_j, const  int& j)

is changed to

SEPARABLE_FUNCTION void loglik_j(const dvar_vector& gamma, const
dvariable& log_psi, const dvar_vector& alpha, const dvariable&
log_theta, const dvariable& lambda, const dvar_vector& beta, const
dvariable& u_j, const dvariable& a, const  int& j)

Then the parameter a is added to the PARAMETER_SECTION so that

PARAMETER_SECTION

  init_bounded_vector gamma(1,3,-10.,10.,2)     	
  init_bounded_number log_psi(-1.,4.,2)		

  init_bounded_vector alpha(0,1,0.,30.,1)     	
  init_bounded_number log_theta(-1.,4.,1)	

  init_bounded_number lambda(-6.,5.,2)		
  init_bounded_vector beta(0,3,-10.,10.,1)     	

  random_effects_vector u(1,n,2)       // N(0,1) distributed r

  objective_function_value g

becomes


PARAMETER_SECTION

  init_bounded_vector gamma(1,3,-3.0,3.0,2)     	
  init_bounded_number log_psi(0.0,4.0,2)		

  init_bounded_vector alpha(0,1,0.0,30.0,1)     	
  init_bounded_number log_theta(0.0,4.0,1)	

  init_bounded_number lambda(-0.3,0.3,2)		
  init_bounded_vector beta(0,3,-3.0,3.0,1)     	

  init_bounded_number a(0.3,0.999,3)   //add the parameter a     	

  random_effects_vector u(1,n,2)   // N(0,1) distributed random effects

  objective_function_value g      // (negative) Log-likelihood


Finally the parameter a is aded to the function call so that

  for(j=1;j<=n;j++)
    loglik_j(gamma,log_psi,alpha,log_theta,lambda,beta,u(j),j);

becomes

  for(j=1;j<=n;j++)
      loglik_j(gamma,log_psi,alpha,log_theta,lambda,beta,u(j),a,j);

and that's it!


