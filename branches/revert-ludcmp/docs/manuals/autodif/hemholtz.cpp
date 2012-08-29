\begin{lstlisting}
//file: hemholtz.cpp

#include <fvar.hpp>

void hemholtz_(int n, dmatrix A, dvector b, dvar_vector x, double& f);
#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
void main()
{
  int n=30;
  double f;
  dvector g(1,n); // this is the n dimensional gradient vector
  dvector b(1,n); // define an n dimensional vector b
  dmatrix A(1,n,1,n); // define an n by n matrix A
  independent_variables x(1,n); // identify the independent variables
  // make up some values for the parameters
  // we don't know what reasonable values are, but it doesn't
  // matter for illustration of the method
  for (int i=1; i<=n; i++)
  {
    b[i]=(n/2.-i)/(n*n); // This could be done using the fill routines
    x[i]=(1.+i)/(n*n);
	for (int j=1; j<=n; j++)
	{
	  A[i][j]=i*j;
	}
  }
  {
    gradient_structure gs; // An object of type gradient structure must
	                   // be declared
    hemholtz_(n,A,b,x,f);// calculate the Hemholtz 
    gradcalc(n,g); // The gradient (partial derivatives) is
                   // calculated and put in the dvector g
    cout << "The gradient is:\n";
    cout << g << "\n";
  }
}
\end{lstlisting}