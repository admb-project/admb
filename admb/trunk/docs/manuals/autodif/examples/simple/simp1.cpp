#include <math.h>
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
  double f;
  int i;
  int nvar=20;
  independent_variables x(1,nvar);  // Identify the independent variables
  dvector g(1,nvar);  // Holds the vector of partial derivatives (the gradient) 
  gradient_structure gs;    // must declare this structure to manage derivative
                            // calculations
  f=fcomp(nvar,x);
  gradcalc(nvar,g);        // The derivatives are calculated
  cout <<" The gradient vector is\n"<<g<<"\n"; // Print out the derivatives
}                                              // on the screen
