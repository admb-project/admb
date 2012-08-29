\begin{lstlisting}
//file: normaliz.cpp

#include <fvar.hpp>
#include "mixture.h"

dvariable normalize_p(dvar_vector& p)
{
  dvariable psum=sum(p);
  p=p/psum; // Now the p's will sum to 1
  dvariable zpen=1000.*log(psum)*log(psum);
  return(zpen);
}
\end{lstlisting}