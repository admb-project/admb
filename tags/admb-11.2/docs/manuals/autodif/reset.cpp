\begin{lstlisting}
//file: reset.cpp

#include <fvar.hpp>
#include "mixture.h"

dvariable reset(ivector& control,dvar_vector& x,dvar_vector& p, dvar_vector& mu,
    dvar_vector& sd,dvector& mumin, dvector& mumax, dvector& sdmin,
    dvector& sdmax)
{
  dvariable zpen=0.;
  int ngroups=p.size();
  int ii=1;
  if (control(1)>0) // control(1) determines whether the p's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      p(j)=boundp(x(ii++),0.,1.,zpen);
    }
  }
  if (control(2)>0) // control(2) determines whether the mu's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      mu(j)=boundp(x(ii++),mumin(j),mumax(j),zpen);
    }
  }
  if (control(3)>0) // control(3) determines whether the sd's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      sd(j)=boundp(x(ii++),sdmin(j),sdmax(j),zpen);
    }
  }
  return(zpen); // Return zpen so it can be added to the function being
                // minimized
}
\end{lstlisting}