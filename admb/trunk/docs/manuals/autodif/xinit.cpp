\begin{lstlisting}
// file: xinit.cpp

#include <fvar.hpp>
#include "mixture.h"

void xinit(ivector& control,independent_variables& x,dvector& p,dvector& mu,
      dvector& sd,dvector& mumin,dvector& mumax,dvector& sdmin,dvector& sdmax)
{
  int ngroups=p.size();
  int ii=1;
  if (control(1)>0) // control(1) determines whether the p's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      x(ii++)=boundpin(p(j),0.,1.);
    }
  }
  if (control(2)>0) // control(2) determines whether the mu's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      x(ii++)=boundpin(mu(j),mumin(j),mumax(j));
    }
  }
  if (control(3)>0) // control(3) determines whether the sd's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      x(ii++)=boundpin(sd(j),sdmin(j),sdmax(j));
    }
  }
}
\end{lstlisting}