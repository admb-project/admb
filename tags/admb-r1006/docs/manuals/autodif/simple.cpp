\begin{lstlisting}
//file: simple.cpp

#include <fvar.hpp>

double fcomp(int, dvar_vector); // Function prototype declaration
#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
void main()
{
  int nvar=20; // This is the number of independent variables
  independent_variables x(1,nvar); // these are the independent variables
  double f; // This is the dependent variable
  dvector g(1,nvar); // Holds the vector of partial derivatives (gradient)
  fmm fmc(nvar); // Create structure to manage minimization
  BEGIN_MINIMIZATION(nvar,f,x,g,fmc) // Macro to set up beginning of
  // minimization loop
  f=fcomp(nvar,x);
  END_MINIMIZATION(nvar,g) // Macro to set up end of minimization loop
  cout << " The minimizing values are\n" << x << "\n"; //Print out answer
}
\end{lstlisting}