\begin{lstlisting}
//file: hem_func.cpp

#include <fvar.hpp>

void hemholtz_energy(int n, dmatrix A, dvector b, dvar_vector x, double& f)
{
  double R=.00005;
  double T=290;
  double root2=pow(2.,.5);
  dvariable btx = b*x;
  dvariable log_one_minus_btx = log(1-btx);
  dvariable z = R * T * ( x * (log(x)-log_one_minus_btx) );
  z -= (x * A * x)/(2*root2*btx) * log((1+(1+root2)*btx)/(1+(1-root2)*btx));
  f=value(z);
}
\end{lstlisting}