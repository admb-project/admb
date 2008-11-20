#include <fvar.hpp>

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
  #include <iomanip.h>
#endif
#ifdef __ZTC__
  long _stack = 20000;
  #include <iomanip.hpp>
#endif
void main()
{
  // the file normsim.par contains the parameters used to simulate
  // a mixture of distributions; exit this file to produce a different
  // mixture
  ifstream infile("normsim.par");
  int ngroups;
  int nsamp;
  // first line of file contains the number of groups
  infile >> ngroups;
  // allocate containers for means, standard deviatons
  // and proportions of each group
  dvector mean(1,ngroups);
  dvector sd(1,ngroups);
  dvector p(1,ngroups);

  // second line of file contains the proportion of the
  // total sample in each group; note these sum to 1
  infile >> p;
  // third line contains the mean of each group
  infile >> mean;
  // fourth line contains the standard deviation of each group
  infile >> sd;
  // fifth line is the sample size
  infile >> nsamp;

  dvector lengths(1,nsamp);

  lengths.fill_randn(213); // 213 is arbirtrary random number seed
                           // lengths has standard normal random variables

  ivector choices(1,nsamp);

  choices.fill_multinomial(101,p); // 101 is arbirtrary random number seed
                                   // choices has multinomial dist

  lengths= elem_prod(sd(choices),lengths)+mean(choices);

  double maxlen=max(lengths);
  double minlen=min(lengths);
  ivector freq(1,maxlen-minlen+1);
  freq.fill_seqadd(0,0);

  ofstream dout("normsim.out");
  dout << setw(15)<< setscientific << column_vector(lengths);
  dout.close();
  cout << "Sample of " << nsamp<< " lengths written to file 'normsim.out'.\n";
  cout << "Copy this file to 'mixture.par' to run the mixture example.\n\n";

  for (int i=lengths.indexmin();i<=lengths.indexmax(); i++)
  {
    freq[lengths(i)-minlen+1]+=1;
  }

  ofstream fout("normsim.frq");
  for (i=freq.indexmin();i<=freq.indexmax(); i++)
  {
    fout << setw(10) << setprecision(4) << setfixed << minlen+i-1
         << setw(10) << freq(i) << "\n";
  }
  fout.close();

  cout << "Frequency distributions written to file 'normsim.frq'.\n";
  cout << "This file may be view graphically with a grapchis\n"
          "utility or spreadsheet.\n";
  exit(0);
}
