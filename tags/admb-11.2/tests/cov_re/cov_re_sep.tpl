// Example intended to check variance/covariance in RE models: separable version
// Motivated by discovery of bug:  [ADMB Users] difference between ADMB-RE and R/mgcv in SEs for smoother coefficients in a GAM fitted by maximum likelihood

DATA_SECTION
   number y
   !! y=10.0;
PARAMETER_SECTION
   init_number x
   random_effects_vector u(1,3)
   objective_function_value f
PROCEDURE_SECTION
   f = 0.0;
   separable_ll(x,u(1));
   for (int i=2;i<=3;i++)
   separable_ll2(u(i));

SEPARABLE_FUNCTION void separable_ll(const prevariable& x, const prevariable& u)
     f -= -0.5*square(x);	  // Prior on x: x = e1
     f -= -0.5*square(u-x);       // u|x: u = x + e2
     f -= -0.5*square(y-u);       // y|u: y = u + e3

SEPARABLE_FUNCTION void separable_ll2(const prevariable& u)
     f -= -0.5*square(u);	

GLOBALS_SECTION
  //#include "getbigs.cpp"

