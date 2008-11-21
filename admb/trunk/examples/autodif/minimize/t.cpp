//file: minimize.cpp
#include <fvar.hpp>

double userfun(dvar_vector&);

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
int main()
{
  int nvar=60;
  independent_variables x(1,nvar);
  fmm fmc(nvar); // creates the function minimizing control structure
  double minimum_value= fmc.minimize(x,userfun); //Call the function minimizer
  cout << "The minimum value = " << minimum_value << "at x =\n"
    << x << "\n";
  return 0;
}
double userfun(dvar_vector& x)
{
  dvariable z,tmp;
  int min,max;
  min=x.indexmin();
  max=x.indexmax();
  tmp=x[min]-1;
  z+=tmp*tmp;
  for (int i=min;i<max;i++)
  {
    tmp=x[i+1]-x[i];
    z+=tmp*tmp;
  }
  return(value(z));
}
