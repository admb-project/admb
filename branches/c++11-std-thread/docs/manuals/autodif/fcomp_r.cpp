\begin{lstlisting}
// file: fcomp_r.cpp

#include <fvar.hpp>

double fcomp(dvector& Y,dvector& Z,dvar_vector& x)
{
  dvariable b;
  b=x[1]; //Put the x vector into the model parameter
  dvar_vector PRED_Y=b*Z+b*b; //calculate the predicted response
  double alpha=0.7;
  dvariable tmp =robust_regression(Y,PRED_Y,alpha);
  return(value(tmp));
}
\end{lstlisting}