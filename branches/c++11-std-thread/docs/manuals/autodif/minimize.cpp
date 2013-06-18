\begin{lstlisting}
//file: minimize.cpp

#include <fvar.hpp>

double userfun(dvar_vector&);

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
void main()
{
  int nvar=60;
  independent_variables x(1,nvar);
  fmm fmc(nvar); // creates the function minimizing   control structure
  double minimum_value= fmc.minimize(x,userfun); //Call the function minimizer
  cout << "The minimum value = " << minimum_value << "at x =\n"
       << x << "\n";
}
\end{lstlisting}