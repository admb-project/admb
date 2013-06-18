/**
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California
 * 
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 * 
 * License:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include <fvar.hpp>

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
  #include <iomanip.h>
#endif
#ifdef __ZTC__
  long _stack = 20000;
  #include <iomanip.hpp>
#endif
int main()
{
  using std::cout;
  using std::endl;
  // the file normsim.par contains the parameters used to simulate
  // a mixture of distributions; exit this file to produce a different
  // mixture
  std::ifstream infile("normsim.par");
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
  ivector freq(1,int(maxlen-minlen+1));
  freq.fill_seqadd(0,0);

  std::ofstream dout("normsim.out");
  dout << setw(15)<< std::ios::scientific << column_vector(lengths);
  dout.close();
  cout << "Sample of " << nsamp<< " lengths written to file 'normsim.out'.\n";
  cout << "Copy this file to 'mixture.par' to run the mixture example.\n\n";

  for (int i=lengths.indexmin();i<=lengths.indexmax(); i++)
  {
    freq[lengths(i)-minlen+1]+=1;
  }

  std::ofstream fout("normsim.frq");
  for (i=freq.indexmin();i<=freq.indexmax(); i++)
  {
    fout << setw(10) << std::setprecision(4) << std::ios::fixed << minlen+i-1
         << setw(10) << freq(i) << "\n";
  }
  fout.close();

  cout << "Frequency distributions written to file 'normsim.frq'.\n";
  cout << "This file may be view graphically with a grapchis\n"
          "utility or spreadsheet.\n";
  return 0;
}
