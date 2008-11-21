#include <fvar.hpp>
// Increases the seed for the random number generators in robsim
#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
int main()
{
  ifstream infile("robsim.par"); // File contains the information for
				 // generating the simulated data
  if (!infile)
  {
    cerr << "Error opening file robsim.par\n";
    exit(1);
  }
  int nobs,seed;
  double b,c,p,sigma;
  // nobs      : The number of simulated observations
  // p         : The proportion of contamination with outliers
  // b,c       : Y=b*z*z+b+c
  // sigma     : The standard deviaitons of the random errors
  // seed      : A seed for the random number generator
  infile >> nobs >> p >> b >> c >> sigma >> seed;
  if (!infile)
  {
    cerr << "Error reading in parameters from robsim.par\n";
    exit(1);
  }
  infile.close();
  seed+=2;
  ofstream outfile("robsim.par"); // File contains the information for
				 // generating the simulated data
  if (!outfile)
  {
    cerr << "Error opening file robsim.par for output\n";
    exit(1);
  }
  outfile << nobs << "\n" << p << "\n" << b << "  " << c <<
      "\n"  << sigma << "\n" << seed;
  if (!outfile)
  {
    cerr << "Error writing parameters to robsim.par\n";
    exit(1);
  }
  return 0;
}
