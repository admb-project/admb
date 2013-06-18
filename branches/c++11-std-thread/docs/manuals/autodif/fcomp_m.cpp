\begin{lstlisting}
// file fcomp_m.cpp

#include <fvar.hpp>
#include "mixture.h"

double fcomp(dvector y,dvar_vector p,dvar_vector& mu,dvar_vector& sd,
    dvector& mumin, dvector& mumax, dvector& sdmin, dvector& sdmax,
    ivector& control,dvar_vector& x,int print_switch)
{
  dvariable zpen;
  zpen=reset(control,x,p,mu,sd,mumin,mumax,sdmin,sdmax); // Put the
                                 // x vector into the model parameters 
                                 // and return the bounding function 
                                 // penalty in zpen
  zpen+=normalize_p(p); // Make the proportions sum to 1
  if (print_switch == 1)
  {
    save_pars(p,mu,sd,mumin,mumax,sdmin,sdmax,control);
  }
  dvariable f;
  f=-log_likelihood(y,p,mu,sd); // Change the sign to minimize
  f=f+zpen; // Add the penalty from the bounding functions
  return(value(f));
}
\end{lstlisting}