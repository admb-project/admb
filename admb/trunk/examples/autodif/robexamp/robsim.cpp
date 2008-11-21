#include <fvar.hpp>
#ifdef __BCPLUSPLUS__
  #include <iomanip.h>
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  #include <iomanip.hpp>
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
  int nobs;
  long int seed;
  double b,p,sigma;
  // nobs      : The number of simulated observations
  // p         : The proportion of contamination with outliers
  // b         : Y=b*z+b*b
  // sigma     : The standard deviaitons of the random errors
  // seed      : A seed for the random number generator
  infile >> nobs >> p >> b >> sigma >> seed;
  if (!infile)
  {
    cerr << "Error reading in parameters from robsim.par\n";
    exit(1);
  }
  infile.close();
  dvector z(1,nobs);
  z.fill_seqadd(1,1); // the z_i go from 1 to nobs;

  dvector Y=b*z+b*b; // Generate the data without error

  dvector bin(1,nobs);
  bin.fill_randbi(seed,p); // The compoments of bin will equal 0
			     // with probability 1-p, 1 otherwise
  dvector eta(1,nobs);
  eta.fill_randn(seed);   // eta contains normall distributed random
			  // variables with mean 0 and std dev 1
  for (int i=1;i<=nobs;i++)
  {
    if (bin(i)==0)
    {
      Y(i)+=sigma*eta(i);
    }
    else
    {
      Y(i)+=5.*sigma*eta(i);  // These are the outliers
    }
  }
  {
    dmatrix tmp(1,nobs,1,2);
    tmp.colfill(1,z);
    tmp.colfill(2,Y);
    ofstream outfile("robust.dat");
    outfile << nobs << "\n\n";
    outfile << /* setfixed << */ setw(15)<< setprecision(4) << tmp ;
  }
  return 0;
}
