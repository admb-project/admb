\begin{lstlisting}
// file: robust.cpp

#include <fvar.hpp>

// function prototype
double fcomp(dvector& OBS_Y,dvector& OBS_Z,dvar_vector& x);

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
double alpha;
void main()
{
  ifstream infile("robust.dat"); // robust.dat contains the observed data
  if(!infile) // Check for I/O error
  {
    cerr << "Error trying to open the file robust.dat\n";
    exit(1);
  }
  int nobs; // nobs is the number of observations
  infile >> nobs; // read in the number of observations
  if(!infile) // Check for I/O error
  {
    cerr << "Error reading number of observations from the file robust.dat\n";
    exit(1);
  }
  dvector Y(1,nobs);
  dvector Z(1,nobs);
  // The Data are in the file in the form one Y_i Z_i pair per line
  { // Limit the scope of the matrix tmp
    dmatrix tmp(1,nobs,1,2);
    infile >> tmp; // Read the Y_i Z_i pairs into tmp
    if(!infile) // Check for I/O error
    {
      cerr << "Error reading data in from the file robust.dat\n";
      exit(1);
    }
    Z=extract_column(tmp,1); // Put the first column of tmp into Z
    Y=extract_column(tmp,2); // Put the second column of tmp into Y
  } // Now tmp goes out of scope
  infile.close(); // Close the input file
  double b=1.0; // This is the model parameter ... use 1.0 as initial value
  alpha=0.7; // alpha is not used in the first stage of the minimization
  double f;
  gradient_structure gs;
  {
    int nvar=1; // There is 1 parameter, b
    independent_variables x(1,nvar);
    dvector g(1,nvar);
    x[1]=b; // Put the model parameters in the x vector
    fmm fmc(nvar);
    fmc.iprint=1;
    fmc.crit=1.e-6;
    while (fmc.ireturn >=0)
    {
      fmc.fmin(f,x,g);
      if (fmc.ireturn > 0)
      {
        {
          f=fcomp(Y,Z,dvar_vector(x));
        }
        gradcalc(nvar,g);
      }
    }
    cout << " The estimate for b = " << x(1) << "\n";
  }
}
\end{lstlisting}