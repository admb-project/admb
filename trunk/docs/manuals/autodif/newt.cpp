\begin{lstlisting}
// file: newt.cpp

#include <fvar.hpp>

// function prototypes for user functions
dvector function(dvar_vector& x,int nvar);
#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
void main()
{
  int nvar=2;
  independent_variables x(1,nvar);
  dvector f(1,nvar);
  dmatrix jacobian(1,nvar,1,nvar);
  gradient_structure gs;
  x[1]=1;
  x[2]=2;
  do // Iterate until the norm of the dvector f is < 1.e-12
  {
    f=function(x,nvar);
    jacobcalc(nvar,jacobian); // calculate the derivatives for the
    // dependent variables
    cout << " The x vector = " << x << endl
         << " The function values = " << f << endl << endl;
    x-=inv(jacobian)*f; // This is the Newton-Raphson step
  }
  while (norm(f)>1.e-12);
  // print out some final statistics
  cout << " Final x vector values = " << x << endl
       << " Final function values = " << f << endl
       << " Final jacobian matrix value = " << jacobian(1) << endl
       << " " << jacobian(2) << endl;
  cout << " The angle between the rows of the jacobian = "
       << acos(jacobian(1)*jacobian(2)
          /(norm(jacobian(1))*norm(jacobian(2))))
          *180/PI << " degrees" << endl;
  cout << " Final inverse jacobian matrix value = "
       << inv(jacobian)(1) << endl
       << " "
       << inv(jacobian)(2) << endl;
}

dvector function(dvar_vector& x,int nvar)
{
  double offset=.0001; // try changing offset a bit to see how
                       // unstable the roots are
  dvar_vector f(1,nvar);
  dvariable z,tmp;
  f[1] << 100*x[1]*x[1]+x[2]*x[2]-1.; // << sets the value of the first
                                      // dependent variable
         // now use the first dependent variable in calculation for the
         // second dependent variable
  f[2] << f[1]+offset-.01*pow(x(2)*x(2),2)+.0001*pow(x(1)*x(1),2);
  return value(f);
}
\end{lstlisting}
