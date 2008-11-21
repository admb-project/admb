// file: mixture.cpp
#include <fvar.hpp>

// header file containing all function prototypes used in this exmaple
#include "mixture.h"

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
int main()
{
  // The observations are in the file mixture.dat
  dvector y("mixture.dat"); // Read in the observations
  ifstream infile2("mixture.par"); // The parameter estimates are in a
				   // file named mixture.par
  int ngroups;
  infile2 >> ngroups; // Read in the number of groups
  ivector control(1,10); // There are 10 control switches for this model
  infile2 >> control; // Read in the control switches
  dvector p(1,ngroups);
  dvector mu(1,ngroups);
  dvector sd(1,ngroups);
  dvector mumin(1,ngroups);
  dvector mumax(1,ngroups);
  dvector sdmin(1,ngroups);
  dvector sdmax(1,ngroups);
  infile2 >> p;  // Read in the mixture proportions
  infile2 >> mu; // Read in the mean lengths
  infile2 >> sd; // Read in the standard deviations
  infile2 >> mumin; // Read in the lower bounds on the mean lengths
  infile2 >> mumax; // Read in the upper bounds on the mean lengths
  infile2 >> sdmin; // Read in the lower bounds on the standard deviations
  infile2 >> sdmax; // Read in the upper bounds on the standard deviations
  infile2.close(); // close the file
  int nvar=nvarcal(control,ngroups); // Get the number of independent variables
  independent_variables x(1,nvar);
  double f;
  dvector g(1,nvar);
  xinit(control,x,p,mu,sd,mumin,mumax,sdmin,sdmax); // Get the initial x values
  fmm fmc(nvar);
  gradient_structure::set_MAX_NVAR_OFFSET(768);
  BEGIN_MINIMIZATION(nvar,f,x,g,fmc) // Estimate the parameters by minimizing fcomp
    dvar_vector x2 = x;
    dvar_vector mu2 = mu;
    dvar_vector sd2 = sd;
    f=fcomp(y,p,mu2,sd2,mumin,mumax,sdmin,sdmax,control,x2,0);
    fcomp(y,p,mu2,sd2,mumin,mumax,sdmin,sdmax,control,x2,1); // Save the parameter
                                                             // estimates
  END_MINIMIZATION(nvar,g)
  return 0;
}
