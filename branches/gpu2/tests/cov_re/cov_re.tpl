// Example intended to check variance/covariance in RE models
// Motivated by discovery of bug:  [ADMB Users] difference between ADMB-RE and R/mgcv in SEs for smoother coefficients in a GAM fitted by maximum likelihood

DATA_SECTION
   init_int is_separable
   number y
   !! y=10.0;
PARAMETER_SECTION
   init_number x
   random_effects_vector u(1,1)
   objective_function_value f
PROCEDURE_SECTION
   f = 0.0;
   f -= -0.5*square(x);	  	// Prior on x: x = e1
   f -= -0.5*square(u(1)-x);    // u|x: u = x + e2
   f -= -0.5*square(y-u(1));    // y|u: y = u + e3
				// where e1, e2, e3 are all distributed N(0,1); standard normal
GLOBALS_SECTION
  //#include "getbigs.cpp"

