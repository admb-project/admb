\begin{lstlisting}
// file: nvarcal.cpp

#include <fvar.hpp>
#include "mixture.h"

int nvarcal(ivector& control ,int ngroups)
{
  int ii=1;
  if (control(1)>0) // control(1) determines whether the p's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      ii++;
    }
  }
  if (control(2)>0) // control(2) determines whether the mu's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      ii++;
    }mix
  }
  if (control(3)>0) // control(3) determines whether the sd's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      ii++;
    }
  }
  int nvar=ii-1;
  return(nvar);
}
\end{lstlisting}