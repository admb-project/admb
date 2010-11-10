\begin{lstlisting}
// file: fcomp_s.cpp

#include <fvar.hpp>

double fcomp(int n, dvar_vector x)
{
  dvariable z;
  dvariable tmp;
  int i;
  z=0;
  for (i=1;i<=n;i++)
  {
    tmp=x[i]-1;
    z=z+tmp*tmp;
  }
  return(value(z));
}
\end{lstlisting}