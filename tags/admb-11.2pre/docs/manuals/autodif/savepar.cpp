\begin{lstlisting}
//file: savepar.cpp

#include <fvar.hpp>
#include "mixture.h"

void save_pars(dvar_vector& p,dvar_vector& mu,dvar_vector& sd,
    dvector& mumin, dvector& mumax,dvector& sdmin, dvector& sdmax,
    ivector& control)
{
  ofstream outfile("mixture.par");
  outfile << p.size() << "\n"; // The number of groups
  outfile << control << "\n";
  outfile << p << "\n\n";
  outfile << mu << "\n\n";
  outfile << sd << "\n\n";
  outfile << mumin << "\n\n";
  outfile << mumax << "\n\n";
  outfile << sdmin << "\n\n";
  outfile << sdmax;
}
\end{lstlisting}