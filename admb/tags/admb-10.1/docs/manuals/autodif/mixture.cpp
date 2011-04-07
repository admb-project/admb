\begin{lstlisting}
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
void main()
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
  infile2 >> p; // Read in the mixture proportions
  infile2 >> mu; // Read in the mean lengths
  infile2 >> sd; // Read in the standard deviations
  infile2 >> mumin; // Read in the lower bounds on the mean lengths
  infile2 >> mumax; // Read in the upper bounds on the mean lengths
  infile2 >> sdmin; // Read in the lower bounds on the standard deviations
  infile2 >> sdmax; // Read in the upper bounds on the standard deviations
  infile2.close(); // close the file
  int nvar=nvarcal(control,ngroups); // Get number of independent variables
  independent_variables x(1,nvar);
  double f;
  dvector g(1,nvar);
  xinit(control,x,p,mu,sd,mumin,mumax,sdmin,sdmax); // Get initial x values
  fmm fmc(nvar);
  BEGIN_MINIMIZATION(nvar,f,x,g,fmc) // Estimate the parameters 
                                            // by minimizing fcomp
    f=fcomp(y,p,mu,sd,mumin,mumax,sdmin,sdmax,control,x,0);
  END_MINIMIZATION(nvar,g)
  fcomp(y,p,mu,sd,mumin,mumax,sdmin,sdmax,control,x,1); // Save the 
                                                    // parameter estimates
}
\end{lstlisting}